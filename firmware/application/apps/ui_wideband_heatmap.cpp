#include "ui_wideband_heatmap.hpp"
#include "baseband_api.hpp"

using namespace ui;

WidebandHeatmapView::WidebandHeatmapView(NavigationView& nav)
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

WidebandHeatmapView::~WidebandHeatmapView() {}

void WidebandHeatmapView::on_show() {
    waterfall.start();
    focus();
}

void WidebandHeatmapView::on_hide() {
    waterfall.stop();
}

void WidebandHeatmapView::focus() {
    field_frequency.focus();
}


