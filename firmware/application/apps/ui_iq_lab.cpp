#include "ui_iq_lab.hpp"
#include "baseband_api.hpp"

using namespace ui;

IQLabView::IQLabView(NavigationView& nav)
    : nav_{nav} {
    baseband::run_image(portapack::spi_flash::image_tag_wideband_spectrum);

    add_children({&rssi,
                  &channel,
                  &field_frequency,
                  &field_rf_amp,
                  &field_lna,
                  &field_vga,
                  &waterfall});

    waterfall.show_audio_spectrum_view(true);
    waterfall.on_select = [this](int32_t offset) {
        field_frequency.set_value(receiver_model.target_frequency() + offset);
    };
}

IQLabView::~IQLabView() {}

void IQLabView::on_show() {
    waterfall.start();
    focus();
}

void IQLabView::on_hide() {
    waterfall.stop();
}

void IQLabView::focus() {
    field_frequency.focus();
}


