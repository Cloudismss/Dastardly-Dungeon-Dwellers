import { computePhosphorColors, makePhosphorTheme, hslToRgb, a2h, XTermTheme } from './colors';

export interface PhosphorProfile {
  name:     string;
  rawFg:    string;
  rawBg:    string;
  satColor: number;
  glow:     string;
  filter:   string;
  bloom:    string;
  menuRgb:  string;
}

export const profiles: PhosphorProfile[] = [
  { name: 'GREEN', rawFg: '#1aff80', rawBg: '#000000', satColor: 0.0,
    glow: 'rgba(26,255,128,0.35)',   filter: 'brightness(1.05)',
    bloom: 'blur(40px)', menuRgb: '26, 255, 128' },
  { name: 'AMBER', rawFg: '#ffb642', rawBg: '#000000', satColor: 0.2,
    glow: 'rgba(255,182,66,0.40)',   filter: 'brightness(1.05)',
    bloom: 'blur(40px)', menuRgb: '255, 182, 66' },
  { name: 'BLUE',  rawFg: '#7fb4ff', rawBg: '#000000', satColor: 0.2,
    glow: 'rgba(127,180,255,0.35)',  filter: 'brightness(1.05)',
    bloom: 'blur(40px)', menuRgb: '127, 180, 255' },
  { name: 'WHITE', rawFg: '#c5ffff', rawBg: '#0f1414', satColor: 0.0,
    glow: 'rgba(197,255,255,0.25)',  filter: 'brightness(1.00)',
    bloom: 'blur(40px)', menuRgb: '197, 255, 255' },
];

export function profileFromHue(hue: number): PhosphorProfile {
  const rgb = hslToRgb(hue, 100, 60);
  const hex = a2h(rgb[0], rgb[1], rgb[2]);
  return {
    name: 'CUSTOM',
    rawFg: hex, rawBg: '#000000', satColor: 0.0,
    glow:   `rgba(${rgb.join(',')},0.35)`,
    filter: 'brightness(1.00)',
    bloom:  'blur(40px)',
    menuRgb: rgb.join(', '),
  };
}

export function computeColors(
  p: PhosphorProfile, contrastLevel: number
): { fg: string; bg: string; theme: XTermTheme } {
  const c = computePhosphorColors(p.rawFg, p.rawBg, p.satColor, contrastLevel);
  return { fg: c.fg, bg: c.bg, theme: makePhosphorTheme(c.fg, c.bg) };
}
