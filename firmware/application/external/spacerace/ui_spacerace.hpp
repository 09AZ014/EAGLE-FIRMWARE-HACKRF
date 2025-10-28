/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#ifndef __UI_SPACERACE_H__
#define __UI_SPACERACE_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::spacerace {

class SpaceRaceView : public View {
   public:
    SpaceRaceView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "SpaceRace"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    void frame_sync();
    bool on_key(const KeyEvent key) override;

   private:
    void reset();
    void spawn_obstacle();
    void update();

    NavigationView& nav_;
    Painter painter{};
    int px=120, py=200, score=0, speed=3;
    struct Obs { int x,y,active; } obs[10];
    bool game_over=false, initialized=false;
    Button dummy{{240,0,0,0},""};
    MessageHandlerRegistration on_frame{Message::ID::DisplayFrameSync,[this](const Message*){this->frame_sync();}};
};

}
#endif
