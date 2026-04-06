#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../../.." && pwd)"
CONTAINER="ddd-crt-$$"
PORT=7681

cleanup() {
  docker stop "$CONTAINER"  2>/dev/null || true
  docker rm   "$CONTAINER"  2>/dev/null || true
  docker image rm ddd-local:latest 2>/dev/null || true
}
trap cleanup EXIT

# ── Validate prerequisites ───────────────────────────────────────────────────

if ! command -v docker &>/dev/null; then
  echo "error: docker not found" >&2
  exit 1
fi

if ! docker info &>/dev/null; then
  echo "error: docker daemon is not running" >&2
  exit 1
fi

if ! docker buildx version &>/dev/null; then
  echo "error: docker buildx plugin not found — install it from https://docs.docker.com/go/buildx/" >&2
  exit 1
fi

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
