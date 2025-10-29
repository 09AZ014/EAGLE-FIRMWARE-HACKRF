#include "ui_multi_channel_recorder.hpp"
#include "baseband_api.hpp"

using namespace ui;

MultiChannelRecorderView::MultiChannelRecorderView(NavigationView& nav)
    : nav_{nav} {
    baseband::run_image(portapack::spi_flash::image_tag_wideband_spectrum);

    add_children({&rssi,
                  &channel,
                  &field_frequency,
                  &field_rf_amp,
                  &field_lna,
                  &field_vga,
                  &record_view,
                  &waterfall});

    waterfall.on_select = [this](int32_t offset) {
        field_frequency.set_value(receiver_model.target_frequency() + offset);
    };

    record_view.set_filename_date_frequency(true);
}

MultiChannelRecorderView::~MultiChannelRecorderView() {}

void MultiChannelRecorderView::on_show() {
    waterfall.start();
    focus();
}

void MultiChannelRecorderView::on_hide() {
    waterfall.stop();
}

void MultiChannelRecorderView::focus() {
    field_frequency.focus();
}


