#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../../.." && pwd)"
CONTAINER="ddd-crt-$$"
PORT=7681
TMP_HTML=""
if [[ "$(uname)" == "Darwin" ]]; then
  BUILD_DIR="${REPO_ROOT}/build-linux"
  PRESET="linux-release"
  USE_DOCKER_BUILD=true
else
  BUILD_DIR="${REPO_ROOT}/build"
  PRESET="linux-release"
  USE_DOCKER_BUILD=false
fi
BINARY="${BUILD_DIR}/Dastardly Dungeon Dwellers"

cleanup() {
  docker stop "$CONTAINER" 2>/dev/null || true
  docker rm   "$CONTAINER" 2>/dev/null || true
  [[ -n "$TMP_HTML" ]] && rm -f "$TMP_HTML"
}
trap cleanup EXIT

TMP_HTML="$(mktemp /tmp/ddd-crt-XXXXXX.html)"

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

echo "Building game (${PRESET})..."

if [[ "$USE_DOCKER_BUILD" == "true" ]]; then
  # On macOS the host binary is Mach-O and can't run in the Linux container,
  # so build a Linux ELF binary inside a Docker builder image instead.
  if ! docker image inspect ddd-builder:latest &>/dev/null; then
    echo "Building Linux builder image..."
    docker build -f "${REPO_ROOT}/.devcontainer/Dockerfile.builder" -t ddd-builder:latest "${REPO_ROOT}"
  fi
  mkdir -p "$BUILD_DIR"
  docker run --rm \
    -v "${REPO_ROOT}:/src" \
    -v "${BUILD_DIR}:/src/build" \
    -w /src \
    ddd-builder:latest \
    sh -c "if [ ! -f build/CMakeCache.txt ] || [ ! -f build/build.ninja ]; then cmake -S . --preset ${PRESET} -B build -DCMAKE_CXX_SCAN_FOR_MODULES=OFF -DFMT_MODULE=OFF; fi && cmake --build build"
else
  # Configure only when the build directory is missing or the preset has changed.
  if [[ ! -f "${BUILD_DIR}/CMakeCache.txt" ]] || [[ ! -f "${BUILD_DIR}/build.ninja" ]]; then
    cmake -S "$REPO_ROOT" --preset "$PRESET" -B "$BUILD_DIR"
  fi
  cmake --build "$BUILD_DIR"
fi

if [[ ! -f "$BINARY" ]]; then
  echo "error: expected binary not found: ${BINARY}" >&2
  exit 1
fi

# ── Patch index.html ─────────────────────────────────────────────────────────

echo "Patching index.html with CRT effects..."

python3 - <<EOF
content = open('${REPO_ROOT}/res/index.html').read()
inject  = open('${REPO_ROOT}/res/crt-inject.html').read()

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