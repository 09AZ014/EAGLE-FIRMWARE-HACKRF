#include "ui_burst_hunter.hpp"
#include "baseband_api.hpp"

using namespace ui;

BurstHunterView::BurstHunterView(NavigationView& nav)
    : nav_{nav} {
    baseband::run_image(portapack::spi_flash::image_tag_wideband_spectrum);

    add_children({&rssi,
                  &channel,
                  &field_frequency,
                  &field_rf_amp,
                  &field_lna,
                  &field_vga,
                  &waterfall});

    waterfall.on_select = [this](int32_t offset) {
        field_frequency.set_value(receiver_model.target_frequency() + offset);
    };
}

BurstHunterView::~BurstHunterView() {}

void BurstHunterView::on_show() {
    waterfall.start();
    focus();
}

void BurstHunterView::on_hide() {
    waterfall.stop();
}

void BurstHunterView::focus() {
    field_frequency.focus();
}


