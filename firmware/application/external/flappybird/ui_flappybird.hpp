/*
 * Flappy Bird UI for PortaPack (rectangle graphics)
 */

#ifndef __UI_FLAPPYBIRD_H__
#define __UI_FLAPPYBIRD_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "event_m0.hpp"
#include "message.hpp"
#include "irq_controls.hpp"
#include "lpc43xx_cpp.hpp"
#include "ui_widget.hpp"

namespace ui::external_app::flappybird {

enum ColorIndex {
    White,
    Blue,
    Yellow,
    Purple,
    Green,
    Red,
    Maroon,
    Orange,
    Black,
};

class FlappyBirdView : public View {
   public:
    FlappyBirdView(NavigationView& nav);
    void on_show() override;

    std::string title() const override { return "Flappy Bird"; }

    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    void frame_sync();
    bool on_key(KeyEvent key) override;

   private:
    // helpers
    void cls();
    void fillrect(int x1, int y1, int x2, int y2, int color);
    void rect(int x1, int y1, int x2, int y2, int color);

    void attach(double delay_sec);
    void detach();
    void check_game_timer();

    // game loop
    void init_game();
    void reset_world();
    void update_game();
    void draw_world_full();
    void draw_ui();
    void spawn_pipe();
    bool collide();

    // constants
    static constexpr int INFO_H = 20;
    static constexpr int GAME_TOP = INFO_H + 2;
    static constexpr int GROUND_H = 16;
    static constexpr int BIRD_W = 10;
    static constexpr int BIRD_H = 8;
    static constexpr int PIPE_W = 26;
    static constexpr int PIPE_GAP = 48; // vertical gap

    const Color pp_colors[9] = {
        Color::white(), Color::blue(), Color::yellow(), Color::purple(),
        Color::green(), Color::red(), Color::magenta(), Color::orange(), Color::black()};

    struct Pipe { int x; int gap_y; bool passed; };

    NavigationView& nav_;
    Painter painter{};

    // timer
    bool timer_enabled = false;
    uint32_t timer_div = 0;
    uint32_t timer_div_target = 2; // ~30 fps (frame_sync ~60Hz)

    // state
    bool initialized = false;
    enum { MENU, PLAYING, GAME_OVER } state = MENU;

    int screen_w = 0, screen_h = 0;
    int game_h = 0;

    int bird_x = 32, bird_y = 100;
    int vel_y = 0;

    std::vector<Pipe> pipes{};
    int spawn_counter = 0;
    int pipe_spawn_period = 70; // frames at 30 fps ~ 2.3s
    int scroll_speed = 2;

    int score = 0;

    // UI widgets
    Button dummy{{screen_width, 0, 0, 0}, ""};

    MessageHandlerRegistration message_handler_frame_sync{
        Message::ID::DisplayFrameSync,
        [this](const Message* const) { this->frame_sync(); }};
};

} // namespace ui::external_app::flappybird

#endif /* __UI_FLAPPYBIRD_H__ */
