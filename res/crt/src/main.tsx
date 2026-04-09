/* webgl-patch must be the first import so it runs before any other module
   code — esbuild evaluates modules in dependency order, and this module has
   no imports of its own, so it is guaranteed to land first in the bundle. */
import './webgl-patch';

import { h, render } from 'preact';
import { CONFIG } from './config';
import { profiles } from './profiles';
import { computePhosphorColors, makePhosphorTheme } from './colors';
import { contrastLevelSig, profileIdxSig } from './state';
import { applyProfile } from './apply';
import { initDOM } from './dom';
import { effectDefs } from './effects/defs';
import { startNoise } from './effects/noise';
import { startJitter } from './effects/jitter';
import { tickBloom } from './effects/bloom';
import { Menu } from './components/Menu';

/* ── Pre-render: set tty_options before xterm.js initialises ─────────────── */
(function () {
  const p = profiles[profileIdxSig.value];
  const c = computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevelSig.value);
  window.tty_options = Object.assign(window.tty_options ?? {}, {
    fontFamily: "'VT323', 'Courier New', monospace",
    fontSize:   18,
    theme:      makePhosphorTheme(c.fg, c.bg),
  });
})();

/* ── Apply initial CSS layout vars synchronously (before first paint) ──────── */
(function () {
  const p   = profiles[CONFIG.profileIdx];
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
})();

/* ── Apply initial effect values synchronously ───────────────────────────── */
effectDefs.forEach(def => def.apply(def.default));

/* ── Boot animation: reveal terminal after xterm applies the phosphor theme ─ */
applyProfile(profiles[CONFIG.profileIdx], () => {
  const tc = document.getElementById('terminal-container') ?? document.body;
  tc.classList.add('crt-boot');
  window.dispatchEvent(new Event('resize'));
});

/* ── DOM overlays, observers, bezel ─────────────────────────────────────────── */
initDOM();

/* ── Render settings menu ────────────────────────────────────────────────── */
const menuRoot = document.createElement('div');
document.body.appendChild(menuRoot);
render(<Menu />, menuRoot);

/* ── Start animation loops ───────────────────────────────────────────────── */
startNoise();
startJitter();
requestAnimationFrame(tickBloom);
