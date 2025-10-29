/*
 * EAGLE-FIRMWARE - Rock-Paper-Scissors Game
 * Best of 5 rounds with statistics
 * by 09AZO14
 */
#ifndef __UI_RPS_H__
#define __UI_RPS_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::rps {

enum class Choice { NONE = 0, ROCK = 1, PAPER = 2, SCISSORS = 3 };
enum class Result { NONE = 0, WIN = 1, LOSE = 2, DRAW = 3 };

class RPSView : public View {
   public:
    RPSView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "Rock-Paper-Scissors"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    bool on_key(const KeyEvent key) override;

   private:
    void reset_game();
    void make_choice(Choice player_choice);
    Choice get_ai_choice();
    Result determine_winner(Choice player, Choice ai);
    void draw_choice(int x, int y, Choice choice, bool highlighted);
    void draw_result_animation();

    NavigationView& nav_;
    Painter painter{};
    
    Choice player_choice = Choice::NONE;
    Choice ai_choice = Choice::NONE;
    Choice cursor_choice = Choice::ROCK;
    Result last_result = Result::NONE;
    
    int player_score = 0;
    int ai_score = 0;
    int draws = 0;
    int round = 0;
    static constexpr int MAX_ROUNDS = 5;
    
    bool game_over = false;
    bool waiting_for_next = false;
    
    int SCREEN_W = 0;
    int SCREEN_H = 0;
    
    Button dummy{{screen_width, 0, 0, 0}, ""};
    bool initialized{false};
};

} // namespace ui::external_app::rps

#endif /* __UI_RPS_H__ */
