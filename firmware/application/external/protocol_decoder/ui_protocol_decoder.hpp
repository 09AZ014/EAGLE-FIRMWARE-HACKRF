/* EAGLE-FIRMWARE - Protocol Decoder (stub) */
#ifndef __UI_PROTOCOL_DECODER_H__
#define __UI_PROTOCOL_DECODER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"

namespace ui::external_app::protocol_decoder {

class ProtocolDecoderView : public View {
   public:
    ProtocolDecoderView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "Protocol Decoder"; }

   private:
    NavigationView& nav_;
    Text header_{{0,0,screen_width,16}, "Protocol Decoder (stub)"};
};

} // namespace ui::external_app::protocol_decoder

#endif /* __UI_PROTOCOL_DECODER_H__ */

/*
 * EAGLE-FIRMWARE v2.0.0 - Advanced Protocol Decoder
 * Auto-detection and decoding for multiple RF protocols
 * By 09AZO14 (2025)
 */
#ifndef __UI_PROTOCOL_DECODER_H__
#define __UI_PROTOCOL_DECODER_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_receiver.hpp"
#include "ui_freq_field.hpp"
#include "radio_state.hpp"
#include "receiver_model.hpp"
#include <string>
#include <vector>

namespace ui::external_app::protocol_decoder {

enum class ProtocolType {
    UNKNOWN,
    OOK_MANCHESTER,
    OOK_PWM,
    FSK_2,
    FSK_4,
    ASK,
    PSK,
    POCSAG,
    FLEX,
    APRS,
    AIS,
    ACARS,
    ADSB,
    DMR,
    DSTAR,
    P25,
    NXDN,
    YSF,
    TETRA
};

struct DecodedPacket {
    ProtocolType protocol;
    std::string data;
    uint32_t timestamp;
    int rssi;
    uint64_t frequency;
    float confidence;
};

class ProtocolDecoderView : public View {
public:
    ProtocolDecoderView(NavigationView& nav);
    ~ProtocolDecoderView();
    
    std::string title() const override { return "Protocol Decoder Pro"; };
    
    void paint(Painter& painter) override;
    void focus() override;
    
private:
    NavigationView& nav_;
    
    static constexpr int MAX_PACKETS = 100;
    std::vector<DecodedPacket> decoded_packets;
    
    rf::Frequency frequency_{433920000};
    bool auto_scan_{true};
    bool logging_enabled_{true};
    int scroll_position_{0};
    
    // Protocol detection state
    uint32_t bit_buffer_[256];
    int bit_count_{0};
    ProtocolType detected_protocol_{ProtocolType::UNKNOWN};
    
    FrequencyField field_frequency{
        {0, 0 * 8},
        nav_
    };
    
    RFAmpField field_rf_amp{
        {10 * 8, 0 * 8}
    };
    
    LNAGainField field_lna{
        {13 * 8, 0 * 8}
    };
    
    VGAGainField field_vga{
        {16 * 8, 0 * 8}
    };
    
    Text label_status{
        {0, 2 * 8, 30 * 8, 16},
        "Status: Ready"
    };
    
    Text label_protocol{
        {0, 3 * 8, 30 * 8, 16},
        "Protocol: Detecting..."
    };
    
    Text label_packets{
        {0, 4 * 8, 30 * 8, 16},
        "Packets: 0"
    };
    
    Labels labels{
        {{0, 6 * 8}, "Decoded Data:", Color::light_grey()}
    };
    
    Button button_auto_scan{
        {1 * 8, 18 * 8, 10 * 8, 32},
        "AUTO: ON"
    };
    
    Button button_clear{
        {13 * 8, 18 * 8, 8 * 8, 32},
        "CLEAR"
    };
    
    Button button_save{
        {22 * 8, 18 * 8, 7 * 8, 32},
        "SAVE"
    };
    
    Console console{
        {0, 7 * 8, 240, 136}
    };
    
    MessageHandlerRegistration message_handler_packet{
        Message::ID::AFSKData,
        [this](const Message* const p) {
            (void)p;
            // Handle decoded packets
        }
    };
    
    void detect_protocol(const uint8_t* data, size_t length);
    void decode_packet();
    std::string protocol_to_string(ProtocolType type);
    float calculate_confidence(const uint8_t* data, size_t length, ProtocolType type);
    void add_packet(const DecodedPacket& packet);
    void save_log();
    void update_display();
    
    // Protocol-specific decoders
    bool try_decode_ook_manchester(const uint8_t* data, size_t length, std::string& output);
    bool try_decode_ook_pwm(const uint8_t* data, size_t length, std::string& output);
    bool try_decode_fsk(const uint8_t* data, size_t length, std::string& output);
    bool try_decode_aprs(const uint8_t* data, size_t length, std::string& output);
    bool try_decode_ais(const uint8_t* data, size_t length, std::string& output);
    bool try_decode_pocsag(const uint8_t* data, size_t length, std::string& output);
};

} // namespace ui::external_app::protocol_decoder

#endif
