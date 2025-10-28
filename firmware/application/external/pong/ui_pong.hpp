/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#ifndef __UI_PONG_H__
#define __UI_PONG_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::pong {

class PongView : public View {
   public:
    PongView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "Pong"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    void frame_sync();
    bool on_key(const KeyEvent key) override;

   private:
    void reset_game();
    void draw_scene();
    void update_ball();

    NavigationView& nav_;
    Painter painter{};

    // Screen
    int SCREEN_W = 0;
    int SCREEN_H = 0;

    // Ball
    int bx = 0, by = 0;
    int bvx = 2, bvy = 2;
    static constexpr int BR = 3; // ball radius

    // Paddles
    int paddle_h = 30;
    int paddle_w = 4;
    int lp_y = 0; // left paddle y (x fixed at 4)
    int rp_y = 0; // right paddle y (x fixed at SCREEN_W-8)
    int rp_dir = 1; // simple AI direction

    // Scores
    int lscore = 0;
    int rscore = 0;

    Button dummy{{screen_width, 0, 0, 0}, ""};
    bool initialized{false};

    MessageHandlerRegistration on_frame{
        Message::ID::DisplayFrameSync,
        [this](const Message* const) {
            this->frame_sync();
        }};
};

} // namespace ui::external_app::pong

#endif /* __UI_PONG_H__ */