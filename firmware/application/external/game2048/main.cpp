/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#include "ui.hpp"
#include "ui_game2048.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::game2048 {
void initialize_app(ui::NavigationView& nav) {
    nav.push<Game2048View>();
}
}

extern "C" {
__attribute__((section(".external_app.app_game2048.application_information"), used)) application_information_t _application_information_game2048 = {
    (uint8_t*)0x00000000, ui::external_app::game2048::initialize_app, CURRENT_HEADER_VERSION, VERSION_MD5, "2048",
    {0xF0,0x0F,0x90,0x09,0x90,0x09,0xF0,0x0F,0x00,0x00,0xF0,0x0F,0x90,0x09,0x90,0x09,0x90,0x09,0xF0,0x0F,0x00,0x00,0xF0,0x0F,0x90,0x00,0x60,0x00,0x90,0x00,0xF0,0x0F},
    ui::Color::yellow().v, app_location_t::GAMES, -1, {0,0,0,0}, 0x00000000,
};
}
