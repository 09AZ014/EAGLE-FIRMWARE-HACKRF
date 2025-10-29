#include "ui_triggered_iq_rec.hpp"

using namespace ui;

TriggeredIQRecorderView::TriggeredIQRecorderView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void TriggeredIQRecorderView::on_show() {
    focus();
}


