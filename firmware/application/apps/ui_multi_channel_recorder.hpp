/* EAGLE-FIRMWARE - Multi-Channel Recorder (stub) */
#ifndef __UI_MULTI_CHANNEL_RECORDER_H__
#define __UI_MULTI_CHANNEL_RECORDER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class MultiChannelRecorderView : public View {
   public:
    explicit MultiChannelRecorderView(NavigationView& nav);
    std::string title() const override { return "Multi-Channel Recorder"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Multi-Channel Recorder (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK to exit"};
};
}

#endif


