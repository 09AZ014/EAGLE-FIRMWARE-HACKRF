/* EAGLE-FIRMWARE - TDOA Logger (stub) */
#ifndef __UI_TDOA_LOGGER_H__
#define __UI_TDOA_LOGGER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class TDOALoggerView : public View {
   public:
    explicit TDOALoggerView(NavigationView& nav);
    std::string title() const override { return "TDOA Logger"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "TDOA Logger (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK to exit"};
};
}

#endif


