/* EAGLE-FIRMWARE - Triggered IQ Recorder (stub) */
#ifndef __UI_TRIGGERED_IQ_REC_H__
#define __UI_TRIGGERED_IQ_REC_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class TriggeredIQRecorderView : public View {
   public:
    explicit TriggeredIQRecorderView(NavigationView& nav);
    std::string title() const override { return "Triggered IQ Recorder"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Triggered IQ Recorder (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK para sair"};
};
}

#endif


