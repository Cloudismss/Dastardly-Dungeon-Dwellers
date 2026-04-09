export type RGB = [number, number, number];

export interface XTermTheme {
  foreground: string; background: string;
  cursor: string;     cursorAccent: string;
  black: string;      red: string;     green: string;   yellow: string;
  blue: string;       magenta: string; cyan: string;    white: string;
  brightBlack: string;   brightRed: string;     brightGreen: string;   brightYellow: string;
  brightBlue: string;    brightMagenta: string; brightCyan: string;    brightWhite: string;
}

export function h2a(h: string): RGB {
  const v = parseInt(h.replace('#', ''), 16);
  return [(v >> 16) & 255, (v >> 8) & 255, v & 255];
}

export function a2h(r: number, g: number, b: number): string {
  return '#' + [r, g, b]
    .map(c => ('0' + Math.max(0, Math.min(255, Math.round(c))).toString(16)).slice(-2))
    .join('');
}

export function hslToRgb(h: number, s: number, l: number): RGB {
  s /= 100; l /= 100;
  const a = s * Math.min(l, 1 - l);
  const f = (n: number): number => {
    const k = (n + h / 30) % 12;
    return l - a * Math.max(-1, Math.min(k - 3, 9 - k, 1));
  };
  return [Math.round(f(0) * 255), Math.round(f(8) * 255), Math.round(f(4) * 255)];
}

/* Replicates cool-retro-term ApplicationSettings.qml phosphor colour formula:
     saturatedColor = mix(rawFg, white, satColor × 0.5)
     fgRendered     = mix(rawBg, saturatedColor, 0.7 + contrast × 0.3)
     bgRendered     = mix(saturatedColor, rawBg, 0.7 + contrast × 0.3)      */
export function computePhosphorColors(
  rawFgHex: string, rawBgHex: string, satColor: number, contrast: number
): { fg: string; bg: string } {
  const f = h2a(rawFgHex), b = h2a(rawBgHex);
  const s = satColor * 0.5;
  const sc: RGB = [f[0] * (1 - s) + 255 * s, f[1] * (1 - s) + 255 * s, f[2] * (1 - s) + 255 * s];
  const mix = 0.7 + contrast * 0.3;
  return {
    fg: a2h(b[0] * (1 - mix) + sc[0] * mix, b[1] * (1 - mix) + sc[1] * mix, b[2] * (1 - mix) + sc[2] * mix),
    bg: a2h(sc[0] * (1 - mix) + b[0] * mix, sc[1] * (1 - mix) + b[1] * mix, sc[2] * (1 - mix) + b[2] * mix),
  };
}

/* Monochrome 16-colour xterm theme tinted to a phosphor colour.
   Each ANSI slot lerps between bg (off) and fg (full) at a chosen brightness. */
export function makePhosphorTheme(fgHex: string, bgHex: string): XTermTheme {
  const f = h2a(fgHex), bk = h2a(bgHex);
  const lerp = (t: number): string =>
    a2h(bk[0] + (f[0] - bk[0]) * t, bk[1] + (f[1] - bk[1]) * t, bk[2] + (f[2] - bk[2]) * t);
  const boost = (t: number): string => a2h(f[0] * t, f[1] * t, f[2] * t);
  return {
    foreground: fgHex, background: bgHex,
    cursor: fgHex,     cursorAccent: bgHex,
    black:       bgHex,      red:           lerp(0.55),
    green:       lerp(0.65), yellow:        lerp(0.80),
    blue:        lerp(0.35), magenta:       lerp(0.60),
    cyan:        lerp(0.70), white:         lerp(0.85),
    brightBlack:   lerp(0.25), brightRed:     lerp(0.70),
    brightGreen:   lerp(0.80), brightYellow:  fgHex,
    brightBlue:    lerp(0.50), brightMagenta: lerp(0.80),
    brightCyan:    lerp(0.90), brightWhite:   boost(1.15),
  };
}
