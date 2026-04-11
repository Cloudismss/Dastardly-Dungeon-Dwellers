# Web Application

## Overview

The web version of "Dastardly Dungeon Dwellers" is served as a browser terminal via [ttyd](https://github.com/tsl0922/ttyd). A set of CRT visual effects inspired by [cool-retro-term](https://github.com/Swordfish90/cool-retro-term) are injected directly into the HTML served by ttyd, requiring no native code changes to the web server itself.

---

## How Injection Works

The web build process patches the upstream `ttyd` interface at build-time:

1.  **Shared Library Build:** The TypeScript source in `app/web/` is compiled by esbuild into a minified IIFE bundle (`dist/crt.js`).
2.  **HTML Capture:** The `ttyd` binary is launched briefly during the Docker build to capture the default `index.html` it serves.
3.  **Patching:** A Python script injects the static `crt.html` fragment (CSS/SVG) and the compiled `crt.js` bundle immediately before the `</body>` tag of the captured HTML.
4.  **Final Image:** The patched `index.html` is saved into the final production image and served by `ttyd`.

---

## Web-Specific Logic (`app/web/src/main.tsx`)

The web version uses a specialized entry point to maintain compatibility with `ttyd`'s internal xterm.js instance:

*   **`main-legacy.tsx`**: Provides a synchronous initialization sequence that runs as soon as the script is loaded.
*   **Theme Polling**: Since `ttyd` initializes xterm.js asynchronously, the web wrapper polls `window.term` until it becomes available, then applies the initial phosphor theme.
*   **Global Options**: Sets `window.tty_options` before xterm initializes to control the default VT323 font and initial colors.

---

## Build and Deployment

### Local Testing
To build and run the web version locally:
```bash
./.github/workflows/scripts/run.sh --web
```
The app will be available at `http://localhost:7681`.

### Production Image
The official production image is built via `.devcontainer/Dockerfile.prod` and pushed to the container registry. It uses a lightweight Alpine-based `ttyd` runtime.

---

## Configuration

*   **`app/web/package.json`**: Defines the build script for the shared CRT library.
*   **`app/web/crt.html`**: The static HTML fragment containing SVG filters and CSS variables.
