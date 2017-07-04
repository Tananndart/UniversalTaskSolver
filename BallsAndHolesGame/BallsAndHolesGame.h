#pragma once

#include "Board.h"

class BallsAndHolesGame;
typedef std::shared_ptr<BallsAndHolesGame> BallsAndHolesGamePtr;

class BallsAndHolesGame
{
public:
	BallsAndHolesGame();

	void create_board(int col_count, int row_count);
	
	void create_wall(int col_1, int row_1, int col_2, int row_2);
	void create_ball(int number, int col, int row);
	void create_hole(int number, int col, int row);

	void bind_ball_with_hole(int ball_number, int hole_number);

	void draw_board(std::ostream& out_stream) const;

	// commands
	void incline_board_left();
	void incline_board_right();
	void incline_board_up();
	void incline_board_down();

private:
	BoardPtr m_board;
	std::map<int, int> m_balls_holes;	// first - ball_id, second - hole_id
	int m_id_counter;
	int m_wall_count, m_ball_count, m_hole_count;

	// commands
	void move_ball_right(const int start_col, const int row, const int fin_col, BallPtr ball);
	void move_ball_left(const int start_col, const int row, const int fin_col, BallPtr ball);
	void move_ball_up(const int col, const int start_row, const int fin_row, BallPtr ball);
	void move_ball_down(const int start_col, const int row, const int fin_col, BallPtr ball);
	void handle_move_ball_in_cell(int col, int row, int next_col, int next_row, BallPtr ball,
		bool & out_is_accept, bool & out_is_cancel, bool & out_is_push_hole);

	// draw
	bool draw_column_wall(int col, int row, std::ostream& out_stream) const;
	bool draw_row_wall(int col, int row, std::ostream& out_stream) const;
	void draw_objects_in_cell(int col, int row, std::ostream& out_stream) const;

	// wall helpers
	bool check_wall(int col_1, int row_1, int col_2, int row_2,
		WallPtr* out_wall_ptr = nullptr) const;
	static int calculate_wall_id(int col_1, int row_1, int col_2, int row_2);

	// service
	int get_new_id();
	void get_all_balls(std::vector<BallPtr> & balls) const;
};

