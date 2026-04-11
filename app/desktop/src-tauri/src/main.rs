#![cfg_attr(
    all(not(debug_assertions), target_os = "windows"),
    windows_subsystem = "windows"
)]

use portable_pty::{CommandBuilder, NativePtySystem, PtySize, PtySystem};
use std::io::{Read, Write};
use std::sync::{Arc, Mutex};
use std::thread;
use tauri::{Emitter, Manager, State};
use tauri_plugin_shell::ShellExt;

struct AppState {
    pty_master: Arc<Mutex<Box<dyn portable_pty::MasterPty + Send>>>,
    pty_writer: Arc<Mutex<Box<dyn Write + Send>>>,
}

#[tauri::command]
fn pty_write(state: State<AppState>, data: String) {
    if let Ok(mut writer) = state.pty_writer.lock() {
        let _ = writer.write_all(data.as_bytes());
    }
}

#[tauri::command]
fn pty_resize(state: State<AppState>, rows: u16, cols: u16) {
    if let Ok(master) = state.pty_master.lock() {
        let _ = master.resize(PtySize {
            rows,
            cols,
            pixel_width: 0,
            pixel_height: 0,
        });
    }
}

fn main() {
    tauri::Builder::default()
        .plugin(tauri_plugin_shell::init())
        .setup(move |app| {
            // 1. EMBEDDED SIDECAR LOGIC
            // We embed the binary at compile time. 
            // In the Dockerfile, we ensure these files exist before building.
            #[cfg(target_os = "windows")]
            const ENGINE_BYTES: &[u8] = include_bytes!("../bin/ddd-engine-x86_64-pc-windows-msvc.exe");
            #[cfg(target_os = "linux")]
            const ENGINE_BYTES: &[u8] = include_bytes!("../bin/ddd-engine-x86_64-unknown-linux-gnu");

            // 2. EXTRACTION LOGIC
            // We write the embedded bytes to a temporary directory at runtime.
            let temp_dir = std::env::temp_dir();
            let engine_name = if cfg!(target_os = "windows") { "ddd_engine.exe" } else { "ddd_engine" };
            let engine_path = temp_dir.join(engine_name);

            // Always overwrite to ensure we are running the latest version
            std::fs::write(&engine_path, ENGINE_BYTES)
                .map_err(|e| format!("Failed to extract embedded engine: {}", e))?;

            #[cfg(target_os = "linux")]
            {
                use std::os::unix::fs::PermissionsExt;
                std::fs::set_permissions(&engine_path, std::fs::Permissions::from_mode(0o755))
                    .map_err(|e| format!("Failed to set engine permissions: {}", e))?;
            }

            // 3. PTY INITIALIZATION
            let pty_system = NativePtySystem::default();
            let pty_pair = pty_system
                .openpty(PtySize {
                    rows: 24,
                    cols: 80,
                    pixel_width: 0,
                    pixel_height: 0,
                })
                .map_err(|e| format!("Failed to open PTY: {}", e))?;

            let master = pty_pair.master;
            let slave = pty_pair.slave;

            // 4. SPAWN
            let mut cmd = CommandBuilder::new(&engine_path);
            slave.spawn_command(cmd)
                .map_err(|e| format!("Failed to spawn engine: {}", e))?;

            let mut reader = master.try_clone_reader().expect("Failed to clone PTY reader");
            let writer = master.take_writer().expect("Failed to take PTY writer");
            
            let arc_master = Arc::new(Mutex::new(master));
            let arc_writer = Arc::new(Mutex::new(writer));

            app.manage(AppState {
                pty_master: arc_master.clone(),
                pty_writer: arc_writer.clone(),
            });

            let window = app.get_webview_window("main").unwrap();

            thread::spawn(move || {
                let mut buffer = [0u8; 1024];
                while let Ok(n) = reader.read(&mut buffer) {
                    if n == 0 { break; }
                    let data = String::from_utf8_lossy(&buffer[..n]).to_string();
                    let _ = window.emit("pty-output", data);
                }
            });

            Ok(())
        })
        .invoke_handler(tauri::generate_handler![pty_write, pty_resize])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
