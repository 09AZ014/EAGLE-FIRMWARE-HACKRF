/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#ifndef __UI_GAME2048_H__
#define __UI_GAME2048_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::game2048 {

class Game2048View : public View {
   public:
    Game2048View(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "2048"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    void frame_sync();
    bool on_key(const KeyEvent key) override;

   private:
    void reset();
    void spawn();
    void move(int dx, int dy);
    void draw_tile(int x, int y, int val);
    bool can_move();

    NavigationView& nav_;
    Painter painter{};
    int grid[4][4], score=0;
    bool game_over=false, initialized=false;
    Button dummy{{240,0,0,0},""};
    MessageHandlerRegistration on_frame{Message::ID::DisplayFrameSync,[this](const Message*){this->frame_sync();}};
};

}
#endif
