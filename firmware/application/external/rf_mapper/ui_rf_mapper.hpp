/* EAGLE-FIRMWARE - RF Mapper (stub) */
#ifndef __UI_RF_MAPPER_H__
#define __UI_RF_MAPPER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui::external_app::rf_mapper {

class RFMapperView : public View {
   public:
    RFMapperView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "RF Mapper"; }

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "RF Mapper (stub)"};
};

} // namespace ui::external_app::rf_mapper

#endif /* __UI_RF_MAPPER_H__ */

/*
 * EAGLE-FIRMWARE v2.0.0 - RF Signal Mapper
 * Advanced signal strength mapping with GPS coordinates
 * By 09AZO14 (2025)
 */
#ifndef __UI_RF_MAPPER_H__
#define __UI_RF_MAPPER_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_receiver.hpp"
#include "ui_rssi.hpp"
#include "radio_state.hpp"
#include "receiver_model.hpp"
#include "string_format.hpp"
#include "file.hpp"
#include <vector>
#include <array>

namespace ui::external_app::rf_mapper {

struct SignalPoint {
    float lat{0};
    float lon{0};
    int rssi{-127};
    uint64_t frequency{0};
    uint32_t timestamp{0};
};

class RFMapperView : public View {
public:
    RFMapperView(NavigationView& nav);
    ~RFMapperView();
    
    std::string title() const override { return "RF Signal Mapper"; };
    
    void paint(Painter& painter) override;
    void frame_sync();
    void focus() override;
    
private:
    NavigationView& nav_;
    
    static constexpr int MAX_POINTS = 500;
    static constexpr int MAP_WIDTH = 200;
    static constexpr int MAP_HEIGHT = 180;
    static constexpr int MAP_X = 20;
    static constexpr int MAP_Y = 60;
    
    std::vector<SignalPoint> signal_points;
    
    rf::Frequency frequency_{433920000};
    int current_rssi_{-127};
    bool recording_{false};
    uint32_t point_count_{0};
    
    // Heatmap colors
    std::array<Color, 10> heatmap_colors = {{
        Color::blue(),
        Color::cyan(),
        Color::green(),
        Color::yellow(),
        Color::orange(),
        Color::red(),
        Color::dark_red(),
        Color::magenta(),
        Color::white(),
        Color::white()
    }};
    
    FrequencyField field_frequency{
        {0, 0 * 16},
        nav_
    };
    
    RFAmpField field_rf_amp{
        {12 * 8, 0 * 16}
    };
    
    LNAGainField field_lna{
        {15 * 8, 0 * 16}
    };
    
    VGAGainField field_vga{
        {18 * 8, 0 * 16}
    };
    
    RSSI rssi{
        {21 * 8, 0, 6 * 8, 4}
    };
    
    Text label_recording{
        {0, 2 * 8, 20 * 8, 16},
        ""
    };
    
    Text label_points{
        {0, 3 * 8, 20 * 8, 16},
        ""
    };
    
    Text label_current_rssi{
        {0, 4 * 8, 20 * 8, 16},
        ""
    };
    
    Button button_start_stop{
        {2 * 8, 17 * 8, 10 * 8, 32},
        "START"
    };
    
    Button button_clear{
        {14 * 8, 17 * 8, 10 * 8, 32},
        "CLEAR"
    };
    
    Button button_save{
        {2 * 8, 21 * 8, 10 * 8, 32},
        "SAVE"
    };
    
    Button button_load{
        {14 * 8, 21 * 8, 10 * 8, 32},
        "LOAD"
    };
    
    MessageHandlerRegistration message_handler_spectrum_config{
        Message::ID::ChannelSpectrumConfig,
        [this](const Message* const p) {
            (void)p;
        }
    };
    
    MessageHandlerRegistration message_handler_frame_sync{
        Message::ID::DisplayFrameSync,
        [this](const Message* const) {
            if (this->is_active()) {
                this->frame_sync();
            }
        }
    };
    
    void on_statistics_update(const ChannelStatistics& statistics);
    void add_signal_point();
    void draw_map();
    void draw_heatmap_point(int x, int y, int rssi);
    Color get_rssi_color(int rssi);
    void save_to_file();
    void load_from_file();
    void update_ui();
    void start_recording();
    void stop_recording();
    void clear_points();
    
    MessageHandlerRegistration message_handler_stats{
        Message::ID::ChannelStatistics,
        [this](const Message* const p) {
            auto stats = reinterpret_cast<const ChannelStatisticsMessage*>(p);
            this->on_statistics_update(stats->statistics);
        }
    };
};

} // namespace ui::external_app::rf_mapper

#endif
