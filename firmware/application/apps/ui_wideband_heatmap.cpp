#include "ui_wideband_heatmap.hpp"

using namespace ui;

WidebandHeatmapView::WidebandHeatmapView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void WidebandHeatmapView::on_show() {
    focus();
}


