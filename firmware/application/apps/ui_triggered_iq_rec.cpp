#include "ui_triggered_iq_rec.hpp"
#include "baseband_api.hpp"

using namespace ui;

TriggeredIQRecorderView::TriggeredIQRecorderView(NavigationView& nav)
    : nav_{nav} {
    baseband::run_image(portapack::spi_flash::image_tag_wideband_spectrum);

    add_children({&rssi,
                  &channel,
                  &field_frequency,
                  &field_rf_amp,
                  &field_lna,
                  &field_vga,
                  &option_trigger,
                  &field_level,
                  &check_prebuf,
                  &check_postbuf,
                  &record_view,
                  &waterfall});

    waterfall.on_select = [this](int32_t offset) {
        field_frequency.set_value(receiver_model.target_frequency() + offset);
    };

    record_view.set_filename_date_frequency(true);
}

TriggeredIQRecorderView::~TriggeredIQRecorderView() {}

void TriggeredIQRecorderView::on_show() {
    waterfall.start();
    focus();
}

void TriggeredIQRecorderView::on_hide() {
    waterfall.stop();
}

void TriggeredIQRecorderView::focus() {
    field_frequency.focus();
}


