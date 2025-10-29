/*
 * EAGLE-FIRMWARE - Tic-Tac-Toe Game
 * Advanced AI with Minimax algorithm
 * by 09AZO14
 */
#include "ui_tictactoe.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace ui::external_app::tictactoe {

TicTacToeView::TicTacToeView(NavigationView& nav) : nav_(nav) {
    srand(time(nullptr));
}

void TicTacToeView::on_show() {
    if (initialized) return;
    SCREEN_W = portapack::display.width();
    SCREEN_H = portapack::display.height();
    
    cell_size = std::min(SCREEN_W, SCREEN_H - 40) / 3;
    board_offset_x = (SCREEN_W - cell_size * 3) / 2;
    board_offset_y = 30;
    
    reset_game();
    initialized = true;
}

void TicTacToeView::reset_game() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = Player::NONE;
        }
    }
    cursor_row = 1;
    cursor_col = 1;
    game_state = GameState::PLAYING;
    set_dirty();
}

void TicTacToeView::paint(Painter& p) {
    p.fill_rectangle({0, 0, SCREEN_W, SCREEN_H}, Color::black());
    
    // Draw title bar
    auto style_title = *ui::Theme::getInstance()->fg_yellow;
    p.draw_string({4, 4}, style_title, "Tic-Tac-Toe");
    
    // Draw difficulty indicator
    std::string diff_str = "Difficulty: ";
    if (difficulty == Difficulty::EASY) diff_str += "Easy";
    else if (difficulty == Difficulty::MEDIUM) diff_str += "Medium";
    else diff_str += "Hard";
    p.draw_string({4, 16}, style_title, diff_str);
    
    // Draw scores
    std::string score_str = "You:" + std::to_string(human_score) + " AI:" + std::to_string(ai_score) + " Draws:" + std::to_string(draws);
    p.draw_string({SCREEN_W - 120, 16}, style_title, score_str);
    
    // Draw grid
    for (int i = 1; i < GRID_SIZE; i++) {
        // Vertical lines
        p.fill_rectangle({board_offset_x + i * cell_size - 2, board_offset_y, 4, cell_size * 3}, Color::white());
        // Horizontal lines
        p.fill_rectangle({board_offset_x, board_offset_y + i * cell_size - 2, cell_size * 3, 4}, Color::white());
    }
    
    // Draw cells
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            draw_cell(row, col, board[row][col]);
        }
    }
    
    // Draw cursor if game is active
    if (game_state == GameState::PLAYING) {
        int cx = board_offset_x + cursor_col * cell_size + cell_size / 2;
        int cy = board_offset_y + cursor_row * cell_size + cell_size / 2;
        p.draw_rectangle({cx - cell_size / 2 + 4, cy - cell_size / 2 + 4, cell_size - 8, cell_size - 8}, Color::yellow());
    }
    
    // Draw game over message
    if (game_state != GameState::PLAYING) {
        std::string msg;
        Color color;
        if (game_state == GameState::HUMAN_WIN) {
            msg = "YOU WIN!";
            color = Color::green();
        } else if (game_state == GameState::AI_WIN) {
            msg = "AI WINS!";
            color = Color::red();
        } else {
            msg = "DRAW!";
            color = Color::yellow();
        }
        
        int msg_width = msg.length() * 8;
        int msg_x = (SCREEN_W - msg_width) / 2;
        int msg_y = board_offset_y + cell_size * 3 + 10;
        
        p.fill_rectangle({msg_x - 4, msg_y - 4, msg_width + 8, 20}, Color::black());
        p.draw_rectangle({msg_x - 4, msg_y - 4, msg_width + 8, 20}, color);
        p.draw_string({msg_x, msg_y}, {color, Color::black()}, msg);
        
        auto style = *ui::Theme::getInstance()->fg_light_grey;
        p.draw_string({msg_x - 20, msg_y + 24}, style, "SELECT=New Game");
    }
}

void TicTacToeView::draw_cell(int row, int col, Player player) {
    if (player == Player::NONE) return;
    
    int cx = board_offset_x + col * cell_size + cell_size / 2;
    int cy = board_offset_y + row * cell_size + cell_size / 2;
    int size = cell_size / 3;
    
    if (player == Player::HUMAN) {
        // Draw X
        painter.draw_line({cx - size, cy - size}, {cx + size, cy + size}, Color::blue());
        painter.draw_line({cx + size, cy - size}, {cx - size, cy + size}, Color::blue());
        painter.draw_line({cx - size + 1, cy - size}, {cx + size + 1, cy + size}, Color::blue());
        painter.draw_line({cx + size + 1, cy - size}, {cx - size + 1, cy + size}, Color::blue());
    } else {
        // Draw O
        for (int r = size - 2; r <= size; r++) {
            painter.draw_circle({cx, cy}, r, Color::red());
        }
    }
}

void TicTacToeView::make_move(int row, int col) {
    if (game_state != GameState::PLAYING) return;
    if (board[row][col] != Player::NONE) return;
    
    board[row][col] = Player::HUMAN;
    set_dirty();
    
    game_state = check_winner();
    if (game_state == GameState::HUMAN_WIN) {
        human_score++;
        return;
    }
    if (is_board_full()) {
        game_state = GameState::DRAW;
        draws++;
        return;
    }
    
    // AI turn
    ai_move();
    set_dirty();
    
    game_state = check_winner();
    if (game_state == GameState::AI_WIN) {
        ai_score++;
    } else if (is_board_full()) {
        game_state = GameState::DRAW;
        draws++;
    }
}

GameState TicTacToeView::check_winner() {
    // Check rows and columns
    for (int i = 0; i < GRID_SIZE; i++) {
        if (board[i][0] != Player::NONE && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == Player::HUMAN) ? GameState::HUMAN_WIN : GameState::AI_WIN;
        }
        if (board[0][i] != Player::NONE && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == Player::HUMAN) ? GameState::HUMAN_WIN : GameState::AI_WIN;
        }
    }
    
    // Check diagonals
    if (board[0][0] != Player::NONE && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == Player::HUMAN) ? GameState::HUMAN_WIN : GameState::AI_WIN;
    }
    if (board[0][2] != Player::NONE && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[0][2] == Player::HUMAN) ? GameState::HUMAN_WIN : GameState::AI_WIN;
    }
    
    return GameState::PLAYING;
}

bool TicTacToeView::is_board_full() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == Player::NONE) return false;
        }
    }
    return true;
}

void TicTacToeView::ai_move() {
    if (difficulty == Difficulty::EASY) {
        ai_move_easy();
    } else if (difficulty == Difficulty::MEDIUM) {
        ai_move_medium();
    } else {
        ai_move_hard();
    }
}

void TicTacToeView::ai_move_easy() {
    // Random move
    int attempts = 0;
    while (attempts < 100) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        if (board[row][col] == Player::NONE) {
            board[row][col] = Player::AI;
            return;
        }
        attempts++;
    }
}

void TicTacToeView::ai_move_medium() {
    // 50% chance of optimal move, 50% random
    if (rand() % 2 == 0) {
        ai_move_hard();
    } else {
        ai_move_easy();
    }
}

void TicTacToeView::ai_move_hard() {
    // Use minimax algorithm for perfect play
    int best_move = get_best_move();
    if (best_move != -1) {
        int row = best_move / GRID_SIZE;
        int col = best_move % GRID_SIZE;
        board[row][col] = Player::AI;
    }
}

int TicTacToeView::evaluate_board() {
    // Check if AI wins
    if (check_winner() == GameState::AI_WIN) return 10;
    // Check if human wins
    if (check_winner() == GameState::HUMAN_WIN) return -10;
    // Draw or ongoing
    return 0;
}

int TicTacToeView::minimax(int depth, bool is_maximizing) {
    int score = evaluate_board();
    
    // Terminal state
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (is_board_full()) return 0;
    
    if (is_maximizing) {
        int best = -1000;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[i][j] == Player::NONE) {
                    board[i][j] = Player::AI;
                    best = std::max(best, minimax(depth + 1, false));
                    board[i][j] = Player::NONE;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[i][j] == Player::NONE) {
                    board[i][j] = Player::HUMAN;
                    best = std::min(best, minimax(depth + 1, true));
                    board[i][j] = Player::NONE;
                }
            }
        }
        return best;
    }
}

int TicTacToeView::get_best_move() {
    int best_val = -1000;
    int best_move = -1;
    
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == Player::NONE) {
                board[i][j] = Player::AI;
                int move_val = minimax(0, false);
                board[i][j] = Player::NONE;
                
                if (move_val > best_val) {
                    best_move = i * GRID_SIZE + j;
                    best_val = move_val;
                }
            }
        }
    }
    
    return best_move;
}

bool TicTacToeView::on_key(const KeyEvent key) {
    if (game_state != GameState::PLAYING) {
        if (key == KeyEvent::Select) {
            reset_game();
            return true;
        }
        return false;
    }
    
    switch (key) {
        case KeyEvent::Up:
            cursor_row = (cursor_row - 1 + GRID_SIZE) % GRID_SIZE;
            set_dirty();
            return true;
        case KeyEvent::Down:
            cursor_row = (cursor_row + 1) % GRID_SIZE;
            set_dirty();
            return true;
        case KeyEvent::Left:
            cursor_col = (cursor_col - 1 + GRID_SIZE) % GRID_SIZE;
            set_dirty();
            return true;
        case KeyEvent::Right:
            cursor_col = (cursor_col + 1) % GRID_SIZE;
            set_dirty();
            return true;
        case KeyEvent::Select:
            make_move(cursor_row, cursor_col);
            return true;
        default:
            break;
    }
    return false;
}

bool TicTacToeView::on_touch(const TouchEvent event) {
    if (event.type != TouchEvent::Type::End) return false;
    if (game_state != GameState::PLAYING) {
        reset_game();
        return true;
    }
    
    int touch_x = event.point.x();
    int touch_y = event.point.y();
    
    if (touch_x < board_offset_x || touch_x > board_offset_x + cell_size * 3) return false;
    if (touch_y < board_offset_y || touch_y > board_offset_y + cell_size * 3) return false;
    
    int col = (touch_x - board_offset_x) / cell_size;
    int row = (touch_y - board_offset_y) / cell_size;
    
    make_move(row, col);
    return true;
}

} // namespace ui::external_app::tictactoe
