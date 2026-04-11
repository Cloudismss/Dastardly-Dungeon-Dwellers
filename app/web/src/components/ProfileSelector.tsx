import { h } from 'preact';
import { profileIdxSig, customActiveSig, customHueSig } from '../state';
import { profiles, profileFromHue } from '../profiles';
import { applyProfile } from '../apply';
import { ColorPicker } from './ColorPicker';

export function ProfileSelector() {
  const idx    = profileIdxSig.value;
  const custom = customActiveSig.value;

  function prevProfile() {
    profileIdxSig.value = (idx - 1 + profiles.length) % profiles.length;
    applyProfile(profiles[profileIdxSig.value]);
  }

  function nextProfile() {
    profileIdxSig.value = (idx + 1) % profiles.length;
    applyProfile(profiles[profileIdxSig.value]);
  }

  function onCustomChange(e: Event) {
    const checked = (e.target as HTMLInputElement).checked;
    customActiveSig.value = checked;
    applyProfile(
      checked ? profileFromHue(customHueSig.value) : profiles[profileIdxSig.value]
    );
  }

  return (
    <>
      <div id="crt-prof-section" class="crt-menu-section">
        <span>PROFILE</span>
        <label id="crt-custom-toggle">
          <input
            type="checkbox"
            id="crt-custom-cb"
            checked={custom}
            onChange={onCustomChange}
          />
          <span>CUSTOM</span>
        </label>
      </div>

      {custom && <ColorPicker />}

      <div class="crt-menu-profile">
        <button disabled={custom} style={custom ? 'opacity:0.20' : ''} onClick={prevProfile}>
          ◄
        </button>
        <span id="crt-profile-label">
          {custom ? 'CUSTOM' : profiles[idx].name}
        </span>
        <button disabled={custom} style={custom ? 'opacity:0.20' : ''} onClick={nextProfile}>
          ►
        </button>
      </div>
    </>
  );
}
