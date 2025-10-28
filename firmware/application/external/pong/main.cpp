/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#include "ui.hpp"
#include "ui_pong.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::pong {
void initialize_app(ui::NavigationView& nav) {
    nav.push<PongView>();
}
}  // namespace ui::external_app::pong

extern "C" {

__attribute__((section(".external_app.app_pong.application_information"), used)) application_information_t _application_information_pong = {
    (uint8_t*)0x00000000,
    ui::external_app::pong::initialize_app,
    CURRENT_HEADER_VERSION,
    VERSION_MD5,
    "Pong",
    {
        0x00,0x00,0x00,0x00,
        0xF0,0xFF,0x0F,0x00,
        0x10,0x00,0x10,0x00,
        0x10,0x00,0x10,0x00,
        0xF0,0xFF,0x0F,0x00,
        0x10,0x00,0x10,0x00,
        0x10,0x00,0x10,0x00,
        0xF0,0xFF,0x0F,0x00,
    },
    ui::Color::green().v,
    app_location_t::GAMES,
    -1,
    {0, 0, 0, 0},
    0x00000000,
};
}