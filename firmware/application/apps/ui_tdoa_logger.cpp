#include "ui_tdoa_logger.hpp"

using namespace ui;

TDOALoggerView::TDOALoggerView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void TDOALoggerView::on_show() {
    focus();
}


