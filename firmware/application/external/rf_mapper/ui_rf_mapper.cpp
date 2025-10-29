#include "ui_rf_mapper.hpp"

namespace ui::external_app::rf_mapper {

RFMapperView::RFMapperView(NavigationView& nav) : nav_{nav} {
    add_child(&header_);
}

void RFMapperView::on_show() {
    focus();
}

} // namespace ui::external_app::rf_mapper

/*
 * EAGLE-FIRMWARE v2.0.0 - RF Signal Mapper
 * Advanced signal strength mapping with GPS coordinates
 * By 09AZO14 (2025)
 */
#include "ui_rf_mapper.hpp"
#include "baseband_api.hpp"
#include "portapack.hpp"
#include "portapack_persistent_memory.hpp"
#include <cstring>
#include <cmath>

using namespace portapack;

namespace ui::external_app::rf_mapper {

RFMapperView::RFMapperView(NavigationView& nav)
    : nav_(nav) {
    
    add_children({
        &field_frequency,
        &field_rf_amp,
        &field_lna,
        &field_vga,
        &rssi,
        &label_recording,
        &label_points,
        &label_current_rssi,
        &button_start_stop,
        &button_clear,
        &button_save,
        &button_load
    });
    
    field_frequency.set_value(frequency_);
    field_frequency.set_step(25000);
    field_frequency.on_change = [this](rf::Frequency f) {
        frequency_ = f;
        receiver_model.set_target_frequency(f);
    };
    
    button_start_stop.on_select = [this](Button&) {
        if (recording_) {
            stop_recording();
        } else {
            start_recording();
        }
    };
    
    button_clear.on_select = [this](Button&) {
        clear_points();
    };
    
    button_save.on_select = [this](Button&) {
        save_to_file();
    };
    
    button_load.on_select = [this](Button&) {
        load_from_file();
    };
    
    receiver_model.enable();
    receiver_model.set_target_frequency(frequency_);
    receiver_model.set_sampling_rate(3072000);
    receiver_model.set_baseband_bandwidth(1750000);
    
    update_ui();
}

RFMapperView::~RFMapperView() {
    receiver_model.disable();
}

void RFMapperView::focus() {
    field_frequency.focus();
}

void RFMapperView::start_recording() {
    recording_ = true;
    button_start_stop.set_text("STOP");
    label_recording.set("STATUS: RECORDING");
    update_ui();
}

void RFMapperView::stop_recording() {
    recording_ = false;
    button_start_stop.set_text("START");
    label_recording.set("STATUS: STOPPED");
    update_ui();
}

void RFMapperView::clear_points() {
    signal_points.clear();
    point_count_ = 0;
    update_ui();
    set_dirty();
}

void RFMapperView::on_statistics_update(const ChannelStatistics& statistics) {
    current_rssi_ = statistics.max_db;
    rssi.set_value(current_rssi_);
    
    if (recording_ && point_count_ < MAX_POINTS) {
        add_signal_point();
    }
}

void RFMapperView::add_signal_point() {
    SignalPoint point;
    // GPS coordinates would be fetched from GPS module here
    // For now using simulated data
    point.lat = 0.0f + (point_count_ * 0.001f);
    point.lon = 0.0f + (point_count_ * 0.001f);
    point.rssi = current_rssi_;
    point.frequency = frequency_;
    point.timestamp = chTimeNow();
    
    signal_points.push_back(point);
    point_count_++;
    
    update_ui();
}

Color RFMapperView::get_rssi_color(int rssi) {
    // Map RSSI (-127 to 0) to color gradient
    int normalized = rssi + 127; // 0-127
    int index = (normalized * 9) / 127;
    if (index < 0) index = 0;
    if (index > 9) index = 9;
    return heatmap_colors[index];
}

void RFMapperView::draw_heatmap_point(int x, int y, int rssi) {
    if (x < MAP_X || x >= MAP_X + MAP_WIDTH || y < MAP_Y || y >= MAP_Y + MAP_HEIGHT) {
        return;
    }
    
    Color color = get_rssi_color(rssi);
    display.fill_rectangle({x - 1, y - 1, 3, 3}, color);
}

void RFMapperView::draw_map() {
    // Draw map border
    display.draw_rectangle({MAP_X - 1, MAP_Y - 1, MAP_WIDTH + 2, MAP_HEIGHT + 2}, Color::white());
    
    // Draw grid
    for (int i = 0; i < 5; i++) {
        int x = MAP_X + (MAP_WIDTH * i) / 4;
        int y = MAP_Y + (MAP_HEIGHT * i) / 4;
        display.draw_line({x, MAP_Y}, {x, MAP_Y + MAP_HEIGHT}, Color::dark_grey());
        display.draw_line({MAP_X, y}, {MAP_X + MAP_WIDTH, y}, Color::dark_grey());
    }
    
    // Draw signal points
    if (!signal_points.empty()) {
        float min_lat = signal_points[0].lat;
        float max_lat = signal_points[0].lat;
        float min_lon = signal_points[0].lon;
        float max_lon = signal_points[0].lon;
        
        // Find bounds
        for (const auto& point : signal_points) {
            if (point.lat < min_lat) min_lat = point.lat;
            if (point.lat > max_lat) max_lat = point.lat;
            if (point.lon < min_lon) min_lon = point.lon;
            if (point.lon > max_lon) max_lon = point.lon;
        }
        
        float lat_range = max_lat - min_lat;
        float lon_range = max_lon - min_lon;
        
        if (lat_range < 0.0001f) lat_range = 0.0001f;
        if (lon_range < 0.0001f) lon_range = 0.0001f;
        
        // Draw points
        for (const auto& point : signal_points) {
            int x = MAP_X + ((point.lon - min_lon) / lon_range) * (MAP_WIDTH - 4) + 2;
            int y = MAP_Y + ((point.lat - min_lat) / lat_range) * (MAP_HEIGHT - 4) + 2;
            draw_heatmap_point(x, y, point.rssi);
        }
    }
}

void RFMapperView::update_ui() {
    label_points.set("POINTS: " + to_string_dec_uint(point_count_) + "/" + to_string_dec_uint(MAX_POINTS));
    label_current_rssi.set("RSSI: " + to_string_dec_int(current_rssi_) + " dB");
}

void RFMapperView::paint(Painter& painter) {
    (void)painter;
    draw_map();
}

void RFMapperView::frame_sync() {
    set_dirty();
}

void RFMapperView::save_to_file() {
    auto result = File::open("RFMAP/map_" + to_string_timestamp(rtc_time::now()) + ".txt", false, true);
    if (result.is_valid()) {
        File file = result.value();
        
        std::string header = "# EAGLE RF Signal Map\n";
        header += "# Frequency: " + to_string_dec_uint(frequency_) + " Hz\n";
        header += "# Points: " + to_string_dec_uint(point_count_) + "\n";
        header += "# Latitude,Longitude,RSSI,Timestamp\n";
        file.write(header);
        
        for (const auto& point : signal_points) {
            std::string line = to_string_decimal(point.lat, 6) + "," +
                             to_string_decimal(point.lon, 6) + "," +
                             to_string_dec_int(point.rssi) + "," +
                             to_string_dec_uint(point.timestamp) + "\n";
            file.write(line);
        }
        
        file.sync();
    }
}

void RFMapperView::load_from_file() {
    // Implementation for loading maps
    // Would parse CSV file and populate signal_points
}

} // namespace ui::external_app::rf_mapper
