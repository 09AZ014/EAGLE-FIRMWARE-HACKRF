/* EAGLE-FIRMWARE - Triggered IQ Recorder (stub) */
#ifndef __UI_TRIGGERED_IQ_REC_H__
#define __UI_TRIGGERED_IQ_REC_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "ui_receiver.hpp"
#include "ui_freq_field.hpp"
#include "ui_rssi.hpp"
#include "ui_channel.hpp"
#include "ui_record_view.hpp"
#include "ui_spectrum.hpp"
#include "radio_state.hpp"

namespace ui {
class TriggeredIQRecorderView : public View {
   public:
    explicit TriggeredIQRecorderView(NavigationView& nav);
    ~TriggeredIQRecorderView();
    std::string title() const override { return "Triggered IQ Recorder"; }
    void on_show() override;
    void on_hide() override;
    void focus() override;

   private:
    NavigationView& nav_;
    RxRadioState radio_state_{ReceiverModel::Mode::Capture};

    RxFrequencyField field_frequency{{0 * 8, 0 * 16}, nav_};
    RFAmpField field_rf_amp{{11 * 8, 0 * 16}};
    LNAGainField field_lna{{13 * 8, 0 * 16}};
    VGAGainField field_vga{{16 * 8, 0 * 16}};
    RSSI rssi{{19 * 8 - 4, 3, 6 * 8, 4}};
    Channel channel{{19 * 8 - 4, 8, 6 * 8, 4}};

    OptionsField option_trigger{{0 * 8, 1 * 16}, 3, {{"SQ ", 0}, {"PEAK", 1}, {"MAN ", 2}}};
    NumberField field_level{{5 * 8, 1 * 16}, 3, {0, 255}, 1, ' '};
    Checkbox check_prebuf{{10 * 8, 1 * 16}, 4, "Pre", true};
    Checkbox check_postbuf{{15 * 8, 1 * 16}, 4, "Post", true};

    RecordView record_view{{0 * 8, 2 * 16, screen_width, 1 * 16}, u"TRG_????.*", captures_dir, RecordView::FileType::RawS16, 16384, 3};
    spectrum::WaterfallView waterfall{false};
};
}

#endif


