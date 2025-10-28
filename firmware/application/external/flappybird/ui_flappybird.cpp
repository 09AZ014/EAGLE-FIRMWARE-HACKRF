/*
 * Flappy Bird implementation (simple physics + pipes)
 */

#include "ui_flappybird.hpp"

namespace ui::external_app::flappybird {

void FlappyBirdView::cls() {
    painter.fill_rectangle({0, 0, portapack::display.width(), portapack::display.height()}, Color::black());
}

void FlappyBirdView::fillrect(int x1, int y1, int x2, int y2, int color) {
    painter.fill_rectangle({x1, y1, x2 - x1, y2 - y1}, pp_colors[color]);
}

void FlappyBirdView::rect(int x1, int y1, int x2, int y2, int color) {
    painter.draw_rectangle({x1, y1, x2 - x1, y2 - y1}, pp_colors[color]);
}

void FlappyBirdView::attach(double /*delay_sec*/) {
    timer_enabled = true; // run at ~30fps using frame_sync divider
}

void FlappyBirdView::detach() { timer_enabled = false; }

void FlappyBirdView::check_game_timer() {
    if (!timer_enabled) return;
    if (++timer_div >= timer_div_target) {
        timer_div = 0;
        if (state == PLAYING) update_game();
    }
}

FlappyBirdView::FlappyBirdView(NavigationView& nav)
    : nav_{nav} {
    add_children({&dummy});
    attach(1.0 / 30.0);
}

void FlappyBirdView::on_show() {}

void FlappyBirdView::paint(Painter& /*p*/) {
    if (!initialized) {
        initialized = true;
        screen_w = screen_width;
        screen_h = screen_height;
        game_h = screen_h - GAME_TOP - GROUND_H;
        init_game();
    }
}

void FlappyBirdView::frame_sync() {
    check_game_timer();
    set_dirty();
}

void FlappyBirdView::init_game() {
    state = MENU;
    reset_world();
    draw_world_full();
}

void FlappyBirdView::reset_world() {
    bird_x = 32;
    bird_y = GAME_TOP + game_h / 2;
    vel_y = 0;
    score = 0;
    pipes.clear();
    spawn_counter = 0;
}

void FlappyBirdView::spawn_pipe() {
    Pipe p;
    p.x = screen_w;
    int margin = 20;
    int gap_center = GAME_TOP + margin + (rand() % (game_h - 2 * margin - PIPE_GAP));
    p.gap_y = gap_center;
    p.passed = false;
    pipes.push_back(p);
}

bool FlappyBirdView::collide() {
    // hit ground or top
    if (bird_y < GAME_TOP || bird_y + BIRD_H > GAME_TOP + game_h) return true;
    // pipes
    for (auto& p : pipes) {
        if (bird_x + BIRD_W > p.x && bird_x < p.x + PIPE_W) {
            // top rect: [GAME_TOP .. gap_y-PIPE_GAP/2)
            int gap_top = p.gap_y - PIPE_GAP / 2;
            int gap_bot = p.gap_y + PIPE_GAP / 2;
            if (bird_y < gap_top || bird_y + BIRD_H > gap_bot) return true;
        }
    }
    return false;
}

void FlappyBirdView::update_game() {
    // physics
    vel_y += 1;            // gravity
    if (vel_y > 6) vel_y = 6;
    bird_y += vel_y;

    // pipes
    spawn_counter++;
    if (spawn_counter >= pipe_spawn_period) {
        spawn_counter = 0;
        spawn_pipe();
    }
    for (auto& p : pipes) {
        p.x -= scroll_speed;
        if (!p.passed && p.x + PIPE_W < bird_x) {
            p.passed = true;
            score++;
        }
    }
    // remove off-screen
    while (!pipes.empty() && pipes.front().x + PIPE_W < 0) pipes.erase(pipes.begin());

    // collision
    if (collide()) {
        state = GAME_OVER;
    }

    // redraw everything (simple)
    draw_world_full();
}

void FlappyBirdView::draw_ui() {
    auto style = *ui::Theme::getInstance()->fg_blue;
    painter.draw_string({5, 2}, style, "Score: " + std::to_string(score));
}

void FlappyBirdView::draw_world_full() {
    // background
    cls();

    // sky area
    fillrect(0, 0, screen_w, GAME_TOP, White);

    // game area background
    fillrect(0, GAME_TOP, screen_w, GAME_TOP + game_h, Black);

    // ground
    int ground_y = GAME_TOP + game_h;
    painter.draw_hline({0, ground_y}, screen_w, Color::white());

    // pipes
    for (auto& p : pipes) {
        int gap_top = p.gap_y - PIPE_GAP / 2;
        int gap_bot = p.gap_y + PIPE_GAP / 2;
        // top pipe
        fillrect(p.x, GAME_TOP, p.x + PIPE_W, gap_top, Green);
        // bottom pipe
        fillrect(p.x, gap_bot, p.x + PIPE_W, GAME_TOP + game_h, Green);
    }

    // bird
    fillrect(bird_x, bird_y, bird_x + BIRD_W, bird_y + BIRD_H, Yellow);

    if (state == MENU) {
        auto y = GAME_TOP + game_h / 2 - 20;
        auto style = *ui::Theme::getInstance()->fg_green;
        painter.draw_string({70, y}, style, "FLAPPY BIRD");
        auto style2 = *ui::Theme::getInstance()->fg_light;
        painter.draw_string({38, y + 30}, style2, "PRESS SELECT TO START / FLAP");
    } else if (state == GAME_OVER) {
        auto y = GAME_TOP + 30;
        auto styleR = *ui::Theme::getInstance()->fg_red;
        auto styleY = *ui::Theme::getInstance()->fg_yellow;
        painter.draw_string({90, y}, styleR, "GAME OVER");
        painter.draw_string({80, y + 20}, styleY, "SCORE: " + std::to_string(score));
        auto styleG = *ui::Theme::getInstance()->fg_green;
        painter.draw_string({40, y + 50}, styleG, "PRESS SELECT TO RESTART");
    }

    // HUD
    draw_ui();
}

bool FlappyBirdView::on_key(const KeyEvent key) {
    if (key == KeyEvent::Select || key == KeyEvent::Up) {
        if (state == MENU) {
            state = PLAYING;
            reset_world();
            draw_world_full();
        } else if (state == PLAYING) {
            vel_y = -5; // flap impulse
        } else if (state == GAME_OVER) {
            state = MENU;
            reset_world();
            draw_world_full();
        }
        return true;
    }
    return false;
}

} // namespace ui::external_app::flappybird
