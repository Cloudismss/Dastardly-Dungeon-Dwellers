import { invoke } from '@tauri-apps/api/core';
import { listen } from '@tauri-apps/api/event';
import { initApp, Bridge } from '../../web/src/lib';

const tauriBridge: Bridge = {
  onOutput: (callback) => {
    listen('pty-output', (event) => callback(event.payload as string));
  },
  write: (data) => {
    invoke('pty_write', { data });
  },
  resize: (rows, cols) => {
    invoke('pty_resize', { rows, cols });
  }
};

initApp(tauriBridge);
