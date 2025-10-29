/* EAGLE-FIRMWARE - Satellite Beacon Tracker Lite (stub) */
#ifndef __UI_SAT_BEACON_TRACKER_H__
#define __UI_SAT_BEACON_TRACKER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui {
class SatelliteBeaconTrackerView : public View {
   public:
    explicit SatelliteBeaconTrackerView(NavigationView& nav);
    std::string title() const override { return "Sat Beacon Tracker"; }
    void on_show() override;

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Sat Beacon Tracker (stub)"};
    Text hint_{{0,20,screen_width,16}, "Press BACK para sair"};
};
}

#endif


