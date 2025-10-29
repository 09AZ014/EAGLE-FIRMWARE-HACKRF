/* EAGLE-FIRMWARE - RF Macro Engine (stub) */
#ifndef __UI_RF_MACRO_ENGINE_H__
#define __UI_RF_MACRO_ENGINE_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class RFMacroEngineView : public View {
   public:
    explicit RFMacroEngineView(NavigationView& nav);
    std::string title() const override { return "RF Macro Engine"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "RF Macro Engine (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK to exit"};
};
}

#endif


