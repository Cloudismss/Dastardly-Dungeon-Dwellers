import { XTermTheme } from './colors';

/* Ambient types for ttyd's globals — not bundled, only used for type checking. */
declare global {
  interface Window {
    term?: {
      options: {
        theme: XTermTheme;
        fontFamily: string;
        fontSize: number;
      };
    };
    tty_options?: {
      fontFamily?: string;
      fontSize?: number;
      theme?: XTermTheme;
    };
  }
}

/* Polls until window.term is available, then applies the theme.
   Double rAF lets xterm schedule its redraw before the optional callback fires,
   so the boot animation only reveals content after the phosphor colours land. */
export function applyXtermTheme(theme: XTermTheme, cb?: () => void): void {
  if (window.term?.options) {
    try { window.term.options.theme = theme; } catch (_) {}
    if (cb) requestAnimationFrame(() => requestAnimationFrame(cb));
  } else {
    setTimeout(() => applyXtermTheme(theme, cb), 50);
  }
}
