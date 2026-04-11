import { h, render } from 'preact';
import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';
import { WebglAddon } from 'xterm-addon-webgl';

// Use relative paths for internal CRT logic
import './webgl-patch';
import { CONFIG } from './config';
import { profiles } from './profiles';
import { computePhosphorColors } from './colors';
import { contrastLevelSig, profileIdxSig } from './state';
import { applyProfile } from './apply';
import { initDOM } from './dom';
import { effectDefs } from './effects/defs';
import { startNoise } from './effects/noise';
import { startJitter } from './effects/jitter';
import { tickBloom } from './effects/bloom';
import { Menu } from './components/Menu';

export interface Bridge {
  onOutput: (callback: (data: string) => void) => void;
  write: (data: string) => void;
  resize: (rows: number, cols: number) => void;
}

export async function initApp(bridge: Bridge) {
  const terminalContainer = document.getElementById('terminal-container')!;
  
  const term = new Terminal({
    fontFamily: "'VT323', monospace",
    fontSize: 18,
    cursorBlink: true,
    theme: { background: '#000000' }
  });

  const fitAddon = new FitAddon();
  term.loadAddon(fitAddon);
  (window as any).term = term;

  term.open(terminalContainer);
  
  try {
    term.loadAddon(new WebglAddon());
  } catch (e) {
    console.warn('WebGL addon could not be loaded', e);
  }

  fitAddon.fit();

  // Initial CRT setup
  const p   = profiles[profileIdxSig.value];
  const c   = computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevelSig.value);
  const s   = document.documentElement.style;
  const fpx = (CONFIG.framesize / 100 * 120).toFixed(0) + 'px';
  s.setProperty('--crt-bg',       c.bg);
  s.setProperty('--crt-glow',     p.glow);
  s.setProperty('--crt-glow-rgb', p.menuRgb);
  s.setProperty('--crt-filter',   p.filter);
  s.setProperty('--crt-frame-px', fpx);
  s.setProperty('--crt-margin-px', fpx);
  s.setProperty('--crt-radius-px', (CONFIG.radius / 100 * 80).toFixed(0) + 'px');
  document.body.style.background = c.bg;

  effectDefs.forEach(def => def.apply(def.default));

  applyProfile(profiles[CONFIG.profileIdx], () => {
    terminalContainer.classList.add('crt-boot');
    window.dispatchEvent(new Event('resize'));
  });

  initDOM();

  const menuRoot = document.createElement('div');
  document.body.appendChild(menuRoot);
  render(<Menu />, menuRoot);

  startNoise();
  startJitter();
  requestAnimationFrame(tickBloom);

  // Bridge Integration
  bridge.onOutput((data) => term.write(data));
  term.onData((data) => bridge.write(data));

  const onResize = () => {
    fitAddon.fit();
    bridge.resize(term.rows, term.cols);
  };

  window.addEventListener('resize', onResize);
  setTimeout(onResize, 100);
}
