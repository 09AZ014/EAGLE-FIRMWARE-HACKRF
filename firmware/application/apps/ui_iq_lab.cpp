#include "ui_iq_lab.hpp"

using namespace ui;

IQLabView::IQLabView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void IQLabView::on_show() {
    focus();
}


