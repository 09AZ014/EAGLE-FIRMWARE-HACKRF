#include "ui_rf_macro_engine.hpp"

using namespace ui;

RFMacroEngineView::RFMacroEngineView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void RFMacroEngineView::on_show() {
    focus();
}


