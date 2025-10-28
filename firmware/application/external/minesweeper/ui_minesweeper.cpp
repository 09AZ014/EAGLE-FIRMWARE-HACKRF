/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#include "ui_minesweeper.hpp"
#include <cstdlib>

namespace ui::external_app::minesweeper {

MinesweeperView::MinesweeperView(NavigationView& nav) : nav_(nav) {}

void MinesweeperView::on_show() {
    if (initialized) return;
    reset_game();
    initialized = true;
}

void MinesweeperView::reset_game() {
    for(int y=0; y<GRID_H; y++) {
        for(int x=0; x<GRID_W; x++) {
            grid[y][x]=0; revealed[y][x]=false; flagged[y][x]=false;
        }
    }
    for(int i=0; i<MINES; i++) {
        int x, y;
        do { x=rand()%GRID_W; y=rand()%GRID_H; } while(grid[y][x]==-1);
        grid[y][x]=-1;
    }
    cursor_x=0; cursor_y=0; game_over=false; won=false; revealed_count=0;
}

void MinesweeperView::paint(Painter& p) {
    p.fill_rectangle({0,0,portapack::display.width(),portapack::display.height()}, Color::black());
    for(int y=0; y<GRID_H; y++) for(int x=0; x<GRID_W; x++) draw_cell(x,y);
    auto st = *ui::Theme::getInstance()->fg_yellow;
    if(game_over) p.draw_string({10,260}, st, won?"WON!":"BOOM!");
}

void MinesweeperView::draw_cell(int x, int y) {
    int sx=10+x*CELL_SIZE, sy=30+y*CELL_SIZE;
    bool cur=(x==cursor_x && y==cursor_y);
    Color bg=cur?Color::dark_grey():Color::grey();
    Color fg=Color::white();
    if(revealed[y][x]) {
        bg=Color::light_grey();
        if(grid[y][x]==-1) { painter.fill_rectangle({sx,sy,CELL_SIZE,CELL_SIZE}, Color::red()); return; }
        int n=count_adjacent_mines(x,y);
        painter.fill_rectangle({sx,sy,CELL_SIZE,CELL_SIZE}, bg);
        if(n>0) {
            auto st = *ui::Theme::getInstance()->fg_blue;
            painter.draw_string({sx+4,sy+2}, st, std::to_string(n));
        }
    } else {
        painter.fill_rectangle({sx,sy,CELL_SIZE,CELL_SIZE}, bg);
        if(flagged[y][x]) {
            auto st = *ui::Theme::getInstance()->fg_red;
            painter.draw_string({sx+6,sy+2}, st, "F");
        }
    }
    painter.draw_rectangle({sx,sy,CELL_SIZE,CELL_SIZE}, Color::black());
}

void MinesweeperView::reveal_cell(int x, int y) {
    if(revealed[y][x]||flagged[y][x]||game_over) return;
    revealed[y][x]=true; revealed_count++;
    if(grid[y][x]==-1) { game_over=true; return; }
    if(count_adjacent_mines(x,y)==0) {
        for(int dy=-1; dy<=1; dy++) for(int dx=-1; dx<=1; dx++) {
            int nx=x+dx, ny=y+dy;
            if(nx>=0&&nx<GRID_W&&ny>=0&&ny<GRID_H) reveal_cell(nx,ny);
        }
    }
    check_win();
}

void MinesweeperView::toggle_flag(int x, int y) {
    if(revealed[y][x]||game_over) return;
    flagged[y][x]=!flagged[y][x];
}

int MinesweeperView::count_adjacent_mines(int x, int y) {
    int c=0;
    for(int dy=-1; dy<=1; dy++) for(int dx=-1; dx<=1; dx++) {
        int nx=x+dx, ny=y+dy;
        if(nx>=0&&nx<GRID_W&&ny>=0&&ny<GRID_H&&grid[ny][nx]==-1) c++;
    }
    return c;
}

void MinesweeperView::check_win() {
    if(revealed_count+MINES==GRID_W*GRID_H) { game_over=true; won=true; }
}

void MinesweeperView::frame_sync() {
    set_dirty();
}

bool MinesweeperView::on_key(const KeyEvent key) {
    switch(key) {
        case KeyEvent::Up: if(cursor_y>0) cursor_y--; return true;
        case KeyEvent::Down: if(cursor_y<GRID_H-1) cursor_y++; return true;
        case KeyEvent::Left: if(cursor_x>0) cursor_x--; return true;
        case KeyEvent::Right: if(cursor_x<GRID_W-1) cursor_x++; return true;
        case KeyEvent::Select: reveal_cell(cursor_x, cursor_y); return true;
        case KeyEvent::Back: toggle_flag(cursor_x, cursor_y); return true;
        default: break;
    }
    if(game_over && key==KeyEvent::Select) reset_game();
    return false;
}

} // namespace ui::external_app::minesweeper
