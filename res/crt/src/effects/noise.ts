/* Animated film-grain: increments the SVG feTurbulence seed every ~80 ms
   to produce a continuously shifting noise texture. */
export function startNoise(): void {
  const turbulence = document.getElementById('crt-turbulence') as SVGFETurbulenceElement | null;
  if (!turbulence) return;
  let seed = 0;
  (function tick() {
    seed = (seed + 1) & 0x3FF;
    turbulence.setAttribute('seed', String(seed));
    setTimeout(() => requestAnimationFrame(tick), 80);
  })();
}
