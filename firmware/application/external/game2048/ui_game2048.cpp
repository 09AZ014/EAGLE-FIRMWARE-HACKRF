/*
 * EAGLE-FIRMWARE by 09AZO14
 */
#include "ui_game2048.hpp"
#include <cstdlib>

namespace ui::external_app::game2048 {

Game2048View::Game2048View(NavigationView& nav) : nav_(nav) {}

void Game2048View::on_show() {
    if(initialized) return;
    reset();
    initialized=true;
}

void Game2048View::reset() {
    for(int y=0;y<4;y++) for(int x=0;x<4;x++) grid[y][x]=0;
    score=0; game_over=false;
    spawn(); spawn();
}

void Game2048View::spawn() {
    int empty[16][2], cnt=0;
    for(int y=0;y<4;y++) for(int x=0;x<4;x++) if(!grid[y][x]) { empty[cnt][0]=x; empty[cnt][1]=y; cnt++; }
    if(cnt>0) { int i=rand()%cnt; grid[empty[i][1]][empty[i][0]]=(rand()%10<9)?2:4; }
}

void Game2048View::move(int dx, int dy) {
    if(game_over) return;
    bool moved=false;
    int temp[4][4]; for(int y=0;y<4;y++) for(int x=0;x<4;x++) temp[y][x]=grid[y][x];
    for(int i=0;i<3;i++) {
        for(int y=0;y<4;y++) for(int x=0;x<4;x++) {
            int nx=x+dx, ny=y+dy;
            if(nx>=0&&nx<4&&ny>=0&&ny<4) {
                if(grid[ny][nx]==0 && grid[y][x]!=0) { grid[ny][nx]=grid[y][x]; grid[y][x]=0; moved=true; }
                else if(grid[ny][nx]==grid[y][x] && grid[y][x]!=0) { grid[ny][nx]*=2; score+=grid[ny][nx]; grid[y][x]=0; moved=true; }
            }
        }
    }
    if(moved) { spawn(); if(!can_move()) game_over=true; }
}

bool Game2048View::can_move() {
    for(int y=0;y<4;y++) for(int x=0;x<4;x++) {
        if(grid[y][x]==0) return true;
        if(x<3 && grid[y][x]==grid[y][x+1]) return true;
        if(y<3 && grid[y][x]==grid[y+1][x]) return true;
    }
    return false;
}

void Game2048View::paint(Painter& p) {
    p.fill_rectangle({0,0,240,320}, Color::dark_grey());
    for(int y=0;y<4;y++) for(int x=0;x<4;x++) draw_tile(x,y,grid[y][x]);
    auto st = ui::Theme::getInstance()->fg_yellow;
    p.draw_string({10,10}, st, "Score: "+std::to_string(score));
    if(game_over) p.draw_string({60,280}, st, "GAME OVER!");
}

void Game2048View::draw_tile(int x, int y, int val) {
    int tx=10+x*55, ty=40+y*55;
    Color bg=(val==0)?Color::grey():(val==2)?Color::light_grey():(val==4)?Color::yellow():(val==8)?Color::orange():(val<128)?Color::red():Color::magenta();
    painter.fill_rectangle({tx,ty,50,50}, bg);
    if(val>0) {
        auto st = ui::Theme::getInstance()->fg_dark;
        painter.draw_string({tx+10,ty+18}, st, std::to_string(val));
    }
}

void Game2048View::frame_sync() {
    set_dirty();
}

bool Game2048View::on_key(const KeyEvent key) {
    if(game_over && key==KeyEvent::Select) { reset(); return true; }
    switch(key) {
        case KeyEvent::Up: move(0,-1); return true;
        case KeyEvent::Down: move(0,1); return true;
        case KeyEvent::Left: move(-1,0); return true;
        case KeyEvent::Right: move(1,0); return true;
        default: break;
    }
    return false;
}

}
