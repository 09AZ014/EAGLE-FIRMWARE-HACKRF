/*
 * Flappy Bird for PortaPack/HackRF (external app)
 * Minimal, fast rectangle-based rendering.
 */

#include "ui.hpp"
#include "ui_flappybird.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::flappybird {
void initialize_app(ui::NavigationView& nav) {
    nav.push<FlappyBirdView>();
}
}  // namespace ui::external_app::flappybird

extern "C" {

__attribute__((section(".external_app.app_flappybird.application_information"), used)) application_information_t _application_information_flappybird = {
    (uint8_t*)0x00000000,
    ui::external_app::flappybird::initialize_app,
    CURRENT_HEADER_VERSION,
    VERSION_MD5,
    "Flappy Bird",
    {
        // 16x16 bird-ish icon
        0x00, 0x00,
        0x1C, 0x00,
        0x3E, 0x00,
        0x7F, 0x00,
        0xFF, 0x80,
        0xFF, 0x80,
        0x7F, 0x00,
        0x7F, 0x00,
        0x7F, 0x00,
        0x7F, 0x00,
        0x3E, 0x00,
        0x3E, 0x00,
        0x1C, 0x00,
        0x08, 0x00,
        0x00, 0x00,
        0x00, 0x00,
    },
    ui::Color::green().v,
    app_location_t::GAMES,
    -1,
    {0, 0, 0, 0},
    0x00000000,
};
}
