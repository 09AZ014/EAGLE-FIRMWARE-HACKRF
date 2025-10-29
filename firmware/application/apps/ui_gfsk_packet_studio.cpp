#include "ui_gfsk_packet_studio.hpp"

using namespace ui;

GFSKPacketStudioView::GFSKPacketStudioView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void GFSKPacketStudioView::on_show() {
    focus();
}


