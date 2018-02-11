#pragma once

#include "Board.h"

class IGameModel;
typedef std::shared_ptr<IGameModel> IGameModelPtr;

class IGameModel
{
public:

	static IGameModelPtr create();

	// init
	virtual void create_board(int col_count, int row_count) = 0;
	virtual void create_wall(int col_1, int row_1, int col_2, int row_2) = 0;
	virtual void create_ball(int number, int col, int row) = 0;
	virtual void create_hole(int number, int col, int row) = 0;
	virtual void bind_ball_with_hole(int ball_number, int hole_number) = 0;

	//getters
		//TODO: board must be unique pointer
	virtual const BoardPtr get_board() const = 0;
	
	//check states
	virtual bool is_win() const = 0;
	virtual bool is_loose() const = 0;

	// commands
	virtual void incline_board_left() = 0;
	virtual void incline_board_right() = 0;
	virtual void incline_board_up() = 0;
	virtual void incline_board_down() = 0;
};