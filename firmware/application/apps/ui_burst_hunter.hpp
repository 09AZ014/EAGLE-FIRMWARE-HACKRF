/* EAGLE-FIRMWARE - Burst Hunter (stub) */
#ifndef __UI_BURST_HUNTER_H__
#define __UI_BURST_HUNTER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class BurstHunterView : public View {
   public:
    explicit BurstHunterView(NavigationView& nav);
    std::string title() const override { return "Burst Hunter"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Burst Hunter (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK to exit"};
};
}

#endif


