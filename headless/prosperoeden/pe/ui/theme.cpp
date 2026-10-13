// ProsperoEden - The launcher's themes, and which one is in use.
// Copyright (C) 2026 BlackBearReloaded
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pe/ui/theme.hpp"

#include "pe/core/strings.hpp"

#include <array>
#include <cstdint>

namespace pe::ui
{

namespace
{

Color rgb(std::uint32_t hex, float alpha = 1.0f)
{
    return Color::rgb(hex, alpha);
}

// Canopy: a tropical dusk, dark green glass and lime. ProsperoEden's own look, and the one a
// part missing from any other theme falls back to.
Theme canopy()
{
    Theme t;
    // The kit's frosted glass: translucent panels over the artwork, soft shadows, a ring of light
    // for the focus, movement that settles without a bounce.
    theme_from_kit("acrylic", &t);
    t.id = "canopy";
    t.name = "Canopy";
    t.summary = TR("Tropical dusk, dark green glass and lime.");

    t.base = rgb(0x06090a);
    t.scrim = rgb(0x010806);
    t.glass = rgb(0x16221d);
    t.panel = rgb(0x0b1713);
    t.panel_edge = rgb(0x768e75);
    t.row = rgb(0x17241e);
    t.row_edge = rgb(0x6a8267);
    t.row_focus = rgb(0x294433);

    t.accent = rgb(0xa9db63);
    t.accent_deep = rgb(0x245d4a);
    t.accent_pale = rgb(0xdfe8a6);
    t.on_accent = rgb(0x0b1713);
    t.highlight = rgb(0xffd76a);

    t.text = rgb(0xf0f5f2);
    t.title = rgb(0xfffcef);
    t.value = rgb(0xf2f4e9);
    t.body = rgb(0xe2e8d7);
    t.copy = rgb(0xc5d0bd);
    t.meta = rgb(0xb7c6b5);
    t.label = rgb(0xaebdaa);
    t.muted = rgb(0xaab8ac);
    t.faint = rgb(0x8c9e90);
    t.warning = rgb(0xe8b39a);
    t.rule = rgb(0x536b55);

    t.radius_row = 18.0f;
    t.radius_card = 22.0f;
    t.radius_panel = 30.0f;
    t.pill_chips = true;
    t.focus_width = 2.0f;
    t.focus_glow = 30.0f;
    t.glass_panels = true;

    t.focus_spring = 20.0f;
    t.cursor_spring = 26.0f;
    t.scroll_spring = 16.0f;

    t.backdrop = "backdrop.tga";
    t.backdrop_blur = "backdrop-blur.tga";
    t.brand = "brand.tga";
    t.light_x = 0.710f;
    t.light_y = 0.391f;
    t.motes = 26;
    t.drift = 1.0f;
    return t;
}

// Switch: the flat charcoal and blue of the Nintendo Switch's dark home menu. No artwork to speak
// of: one even grey, lighter grey plates, the blue of its highlight.
Theme nintendo_switch()
{
    Theme t;
    // The kit's flat tiles: no glass, no depth, square corners, a firm ring for the focus.
    theme_from_kit("tiles", &t);
    t.id = "switch";
    t.name = "Switch";
    t.summary = TR("Flat charcoal and blue, like the Switch's dark home menu.");

    t.base = rgb(0x313131);
    t.scrim = rgb(0x141414);
    t.glass = rgb(0x555555);
    t.panel = rgb(0x3d3d3d);
    t.panel_edge = rgb(0x6b6b6b);
    t.row = rgb(0x464646);
    t.row_edge = rgb(0x5f5f5f);
    t.row_focus = rgb(0x4f4f4f);

    t.accent = rgb(0x3e97f7);
    t.accent_deep = rgb(0x1f6dcc);
    t.accent_pale = rgb(0x5aaaf9);
    t.on_accent = rgb(0x161616);
    t.highlight = rgb(0x3e97f7);

    t.text = rgb(0xe5e5e5);
    t.title = rgb(0xffffff);
    t.value = rgb(0xf2f2f2);
    t.body = rgb(0xdadada);
    t.copy = rgb(0xc8c8c8);
    t.meta = rgb(0xb4b4b4);
    t.label = rgb(0xaaaaaa);
    t.muted = rgb(0xa4a4a4);
    t.faint = rgb(0x8a8a8a);
    t.warning = rgb(0xff8a73);
    t.rule = rgb(0x717171);

    t.radius_row = 8.0f;
    t.radius_card = 4.0f;
    t.radius_panel = 12.0f;
    t.pill_chips = true;
    t.focus_width = 4.0f;
    t.focus_glow = 10.0f;
    t.glass_panels = false;

    t.backdrop = "switch-backdrop.tga";
    t.backdrop_blur = "switch-backdrop-blur.tga";
    t.brand = "switch-brand.tga";
    // The art has no light of its own: what little glow there is sits behind the home screen's
    // cover (home.cpp, kCover), as the cover's halo.
    t.light_x = 0.814f;
    t.light_y = 0.375f;
    t.motes = 0;
    t.drift = 0.0f;
    return t;
}

struct Store
{
    std::array<Theme, 2> all{canopy(), nintendo_switch()};
    int index = 0;
    Theme active = all[0];
};

Store &store()
{
    static Store value;
    return value;
}

} // namespace

const Theme &th()
{
    return store().active;
}

std::span<const Theme> themes()
{
    return store().all;
}

int theme_index()
{
    return store().index;
}

bool use_theme(std::string_view id)
{
    Store &all = store();
    for (std::size_t i = 0; i < all.all.size(); ++i)
    {
        if (id == all.all[i].id)
        {
            all.index = static_cast<int>(i);
            all.active = all.all[i];
            return true;
        }
    }
    return false;
}

} // namespace pe::ui
