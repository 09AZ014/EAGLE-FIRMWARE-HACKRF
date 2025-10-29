/* EAGLE-FIRMWARE - RF Mapper (stub) */

#include "ui.hpp"
#include "ui_rf_mapper.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::rf_mapper {
void initialize_app(ui::NavigationView& nav) {
    nav.push<RFMapperView>(nav);
}
}  // namespace ui::external_app::rf_mapper

extern "C" {
__attribute__((section(".external_app.app_rf_mapper.application_information"), used)) application_information_t _application_information_rf_mapper = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::rf_mapper::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,

    /*.app_name = */ "RF Mapper",
    /*.bitmap_data = */ {
        0x00,0x00,0x00,0x00,
        0x1C,0x36,0x63,0x41,
        0x41,0x63,0x36,0x1C,
        0x00,0x00,0x00,0x00,
    },
    /*.icon_color = */ ui::Color::cyan().v,
    /*.menu_location = */ app_location_t::UTILITIES,

    /*.m4_app_tag = */ {'R','F','M','P'},
    /*.m4_app_offset = */ 0x00000000,
};
}



