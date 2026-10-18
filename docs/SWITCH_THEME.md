# Embedded Switch theme

This local adaptation of `patrickisaway/ProsperoEden` uses the current ProsperoEden
v1.005.000 source as its application base. The fork's earlier `switch-theme` branch was
based on v1.001.000, which did not have the host API required by the full
[SwitchLauncher](https://github.com/kasobos67/SwitchLauncher) presentation.

Choose **Settings > Appearance > Theme > Switch**. The choice is stored in the existing
`launcher.theme` preference. The built-in runtime then reads `ui/switch/main.lua` and
its resources from the application package. No folder under
`/data/prosperoeden/launchers` is needed. Canopy and Slate remain available native themes.

The embedded script is SwitchLauncher v1.004.002's `motion.lua` followed by `ui.lua`,
with six integration edits: replace its version placeholder, disable its separate launcher
updater, disable the now-inert update buttons, show the installed theme status in About,
and correct the application update message.
All screen drawing, navigation,
animations, white/black appearances, avatar selection, menus and loading art remain in
the original script. The theme's own white/black appearance and avatar choices are kept
in `/data/prosperoeden/config/launcher-state/switch-theme.json`.

The theme files belong under `headless/prosperoeden/ui/switch`; the packaging script copies
the entire `ui` folder. **They are not in this repository:** their artwork, font and recordings
are Nintendo's, so they stay on the builder's machine. A build without them still runs: choosing
Switch then falls back to the native Canopy theme. Copy the folder into `PPSA99008/ui/switch` of
the built package (or into `headless/prosperoeden/ui/switch` before packaging). `ui/switch/ASSET_NOTICES.md` retains the original resource
ownership notice. Theme selection does not connect to the SwitchLauncher update feed.

To build the PS5 application, use the repository's Linux toolchain (`make package`).
The static resource check is `python3 tools/launcher/check-embedded-switch.py`. The
Lua screen smoke test is
`lua tools/launcher/test-embedded-switch.lua headless/prosperoeden/ui/switch` and
exercises HOME, Library, About and Settings in both appearances. The
source archive alone is not an installable PS5 package; a native build and console
validation are still required.
