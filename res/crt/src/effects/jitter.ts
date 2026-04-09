import { imperativeState } from '../state';

/* Periodically applies a small random pixel offset to the terminal container,
   simulating analog horizontal sync instability.
   Interval and amplitude both scale with jitterStrength (0–100). */
export function startJitter(): void {
  scheduleJitter();
}

function scheduleJitter(): void {
  const strength = imperativeState.jitterStrength;
  const gap = strength === 0
    ? 60_000
    : Math.max(300, (100 - strength) * 150) + Math.random() * Math.max(300, (100 - strength) * 100);

  setTimeout(() => {
    if (imperativeState.jitterStrength > 0) {
      const tc = document.getElementById('terminal-container');
      if (tc) {
        const frames = 5;
        let   count  = 0;
        const amp    = imperativeState.jitterStrength / 100 * 5;
        const iv = setInterval(() => {
          const dx = (Math.random() - 0.5) * amp;
          const dy = (Math.random() - 0.5) * amp;
          tc.style.setProperty('--crt-jitter-x', `${dx.toFixed(2)}px`);
          tc.style.setProperty('--crt-jitter-y', `${dy.toFixed(2)}px`);
          if (++count >= frames) {
            clearInterval(iv);
            tc.style.setProperty('--crt-jitter-x', '0px');
            tc.style.setProperty('--crt-jitter-y', '0px');
          }
        }, 30);
      }
    }
    scheduleJitter();
  }, gap);
}
