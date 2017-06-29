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
private:
	BoardPtr m_board;
	std::map<int, int> m_balls_holes;	// first - ball_id, second - hole_id
	int m_id_counter;

	int get_new_id();

	void draw_objects_in_cell(int col, int row, std::ostream& out_stream) const;


	bool draw_column_wall(int col, int row, std::ostream& out_stream) const;
	bool draw_row_wall(int col, int row, std::ostream& out_stream) const;

	bool check_wall(int col_1, int row_1, int col_2, int row_2, 
		WallPtr* out_wall_ptr = nullptr) const;
	static int calculate_wall_id(int col_1, int row_1, int col_2, int row_2);
};

