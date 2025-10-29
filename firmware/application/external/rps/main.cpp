/*
 * EAGLE-FIRMWARE - Rock-Paper-Scissors
 * by 09AZO14
 */

#include "ui.hpp"
#include "ui_rps.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::rps {
void initialize_app(ui::NavigationView& nav) {
    nav.push<RPSView>();
}
}  // namespace ui::external_app::rps

extern "C" {
__attribute__((section(".external_app.app_rps.application_information"), used)) application_information_t _application_information_rps = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::rps::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,

    /*.app_name = */ "RPS",
    /*.bitmap_data = */ {
        0x00, 0x00,
        0x1E, 0x3C,
        0x33, 0x66,
        0x33, 0x66,
        0x1E, 0x3C,
        0x33, 0x66,
        0x33, 0x66,
        0x33, 0x66,
        0x1E, 0x3C,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
    },
    /*.icon_color = */ ui::Color::magenta().v,
    /*.menu_location = */ app_location_t::UTILITIES,

    /*.m4_app_tag = portapack::spi_flash::image_tag_none */ {'P', 'R', 'P', 'S'},
    /*.m4_app_offset = */ 0x00000000,
};
}
