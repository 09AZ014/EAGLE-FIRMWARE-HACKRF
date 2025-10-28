/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#include "ui.hpp"
#include "ui_spacerace.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::spacerace {
void initialize_app(ui::NavigationView& nav) {
    nav.push<SpaceRaceView>();
}
}

extern "C" {
__attribute__((section(".external_app.app_spacerace.application_information"), used)) application_information_t _application_information_spacerace = {
    (uint8_t*)0x00000000, ui::external_app::spacerace::initialize_app, CURRENT_HEADER_VERSION, VERSION_MD5, "SpaceRace",
    {0x00,0x00,0x7E,0x00,0x42,0x00,0x5A,0x00,0x66,0x00,0x7E,0x00,0x66,0x00,0x5A,0x00,0x42,0x00,0x7E,0x00,0x00,0x00,0x3C,0x00,0x24,0x00,0x24,0x00,0x3C,0x00,0x00,0x00,0x00,0x00},
    ui::Color::cyan().v, app_location_t::GAMES, -1, {0,0,0,0}, 0x00000000,
};
}
