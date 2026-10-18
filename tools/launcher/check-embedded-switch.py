#!/usr/bin/env python3
"""Check that the built-in Switch theme fits the launcher runtime's resource limits."""

from pathlib import Path
import json
import struct
import wave

root = Path(__file__).resolve().parents[2]
theme = root / "headless/prosperoeden/ui/switch"
manifest = json.loads((theme / "manifest.json").read_text(encoding="utf-8"))
assert manifest["schema"] == 1 and manifest["id"] == "switch-theme"
assert manifest["api"] == {"major": 1, "min_minor": 1}
assert manifest["host_contract"] == "launcher-v1.0"
assert "updates" not in manifest
assert "updates.launcher-packs.v1" not in manifest["required_capabilities"]
assert (theme / manifest["entry"]).stat().st_size < 2 * 1024 * 1024
assert (theme / manifest["font"]).stat().st_size < 16 * 1024 * 1024

decoded_images = 0
for relative in manifest["assets"].values():
    path = theme / relative
    header = path.read_bytes()[:18]
    width, height, depth = struct.unpack_from("<HHB", header, 12)
    assert header[1] == 0 and header[2] == 2 and depth in (24, 32), path
    assert 0 < width <= 4096 and 0 < height <= 8192, path
    decoded_images += width * height * 4
assert decoded_images < 96 * 1024 * 1024, decoded_images

scene = json.loads((theme / manifest["loading_scene"]).read_text(encoding="utf-8"))
assert (theme / scene["atlas"]).is_file()

decoded_audio = 0
sounds = list((theme / manifest["sounds"]).glob("*.wav"))
assert sounds
for path in sounds:
    with wave.open(str(path), "rb") as sound:
        assert sound.getframerate() == 48000 and sound.getsampwidth() == 2, path
        decoded_audio += sound.getnframes() * 2 * 4
assert decoded_audio < 32 * 1024 * 1024, decoded_audio

script = (theme / manifest["entry"]).read_text(encoding="utf-8")
assert "local LAUNCHER_UPDATES = false" in script
assert "@PACK_VERSION@" not in script
print(f"Embedded Switch: {len(manifest['assets'])} images, {len(sounds)} sounds, "
      f"{decoded_images // 1024 // 1024} MiB decoded images, "
      f"{decoded_audio // 1024 // 1024} MiB decoded audio: PASS")
