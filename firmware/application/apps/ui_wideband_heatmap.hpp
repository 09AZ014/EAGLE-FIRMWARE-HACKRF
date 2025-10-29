/* EAGLE-FIRMWARE - Wideband Channel Heatmap (stub) */
#ifndef __UI_WIDEBAND_HEATMAP_H__
#define __UI_WIDEBAND_HEATMAP_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class WidebandHeatmapView : public View {
   public:
    explicit WidebandHeatmapView(NavigationView& nav);
    std::string title() const override { return "Wideband Heatmap"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Wideband Heatmap (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK para sair"};
};
}

#endif


