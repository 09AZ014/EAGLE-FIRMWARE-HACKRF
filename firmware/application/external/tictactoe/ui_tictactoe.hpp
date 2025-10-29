/*
 * EAGLE-FIRMWARE - Tic-Tac-Toe Game
 * Advanced AI with multiple difficulty levels
 * by 09AZO14
 */
#ifndef __UI_TICTACTOE_H__
#define __UI_TICTACTOE_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::tictactoe {

enum class Player { NONE = 0, HUMAN = 1, AI = 2 };
enum class Difficulty { EASY = 0, MEDIUM = 1, HARD = 2 };
enum class GameState { PLAYING, HUMAN_WIN, AI_WIN, DRAW };

class TicTacToeView : public View {
   public:
    TicTacToeView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "Tic-Tac-Toe"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    bool on_key(const KeyEvent key) override;
    bool on_touch(const TouchEvent event) override;

   private:
    void reset_game();
    void draw_board();
    void draw_cell(int row, int col, Player player);
    void make_move(int row, int col);
    void ai_move();
    GameState check_winner();
    bool is_board_full();
    
    // AI algorithms
    int minimax(int depth, bool is_maximizing);
    int evaluate_board();
    int get_best_move();
    void ai_move_easy();
    void ai_move_medium();
    void ai_move_hard();

    NavigationView& nav_;
    Painter painter{};
    
    static constexpr int GRID_SIZE = 3;
    Player board[GRID_SIZE][GRID_SIZE];
    
    int cursor_row = 1;
    int cursor_col = 1;
    
    GameState game_state = GameState::PLAYING;
    Difficulty difficulty = Difficulty::MEDIUM;
    
    int human_score = 0;
    int ai_score = 0;
    int draws = 0;
    
    // Display metrics
    int SCREEN_W = 0;
    int SCREEN_H = 0;
    int cell_size = 0;
    int board_offset_x = 0;
    int board_offset_y = 0;
    
    Button dummy{{screen_width, 0, 0, 0}, ""};
    bool initialized{false};
};

} // namespace ui::external_app::tictactoe

#endif /* __UI_TICTACTOE_H__ */
