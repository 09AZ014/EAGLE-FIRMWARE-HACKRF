/*
 * EAGLE-FIRMWARE - Signal Inspector (stub)
 */

#ifndef __UI_SIGNAL_INSPECTOR_H__
#define __UI_SIGNAL_INSPECTOR_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {

class SignalInspectorView : public View {
   public:
    explicit SignalInspectorView(NavigationView& nav);
    std::string title() const override { return "Signal Inspector"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{
        {0, 0, screen_width, 16},
        "Signal Inspector (stub)"};
    Text hint_{
        {0, 20, screen_width, 16},
        "Press BACK para sair"};
};

}  // namespace ui

#endif  // __UI_SIGNAL_INSPECTOR_H__


