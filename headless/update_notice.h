// SPDX-License-Identifier: GPL-3.0-or-later
// Updates: check this fork's GitHub releases. The in-app installer stays unavailable
// until release packages can preserve locally supplied Switch resources.
#pragma once
#include <cstdint>
#include <string>

namespace Eden::UpdateNotice {
// Starts the check on a thread of its own; only the first call of a launch does anything.
bool Start();
std::string CheckMessage();

struct Offer {
    bool installable = false;  // the release can be installed by the app itself
    std::string version;       // the release's name ("v1.000.060")
    std::string available;     // its content version ("01.000.060")
    std::uint64_t size = 0;    // the ZIP's size in bytes; 0 when the catalog doesn't know
    std::string notes;         // the release notes, plain text; empty when there are none
    bool notes_truncated = false;
};
// A newer release than this one, once, when the check's answer has come: false when there is
// nothing (yet) to tell.
bool Take(Offer* offer);

// In the order of pe::ui::UpdatePhase (eden_services.cpp converts one to the other by number).
enum class Phase { idle, starting, downloading, unpacking, ready, applying, cancelled, failed };
struct Progress {
    Phase phase = Phase::idle;
    std::uint64_t done = 0;
    std::uint64_t total = 0;      // 0 while it isn't known
    std::string time_left;        // "about 20 s left"; empty until it can be said
    std::string error;            // why it failed
};
// The update of the offered release: begins the download and the staging (true: begun), where
// it is now, stop it (nothing changed until Apply), and the go-ahead once staged (true: the
// helper waits for the app to close; close it now).
bool Begin();
Progress Poll();
void Cancel();
bool Apply();
// After a cancel or a failure, before beginning again.
void Finish();
} // namespace Eden::UpdateNotice
