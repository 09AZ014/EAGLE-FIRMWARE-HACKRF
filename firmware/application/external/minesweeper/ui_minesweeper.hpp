/*
 * EAGLE-FIRMWARE addition by 09AZO14
 */
#ifndef __UI_MINESWEEPER_H__
#define __UI_MINESWEEPER_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "ui_widget.hpp"
#include "message.hpp"

namespace ui::external_app::minesweeper {

#define GRID_W 10
#define GRID_H 12
#define CELL_SIZE 20
#define MINES 15

class MinesweeperView : public View {
   public:
    MinesweeperView(NavigationView& nav);
    void on_show() override;
    std::string title() const override { return "Minesweeper"; }
    void focus() override { dummy.focus(); }
    void paint(Painter& painter) override;
    void frame_sync();
    bool on_key(const KeyEvent key) override;

   private:
    void reset_game();
    void draw_cell(int x, int y);
    void reveal_cell(int x, int y);
    void toggle_flag(int x, int y);
    int count_adjacent_mines(int x, int y);
    void check_win();

    NavigationView& nav_;
    Painter painter{};

    int grid[GRID_H][GRID_W] = {0}; // 0=empty, -1=mine
    bool revealed[GRID_H][GRID_W] = {false};
    bool flagged[GRID_H][GRID_W] = {false};
    int cursor_x = 0, cursor_y = 0;
    bool game_over = false;
    bool won = false;
    int revealed_count = 0;

    Button dummy{{screen_width, 0, 0, 0}, ""};
    bool initialized{false};

    MessageHandlerRegistration on_frame{
        Message::ID::DisplayFrameSync,
        [this](const Message* const) {
            this->frame_sync();
        }};
};

} // namespace ui::external_app::minesweeper

#endif /* __UI_MINESWEEPER_H__ */
