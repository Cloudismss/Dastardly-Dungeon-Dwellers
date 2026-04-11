# Desktop Application

## Overview

The desktop version of "Dastardly Dungeon Dwellers" is a native wrapper built with [Tauri v2](https://tauri.app/). It provides a standalone windowed experience with high-performance terminal rendering and integrated CRT visual effects.

---

## Architecture

The desktop app follows a **"Fat Binary"** architecture to ensure a true single-file distribution experience.

### 1. Embedded Sidecar
The C++ game engine (`ddd-engine`) is baked directly into the Rust desktop wrapper at compile-time using the `include_bytes!` macro. This eliminates the need for separate DLLs or sidecar folders.

### 2. Runtime Extraction
When launched, the Rust backend:
1.  Extracts the embedded engine bytes to the system's temporary directory.
2.  Sets executable permissions (on Linux).
3.  Spawns the engine inside a **PTY (Pseudo-Terminal)** session.

### 3. PTY Bridge
The backend uses the `portable-pty` crate to bridge the gap between the C++ engine and the xterm.js frontend.
*   **Input:** Tauri commands (`pty_write`, `pty_resize`) send data to the PTY master.
*   **Output:** A background thread reads from the PTY and emits Tauri events (`pty-output`) to the frontend.

---

## Build System

The desktop app is built using a unified multi-stage Dockerfile located at `.devcontainer/Dockerfile.desktop`.

### Linux Build
*   **Target:** `x86_64-unknown-linux-gnu`
*   **Format:** Portable **AppImage** (bundles GTK3 and WebKit dependencies).
*   **Command:** `./.github/workflows/scripts/run.sh --linux`

### Windows Build
*   **Target:** `x86_64-pc-windows-msvc`
*   **Method:** Cross-compiled from Linux using **`cargo-xwin`** and **MinGW**.
*   **Command:** `./.github/workflows/scripts/run.sh --windows`

---

## Configuration (`app/desktop/src-tauri/`)

*   **`tauri.conf.json`**: Main configuration for window size, bundle identifiers, and sidecar definitions.
*   **`capabilities/default.json`**: Permissions for the frontend to call Rust commands.
*   **`icons/`**: The application icon set (512x512 PNG, ICO, etc.).
