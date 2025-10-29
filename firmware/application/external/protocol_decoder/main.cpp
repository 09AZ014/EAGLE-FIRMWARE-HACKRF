/* EAGLE-FIRMWARE - Protocol Decoder (stub) */

#include "ui.hpp"
#include "ui_protocol_decoder.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::protocol_decoder {
void initialize_app(ui::NavigationView& nav) {
    nav.push<ProtocolDecoderView>(nav);
}
}  // namespace ui::external_app::protocol_decoder

extern "C" {
__attribute__((section(".external_app.app_protocol_decoder.application_information"), used)) application_information_t _application_information_protocol_decoder = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::protocol_decoder::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,

    /*.app_name = */ "Protocol Decoder",
    /*.bitmap_data = */ {
        0x00,0x00,0x00,0x00,
        0x1C,0x36,0x63,0x49,
        0x49,0x63,0x36,0x1C,
        0x00,0x00,0x00,0x00,
    },
    /*.icon_color = */ ui::Color::cyan().v,
    /*.menu_location = */ app_location_t::UTILITIES,

    /*.m4_app_tag = */ {'P','R','O','T'},
    /*.m4_app_offset = */ 0x00000000,
};
}



