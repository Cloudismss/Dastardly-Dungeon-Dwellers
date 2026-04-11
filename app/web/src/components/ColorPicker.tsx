import { h } from 'preact';
import { useEffect, useRef } from 'preact/hooks';
import { customHueSig } from '../state';
import { profileFromHue } from '../profiles';
import { applyProfile } from '../apply';

const WHEEL_SIZE = 110, OUTER_R = 50, INNER_R = 32;

function drawHueWheel(canvas: HTMLCanvasElement, hue: number): void {
  const ctx = canvas.getContext('2d');
  if (!ctx) return;
  ctx.clearRect(0, 0, WHEEL_SIZE, WHEEL_SIZE);
  const cx = WHEEL_SIZE / 2, cy = WHEEL_SIZE / 2;
  for (let i = 0; i < 360; i++) {
    const a0 = (i / 360) * Math.PI * 2 - Math.PI / 2;
    const a1 = ((i + 1) / 360) * Math.PI * 2 - Math.PI / 2;
    ctx.beginPath();
    ctx.moveTo(cx + Math.cos(a0) * INNER_R, cy + Math.sin(a0) * INNER_R);
    ctx.arc(cx, cy, OUTER_R, a0, a1);
    ctx.arc(cx, cy, INNER_R, a1, a0, true);
    ctx.closePath();
    ctx.fillStyle = `hsl(${i},100%,55%)`;
    ctx.fill();
  }
  /* Selection dot */
  const sel = (hue / 360) * Math.PI * 2 - Math.PI / 2;
  const midR = (OUTER_R + INNER_R) / 2;
  ctx.beginPath();
  ctx.arc(cx + Math.cos(sel) * midR, cy + Math.sin(sel) * midR, 5, 0, Math.PI * 2);
  ctx.fillStyle = '#fff';
  ctx.fill();
  ctx.strokeStyle = 'rgba(0,0,0,0.6)';
  ctx.lineWidth = 1.5;
  ctx.stroke();
}

function hueFromEvent(canvas: HTMLCanvasElement, e: MouseEvent | TouchEvent): number {
  const rect = canvas.getBoundingClientRect();
  const cx = rect.left + rect.width / 2, cy = rect.top + rect.height / 2;
  const src = 'touches' in e ? e.touches[0] : e;
  const angle = Math.atan2(src.clientY - cy, src.clientX - cx) + Math.PI / 2;
  return ((angle / (Math.PI * 2)) * 360 + 360) % 360;
}

export function ColorPicker() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const dragging  = useRef(false);

  /* Draw the wheel once on mount. */
  useEffect(() => {
    if (canvasRef.current) drawHueWheel(canvasRef.current, customHueSig.value);
  }, []);

  function pick(e: MouseEvent | TouchEvent) {
    if (!canvasRef.current) return;
    const hue = hueFromEvent(canvasRef.current, e);
    customHueSig.value = hue;
    /* Redraw immediately — pick() is called from document-level mousemove,
       which is outside Preact's event system. Relying on a re-render cycle
       causes the indicator to lag or not move at all during a drag. */
    drawHueWheel(canvasRef.current, hue);
    applyProfile(profileFromHue(hue));
  }

  useEffect(() => {
    const move = (e: MouseEvent) => { if (dragging.current) pick(e); };
    const up   = () => { dragging.current = false; };
    document.addEventListener('mousemove', move);
    document.addEventListener('mouseup',   up);
    return () => {
      document.removeEventListener('mousemove', move);
      document.removeEventListener('mouseup',   up);
    };
  }, []);

  return (
    <div id="crt-color-picker" class="visible">
      <canvas
        ref={canvasRef}
        id="crt-hue-wheel"
        width={WHEEL_SIZE}
        height={WHEEL_SIZE}
        onMouseDown={e => { dragging.current = true; pick(e); }}
        onTouchStart={e => { e.preventDefault(); pick(e); }}
        onTouchMove={e => { e.preventDefault(); pick(e); }}
      />
    </div>
  );
}
