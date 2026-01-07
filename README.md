# Simple Unlock

A lightweight Geode mod for Geometry Dash that unlocks content and adds quality-of-life features.

## Features

### Unlocks
- **All Icons & Colors**: Access all icons across all gamemodes (cube, ship, ball, UFO, wave, robot, spider, swing) and all colors
- **Persistent Selections**: Your icon and color choices automatically save between sessions
- **Practice Music Sync**: Synchronized music during practice mode

### Quality of Life
- **Accurate Percentages**: Shows percentage with 10 decimal places (e.g., 99.8730000000%)
- **Auto-Save**: Automatically saves your progress when completing or quitting levels

## Installation

### Via Geode Mod Loader (Recommended)

1. Ensure you have [Geode](https://geode-sdk.org/) installed
2. Download the latest `.geode` file from releases
3. Place it in your mods folder:
   - **Windows**: `%LOCALAPPDATA%\GeometryDash\geode\mods`
   - **macOS**: `~/Library/Application Support/GeometryDash/geode/mods`
4. Restart Geometry Dash

### Manual Installation

Copy `max.simple-unlock.geode` to your Geometry Dash mods directory and restart the game.

## Usage

Once installed, all features work automatically:
- All icons and colors are immediately available
- Selected icons persist across game restarts
- Accurate percentages work on all levels (main, online, saved)
- Auto-save triggers when completing or quitting levels

No configuration required.

## Building from Source

Requires [Geode SDK](https://docs.geode-sdk.org/):

```bash
git clone https://github.com/wong-max-max/simple-unlock-mod
cd simple-unlock-mod
cmake -B build
cmake --build build --config Release
```

The built `.geode` file will be in the `build/` directory.

## Technical Details

This mod uses Geode's hooking system to:
- Override unlock checks for icons, colors, shops, and vaults
- Call `unlockIcon()` on startup to persist user choices
- Intercept coin collection in practice mode
- Enhance percentage display precision
- Trigger saves at appropriate times

All data is stored using Geode's built-in persistence API and GD's native save system.

## License

Created by Max. Free to use and modify.

## Support

For issues or questions, please open an issue on the [GitHub repository](https://github.com/wong-max-max/simple-unlock-mod).
