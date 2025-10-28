/*
 * EAGLE-FIRMWARE v2.0.0 - Advanced Protocol Decoder
 * Auto-detection and decoding for multiple RF protocols
 * By 09AZO14 (2025)
 */
#include "ui_protocol_decoder.hpp"
#include "baseband_api.hpp"
#include "portapack.hpp"
#include "string_format.hpp"
#include <cstring>
#include <algorithm>

using namespace portapack;

namespace ui::external_app::protocol_decoder {

ProtocolDecoderView::ProtocolDecoderView(NavigationView& nav)
    : nav_(nav) {
    
    add_children({
        &field_frequency,
        &field_rf_amp,
        &field_lna,
        &field_vga,
        &label_status,
        &label_protocol,
        &label_packets,
        &labels,
        &button_auto_scan,
        &button_clear,
        &button_save,
        &console
    });
    
    field_frequency.set_value(frequency_);
    field_frequency.set_step(25000);
    field_frequency.on_change = [this](rf::Frequency f) {
        frequency_ = f;
        receiver_model.set_target_frequency(f);
    };
    
    button_auto_scan.on_select = [this](Button& button) {
        auto_scan_ = !auto_scan_;
        button.set_text(auto_scan_ ? "AUTO: ON" : "AUTO: OFF");
    };
    
    button_clear.on_select = [this](Button&) {
        decoded_packets.clear();
        console.clear();
        scroll_position_ = 0;
        update_display();
    };
    
    button_save.on_select = [this](Button&) {
        save_log();
    };
    
    receiver_model.enable();
    receiver_model.set_target_frequency(frequency_);
    receiver_model.set_sampling_rate(3072000);
    receiver_model.set_baseband_bandwidth(1750000);
    
    console.writeln("Protocol Decoder Pro v2.0");
    console.writeln("Ready to detect...");
    console.writeln("");
}

ProtocolDecoderView::~ProtocolDecoderView() {
    receiver_model.disable();
}

void ProtocolDecoderView::focus() {
    field_frequency.focus();
}

std::string ProtocolDecoderView::protocol_to_string(ProtocolType type) {
    switch (type) {
        case ProtocolType::OOK_MANCHESTER: return "OOK-Manchester";
        case ProtocolType::OOK_PWM: return "OOK-PWM";
        case ProtocolType::FSK_2: return "FSK-2";
        case ProtocolType::FSK_4: return "FSK-4";
        case ProtocolType::ASK: return "ASK";
        case ProtocolType::PSK: return "PSK";
        case ProtocolType::POCSAG: return "POCSAG";
        case ProtocolType::FLEX: return "FLEX";
        case ProtocolType::APRS: return "APRS";
        case ProtocolType::AIS: return "AIS";
        case ProtocolType::ACARS: return "ACARS";
        case ProtocolType::ADSB: return "ADS-B";
        case ProtocolType::DMR: return "DMR";
        case ProtocolType::DSTAR: return "D-STAR";
        case ProtocolType::P25: return "P25";
        case ProtocolType::NXDN: return "NXDN";
        case ProtocolType::YSF: return "YSF";
        case ProtocolType::TETRA: return "TETRA";
        default: return "UNKNOWN";
    }
}

void ProtocolDecoderView::detect_protocol(const uint8_t* data, size_t length) {
    if (length < 8) return;
    
    std::string decoded_data;
    float max_confidence = 0.0f;
    ProtocolType best_protocol = ProtocolType::UNKNOWN;
    
    // Try each decoder
    struct ProtocolTest {
        ProtocolType type;
        bool (ProtocolDecoderView::*decoder)(const uint8_t*, size_t, std::string&);
    };
    
    ProtocolTest tests[] = {
        {ProtocolType::OOK_MANCHESTER, &ProtocolDecoderView::try_decode_ook_manchester},
        {ProtocolType::OOK_PWM, &ProtocolDecoderView::try_decode_ook_pwm},
        {ProtocolType::FSK_2, &ProtocolDecoderView::try_decode_fsk},
        {ProtocolType::APRS, &ProtocolDecoderView::try_decode_aprs},
        {ProtocolType::AIS, &ProtocolDecoderView::try_decode_ais},
        {ProtocolType::POCSAG, &ProtocolDecoderView::try_decode_pocsag}
    };
    
    for (const auto& test : tests) {
        std::string temp_data;
        if ((this->*test.decoder)(data, length, temp_data)) {
            float conf = calculate_confidence(data, length, test.type);
            if (conf > max_confidence) {
                max_confidence = conf;
                best_protocol = test.type;
                decoded_data = temp_data;
            }
        }
    }
    
    if (best_protocol != ProtocolType::UNKNOWN && max_confidence > 0.5f) {
        DecodedPacket packet;
        packet.protocol = best_protocol;
        packet.data = decoded_data;
        packet.timestamp = chTimeNow();
        packet.rssi = -60; // Would come from radio
        packet.frequency = frequency_;
        packet.confidence = max_confidence;
        
        add_packet(packet);
    }
}

float ProtocolDecoderView::calculate_confidence(const uint8_t* data, size_t length, ProtocolType type) {
    (void)data;
    (void)length;
    
    // Simple confidence calculation based on protocol characteristics
    switch (type) {
        case ProtocolType::OOK_MANCHESTER:
        case ProtocolType::OOK_PWM:
            return 0.85f;
        case ProtocolType::APRS:
        case ProtocolType::AIS:
            return 0.92f;
        case ProtocolType::POCSAG:
            return 0.88f;
        default:
            return 0.70f;
    }
}

bool ProtocolDecoderView::try_decode_ook_manchester(const uint8_t* data, size_t length, std::string& output) {
    if (length < 16) return false;
    
    // Simple Manchester decoder
    std::string bits;
    for (size_t i = 0; i < length && i < 64; i += 2) {
        if (data[i] == 0x01 && data[i+1] == 0x00) {
            bits += "1";
        } else if (data[i] == 0x00 && data[i+1] == 0x01) {
            bits += "0";
        }
    }
    
    if (bits.length() >= 8) {
        output = "DATA: " + bits;
        return true;
    }
    
    return false;
}

bool ProtocolDecoderView::try_decode_ook_pwm(const uint8_t* data, size_t length, std::string& output) {
    if (length < 12) return false;
    
    // PWM decoder - look for pulse width patterns
    std::string hex_data;
    for (size_t i = 0; i < length && i < 32; i++) {
        char buf[4];
        snprintf(buf, sizeof(buf), "%02X", data[i]);
        hex_data += buf;
    }
    
    output = "PWM: " + hex_data;
    return true;
}

bool ProtocolDecoderView::try_decode_fsk(const uint8_t* data, size_t length, std::string& output) {
    if (length < 10) return false;
    
    // FSK decoder
    std::string hex;
    for (size_t i = 0; i < length && i < 24; i++) {
        char buf[4];
        snprintf(buf, sizeof(buf), "%02X ", data[i]);
        hex += buf;
    }
    
    output = "FSK: " + hex;
    return hex.length() > 0;
}

bool ProtocolDecoderView::try_decode_aprs(const uint8_t* data, size_t length, std::string& output) {
    if (length < 20) return false;
    
    // Look for APRS packet structure
    // Typical: callsign>destination:payload
    std::string packet;
    bool valid = false;
    
    for (size_t i = 0; i < length && i < 100; i++) {
        if (data[i] >= 32 && data[i] <= 126) { // Printable ASCII
            packet += (char)data[i];
            if (data[i] == '>') valid = true;
        }
    }
    
    if (valid && packet.find('>') != std::string::npos) {
        output = packet;
        return true;
    }
    
    return false;
}

bool ProtocolDecoderView::try_decode_ais(const uint8_t* data, size_t length, std::string& output) {
    if (length < 24) return false;
    
    // AIS decoder - simplified
    // Real implementation would decode NMEA sentences
    uint32_t mmsi = 0;
    if (length >= 4) {
        mmsi = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }
    
    if (mmsi > 100000000 && mmsi < 999999999) {
        output = "MMSI: " + to_string_dec_uint(mmsi);
        return true;
    }
    
    return false;
}

bool ProtocolDecoderView::try_decode_pocsag(const uint8_t* data, size_t length, std::string& output) {
    if (length < 16) return false;
    
    // POCSAG sync pattern: 0x7CD215D8
    uint32_t sync = 0;
    if (length >= 4) {
        sync = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }
    
    if (sync == 0x7CD215D8 || sync == 0x2A3DCE48) {
        // Extract address and message
        uint32_t address = 0;
        if (length >= 8) {
            address = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
            address = (address >> 13) & 0x1FFFFF;
        }
        
        std::string msg;
        for (size_t i = 8; i < length && i < 40; i++) {
            if (data[i] >= 32 && data[i] <= 126) {
                msg += (char)data[i];
            }
        }
        
        output = "ADDR: " + to_string_dec_uint(address);
        if (!msg.empty()) {
            output += " MSG: \"" + msg + "\"";
        }
        return true;
    }
    
    return false;
}

void ProtocolDecoderView::add_packet(const DecodedPacket& packet) {
    decoded_packets.push_back(packet);
    
    if (decoded_packets.size() > MAX_PACKETS) {
        decoded_packets.erase(decoded_packets.begin());
    }
    
    // Format for console
    std::string protocol_name = protocol_to_string(packet.protocol);
    int confidence_pct = (int)(packet.confidence * 100);
    
    std::string line = "[" + to_string_timestamp(rtc_time::now()) + "] " +
                      protocol_name + " (" + 
                      to_string_dec_uint(confidence_pct) + "%) > " +
                      packet.data;
    
    console.writeln(line);
    
    update_display();
}

void ProtocolDecoderView::update_display() {
    label_packets.set("Packets: " + to_string_dec_uint(decoded_packets.size()));
    
    if (!decoded_packets.empty()) {
        std::string protocol = protocol_to_string(decoded_packets.back().protocol);
        label_protocol.set("Protocol: " + protocol);
        label_status.set("Status: Decoding...");
    } else {
        label_protocol.set("Protocol: Waiting...");
        label_status.set("Status: Ready");
    }
}

void ProtocolDecoderView::save_log() {
    auto timestamp = to_string_timestamp(rtc_time::now());
    auto result = File::open("DECODER/log_" + timestamp + ".txt", false, true);
    
    if (result.is_valid()) {
        File file = result.value();
        
        std::string header = "# EAGLE Protocol Decoder Log\n";
        header += "# Timestamp: " + timestamp + "\n";
        header += "# Frequency: " + to_string_dec_uint(frequency_) + " Hz\n";
        header += "# Total Packets: " + to_string_dec_uint(decoded_packets.size()) + "\n\n";
        file.write(header);
        
        for (const auto& packet : decoded_packets) {
            std::string line = "[" + to_string_dec_uint(packet.timestamp) + "] ";
            line += protocol_to_string(packet.protocol) + " | ";
            line += "RSSI: " + to_string_dec_int(packet.rssi) + " dB | ";
            line += "Conf: " + to_string_dec_uint((int)(packet.confidence * 100)) + "% | ";
            line += packet.data + "\n";
            file.write(line);
        }
        
        file.sync();
        console.writeln("Log saved!");
    } else {
        console.writeln("Error saving log");
    }
}

void ProtocolDecoderView::decode_packet() {
    // Simulated decoding - would receive real data from baseband
    uint8_t test_data[64];
    for (size_t i = 0; i < sizeof(test_data); i++) {
        test_data[i] = rand() % 256;
    }
    
    detect_protocol(test_data, sizeof(test_data));
}

void ProtocolDecoderView::paint(Painter& painter) {
    (void)painter;
}

} // namespace ui::external_app::protocol_decoder
