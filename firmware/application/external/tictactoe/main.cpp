/*
 * EAGLE-FIRMWARE - Tic-Tac-Toe
 * by 09AZO14
 */

#include "ui.hpp"
#include "ui_tictactoe.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::tictactoe {
void initialize_app(ui::NavigationView& nav) {
    nav.push<TicTacToeView>();
}
}  // namespace ui::external_app::tictactoe

extern "C" {
__attribute__((section(".external_app.app_tictactoe.application_information"), used)) application_information_t _application_information_tictactoe = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::tictactoe::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,

    /*.app_name = */ "TicTacToe",
    /*.bitmap_data = */ {
        0x00, 0x00,
        0x00, 0x00,
        0x1C, 0x1C,
        0x3E, 0x3E,
        0x77, 0x77,
        0x63, 0x63,
        0x63, 0x63,
        0x77, 0x77,
        0x3E, 0x3E,
        0x1C, 0x1C,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
    },
    /*.icon_color = */ ui::Color::cyan().v,
    /*.menu_location = */ app_location_t::UTILITIES,

    /*.m4_app_tag = portapack::spi_flash::image_tag_none */ {'P', 'T', 'T', 'T'},
    /*.m4_app_offset = */ 0x00000000,
};
}
