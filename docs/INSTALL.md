# Game files, app data and updates

Where ProsperoEden looks for your keys, firmware and games, where it keeps its own data, and how it is updated. The install steps themselves are in the [README](../README.md#install).

## Game files folder

Only these subfolders matter; the folder itself can have any name and location.

```text
<game files folder>/                    # e.g. /data/prosperoeden, /mnt/ext1/eden, /mnt/usb0/eden
├── keys/
│   ├── prod.keys
│   └── title.keys                      # optional
├── firmware/
│   └── *.nca                           # extracted firmware NCAs
├── roms/
│   └── <Game>/                         # one folder per game
│       ├── <game>.nsp                  # the game (NSP or XCI)
│       ├── <game> update.nsp           # optional: its update and DLC files, beside it
│       ├── <game> DLC.nsp
│       ├── mods/                       # optional: its mods, one folder each (see Mods and cheats)
│       │   └── <mod name>/
│       │       ├── exefs/              # code patches: *.pchtxt, *.ips
│       │       ├── romfs/              # replacement game files
│       │       └── romfs_ext/          # files added to the game's own
│       ├── cheats/                     # optional: its cheats
│       │   └── <build ID>.txt          # one file per version of the game
│       └── reshade/                    # optional: its post-processing presets and effects
│           ├── <preset>.fxp            # offered in this game's settings
│           └── <effect>.fx             # and the .fxh files and Textures/ they use
├── save-import/                        # optional: saves to import, one folder per title ID
├── ryujinx/                            # optional: a Ryujinx data folder to import saves from
├── save-export/                        # written by "Export a copy"
└── .remote-downloads/                  # downloads that are not finished yet (see Download sources)
```

Each game sits in a folder of its own in `roms/`, with everything that belongs to it: its update and DLC files, its mods, its cheats and its post-processing presets. ProsperoEden tells the game from its update and DLC by what each file holds, not by its name, so the files can have any names. Folders inside a game folder are not searched for games, and folders whose names start with a dot are skipped. **Delete from console** also deletes the update and DLC files in the game's folder, and the folder once it is empty.

The folder browser shows how many keys, firmware files, and games each folder holds, so you can check a folder before selecting it. Moving your files later only needs a new selection in Settings; saved settings, covers, and recently played games carry over.

## App data

ProsperoEden keeps its own data in `/data/prosperoeden`, separately from the game files folder:

```text
/data/prosperoeden/
├── config/prosperoeden.json            # every profile's settings, and the game files folder
├── config/remote/                      # download sources and save sync, when you use them:
│   ├── sources.json                    #   the sources and how to reach them (written by you)
│   ├── queue.json                      #   the download queue
│   ├── <source>/catalog.json           #   each source's game list, kept for the next start
│   ├── save-sync.json                  #   where each profile syncs its save data (filled in by you)
│   └── save-sync/                      #   what the save sync keeps: the console as a device of
│                                       #   each profile's server, the games still to be synced
├── backup/save-sync/                   # save data the save sync replaced, the last three per game
├── covers/                             # cached game covers
├── logs/                               # current and previous session logs, crash reports
├── previous-version/PPSA99008-backup/  # the version the last self-update replaced
└── user/                               # every profile's saves, and emulator user data
    └── lossless/Lossless.dll           # optional: your copy, for frame generation
```

The app itself stays in `/data/homebrew/PPSA99008`; see [Updating](#updating).

ProsperoEden does not include keys, firmware, games, or other copyrighted console data. Dump these files from hardware and software you own. Do not download or redistribute them.

This is the only place it keeps them. If ProsperoEden cannot get access to the console's storage when it starts, the home screen says so and no game can be started; your data is untouched, and closing ProsperoEden and opening it again is the first thing to try. Earlier versions kept a second set of settings and saves in the app's own sandbox in that case, which made saves and settings seem to disappear on consoles where access came and went.

Keys, firmware and games that an early version kept inside the app's folder (`/data/homebrew/PPSA99008/assets`) are moved to `/data/prosperoeden` the first time this version starts, so that replacing the app cannot remove them.

## Updating this fork

The app checks [patrickisaway/ProsperoEden releases](https://github.com/patrickisaway/ProsperoEden/releases) when it starts. You can also press **Triangle** on the native About screen, or **Check GitHub updates** in the Switch About screen. This check uses only your fork; it never offers the Swordpdf/Homebrew catalog's build, which would remove the customized theme. If no release is published yet, the check shows no update.

The About screen shows a newer release, when one exists. Install it manually: close the app, download the release ZIP from your fork, then copy its `PPSA99008` folder **over** `/data/homebrew/PPSA99008` without deleting that folder first. This preserves `ui/switch/assets`, which is supplied locally and excluded from the repository. Check the release contents before copying. Reopen the app and confirm the version and Switch/OLED selection.

The in-app self-installer is deliberately unavailable for this fork until its release process can preserve the locally supplied Switch resources. GitHub Actions workflow artifacts are not published releases, and the app does not treat a source archive or workflow artifact as an installable update. Settings, saves, covers and logs remain under `/data/prosperoeden`.

## Upgrading from an earlier alpha

Earlier versions read everything from `/data/homebrew/PPSA99008/assets/`. That folder keeps working until you choose a game files folder, and settings are migrated automatically on first launch. To move to the new layout, move `assets/keys`, `assets/firmware` and `assets/roms` into any folder, then select it in **Settings > Game files**. The release ZIP contains no user files, so copy its app files over your installation without deleting your own data.
