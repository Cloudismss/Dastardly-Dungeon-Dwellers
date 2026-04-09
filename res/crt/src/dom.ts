import { resizeBloom, setupBloom } from './effects/bloom';
import { rebuildCurveOnResize } from './effects/curve';

/* ── Bezel clip-path ─────────────────────────────────────────────────────── */
/* The clip is an evenodd SVG path: outer viewport rect minus a rounded-rect
   hole matching the terminal area. Called on resize and whenever the frame
   size or radius CSS vars change. */
const bezelClipPath = document.getElementById('bezel-clip-path') as SVGPathElement | null;

export function updateBezelClip(): void {
  if (!bezelClipPath) return;
  const s   = getComputedStyle(document.documentElement);
  const fpx = parseFloat(s.getPropertyValue('--crt-frame-px'))  || 0;
  let   rpx = parseFloat(s.getPropertyValue('--crt-radius-px')) || 0;
  const W   = window.innerWidth, H = window.innerHeight;
  const x = fpx, y = fpx, w = W - 2 * fpx, h = H - 2 * fpx;
  rpx = Math.min(rpx, w / 2, h / 2);
  /* Outer rect (CW) then inner rounded rect (CW) — evenodd punches the hole. */
  const d =
    `M0,0 H${W} V${H} H0 Z` +
    ` M${x + rpx},${y}` +
    ` H${x + w - rpx}` +
    ` Q${x + w},${y} ${x + w},${y + rpx}` +
    ` V${y + h - rpx}` +
    ` Q${x + w},${y + h} ${x + w - rpx},${y + h}` +
    ` H${x + rpx}` +
    ` Q${x},${y + h} ${x},${y + h - rpx}` +
    ` V${y + rpx}` +
    ` Q${x},${y} ${x + rpx},${y} Z`;
  bezelClipPath.setAttribute('d', d);
}

/* ── Static overlay elements ─────────────────────────────────────────────── */
const overlay  = document.createElement('div');
overlay.id     = 'crt-overlay';
const glowLine = document.createElement('div');
glowLine.id    = 'crt-glow-line';
const bezel    = document.createElement('div');
bezel.id       = 'crt-bezel';
document.body.appendChild(bezel);

/* Appended to body (not inside terminal-container) so they sit above the WebGL
   canvas GPU compositor layer, which is promoted above TC's stacking context
   on HTTPS pages. */
function setupOverlays(): void {
  const tc = document.getElementById('terminal-container');
  if (!tc || document.body.contains(overlay)) return;

  document.body.appendChild(overlay);
  document.body.appendChild(glowLine);

  const termEl = tc.querySelector('.terminal');
  if (termEl) ro.observe(termEl);
}

/* ── ResizeObserver ──────────────────────────────────────────────────────── */
const ro = new ResizeObserver(() => {
  window.dispatchEvent(new Event('resize'));
  setTimeout(() => window.dispatchEvent(new Event('resize')), 50);
  resizeBloom();
  rebuildCurveOnResize();
});

/* ── MutationObserver — re-attach overlays if Preact swaps them ─────────── */
const bodyObserver = new MutationObserver(setupOverlays);
bodyObserver.observe(document.body, { childList: true, subtree: true });

/* ── Initialise ──────────────────────────────────────────────────────────── */
export function initDOM(): void {
  updateBezelClip();
  window.addEventListener('resize', updateBezelClip);
  window.addEventListener('resize', rebuildCurveOnResize);
  setupOverlays();
  setupBloom();
}
