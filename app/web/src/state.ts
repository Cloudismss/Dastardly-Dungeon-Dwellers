import { signal, computed } from '@preact/signals';
import { CONFIG } from './config';
import { profiles, profileFromHue, PhosphorProfile } from './profiles';

/* ── Signals (drive Preact component re-renders) ─────────────────────────── */
export const profileIdxSig  = signal(CONFIG.profileIdx);
export const customActiveSig = signal(false);
export const customHueSig   = signal(0);
export const contrastSig    = signal(CONFIG.contrast);   /* 0–100 % */

/* Derived contrastLevel (0.0–1.0) used by both colour math and effects. */
export const contrastLevelSig = computed(() => contrastSig.value / 100);

/* ── Imperative mutable state (read by animation loops) ─────────────────── */
let _jitterStrength = CONFIG.jitter;
let _curvatureParam = 0;

export const imperativeState = {
  get jitterStrength() { return _jitterStrength; },
  get curvatureParam()  { return _curvatureParam; },
};

export function setJitterStrength(v: number) { _jitterStrength = v; }
export function setCurvatureParam(v: number)  { _curvatureParam = v; }

/* ── Helpers ─────────────────────────────────────────────────────────────── */
export function currentProfile(): PhosphorProfile {
  return customActiveSig.value
    ? profileFromHue(customHueSig.value)
    : profiles[profileIdxSig.value];
}
