/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#include "ui.hpp"
#include "ui_minesweeper.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::minesweeper {
void initialize_app(ui::NavigationView& nav) {
    nav.push<MinesweeperView>();
}
}  // namespace ui::external_app::minesweeper

extern "C" {

__attribute__((section(".external_app.app_minesweeper.application_information"), used)) application_information_t _application_information_minesweeper = {
    (uint8_t*)0x00000000,
    ui::external_app::minesweeper::initialize_app,
    CURRENT_HEADER_VERSION,
    VERSION_MD5,
    "Minesweeper",
    {
        0x00,0x00,0x00,0x00,
        0xFE,0xFF,0xFF,0x7F,
        0x02,0x00,0x00,0x40,
        0xFA,0xBF,0xEF,0x5F,
        0x0A,0xA0,0x28,0x52,
        0xEA,0xBF,0xEF,0x57,
        0x02,0x00,0x00,0x40,
        0xFE,0xFF,0xFF,0x7F,
    },
    ui::Color::orange().v,
    app_location_t::GAMES,
    -1,
    {0, 0, 0, 0},
    0x00000000,
};
}
