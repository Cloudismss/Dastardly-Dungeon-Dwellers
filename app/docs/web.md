# CRT Visual Effects

## Overview

A set of CRT visual effects layered on top of [ttyd](https://github.com/tsl0922/ttyd) + [xterm.js](https://xtermjs.org/) entirely in the browser — no native code, no ttyd modifications, no server-side logic.

**Tech stack:** TypeScript · Preact · Preact Signals · esbuild

**How it works at a glance:**

```
res/crt.html          Static fragment: Google Fonts link, SVG filters, CSS
res/crt/src/          TypeScript source, compiled by esbuild → dist/crt.js
                      ↓ Docker build (crt-build stage)
dist/crt.js           Minified IIFE bundle (~single <script> tag)
                      ↓ ttyd-html stage: inject before </body>
index.html            ttyd's patched page, served by the final container
```

**Two categories of code:**

| Category | What it covers | Pattern |
|----------|---------------|---------|
| Settings menu | `Menu`, `ProfileSelector`, `EffectSlider`, `ColorPicker` | Preact components + signals |
| Visual effects | bloom, noise, jitter, curvature, glow line, bezel, scanlines | Imperative canvas/DOM/CSS |

The two categories share state via Preact signals defined in `state.ts`. Signals are readable both inside components (triggering re-renders) and from the imperative animation loops (plain `.value` reads).

**xterm.js integration points** (the only two places the overlay touches ttyd):

- `window.tty_options` — set before xterm initialises; controls font and initial phosphor theme.
- `window.term.options.theme` — patched at runtime by `applyXtermTheme()` whenever the profile or contrast changes. Polled until available because ttyd initialises xterm asynchronously.

**If you're new to this codebase, start with:**

1. `res/crt/src/config.ts` — all default values in one place
2. `res/crt/src/effects/defs.ts` — the full list of effects and what each `apply()` does
3. `res/crt/src/main.tsx` — the initialisation sequence in order

---

## TODO

- Investigate performance
- Complete implementation status

---

## Implementation status

| # | Effect | Status |
|---|--------|--------|
| 1 | Bloom | completed |
| 2 | Jitter | completed |
| 3 | Glow Line | completed |
| 4 | Frame Size | completed |
| 5 | Margin | completed |
| 6 | Rounded Frame | completed |
| 7 | Ambient Light | pending |
| 8 | Flickering | completed |
| 9 | Burn-In | pending |
| 10 | Static Noise | completed |
| 11 | Horizontal Sync | pending |
| 12 | Screen Curvature | completed |

---

## cool-retro-term reference

These settings from a customised cool-retro-term profile represent the target aesthetic. Use them as a reference when tuning effect intensities.

### Color themes (in order of preference)

1. Green
2. Amber
3. Blue
4. White

### Screen

| Setting | Value |
|---------|-------|
| Brightness | 100% |
| Contrast | 80% |
| Margin | 30% |
| Radius | 20% |
| Frame Size | 10% |

### Terminal

| Setting | Value |
|---------|-------|
| Chroma Color | 100% |
| Saturation Color | 20% |

### Effects (Project Defaults)

| Effect | Strength |
|--------|----------|
| Bloom | 50% |
| Burn-In | 3% |
| Static Noise | 15% |
| Jitter | 15% |
| Glow Line | 40% |
| Ambient Light | 25% |
| Flickering | 10% |
| Horizontal Sync | 10% |

### Advanced

| Setting | Value |
|---------|-------|
| Bloom Quality | 50% |
| Burn-In Quality | 50% |
| Texture Quality | 100% |

---

Dastardly Dungeon Dwellers is served as a browser terminal via [ttyd](https://github.com/tsl0922/ttyd) using [xterm.js](https://xtermjs.org/). A set of CRT visual effects inspired by [cool-retro-term](https://github.com/Swordfish90/cool-retro-term) are layered on top of the xterm.js output entirely in HTML/CSS/JS — no native code changes required.

## How injection works

The effects are split into two parts:

- **`res/crt.html`** — static fragment containing the Google Fonts link, SVG filter definitions, and all CSS. Checked into the repo as-is.
- **`res/crt/`** — TypeScript + Preact source project. Compiled by esbuild into `res/crt/dist/crt.js` during the Docker build.

The `Dockerfile.prod` has a dedicated `crt-build` stage (`node:lts-alpine`) that runs `npm ci && npm run build`. The compiled bundle is then copied into the `ttyd-html` stage, which:

1. Spins up ttyd briefly to capture the `index.html` it normally serves
2. Patches the favicon
3. Injects `crt.html` (static parts) + `<script>` with the compiled bundle immediately before `</body>`

The final ttyd container serves the patched page.

## Source structure

```
res/crt/
  package.json          esbuild + preact + @preact/signals + typescript
  tsconfig.json
  src/
    webgl-patch.ts      Forces preserveDrawingBuffer on WebGL contexts (runs first in bundle)
    config.ts           CRTConfig interface + CONFIG defaults
    colors.ts           Color math: h2a, a2h, hslToRgb, computePhosphorColors, makePhosphorTheme
    profiles.ts         PhosphorProfile type, profiles[], profileFromHue(), computeColors()
    xterm.ts            Window type augmentation for window.term/tty_options, applyXtermTheme()
    state.ts            Preact signals (profileIdxSig, customActiveSig, etc.) + imperative state
    apply.ts            applyProfile(), updateMenuTheme() — DOM and xterm side effects
    effectControls.ts   Imperative handle map for framesize→radius coupling
    dom.ts              Bezel clip, static overlays, ResizeObserver, MutationObserver
    effects/
      defs.ts           Typed EffectDef[] — one entry per slider with its apply() function
      bloom.ts          Canvas bloom pipeline (setup, resize, tick)
      noise.ts          SVG feTurbulence seed animation
      jitter.ts         Random pixel offset loop
      curve.ts          Barrel-distortion displacement map
    components/
      Menu.tsx          Root menu component (open/close, click-outside)
      ProfileSelector.tsx   Profile cycling and custom checkbox
      EffectSlider.tsx  Per-effect row: label, ON/OFF toggle, value readout, range slider
      ColorPicker.tsx   Hue wheel canvas with mouse/touch dragging
    main.tsx            Entry point: init sequence, render <Menu />, start animation loops
```

To build locally (requires Docker if npm is not installed):

```bash
docker run --rm -v "$(pwd)/res/crt:/app" -w /app node:lts-alpine npm run build
```

## Tech stack rationale

### TypeScript

The original implementation was ~600 lines of ES5-style JavaScript in a single `<script>` block with no type checking. The xterm.js integration (`window.term`, `window.tty_options`) is especially prone to silent runtime failures — wrong property names or stale theme shapes fail without any error. TypeScript makes these catchable at build time, and makes the codebase significantly easier to navigate and refactor.

TypeScript is compiled away entirely by esbuild; it adds zero runtime cost and the browser still receives plain JavaScript.

### esbuild

esbuild was chosen as the bundler because:

- It handles TypeScript natively — no separate `tsc` emit step required.
- Build times are sub-100 ms, which keeps the Docker layer fast.
- It outputs a single minified IIFE with `--format=iife`, which can be inlined directly as a `<script>` tag — exactly what the injection mechanism requires.
- It is a single static binary with no complex configuration.

webpack and Rollup were considered but rejected as slower and more complex for a project of this size.

### Preact

ttyd already bundles Preact internally for its own UI. Preact was chosen (over React, Vue, or Svelte) for the settings menu for three reasons:

1. **Alignment with the host page** — using the same framework as ttyd avoids shipping two competing virtual DOM runtimes in the same page.
2. **Size** — Preact is ~3 KB minified + gzipped. The entire overlay bundle (including Preact, signals, and all component code) stays small enough to inline as a `<script>` tag without impacting page load.
3. **Fitness for the problem** — the settings menu is a natural fit for a reactive component tree. The original implementation was ~300 lines of imperative `document.createElement` and manual DOM patching, which Preact components replace with a declarative structure that is easier to follow and extend.

The canvas-based effects (bloom, noise, jitter, curvature) remain entirely imperative — Preact adds nothing there — so only the menu UI was migrated to components.

### Preact Signals

`@preact/signals` was added alongside Preact because shared state (active profile index, custom mode, custom hue, contrast level) needs to be readable from two different contexts:

- **Preact components** — for re-rendering the menu when state changes.
- **Imperative animation loops** — `tickBloom` reads the current profile on every frame to tint the bloom canvas correctly.

Signals satisfy both: inside a component, reading `.value` automatically subscribes the component and re-renders it on change; outside a component (in the bloom loop or jitter scheduler), `.value` is a plain synchronous read with no overhead. This avoids prop drilling and keeps the animation loop code free of React/Preact lifecycle concerns.

---

## Maintainer notes

Non-obvious constraints and gotchas discovered during development. Read before making changes.

### webgl-patch must be the first module evaluated

`src/webgl-patch.ts` monkey-patches `HTMLCanvasElement.prototype.getContext` to force `preserveDrawingBuffer: true` on all WebGL contexts. This must run before xterm.js initialises its WebGL renderer, otherwise the bloom canvas cannot read back pixels via `drawImage`.

esbuild evaluates bundled modules in dependency-tree order. `webgl-patch.ts` has no imports of its own, so importing it as the **first** line in `main.tsx` guarantees it lands first in the IIFE output. Do not move that import or add imports above it.

The bundle uses `--format=iife`, which means the entire output is a synchronous immediately-invoked function. The script tag is injected before `</body>`, so the DOM is ready but ttyd's async xterm initialisation has not yet run — exactly the window the patch needs.

### package-lock.json must be committed

The `crt-build` Dockerfile stage runs `npm ci`, which requires a `package-lock.json` to exist. If you add or update a dependency, regenerate the lockfile and commit it. Without npm installed locally, use Docker:

```bash
docker run --rm -v "$(pwd)/res/crt:/app" -w /app node:lts-alpine npm install
```

### menuThemeStyle must be appended to document.body

`updateMenuTheme` in `apply.ts` rewrites a `<style>` element to apply the active phosphor colour to all menu elements. This element **must** be appended to `document.body`, not `document.head`.

The static `<style id="crt-styles">` block is part of `res/crt.html`, which is injected before `</body>` and therefore lands in the body. CSS resolves equal-specificity rules in document order — later wins. A `<head>`-appended style appears *before* the body stylesheet and loses the cascade, leaving all menu elements uncoloured (they fall back to `rgba(var(--crt-menu-rgb), ...)` where `--crt-menu-rgb` is undefined).

### ColorPicker canvas must be redrawn directly in the event handler

The hue wheel indicator must be redrawn by calling `drawHueWheel` directly inside `pick()`, not by relying on a Preact re-render + `useEffect`.

The `mousemove` listener is registered on `document` via a `useEffect` with `[]`, making it external to Preact's event system. When `pick` sets `customHueSig.value`, Preact may defer the component re-render rather than doing it synchronously, causing the indicator to lag or appear frozen during a drag. Calling `drawHueWheel(canvasRef.current, hue)` immediately inside `pick` gives frame-accurate feedback regardless of when Preact schedules the re-render.

### Screen curvature is silently non-functional without the SVG id

`buildCurveMap` in `effects/curve.ts` looks up the `<feDisplacementMap>` element by `id="crt-curve-displace"`. This id **does not currently exist** in `res/crt.html` — the element has no id attribute. As a result, `buildCurveMap` detects the null reference and returns early without enabling the filter. The curvature slider moves but has no visual effect.

To fix: add `id="crt-curve-displace"` to the `<feDisplacementMap>` element inside `#crt-curve-filter` in `res/crt.html`. The JS logic is correct and will work once the element is reachable.

### Adding effects

1. Add a new `EffectDef` entry to `effects/defs.ts` with an `id`, `label`, `default`, and `apply(v)` function.
2. Add the corresponding default to `CONFIG` in `config.ts`.
3. If the effect needs persistent animation (like bloom or noise), add a start function and call it from `main.tsx`.
4. The `EffectSlider` component renders all entries in `effectDefs` automatically — no component changes required for a standard slider effect.

### Extending the tech stack

The injection constraint is that everything must be deliverable as content injected before `</body>`. This rules out separate JS files unless a reverse proxy (nginx, Caddy) is placed in front of ttyd. Within the single-bundle constraint:

- **Additional npm packages** — add to `res/crt/package.json`, regenerate the lockfile, commit.
- **CSS preprocessors** (SCSS, Less) — add a build step to the esbuild command; compiled CSS can be injected alongside the JS bundle in the Dockerfile Python step.
- **Backend framework** (Express, FastAPI, etc.) — not possible without restructuring the container to run a second process and proxy through it. The only server is ttyd.

---

## Effects

A CSS `filter` chain is applied to `.xterm` (the xterm.js root element):

```css
.xterm {
  filter: sepia(1) saturate(5) hue-rotate(5deg) brightness(1.15) contrast(1.08);
}
```

`sepia(1)` converts all terminal colours to warm brown tones. `saturate(5)` pushes those tones into a vivid amber. The `brightness` and `contrast` nudges fine-tune the final look. The filter is driven by the `--crt-filter` CSS variable so the profile switcher can change it at runtime.

**Tuning knobs** (in the `profiles` array in the JS):
- `hue-rotate(Ndeg)` — shifts the phosphor hue; 5° = amber, 80° = green, 95° = apple-green
- `saturate(N)` — phosphor vividness; higher = more colourful
- `brightness(N)` / `contrast(N)` — overall brightness and punch

---

### Scanlines

A `repeating-linear-gradient` on `#crt-overlay::before` draws a 1 px transparent / 1 px dark stripe pattern every 4 px, simulating the space between CRT phosphor rows.

```css
background: repeating-linear-gradient(
  180deg,
  transparent                       0px,
  transparent                       2px,
  rgba(0,0,0,var(--crt-scanlines))  2px,
  rgba(0,0,0,var(--crt-scanlines))  4px
);
```

**Tuning:** `--crt-scanlines` (default `0.125` at `CONFIG.scanlines = 25`, mapping `0–100%` to `0–0.5`) — opacity of the dark stripe. Higher = more pronounced lines.

---

### Film-grain noise

An SVG `feTurbulence` filter generates fractal noise. Its `seed` attribute is incremented every ~80 ms by a JS timer, animating the grain frame by frame.

The noise SVG must **not** be `display:none` — browsers refuse to resolve `url(#id)` filter references into hidden elements. It is kept invisible via `width:0; height:0; overflow:hidden`.

The rendered noise is overlaid as a full-viewport SVG rect with `mix-blend-mode: screen` so it only brightens, never darkens, the terminal. The noise SVG is an `<svg>` element, not a `<div>`, so adblock filters targeting `div[id^="crt-"][style]` do not affect it and inline style is safe to set directly.

**Tuning:** `opacity` on `#crt-noise-svg` (default `0.08` at `CONFIG.noise = 15`, mapping `0–100%` to `0–0.53`). `baseFrequency` on `feTurbulence` (currently `0.75`) — higher = finer grain.

---

### Bloom

Simulates the soft phosphor glow that bleeds outward from bright pixels on a real CRT. This implementation is decoupled from the user's contrast slider, ensuring consistent bloom thickness and color across all settings.

**Architecture:** xterm.js uses a WebGL renderer whose framebuffer is discarded after each composite (`preserveDrawingBuffer: false` by default). To read pixels, `HTMLCanvasElement.prototype.getContext` is monkey-patched at the top of the script — before xterm.js initialises its renderer — to force `preserveDrawingBuffer: true` on every WebGL context.

A three-canvas pipeline runs at ~20 fps:

1. **Composite pass** — all xterm.js canvas layers are drawn onto an offscreen `tmp` canvas at ½ resolution (`SCALE = 0.50`). Half-resolution keeps JS compositing cheap while avoiding sub-pixel aliasing issues.
2. **Normalisation pass** — a `blur(1px)` filter is applied to an intermediate `extract` canvas. This minimal blur smooths glyph edges slightly while preserving the high peak intensity required for a stable threshold.
3. **Threshold & Colorize pass** — the bloom mask is generated and colorised on the `#crt-bloom-canvas`:
   - **Adaptive Brightness**: JS calculates a `_brt` gain based on the current contrast-adjusted background color. It targets the background to land at ~0.47 intensity, ensuring the subsequent `contrast(12)` filter (which has a 0.5 threshold) crushes it to absolute black.
   - **Luminance-Safe Masking**: A filter chain of `grayscale(1) brightness(adaptive) contrast(12)` is applied. `grayscale(1)` is critical: it averages color channels before the high-gain brightness is applied, preventing individual channels (like the red in amber text) from clipping and causing hue shifts or "red flashes" during slider adjustments.
   - **In-Canvas Colorisation**: The resulting binary mask (white text on a black background) is colorised using `globalCompositeOperation = 'multiply'` with the profile's `menuRgb`. This decouples the bloom color from the screen's internal colors.

The colorised mask is then processed by a CSS `filter: blur(40px)` on the `#crt-bloom-canvas` element, which spreads the sharp mask into soft gradient halos. The wrapper div `#crt-bloom` carries `mix-blend-mode: screen` to blend the halos onto the display. Because the background was crushed to absolute black in Pass 3, it contributes nothing to the screen blend, keeping the bloom perfectly localised to text regions.

**Tuning:**
- `opacity` on `#crt-bloom` — overall bloom strength; slider maps `0–100%` to `0–1.0`.
- `blur(40px)` in CSS — halo spread radius.
- `contrast(12)` in Pass 3 — binary mask sharpness.
- `_brt` gain range (currently `1.0–15.0`) — stability threshold for low-contrast settings.

---

### Glow line

Simulates the faint bright horizontal band produced by the CRT electron beam sweeping from top to bottom. A `position: fixed` div with a multi-stop vertical `linear-gradient` and a CSS animation translates it from −220 px (above the viewport) to `100vh` over 8 seconds, then repeats.

The glow line is appended to `document.body` (not `#terminal-container`) by `setupOverlays`, placing it above the WebGL compositor layer that would promote above the terminal container's stacking context on HTTPS pages. Clipping comes from z-index ordering, not overflow.

`mix-blend-mode: screen` ensures it only brightens. Gradient stop colours use `rgba(var(--crt-glow-rgb), ...)` to match the active phosphor tint. The gradient has a tapered leading edge and a short bright peak near the bottom of the element:

```
0%   → 0 opacity
45%  → 0.02
72%  → 0.06
86%  → 0.12
95%  → 0.25  ← peak (leading edge of beam)
98%  → 0.06
100% → 0
```

Opacity is driven by `--crt-glow-opacity` (set via the slider) so no inline style is placed on the element — adblock filters targeting `div[id^="crt-"][style]` skip it.

**Tuning:**
- Animation duration (`8s`) — slower = more gentle sweep
- Peak stop opacity (`0.25` at 95%) — brightness of the beam at its leading edge
- Element height (`220px`) — length of the trailing glow

---

### Horizontal jitter

Occasionally shifts the entire terminal container a few pixels in both X and Y, simulating analogue signal instability. Unlike earlier versions, this does not use a CSS class or keyframe animation.

`scheduleJitter()` fires a random interval whose gap scales inversely with `jitterStrength` (range: roughly 300 ms at 100% to 15 s at 0%). Each trigger runs 5 frames at 30 ms intervals, writing randomised `--crt-jitter-x` and `--crt-jitter-y` CSS variables directly onto `#terminal-container`. The element's `transform: translate(var(--crt-jitter-x, 0), var(--crt-jitter-y, 0))` picks these up without any animation layer. After 5 frames both vars are reset to `0px`.

At `jitterStrength = 0` the interval is set to 60 s and no displacement is applied, effectively disabling the effect without cancelling the timer.

**Tuning:**
- `(100 - jitterStrength) * 150 + random * (100 - jitterStrength) * 100` — interval formula (ms)
- `jitterStrength / 100 * 5` — amplitude (`amp`) of each frame's random displacement in px
- `5 frames × 30 ms` — duration of each jitter burst

---

### Screen flicker

A CSS `steps(1)` animation on `#terminal-container` occasionally dips `opacity` slightly, simulating the mains-frequency flicker of a real CRT.

```css
@keyframes crt-flicker {
  0%,92%,100% { opacity: 1; }
  93%  { opacity: calc(1 - var(--crt-flicker-amt) * 0.50); }
  94%  { opacity: 1; }
  95%  { opacity: calc(1 - var(--crt-flicker-amt)); }
  96%  { opacity: calc(1 - var(--crt-flicker-amt) * 0.25); }
  97%  { opacity: 1; }
  98%  { opacity: calc(1 - var(--crt-flicker-amt) * 0.75); }
  99%  { opacity: 1; }
}
#terminal-container { animation: crt-flicker 10s steps(1) infinite; }
```

`steps(1)` makes each opacity change instantaneous rather than eased, matching the hard on/off character of real power-line flicker. All dip depths are proportional to `--crt-flicker-amt` (set by the slider: `0–100%` maps to `0–0.8`) so a single variable controls intensity without rewriting keyframe values. When the effect is toggled off, `animationPlayState` is set to `paused` rather than removing the animation.

**Tuning:** `--crt-flicker-amt` (default `0.08` at `CONFIG.flicker = 10`). Extend the cycle from `10s` to reduce frequency.

---

### Power-on sweep

On page load, `#terminal-container` receives the class `crt-boot` which plays a `clip-path` animation that expands the visible area from a thin horizontal line at the centre outward to the full screen, while `filter: brightness(N)` fades the initial flash down to normal. This mimics the warm-up behaviour of a CRT monitor.

```css
@keyframes crt-poweron {
  0%   { clip-path: inset(49.6% 0 49.6% 0); filter: brightness(4);   }
  25%  { clip-path: inset(20%   0 20%   0); filter: brightness(3);   }
  65%  { clip-path: inset(0%    0 0%    0); filter: brightness(1.4); }
  100% { clip-path: inset(0%    0 0%    0); }
}
```

The final keyframe has no `filter` property. Leaving `filter: brightness(1)` on the last frame would permanently lock a filter stacking context onto `#terminal-container`, corrupting the semi-transparent compositing of later overlays.

The class is added inside `applyXtermTheme`'s callback, which fires only after the phosphor theme is confirmed painted (double `requestAnimationFrame`). This ensures the boot animation reveals an already-coloured terminal rather than flashing the browser default colours. The flicker animation runs concurrently via a combined `animation` property on `.crt-boot`: `crt-poweron 0.7s ... forwards, crt-flicker 10s 0.7s steps(1) infinite`.

**Tuning:** Animation duration (`0.7s`) and the `brightness` values at each keyframe.

---

### Frame size

Adds a bezel around the edges of the screen, simulating the plastic casing of a computer monitor. The frame has square outer corners (flush with the viewport) and rounded inner corners (matching the glass curvature).

**Architecture:** Two CSS variables are driven in lockstep by a single slider:

- `--crt-frame-px` — the visual width of the bezel (border thickness).
- `--crt-margin-px` — the inset of `#terminal-container` from the viewport edges. Set equal to `--crt-frame-px` so the terminal content sits exactly inside the frame.

`#terminal-container` uses `position: fixed; inset: var(--crt-margin-px)` (not padding) to physically shrink the element from all four viewport edges. This ensures xterm.js receives a correct container size and nothing is clipped.

**Bezel rendering:** A `#crt-bezel` div (`position: fixed; inset: 0; background: #1a1a1a`) is clipped by an SVG `clipPath` (`#bezel-clip`) using the `evenodd` fill rule. The path contains two sub-paths:

1. A full-viewport rectangle (outer boundary — opaque, square corners).
2. A rounded rectangle matching the terminal area (inner boundary — evenodd cancels this to transparent, creating a rounded hole).

The `updateBezelClip()` JS function recomputes the SVG path whenever frame size, radius, or window dimensions change. The viewport naturally clips the outer rectangle's corners square.

**Depth:** An `inset 0 0 15px rgba(0,0,0,0.85)` box-shadow on `#terminal-container` simulates the shadow the bezel casts onto the recessed glass.

**Tuning:**
- `--crt-frame-px` (default `12px` via `10%`) — width of the plastic bezel.
- `0 0 0 120` — slider maps `0–100%` to `0–120px` for both frame and margin.

---

### Rounded frame

A toggle (no slider) that controls the corner rounding of the terminal glass and the bezel's inner edge via `--crt-radius-px`.

- **ON** (default): `20%` → `16px` radius. `#terminal-container` clips its content to rounded corners via `border-radius` + `overflow: hidden`. The SVG bezel clip path's inner rounded rectangle uses the same radius, so the frame's inner edge matches the glass curve.
- **OFF**: `0%` → `0px`. Both the glass and the frame inner edge are square.

`updateBezelClip()` is called on every toggle so the SVG path updates immediately.

---

### Phosphor profile switcher

A collapsible settings menu (`[ CRT ]` button, bottom-right) contains a profile row with `◄` / `►` arrows that cycle through four phosphor profiles. Each profile sets `--crt-bg`, `--crt-filter`, the bloom tint filter, and regenerates the menu theme styles.

| Profile | Raw fg hex | Based on |
|---------|------------|----------|
| GREEN   | `#1aff80` | P1/P31 phosphor |
| AMBER   | `#ffb642` | P3 phosphor (vintage monochrome) |
| BLUE    | `#7fb4ff` | Specialized data display |
| WHITE   | `#c5ffff` (bg `#0f1414`) | High-contrast reading mode |

Each profile entry in the `profiles` array carries `rawFg`, `rawBg`, `satColor`, and a `menuRgb` field (e.g. `'26, 255, 128'`) that `updateMenuTheme()` uses to colour the menu. The actual rendered `fg`/`bg` colours are computed at runtime by `computePhosphorColors()` so they track the contrast slider.

#### Custom profile

A **CUSTOM** checkbox in the profile section activates a custom phosphor colour. When checked:

- The `◄`/`►` arrows are disabled (opacity `0.20`).
- A hue wheel canvas (`#crt-hue-wheel`) appears beneath the section header.
- Dragging on the wheel calls `applyCustomHue(hue)`, which derives `rawFg` from `hslToRgb(hue, 100, 60)`, updates `customProfile`, and calls `applyProfile(customProfile)`.

Unchecking restores `profiles[profileIdx]` and hides the wheel.

#### Phosphor colour formula

The rendered fg/bg colours replicate the formula from cool-retro-term `ApplicationSettings.qml`:

```
saturatedColor = mix(rawFg, white, satColor × 0.5)
fgRendered     = mix(rawBg, saturatedColor, 0.7 + contrast × 0.3)
bgRendered     = mix(saturatedColor, rawBg, 0.7 + contrast × 0.3)
```

This means both fg and bg shift with the contrast slider: higher contrast moves fg toward the saturated phosphor colour and bg toward black.

#### Phosphor palette (`makePhosphorTheme`)

Generates a monochrome 16-colour xterm theme tinted to the profile. Each ANSI slot maps to a `lerp(t)` between `bgHex` (off) and `fgHex` (full-bright), at brightness levels chosen to preserve visual differentiation of ANSI colours while maintaining the phosphor monochrome look.

---

### Screen curvature

Simulates the convex glass surface of a CRT monitor. The terminal content is barrel-distorted so the centre appears flat and the edges/corners curve away, with the extreme corners going black as they pass behind the bezel.

**Architecture:** An SVG `feDisplacementMap` filter (`#crt-curve-filter`) is applied to `#terminal-container` via the `--crt-curve-filter` CSS variable. The displacement map is a 128×128 `<canvas>` whose R and G channels encode the per-pixel x/y displacements respectively, with 0.5 as the neutral (no-displacement) value.

The displacement formula is a direct port of cool-retro-term's `distortCoordinates()` function in `terminal_static.frag`:

```
cc   = UV - (0.5, 0.5)               // center-relative UV
dist = dot(cc, cc) × k               // k = curvature strength
disp_uv = cc × (1 + dist) × dist     // UV displacement
disp_px  = disp_uv × (W, H)          // convert to pixels for this terminal size
```

The canvas is generated by `buildCurveMap(k)` (called on slider change and every resize). The `feDisplacementMap scale` attribute is set to `max(W, H)` pixels so the R/G values encode displacement as a fraction of the largest terminal dimension. The filter region is limited to the element's bounding box (`x="0%" y="0%" width="100%" height="100%"`) so displaced pixels that sample outside the source (at the curved edges) show transparent, revealing the CRT background colour through the bezel.

The effect is applied to `#terminal-container` so it distorts the entire xterm output. The bloom overlay (on `body`) is not distorted; at default strength the misalignment is sub-pixel for most content.

**Tuning:**
- Slider maps 0–100% to curvature `k` 0–0.4 (matches cool-retro-term's effective range after its `screenCurvatureSize × 0.6` scale factor).
- Default: 20% → `k = 0.08` — subtle, similar to a cool-retro-term value of ~0.13.
- `N = 128` — displacement map resolution; higher = smoother but slower to generate.

---

### Centralized Configuration

All project-wide CRT defaults are managed via the `CONFIG` object in `res/crt/src/config.ts`. It acts as the single source of truth for:

- `profileIdx` — Default active phosphor profile.
- `bloom`, `glowline`, `scanlines`, etc. — Default effect intensities (0–100%).
- `contrast` — Default contrast level.

`main.tsx` reads `CONFIG` to initialize CSS variables, the xterm theme, and all effect `apply()` functions synchronously on load, before the first paint.

---

### Settings menu

The `[ CRT ]` button in the bottom-right corner opens a collapsible panel built as a Preact component tree (`src/components/`). The panel contains:

- **Profile row** — `◄` / `►` buttons to cycle phosphor profiles, a CUSTOM checkbox, and (when custom is active) a hue wheel canvas.
- **Effects section** — one row per effect rendered by `EffectSlider`. Standard effects show a label, an ON/OFF toggle, a live percentage readout, and a range slider (0–100%). Effects marked `toggleOnly: true` in `effectDefs` show only a label and toggle — no slider or readout.

Sliders map to CSS custom properties or element styles via `apply(v)` functions in `effects/defs.ts`. The toggle saves the last slider value and passes `0` to `apply` when turning an effect off. For `toggleOnly` effects the saved value is the fixed `default` (e.g. `20` for Rounded Frame).

Global UI state (active profile index, custom mode, custom hue) is held in Preact signals defined in `state.ts`, making it accessible to both the component tree and the imperative effect modules.

---

### Menu theme colouring

All menu colours track the active phosphor profile. Because CSS custom properties can stale-cache their resolved values when updated via JavaScript, the menu does **not** use `var()` references for colours. Instead, `updateMenuTheme(rgb)` in `apply.ts` rewrites a dedicated `<style>` element (`menuThemeStyle`) appended to `<body>` on every profile change, injecting rules with hardcoded `rgba(r,g,b,alpha)` values:

```typescript
function updateMenuTheme(rgb: string): void {
  menuThemeStyle.textContent =
    `#crt-menu-btn{color:rgba(${rgb},0.80); ...}` +
    `.crt-slider::-webkit-slider-thumb{background:rgba(${rgb},0.85);}` +
    // …all other menu selectors including pseudo-elements
}
```

The style element must be appended to `<body>` (not `<head>`). The static `<style id="crt-styles">` block is part of `res/crt.html`, which is injected before `</body>` and therefore also lands in the body. CSS processes stylesheets in document order — later wins at equal specificity — so `menuThemeStyle` must appear after `#crt-styles` to override it. A `<head>`-appended style would lose the cascade and leave all menu elements uncoloured.

The static `#crt-styles` block references `var(--crt-menu-rgb)` for base menu colours as a fallback. The dynamic `menuThemeStyle` element overrides these with hardcoded `rgba()` values, which also covers pseudo-elements such as `::webkit-slider-thumb` that cannot be set via inline styles.

Profile arrow buttons (`◄`/`►`) use CSS `opacity` (0.6 at rest, 1 on hover via `.crt-menu-profile button:hover`) for the dim/bright hover effect, keeping hover feedback purely in CSS with no JS state tracking.

---

## Z-index stack

| Layer | Element | z-index |
|-------|---------|---------|
| Bloom | `#crt-bloom` | 9100 |
| Noise | `#crt-noise-svg` | 9101 |
| Scanlines / overlay | `#crt-overlay` | 9102 |
| Glow line | `#crt-glow-line` | 9103 |
| Bezel / Frame | `#crt-bezel` | 9110 |
| Settings menu | `#crt-menu` | 9200 |

---

## Local testing

```bash
.github/workflows/scripts/run.sh
```

Prerequisites: `docker` (daemon running), `docker buildx`. The script:

1. Runs `docker buildx build` with `Dockerfile.prod` as the build file (repo root as context)
2. The `crt-build` stage compiles the TypeScript overlay (`npm ci && npm run build`)
3. The `ttyd-html` stage captures ttyd's upstream `index.html`, patches the favicon, and injects the compiled CRT overlay
4. The final image is tagged `ddd-local:latest` and run as a container serving on `http://localhost:7681`
5. Cleans up the container and image on exit via a `trap`

## Production deployment

On every tag push, the `Publish` job in `.github/workflows/release.yml`:

1. Runs `docker/build-push-action` with `Dockerfile.prod` (same build as local testing)
2. The `crt-build` stage compiles `res/crt/` TypeScript source via esbuild
3. The `ttyd-html` stage injects `res/crt.html` (static) + the compiled bundle before `</body>`
4. Builds a multi-arch Docker image (`linux/amd64`, `linux/arm64`) and pushes it to `images.cloudisms.dev`
