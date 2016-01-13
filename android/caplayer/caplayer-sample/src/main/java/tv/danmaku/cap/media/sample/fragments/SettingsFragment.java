

package tv.danmaku.cap.media.sample.fragments;

import android.os.Bundle;
import android.support.v7.preference.PreferenceFragmentCompat;

import tv.danmaku.cap.media.sample.R;

public class SettingsFragment extends PreferenceFragmentCompat {
    public static SettingsFragment newInstance() {
        SettingsFragment f = new SettingsFragment();
        return f;
    }

    @Override
    public void onCreatePreferences(Bundle bundle, String s) {
        addPreferencesFromResource(R.xml.settings);
    }
}
