/*
 * EAGLE-FIRMWARE - Rock-Paper-Scissors Game
 * by 09AZO14
 */
#include "ui_rps.hpp"
#include <cstdlib>
#include <ctime>

namespace ui::external_app::rps {

RPSView::RPSView(NavigationView& nav) : nav_(nav) {
    srand(time(nullptr));
}

void RPSView::on_show() {
    if (initialized) return;
    SCREEN_W = portapack::display.width();
    SCREEN_H = portapack::display.height();
    reset_game();
    initialized = true;
}

void RPSView::reset_game() {
    player_score = 0;
    ai_score = 0;
    draws = 0;
    round = 0;
    player_choice = Choice::NONE;
    ai_choice = Choice::NONE;
    cursor_choice = Choice::ROCK;
    game_over = false;
    waiting_for_next = false;
    set_dirty();
}

void RPSView::paint(Painter& p) {
    p.fill_rectangle({0, 0, SCREEN_W, SCREEN_H}, Color::black());
    
    // Title
    auto style_title = *ui::Theme::getInstance()->fg_yellow;
    p.draw_string({4, 4}, style_title, "Rock-Paper-Scissors");
    
    // Round and score
    std::string round_str = "Round " + std::to_string(round) + "/" + std::to_string(MAX_ROUNDS);
    p.draw_string({4, 18}, style_title, round_str);
    
    std::string score_str = "You:" + std::to_string(player_score) + " AI:" + std::to_string(ai_score) + " Draws:" + std::to_string(draws);
    p.draw_string({SCREEN_W - 130, 18}, style_title, score_str);
    
    // Draw choices
    int y_pos = 60;
    int spacing = 70;
    
    draw_choice(SCREEN_W/2 - spacing, y_pos, Choice::ROCK, cursor_choice == Choice::ROCK && !waiting_for_next);
    draw_choice(SCREEN_W/2, y_pos, Choice::PAPER, cursor_choice == Choice::PAPER && !waiting_for_next);
    draw_choice(SCREEN_W/2 + spacing, y_pos, Choice::SCISSORS, cursor_choice == Choice::SCISSORS && !waiting_for_next);
    
    // Draw result
    if (waiting_for_next || game_over) {
        int result_y = y_pos + 80;
        
        // Player choice
        p.draw_string({20, result_y}, style_title, "You:");
        draw_choice(50, result_y, player_choice, false);
        
        // AI choice
        p.draw_string({SCREEN_W - 80, result_y}, style_title, "AI:");
        draw_choice(SCREEN_W - 50, result_y, ai_choice, false);
        
        // Result message
        std::string msg;
        Color color;
        if (last_result == Result::WIN) {
            msg = "YOU WIN!";
            color = Color::green();
        } else if (last_result == Result::LOSE) {
            msg = "AI WINS!";
            color = Color::red();
        } else {
            msg = "DRAW!";
            color = Color::yellow();
        }
        
        int msg_x = (SCREEN_W - msg.length() * 8) / 2;
        p.draw_string({msg_x, result_y + 40}, {color, Color::black()}, msg);
    }
    
    // Game over
    if (game_over) {
        int y = SCREEN_H - 60;
        std::string final_msg;
        Color final_color;
        
        if (player_score > ai_score) {
            final_msg = "CONGRATULATIONS! YOU WON!";
            final_color = Color::green();
        } else if (ai_score > player_score) {
            final_msg = "AI WON THE MATCH!";
            final_color = Color::red();
        } else {
            final_msg = "IT'S A TIE!";
            final_color = Color::yellow();
        }
        
        int msg_x = (SCREEN_W - final_msg.length() * 8) / 2;
        p.fill_rectangle({msg_x - 4, y - 4, (int)final_msg.length() * 8 + 8, 20}, Color::black());
        p.draw_rectangle({msg_x - 4, y - 4, (int)final_msg.length() * 8 + 8, 20}, final_color);
        p.draw_string({msg_x, y}, {final_color, Color::black()}, final_msg);
        
        auto style = *ui::Theme::getInstance()->fg_light_grey;
        p.draw_string({SCREEN_W/2 - 60, y + 24}, style, "SELECT=New Game");
    } else if (waiting_for_next) {
        auto style = *ui::Theme::getInstance()->fg_light_grey;
        p.draw_string({SCREEN_W/2 - 60, SCREEN_H - 30}, style, "SELECT=Continue");
    } else {
        auto style = *ui::Theme::getInstance()->fg_light_grey;
        p.draw_string({SCREEN_W/2 - 70, SCREEN_H - 30}, style, "Arrows=Choose SELECT=Play");
    }
}

void RPSView::draw_choice(int x, int y, Choice choice, bool highlighted) {
    Color color = highlighted ? Color::yellow() : Color::white();
    Color bg = highlighted ? Color::dark_blue() : Color::black();
    
    // Draw box
    if (highlighted) {
        painter.fill_rectangle({x - 25, y - 15, 50, 50}, bg);
    }
    painter.draw_rectangle({x - 25, y - 15, 50, 50}, color);
    
    std::string label;
    switch (choice) {
        case Choice::ROCK:
            label = "ROCK";
            // Draw rock symbol
            painter.fill_circle({x, y + 5}, 12, color);
            break;
        case Choice::PAPER:
            label = "PAPER";
            // Draw paper symbol
            painter.draw_rectangle({x - 10, y, 20, 15}, color);
            painter.fill_rectangle({x - 8, y + 2, 16, 11}, color);
            break;
        case Choice::SCISSORS:
            label = "SCIS";
            // Draw scissors symbol
            painter.draw_line({x - 8, y}, {x + 8, y + 15}, color);
            painter.draw_line({x + 8, y}, {x - 8, y + 15}, color);
            break;
        default:
            return;
    }
    
    // Draw label
    auto style = highlighted ? *ui::Theme::getInstance()->fg_yellow : *ui::Theme::getInstance()->fg_white;
    int label_x = x - (label.length() * 8 / 2);
    painter.draw_string({label_x, y - 28}, style, label);
}

void RPSView::make_choice(Choice choice) {
    if (waiting_for_next || game_over) return;
    
    player_choice = choice;
    ai_choice = get_ai_choice();
    last_result = determine_winner(player_choice, ai_choice);
    
    round++;
    
    if (last_result == Result::WIN) {
        player_score++;
    } else if (last_result == Result::LOSE) {
        ai_score++;
    } else {
        draws++;
    }
    
    if (round >= MAX_ROUNDS) {
        game_over = true;
    } else {
        waiting_for_next = true;
    }
    
    set_dirty();
}

Choice RPSView::get_ai_choice() {
    int r = rand() % 3;
    return static_cast<Choice>(r + 1);
}

Result RPSView::determine_winner(Choice player, Choice ai) {
    if (player == ai) return Result::DRAW;
    
    if ((player == Choice::ROCK && ai == Choice::SCISSORS) ||
        (player == Choice::PAPER && ai == Choice::ROCK) ||
        (player == Choice::SCISSORS && ai == Choice::PAPER)) {
        return Result::WIN;
    }
    
    return Result::LOSE;
}

bool RPSView::on_key(const KeyEvent key) {
    if (game_over) {
        if (key == KeyEvent::Select) {
            reset_game();
            return true;
        }
        return false;
    }
    
    if (waiting_for_next) {
        if (key == KeyEvent::Select) {
            waiting_for_next = false;
            player_choice = Choice::NONE;
            ai_choice = Choice::NONE;
            cursor_choice = Choice::ROCK;
            set_dirty();
            return true;
        }
        return false;
    }
    
    switch (key) {
        case KeyEvent::Left:
            if (cursor_choice == Choice::PAPER) cursor_choice = Choice::ROCK;
            else if (cursor_choice == Choice::SCISSORS) cursor_choice = Choice::PAPER;
            set_dirty();
            return true;
            
        case KeyEvent::Right:
            if (cursor_choice == Choice::ROCK) cursor_choice = Choice::PAPER;
            else if (cursor_choice == Choice::PAPER) cursor_choice = Choice::SCISSORS;
            set_dirty();
            return true;
            
        case KeyEvent::Select:
            make_choice(cursor_choice);
            return true;
            
        default:
            break;
    }
    
    return false;
}

} // namespace ui::external_app::rps
