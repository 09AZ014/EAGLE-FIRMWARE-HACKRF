#include "ui_signal_inspector.hpp"

using namespace ui;

SignalInspectorView::SignalInspectorView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void SignalInspectorView::on_show() {
    focus();
}


