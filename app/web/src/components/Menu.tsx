import { h } from 'preact';
import { useState, useEffect } from 'preact/hooks';
import { ProfileSelector } from './ProfileSelector';
import { EffectSlider } from './EffectSlider';
import { effectDefs } from '../effects/defs';

export function Menu() {
  const [open, setOpen] = useState(false);

  /* Close on any click outside the panel. */
  useEffect(() => {
    const close = () => setOpen(false);
    document.addEventListener('click', close);
    return () => document.removeEventListener('click', close);
  }, []);

  return (
    <div id="crt-menu">
      <div
        id="crt-menu-panel"
        class={open ? 'open' : ''}
        onClick={e => e.stopPropagation()}
      >
        <ProfileSelector />
        <div class="crt-menu-section">EFFECTS</div>
        {effectDefs.map(def => (
          <EffectSlider key={def.id} def={def} />
        ))}
      </div>

      <button
        id="crt-menu-btn"
        onClick={e => { e.stopPropagation(); setOpen(o => !o); }}
      >
        [ CRT ]
      </button>
    </div>
  );
}
