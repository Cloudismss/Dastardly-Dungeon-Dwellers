import { h2a, computePhosphorColors } from '../colors';
import { currentProfile } from '../state';
import { contrastLevelSig } from '../state';

const SCALE = 0.50; /* Render at half resolution; CSS stretches it back up. */

let bloomCanvas:  HTMLCanvasElement | null          = null;
let bloomCtx:     CanvasRenderingContext2D | null   = null;
let tmp:          HTMLCanvasElement | null          = null;
let tmpCtx:       CanvasRenderingContext2D | null   = null;
let extract:      HTMLCanvasElement | null          = null;
let extractCtx:   CanvasRenderingContext2D | null   = null;

export function resizeBloom(): void {
  const screen = document.querySelector<HTMLElement>('.xterm-screen');
  if (!screen || !bloomCanvas) return;
  const w = Math.max(1, Math.round(screen.offsetWidth  * SCALE));
  const h = Math.max(1, Math.round(screen.offsetHeight * SCALE));
  tmp!.width  = extract!.width  = bloomCanvas.width  = w;
  tmp!.height = extract!.height = bloomCanvas.height = h;
  const r = screen.getBoundingClientRect();
  bloomCanvas.style.left   = `${r.left}px`;
  bloomCanvas.style.top    = `${r.top}px`;
  bloomCanvas.style.width  = `${r.width}px`;
  bloomCanvas.style.height = `${r.height}px`;
}

export function setupBloom(): void {
  if (document.getElementById('crt-bloom')) return;

  const bloomWrap = document.createElement('div');
  bloomWrap.id = 'crt-bloom';
  bloomCanvas = document.createElement('canvas');
  bloomCanvas.id = 'crt-bloom-canvas';
  bloomWrap.appendChild(bloomCanvas);
  document.body.appendChild(bloomWrap);

  bloomCtx   = bloomCanvas.getContext('2d');
  tmp        = document.createElement('canvas');
  tmpCtx     = tmp.getContext('2d');
  extract    = document.createElement('canvas');
  extractCtx = extract.getContext('2d');

  window.addEventListener('resize', resizeBloom);
}

export function tickBloom(): void {
  requestAnimationFrame(tickBloom);

  const screen = document.querySelector<HTMLElement>('.xterm-screen');
  if (!screen || !bloomCtx || !tmp || !tmpCtx || !extract || !extractCtx || !bloomCanvas) return;

  const r = screen.getBoundingClientRect();
  if (r.width > 0 && r.height > 0) {
    bloomCanvas.style.left   = `${r.left}px`;
    bloomCanvas.style.top    = `${r.top}px`;
    bloomCanvas.style.width  = `${r.width}px`;
    bloomCanvas.style.height = `${r.height}px`;

    const w = Math.max(1, Math.round(r.width  * SCALE));
    const h = Math.max(1, Math.round(r.height * SCALE));
    if (Math.abs(bloomCanvas.width - w) > 1 || Math.abs(bloomCanvas.height - h) > 1) {
      tmp.width  = extract.width  = bloomCanvas.width  = w;
      tmp.height = extract.height = bloomCanvas.height = h;
    }
  }

  const w = tmp.width, h = tmp.height;
  if (!w || !h) return;

  /* Pass 1 — composite all xterm canvas layers at half resolution. */
  tmpCtx.clearRect(0, 0, w, h);
  screen.querySelectorAll('canvas').forEach(c => {
    if (c === bloomCanvas) return;
    try { tmpCtx!.drawImage(c as HTMLCanvasElement, 0, 0, w, h); } catch (_) {}
  });

  /* Adaptive brightness: keep background crushed to black regardless of the
     contrast slider, so the bloom mask stays stable. */
  const p   = currentProfile();
  const bg  = p.rawFg
    ? computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevelSig.value).bg
    : p.rawBg;
  const bgc  = h2a(bg);
  const bgMax = Math.max(bgc[0], bgc[1], bgc[2]);
  const brt   = bgMax > 8 ? (120 / bgMax) : 15;

  /* Pass 2 — minimal blur to smooth glyphs without killing intensity. */
  extractCtx.clearRect(0, 0, w, h);
  extractCtx.filter = 'blur(1px)';
  extractCtx.drawImage(tmp, 0, 0);
  extractCtx.filter = 'none';

  /* Pass 3 — threshold, colorize, composite. */
  bloomCtx.globalCompositeOperation = 'source-over';
  bloomCtx.clearRect(0, 0, w, h);
  bloomCtx.fillStyle = '#000';
  bloomCtx.fillRect(0, 0, w, h);
  bloomCtx.filter = `grayscale(1) brightness(${brt.toFixed(2)}) contrast(12)`;
  bloomCtx.drawImage(extract, 0, 0);
  bloomCtx.filter = 'none';

  bloomCtx.globalCompositeOperation = 'multiply';
  bloomCtx.fillStyle = `rgb(${p.menuRgb})`;
  bloomCtx.fillRect(0, 0, w, h);
  bloomCtx.globalCompositeOperation = 'source-over';
}
