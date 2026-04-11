import { Bridge } from './lib';

/* Ambient types for ttyd's globals */
declare global {
  interface Window {
    term?: any;
    tty_options?: any;
  }
}

/* ── Pre-render: set tty_options before xterm.js initialises ─────────────── */
(function () {
  const { profiles } = require('./profiles');
  const { computePhosphorColors, makePhosphorTheme } = require('./colors');
  const { contrastLevelSig, profileIdxSig } = require('./state');
  const p = profiles[profileIdxSig.value];
  const c = computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevelSig.value);
  window.tty_options = Object.assign(window.tty_options ?? {}, {
    fontFamily: "'VT323', 'Courier New', monospace",
    fontSize:   18,
    theme:      makePhosphorTheme(c.fg, c.bg),
  });
})();

/* In ttyd mode, we use the legacy entry point because ttyd manages the Terminal. */
import './main-legacy'; 
