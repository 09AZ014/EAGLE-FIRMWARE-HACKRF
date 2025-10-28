/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#include "ui_pong.hpp"

namespace ui::external_app::pong {

PongView::PongView(NavigationView& nav) : nav_(nav) {
}

void PongView::on_show() {
    if (initialized) return;
    SCREEN_W = portapack::display.width();
    SCREEN_H = portapack::display.height();
    lp_y = SCREEN_H / 2 - paddle_h / 2;
    rp_y = lp_y;
    reset_game();
    initialized = true;
}

void PongView::reset_game() {
    bx = SCREEN_W / 2;
    by = SCREEN_H / 2;
    bvx = (bvx >= 0) ? 2 : -2;
    bvy = (bvy >= 0) ? 2 : -2;
}

void PongView::paint(Painter& p) {
    // background
    p.fill_rectangle({0, 0, SCREEN_W, SCREEN_H}, Color::black());
    // center line
    for (int y = 0; y < SCREEN_H; y += 8) {
        p.fill_rectangle({SCREEN_W / 2 - 1, y, 2, 4}, Color::dark_grey());
    }
    // paddles
    p.fill_rectangle({4, lp_y, paddle_w, paddle_h}, Color::white());
    p.fill_rectangle({SCREEN_W - 8, rp_y, paddle_w, paddle_h}, Color::white());
    // ball
    p.fill_rectangle({bx - BR, by - BR, BR * 2, BR * 2}, Color::green());
    // scores
    auto style = *ui::Theme::getInstance()->fg_yellow;
    p.draw_string({SCREEN_W / 2 - 50, 4}, style, std::to_string(lscore));
    p.draw_string({SCREEN_W / 2 + 40, 4}, style, std::to_string(rscore));
}

void PongView::draw_scene() {
    set_dirty();
}

void PongView::update_ball() {
    bx += bvx;
    by += bvy;

    // wall collision top/bottom
    if (by - BR <= 0) { by = BR; bvy = -bvy; }
    if (by + BR >= SCREEN_H) { by = SCREEN_H - BR; bvy = -bvy; }

    // paddle collision left
    if (bx - BR <= 4 + paddle_w) {
        if (by >= lp_y && by <= lp_y + paddle_h) {
            bx = 4 + paddle_w + BR;
            bvx = -bvx;
        }
    }
    // paddle collision right
    if (bx + BR >= SCREEN_W - 8) {
        if (by >= rp_y && by <= rp_y + paddle_h) {
            bx = SCREEN_W - 8 - BR;
            bvx = -bvx;
        }
    }

    // score left/right
    if (bx < 0) { rscore++; reset_game(); }
    if (bx > SCREEN_W) { lscore++; reset_game(); }

    // simple AI for right paddle
    if (by < rp_y + paddle_h / 2) rp_y -= 2; else rp_y += 2;
    if (rp_y < 0) rp_y = 0; if (rp_y + paddle_h > SCREEN_H) rp_y = SCREEN_H - paddle_h;
}

void PongView::frame_sync() {
    update_ball();
    draw_scene();
}

bool PongView::on_key(const KeyEvent key) {
    switch (key) {
        case KeyEvent::Up:
            lp_y -= 6; if (lp_y < 0) lp_y = 0; return true;
        case KeyEvent::Down:
            lp_y += 6; if (lp_y + paddle_h > SCREEN_H) lp_y = SCREEN_H - paddle_h; return true;
        case KeyEvent::Right:
        case KeyEvent::Left:
            return true;
        case KeyEvent::Select:
            reset_game(); return true;
        default:
            break;
    }
    return false;
}

} // namespace ui::external_app::pong