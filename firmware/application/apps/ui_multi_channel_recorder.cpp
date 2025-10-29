#include "ui_multi_channel_recorder.hpp"

using namespace ui;

MultiChannelRecorderView::MultiChannelRecorderView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void MultiChannelRecorderView::on_show() {
    focus();
}


