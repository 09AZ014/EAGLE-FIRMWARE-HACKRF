/* EAGLE-FIRMWARE - IQ Lab (stub) */
#ifndef __UI_IQ_LAB_H__
#define __UI_IQ_LAB_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class IQLabView : public View {
   public:
    explicit IQLabView(NavigationView& nav);
    std::string title() const override { return "IQ Lab"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "IQ Lab (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK para sair"};
};
}

#endif


