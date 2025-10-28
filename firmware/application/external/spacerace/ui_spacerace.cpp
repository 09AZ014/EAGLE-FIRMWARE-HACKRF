/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#include "ui_spacerace.hpp"
#include <cstdlib>

namespace ui::external_app::spacerace {

SpaceRaceView::SpaceRaceView(NavigationView& nav) : nav_(nav) {}

void SpaceRaceView::on_show() {
    if(initialized) return;
    reset();
    initialized=true;
}

void SpaceRaceView::reset() {
    px=120; py=200; score=0; speed=3; game_over=false;
    for(int i=0;i<10;i++) obs[i].active=0;
}

void SpaceRaceView::spawn_obstacle() {
    for(int i=0;i<10;i++) {
        if(!obs[i].active) {
            obs[i].x=rand()%200+20; obs[i].y=-20; obs[i].active=1;
            break;
        }
    }
}

void SpaceRaceView::update() {
    if(game_over) return;
    score++;
    if(score%100==0 && speed<10) speed++;
    if(score%30==0) spawn_obstacle();
    for(int i=0;i<10;i++) {
        if(obs[i].active) {
            obs[i].y+=speed;
            if(obs[i].y>320) obs[i].active=0;
            if(obs[i].y>py-10 && obs[i].y<py+20 && obs[i].x>px-10 && obs[i].x<px+10) game_over=true;
        }
    }
}

void SpaceRaceView::paint(Painter& p) {
    p.fill_rectangle({0,0,240,320}, Color::black());
    p.fill_rectangle({px-5,py-10,10,20}, Color::cyan());
    for(int i=0;i<10;i++) {
        if(obs[i].active) p.fill_rectangle({obs[i].x-8,obs[i].y-8,16,16}, Color::red());
    }
    auto st = ui::Theme::getInstance()->fg_green;
    p.draw_string({10,10}, st, "Score: "+std::to_string(score));
    if(game_over) p.draw_string({60,150}, st, "GAME OVER!");
}

void SpaceRaceView::frame_sync() {
    update();
    set_dirty();
}

bool SpaceRaceView::on_key(const KeyEvent key) {
    if(game_over && key==KeyEvent::Select) { reset(); return true; }
    switch(key) {
        case KeyEvent::Left: if(px>20) px-=8; return true;
        case KeyEvent::Right: if(px<220) px+=8; return true;
        default: break;
    }
    return false;
}

}
