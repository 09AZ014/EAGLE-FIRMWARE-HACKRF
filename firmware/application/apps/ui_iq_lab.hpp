/* EAGLE-FIRMWARE - IQ Lab (stub) */
#ifndef __UI_IQ_LAB_H__
#define __UI_IQ_LAB_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "ui_receiver.hpp"
#include "ui_freq_field.hpp"
#include "ui_rssi.hpp"
#include "ui_channel.hpp"
#include "ui_spectrum.hpp"
#include "radio_state.hpp"

namespace ui {
class IQLabView : public View {
   public:
    explicit IQLabView(NavigationView& nav);
    ~IQLabView();
    std::string title() const override { return "IQ Lab"; }
    void on_show() override;
    void on_hide() override;
    void focus() override;

   private:
    NavigationView& nav_;
    RxRadioState radio_state_{
        100'000'000 /* freq */, 2500000 /* bw */, 3072000 /* sr */, ReceiverModel::Mode::SpectrumAnalysis};

    RxFrequencyField field_frequency{{0 * 8, 0 * 16}, nav_};
    RFAmpField field_rf_amp{{11 * 8, 0 * 16}};
    LNAGainField field_lna{{13 * 8, 0 * 16}};
    VGAGainField field_vga{{16 * 8, 0 * 16}};
    RSSI rssi{{19 * 8 - 4, 3, 6 * 8, 4}};
    Channel channel{{19 * 8 - 4, 8, 6 * 8, 4}};

    spectrum::WaterfallView waterfall{true};
};
}

#endif


