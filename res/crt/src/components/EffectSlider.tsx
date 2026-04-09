import { h } from 'preact';
import { useState, useEffect, useRef } from 'preact/hooks';
import { EffectDef } from '../effects/defs';
import {
  effectControls,
  frameSizeRadiusWasOn,
  setFrameSizeRadiusWasOn,
} from '../effectControls';

interface Props {
  def: EffectDef;
}

export function EffectSlider({ def }: Props) {
  const [enabled,  setEnabled]  = useState(true);
  const [value,    setValue]    = useState(def.default);
  const savedValue = useRef(def.default);

  /* Register imperative handle so other sliders (framesize → radius) can
     programmatically toggle this one. */
  useEffect(() => {
    effectControls.set(def.id, {
      isOn:    () => enabled,
      turnOn:  () => { if (!enabled) toggle(false); },
      turnOff: () => { if (enabled)  toggle(true);  },
    });
  }, [enabled]);

  /* Unregister on unmount. */
  useEffect(() => () => { effectControls.delete(def.id); }, []);

  function toggle(currentlyEnabled: boolean) {
    if (currentlyEnabled) {
      /* Turning off: save current value, apply 0. */
      savedValue.current = value;
      setEnabled(false);
      def.apply(0);
      if (def.id === 'framesize') {
        setFrameSizeRadiusWasOn(effectControls.get('radius')?.isOn() ?? true);
        effectControls.get('radius')?.turnOff();
      }
    } else {
      /* Turning on: restore saved value. */
      setEnabled(true);
      setValue(savedValue.current);
      def.apply(savedValue.current);
      if (def.id === 'framesize' && frameSizeRadiusWasOn) {
        effectControls.get('radius')?.turnOn();
      }
    }
  }

  return (
    <div class="crt-effect-row">
      <div class={`crt-effect-header${enabled ? '' : ' dim'}`}>
        <span class="crt-effect-label">{def.label}</span>
        {!def.toggleOnly && (
          <span class="crt-effect-value">{value}%</span>
        )}
        <button
          class={`crt-effect-toggle${enabled ? '' : ' off'}`}
          onClick={() => toggle(enabled)}
        >
          {enabled ? 'ON' : 'OFF'}
        </button>
      </div>
      {!def.toggleOnly && (
        <input
          type="range"
          class="crt-slider"
          min="0"
          max="100"
          value={value}
          disabled={!enabled}
          onInput={e => {
            const v = parseInt((e.target as HTMLInputElement).value, 10);
            setValue(v);
            def.apply(v);
          }}
        />
      )}
    </div>
  );
}
