/* EAGLE-FIRMWARE - GFSK/2FSK Packet Studio (stub) */
#ifndef __UI_GFSK_PACKET_STUDIO_H__
#define __UI_GFSK_PACKET_STUDIO_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class GFSKPacketStudioView : public View {
   public:
    explicit GFSKPacketStudioView(NavigationView& nav);
    std::string title() const override { return "GFSK Packet Studio"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "GFSK Packet Studio (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK to exit"};
};
}

#endif


