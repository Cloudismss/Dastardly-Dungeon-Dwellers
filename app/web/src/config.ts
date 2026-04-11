export interface CRTConfig {
  profileIdx: number;
  bloom:      number;
  glowline:   number;
  scanlines:  number;
  noise:      number;
  jitter:     number;
  flicker:    number;
  radius:     number;
  framesize:  number;
  contrast:   number;
  curve:      number;
}

export const CONFIG: CRTConfig = {
  profileIdx: 0,
  bloom:      50,
  glowline:   40,
  scanlines:  25,
  noise:      15,
  jitter:     15,
  flicker:    10,
  radius:     20,
  framesize:  10,
  contrast:   80,
  curve:      20,
};
