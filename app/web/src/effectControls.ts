/* Imperative handles registered by EffectSlider components on mount.
   Used for the framesize → radius coupling (turning off the frame disables
   the rounded corner toggle since there is no frame to round). */
export interface EffectControl {
  isOn:    () => boolean;
  turnOn:  () => void;
  turnOff: () => void;
}

export const effectControls = new Map<string, EffectControl>();

/* Tracks whether radius was on when framesize was turned off, so it can be
   restored if framesize is turned back on. */
export let frameSizeRadiusWasOn = true;
export function setFrameSizeRadiusWasOn(v: boolean): void {
  frameSizeRadiusWasOn = v;
}
