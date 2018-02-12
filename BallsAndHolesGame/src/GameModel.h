#pragma once

#include "I_GameModel.h"
#include "Board.h"

class GameModel : public IGameModel
{
public:
	GameModel();

	// init
	void create_board(int col_count, int row_count) override;
	void create_wall(int col_1, int row_1, int col_2, int row_2) override;
	void create_ball(int number, int col, int row) override;
	void create_hole(int number, int col, int row) override;
	void bind_ball_with_hole(int ball_number, int hole_number) override;

	//getters
	const BoardUnicPtr& get_board() const override;

	// check states
	bool is_win() const override;
	bool is_loose() const override;

	// commands
	void incline_board_left() override;
	void incline_board_right() override;
	void incline_board_up() override;
	void incline_board_down() override;

private:
	BoardUnicPtr m_board;
	std::map<int, int> m_ball_hole_numbers;	// <ball_number, hole_number>
	int m_id_counter;
	int m_wall_count, m_ball_count, m_hole_count;

	// commands
	void move_ball_right(const int start_col, const int row, const int fin_col, BallPtr ball);
	void move_ball_left(const int start_col, const int row, const int fin_col, BallPtr ball);
	void move_ball_up(const int col, const int start_row, const int fin_row, BallPtr ball);
	void move_ball_down(const int start_col, const int row, const int fin_col, BallPtr ball);
	void handle_move_ball_in_cell(int col, int row, int next_col, int next_row, BallPtr ball,
		bool & out_is_accept, bool & out_is_cancel, bool & out_is_push_hole);

	// wall helpers
	bool check_wall(int col_1, int row_1, int col_2, int row_2,
		WallPtr* out_wall_ptr = nullptr) const;
	static int calculate_wall_id(int col_1, int row_1, int col_2, int row_2);

	// service
	int get_new_id();
	void get_all_balls(std::vector<BallPtr> & balls) const;
	bool check_bind_ball_with_hole(const int ball_number, const int hole_number) const;
};

IGameModelPtr IGameModel::create()
{
	return std::make_shared<GameModel>();
}