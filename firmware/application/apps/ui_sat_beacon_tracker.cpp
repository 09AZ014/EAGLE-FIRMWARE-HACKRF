#include "ui_sat_beacon_tracker.hpp"

using namespace ui;

SatelliteBeaconTrackerView::SatelliteBeaconTrackerView(NavigationView& nav)
    : nav_{nav} {
    add_child(&header_);
    add_child(&hint_);
}

void SatelliteBeaconTrackerView::on_show() {
    focus();
}


