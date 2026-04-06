#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../../.." && pwd)"
CONTAINER="ddd-crt-$$"
PORT=7681
INDEX_HTML_BACKUP=""

cleanup() {
  docker stop "$CONTAINER"  2>/dev/null || true
  docker rm   "$CONTAINER"  2>/dev/null || true
  docker stop ttyd-patch    2>/dev/null || true
  docker image rm ddd-local:latest 2>/dev/null || true
  rm -f /tmp/ttyd_index.html
  if [[ -n "$INDEX_HTML_BACKUP" && -f "$INDEX_HTML_BACKUP" ]]; then
    cp "$INDEX_HTML_BACKUP" "${REPO_ROOT}/res/index.html"
    rm -f "$INDEX_HTML_BACKUP"
  fi
}
trap cleanup EXIT

# ── Validate prerequisites ───────────────────────────────────────────────────

for cmd in docker python3 curl; do
  if ! command -v "$cmd" &>/dev/null; then
    echo "error: $cmd not found" >&2
    exit 1
  fi
done

if ! docker info &>/dev/null; then
  echo "error: docker daemon is not running" >&2
  exit 1
fi

if ! docker buildx version &>/dev/null; then
  echo "error: docker buildx plugin not found — install it from https://docs.docker.com/go/buildx/" >&2
  exit 1
fi

# ── Pull latest ttyd image ───────────────────────────────────────────────────

echo "Pulling tsl0922/ttyd:latest..."
docker pull tsl0922/ttyd:latest

# ── Extract ttyd HTML ────────────────────────────────────────────────────────

echo "Extracting ttyd index.html..."
docker run --rm -d --name ttyd-patch -p 17681:17681 tsl0922/ttyd:latest ttyd --port 17681 /bin/sh
sleep 2
for i in $(seq 1 10); do
  curl -sf http://localhost:17681/ -o /tmp/ttyd_index.html && [ -s /tmp/ttyd_index.html ] && break
  rm -f /tmp/ttyd_index.html
  sleep 1
done
docker stop ttyd-patch
[ -s /tmp/ttyd_index.html ] || { echo "ERROR: failed to extract ttyd index.html" >&2; exit 1; }

# ── Patch favicon ────────────────────────────────────────────────────────────

echo "Patching favicon..."
INDEX_HTML_BACKUP="$(mktemp /tmp/ddd-index-backup-XXXXXX.html)"
cp "${REPO_ROOT}/res/index.html" "$INDEX_HTML_BACKUP"

ICO_B64=$(base64 -w 0 "${REPO_ROOT}/res/DDD.ico")
sed "s|<link rel=\"icon\" type=\"image/png\" href=\"data:image/png;base64,[^\"]*\"|<link rel=\"icon\" type=\"image/x-icon\" href=\"data:image/x-icon;base64,${ICO_B64}\"|" /tmp/ttyd_index.html > "${REPO_ROOT}/res/index.html"

# ── Inject CRT effects ───────────────────────────────────────────────────────

echo "Injecting CRT effects..."
python3 -c "
content = open('${REPO_ROOT}/res/index.html').read()
inject  = open('${REPO_ROOT}/res/crt-inject.html').read()
open('${REPO_ROOT}/res/index.html', 'w').write(content.replace('</body>', inject + '</body>', 1))
"

# ── Build game image ─────────────────────────────────────────────────────────

echo "Building game image..."
docker buildx build -f "${REPO_ROOT}/.devcontainer/Dockerfile.prod" -t ddd-local:latest --load "${REPO_ROOT}"

# ── Run ──────────────────────────────────────────────────────────────────────

echo ""
echo "Starting ttyd on http://localhost:${PORT}"
echo "Press Ctrl+C to stop."
echo ""

docker run \
  --name "$CONTAINER" \
  -p "${PORT}:${PORT}" \
  ddd-local:latest \
  ttyd --writable --index=/index.html --port "${PORT}" --max-clients=10  -t titleFixed='Dastardly Dungeon Dwellers' -t disableLeaveAlert=true  -t disableResizeOverlay=true -t cursorBlink=true -t fontSize=14 sh -c 'while true; do printf "\t\ttip - \"ctrl +/-\" to zoom in/out\n\n"; /usr/local/bin/ddd; clear; done'
