import { setCurvatureParam, imperativeState } from '../state';

/* Lazy-init references to SVG nodes and the off-screen canvas. */
let _curveImg:     SVGFEImageElement | null          = null;
let _curveDisplace: SVGFEDisplacementMapElement | null = null;
let _curveCanvas:  HTMLCanvasElement | null          = null;
let _curveCtx:     CanvasRenderingContext2D | null   = null;

/* Generates a 128×128 barrel-distortion displacement map and wires it into
   the SVG feDisplacementMap filter on #terminal-container.
   Formula mirrors cool-retro-term's distortCoordinates() shader:
     cc   = UV - 0.5
     dist = dot(cc, cc) * k
     displacement = cc * (1 + dist) * dist
   Pixel displacements are baked into R/G channels (0.5 = neutral).
   Called on slider change and on every window resize. */
export function buildCurveMap(k: number): void {
  setCurvatureParam(k);

  if (!_curveImg) {
    _curveImg      = document.getElementById('crt-curve-img')      as SVGFEImageElement | null;
    _curveDisplace = document.getElementById('crt-curve-displace') as SVGFEDisplacementMapElement | null;
    if (_curveImg && _curveDisplace) {
      _curveCanvas = document.createElement('canvas');
      _curveCtx    = _curveCanvas.getContext('2d');
    }
  }
  if (!_curveImg || !_curveDisplace || !_curveCanvas || !_curveCtx) return;

  if (k <= 0) {
    document.documentElement.style.setProperty('--crt-curve-filter', 'none');
    return;
  }

  const tc = document.getElementById('terminal-container');
  const W  = tc ? tc.offsetWidth  : window.innerWidth;
  const H  = tc ? tc.offsetHeight : window.innerHeight;
  if (W <= 0 || H <= 0) return;

  const N = 128;
  _curveCanvas.width = _curveCanvas.height = N;

  const SCALE = Math.max(W, H);
  const img   = _curveCtx.createImageData(N, N);
  for (let row = 0; row < N; row++) {
    for (let col = 0; col < N; col++) {
      const u  = col / (N - 1), v = row / (N - 1);
      const cx = u - 0.5,       cy = v - 0.5;
      const dist = (cx * cx + cy * cy) * k;
      const dpx  = cx * (1 + dist) * dist * W;
      const dpy  = cy * (1 + dist) * dist * H;
      const r    = dpx / SCALE + 0.5;
      const g    = dpy / SCALE + 0.5;
      const idx  = (row * N + col) << 2;
      img.data[idx]     = Math.max(0, Math.min(255, (r * 255 + 0.5) | 0));
      img.data[idx + 1] = Math.max(0, Math.min(255, (g * 255 + 0.5) | 0));
      img.data[idx + 2] = 0;
      img.data[idx + 3] = 255;
    }
  }
  _curveCtx.putImageData(img, 0, 0);
  _curveImg.setAttribute('href', _curveCanvas.toDataURL());
  _curveImg.setAttribute('x',      '0');
  _curveImg.setAttribute('y',      '0');
  _curveImg.setAttribute('width',  String(W));
  _curveImg.setAttribute('height', String(H));
  _curveDisplace.setAttribute('scale', String(SCALE));
  document.documentElement.style.setProperty('--crt-curve-filter', 'url(#crt-curve-filter)');
}

export function rebuildCurveOnResize(): void {
  buildCurveMap(imperativeState.curvatureParam);
}
