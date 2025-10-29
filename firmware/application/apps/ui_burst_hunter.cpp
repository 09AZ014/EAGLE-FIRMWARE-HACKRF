#include "ui_burst_hunter.hpp"

using namespace ui;

BurstHunterView::BurstHunterView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void BurstHunterView::on_show() {
    focus();
}


