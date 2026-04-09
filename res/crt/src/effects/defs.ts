import { CONFIG } from '../config';
import { contrastSig, contrastLevelSig, currentProfile } from '../state';
import { setJitterStrength } from '../state';
import { applyProfile } from '../apply';
import { computePhosphorColors, makePhosphorTheme } from '../colors';
import { buildCurveMap } from './curve';
import { updateBezelClip } from '../dom';

export interface EffectDef {
  id:         string;
  label:      string;
  default:    number;
  toggleOnly?: boolean;
  apply:      (v: number) => void;
}

export const effectDefs: EffectDef[] = [
  {
    id: 'contrast', label: 'CONTRAST', default: CONFIG.contrast,
    /* Replicates cool-retro-term's contrast knob: shifts both fg and bg.
       100% = saturatedColor fg / black bg. 0% = ~30% phosphor on bg. */
    apply(v) {
      contrastSig.value = v;
      const p = currentProfile();
      if (!p.rawFg) return;
      const c = computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevelSig.value);
      document.documentElement.style.setProperty('--crt-bg', c.bg);
      document.body.style.background = c.bg;
      const tc = document.getElementById('terminal-container');
      if (tc) tc.style.background = c.bg;
      if (window.term?.options) {
        try { window.term.options.theme = makePhosphorTheme(c.fg, c.bg); } catch (_) {}
      }
    },
  },
  {
    id: 'bloom', label: 'BLOOM', default: CONFIG.bloom,
    /* Maps 0–100% to 0–1.0 opacity via CSS var (no inline style on the element,
       which would trigger adblocker div[id^="crt-"][style] rules). */
    apply(v) {
      document.documentElement.style.setProperty('--crt-bloom-opacity', (v / 100).toFixed(3));
    },
  },
  {
    id: 'glowline', label: 'GLOW LINE', default: CONFIG.glowline,
    apply(v) {
      document.documentElement.style.setProperty('--crt-glow-opacity', (v / 100).toFixed(2));
    },
  },
  {
    id: 'scanlines', label: 'SCANLINES', default: CONFIG.scanlines,
    /* 25% → 0.125 (reference strength). 100% → 0.50 max alpha. */
    apply(v) {
      document.documentElement.style.setProperty('--crt-scanlines', (v / 100 * 0.5).toFixed(3));
    },
  },
  {
    id: 'noise', label: 'FILM GRAIN', default: CONFIG.noise,
    /* 15% → opacity 0.08. SVG element so inline style is safe from adblockers
       (their filter targets div[id^="crt-"][style], not SVG elements). */
    apply(v) {
      const el = document.getElementById('crt-noise-svg');
      if (!el) return;
      el.style.opacity = (v / 100 * 0.53).toFixed(3);
      el.style.display = v === 0 ? 'none' : 'block';
    },
  },
  {
    id: 'jitter', label: 'JITTER', default: CONFIG.jitter,
    apply(v) {
      setJitterStrength(v);
      if (v === 0) {
        document.documentElement.style.setProperty('--crt-jitter-x', '0px');
        document.documentElement.style.setProperty('--crt-jitter-y', '0px');
      }
    },
  },
  {
    id: 'flicker', label: 'FLICKERING', default: CONFIG.flicker,
    /* --crt-flicker-amt feeds directly into keyframe calc() expressions.
       10% → 0.08 amt. 100% → 0.80 amt (very deep dips). */
    apply(v) {
      const tc = document.getElementById('terminal-container');
      if (v === 0) {
        if (tc) tc.style.animationPlayState = 'paused';
        document.documentElement.style.setProperty('--crt-flicker-amt', '0');
      } else {
        if (tc) tc.style.animationPlayState = 'running';
        document.documentElement.style.setProperty('--crt-flicker-amt', (v / 100 * 0.8).toFixed(3));
      }
    },
  },
  {
    id: 'framesize', label: 'FRAME SIZE', default: CONFIG.framesize,
    /* 10% → 12px border. 100% → 120px. margin tracks framesize so the terminal
       always sits inside the bezel. */
    apply(v) {
      const px = `${(v / 100 * 120).toFixed(0)}px`;
      document.documentElement.style.setProperty('--crt-frame-px',  px);
      document.documentElement.style.setProperty('--crt-margin-px', px);
      updateBezelClip();
      window.dispatchEvent(new Event('resize'));
    },
  },
  {
    id: 'radius', label: 'ROUNDED FRAME', default: CONFIG.radius,
    toggleOnly: true,
    apply(v) {
      document.documentElement.style.setProperty('--crt-radius-px', `${(v / 100 * 80).toFixed(0)}px`);
      updateBezelClip();
    },
  },
  {
    id: 'curve', label: 'CURVATURE', default: CONFIG.curve,
    /* Maps 0–100% to shader curvature k = 0–0.4. Delegates to buildCurveMap
       which generates the barrel-distortion canvas and updates the SVG filter. */
    apply(v) {
      buildCurveMap(v / 100 * 0.4);
    },
  },
];
