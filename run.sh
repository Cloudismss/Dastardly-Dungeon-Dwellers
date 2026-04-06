#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BINARY="${SCRIPT_DIR}/build/Dastardly Dungeon Dwellers"
TMP_HTML="$(mktemp /tmp/ddd-crt-XXXXXX.html)"
CONTAINER="ddd-crt-$$"
PORT=7681

cleanup() {
  docker stop "$CONTAINER" 2>/dev/null || true
  docker rm   "$CONTAINER" 2>/dev/null || true
  rm -f "$TMP_HTML"
}
trap cleanup EXIT

# ── Validate prerequisites ───────────────────────────────────────────────────

for cmd in cmake docker python3; do
  if ! command -v "$cmd" &>/dev/null; then
    echo "error: $cmd not found" >&2
    exit 1
  fi
done

if ! docker info &>/dev/null; then
  echo "error: docker daemon is not running" >&2
  exit 1
fi

# ── Build game ───────────────────────────────────────────────────────────────

echo "Building game (linux-release)..."

# Configure only when the build directory is missing or the preset has changed.
if [[ ! -f "${SCRIPT_DIR}/build/CMakeCache.txt" ]]; then
  cmake -S "$SCRIPT_DIR" --preset linux-release
fi

cmake --build "${SCRIPT_DIR}/build"

if [[ ! -f "$BINARY" ]]; then
  echo "error: expected binary not found: ${BINARY}" >&2
  exit 1
fi

# ── Patch index.html ─────────────────────────────────────────────────────────

echo "Patching index.html with CRT effects..."

python3 - <<EOF
content = open('${SCRIPT_DIR}/res/index.html').read()
inject  = open('${SCRIPT_DIR}/res/crt-inject.html').read()

if '</body>' not in content:
    raise SystemExit("error: </body> not found in index.html")

if 'crt-styles' in content:
    raise SystemExit("error: CRT effects already injected — remove them before re-running")

open('${TMP_HTML}', 'w').write(content.replace('</body>', inject + '</body>', 1))
print(f"  Wrote patched HTML to ${TMP_HTML}")
EOF

# ── Pull image if needed ─────────────────────────────────────────────────────

if ! docker image inspect tsl0922/ttyd:latest &>/dev/null; then
  echo "Pulling tsl0922/ttyd:latest..."
  docker pull tsl0922/ttyd:latest
fi

# ── Run ──────────────────────────────────────────────────────────────────────

echo ""
echo "Starting ttyd on http://localhost:${PORT}"
echo "Press Ctrl+C to stop."
echo ""

docker run \
  --name "$CONTAINER" \
  -p "${PORT}:${PORT}" \
  -v "${TMP_HTML}:/index.html:ro" \
  -v "${BINARY}:/usr/local/bin/ddd:ro" \
  tsl0922/ttyd:latest \
  ttyd --writable --index=/index.html --port "${PORT}" --max-clients=10  -t titleFixed='Dastardly Dungeon Dwellers' -t disableLeaveAlert=true  -t disableResizeOverlay=true -t cursorBlink=true -t fontSize=14 sh -c 'while true; do printf "\t\ttip - \"ctrl +/-\" to zoom in/out\n\n"; /usr/local/bin/ddd; clear; done'