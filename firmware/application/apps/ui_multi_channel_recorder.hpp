/* EAGLE-FIRMWARE - Multi-Channel Recorder (stub) */
#ifndef __UI_MULTI_CHANNEL_RECORDER_H__
#define __UI_MULTI_CHANNEL_RECORDER_H__

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
class MultiChannelRecorderView : public View {
   public:
    explicit MultiChannelRecorderView(NavigationView& nav);
    ~MultiChannelRecorderView();
    std::string title() const override { return "Multi-Channel Recorder"; }
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

    RecordView record_view{{0 * 8, 1 * 16, screen_width, 1 * 16}, u"MCR_????.*", captures_dir, RecordView::FileType::RawS16, 16384, 3};
    spectrum::WaterfallView waterfall{false};
};
}

#endif


