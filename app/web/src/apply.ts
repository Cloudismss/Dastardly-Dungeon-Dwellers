import { PhosphorProfile } from './profiles';
import { computeColors } from './profiles';
import { applyXtermTheme } from './xterm';
import { contrastLevelSig } from './state';

/* Injected <style> block for menu theming. Using hardcoded RGB values rather
   than CSS variables avoids stale-cache false-positives in some adblockers.
   Must be appended to document.body (not head) so it appears after
   <style id="crt-styles">, which is also in the body (injected before </body>).
   CSS processes stylesheets in document order — later wins on equal specificity,
   so body placement ensures these overrides beat the base stylesheet. */
const menuThemeStyle = document.createElement('style');
document.body.appendChild(menuThemeStyle);

export function updateMenuTheme(rgb: string): void {
  menuThemeStyle.textContent =
    `#crt-menu-btn{color:rgba(${rgb},0.80);border-color:rgba(${rgb},0.30);}` +
    `#crt-menu-panel{border-color:rgba(${rgb},0.30);}` +
    `.crt-menu-section{color:rgba(${rgb},0.45);border-bottom-color:rgba(${rgb},0.15);}` +
    `.crt-menu-profile{color:rgba(${rgb},0.90);}` +
    `.crt-menu-profile button{color:rgba(${rgb},1);}` +
    `.crt-effect-header{color:rgba(${rgb},0.80);}` +
    `.crt-effect-header.dim{color:rgba(${rgb},0.30);}` +
    `.crt-effect-toggle{border-color:rgba(${rgb},0.30);color:rgba(${rgb},0.70);}` +
    `.crt-effect-toggle:hover{color:rgba(${rgb},1);border-color:rgba(${rgb},0.60);}` +
    `.crt-effect-toggle.off{color:rgba(${rgb},0.30);border-color:rgba(${rgb},0.15);}` +
    `.crt-slider{background:rgba(${rgb},0.20);}` +
    `.crt-slider::-webkit-slider-thumb{background:rgba(${rgb},0.85);}` +
    `.crt-slider::-moz-range-thumb{background:rgba(${rgb},0.85);}` +
    `#crt-custom-toggle{color:rgba(${rgb},0.70);}`;
}

export function applyProfile(p: PhosphorProfile, cb?: () => void): void {
  const c = computeColors(p, contrastLevelSig.value);
  const s = document.documentElement.style;
  s.setProperty('--crt-bg',       c.bg);
  s.setProperty('--crt-glow',     p.glow);
  s.setProperty('--crt-glow-rgb', p.menuRgb);
  s.setProperty('--crt-filter',   p.filter);
  document.body.style.background = c.bg;
  const tc = document.getElementById('terminal-container');
  if (tc) tc.style.background = c.bg;
  const bc = document.getElementById('crt-bloom-canvas') as HTMLElement | null;
  if (bc) bc.style.filter = p.bloom;
  updateMenuTheme(p.menuRgb);
  applyXtermTheme(c.theme, cb);
}
