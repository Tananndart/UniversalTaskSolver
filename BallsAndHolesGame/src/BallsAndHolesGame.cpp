#include "BallsAndHolesGame.h"

#include <sstream>
#include <algorithm>

using namespace std;

BallsAndHolesGame::BallsAndHolesGame()
{
	m_board = nullptr;
	m_id_counter = 0;
	m_wall_count = m_ball_count = m_hole_count = 0;
}

void BallsAndHolesGame::create_board(int col_count, int row_count)
{
	m_board = make_shared<Board>(col_count, row_count);
}

void BallsAndHolesGame::create_wall(int col_1, int row_1, int col_2, int row_2)
{
	const int wall_id = calculate_wall_id(col_1, row_1, col_2, row_2);
	WallPtr wall = make_shared<Wall>(wall_id);
	m_board->add_object(wall);

	m_wall_count++;
}

void BallsAndHolesGame::create_ball(int number, int col, int row)
{
	const int ball_id = get_new_id();
	BallPtr ball = make_shared<Ball>(ball_id, number);
	m_board->add_object(col, row, ball);

	m_ball_count++;
}

void BallsAndHolesGame::create_hole(int number, int col, int row)
{
	const int hole_id = get_new_id();
	HolePtr hole = make_shared<Hole>(hole_id, number);
	m_board->add_object(col, row, hole);
	
	m_hole_count++;
}

void BallsAndHolesGame::bind_ball_with_hole(int ball_number, int hole_number)
{
	m_balls_holes[ball_number] = hole_number;
}

void BallsAndHolesGame::play(std::ostream & out, std::istream & in)
{
	out << "Let's go!" << endl;

	out << "Commands:" << endl;
	out << "W - up board" << endl;
	out << "S - down board" << endl;
	out << "A - left board" << endl;
	out << "D - right board" << endl;

	draw_board(out);

	while (!is_win())
	{
		if (is_loose())
		{
			out << "Epic fail!" << endl;
			return;
		}

		char ch;
		in >> ch;

		if (ch == 'W') incline_board_up();
		if (ch == 'S') incline_board_down();
		if (ch == 'A') incline_board_left();
		if (ch == 'D') incline_board_right();

		out << endl;

		draw_board(out);
	}

	out << "YOU WIN!" << endl;
}

bool BallsAndHolesGame::is_win() const
{
	vector<HolePtr> holes;
	holes.reserve(m_hole_count);
	m_board->get_objects<Hole>(back_inserter(holes));

	for (unsigned i = 0; i < holes.size(); ++i)
	{
		const HolePtr hole = holes[i];

		if (!hole->is_closed())
			return false;

		int ball_numb = hole->get_ball()->number();
		if (!check_bind_ball_with_hole(ball_numb, hole->number()))
			return false;
	}

	return true;
}

bool BallsAndHolesGame::is_loose() const
{
	vector<HolePtr> holes;
	holes.reserve(m_hole_count);
	m_board->get_objects<Hole>(back_inserter(holes));

	for (unsigned i = 0; i < holes.size(); ++i)
	{
		const HolePtr hole = holes[i];

		if (hole->is_closed())
		{
			int ball_numb = hole->get_ball()->number();
			if (!check_bind_ball_with_hole(ball_numb, hole->number()))
				return true;
		}
	}

	return false;
}

void BallsAndHolesGame::draw_board(std::ostream & out_stream) const
{
	const int col_count = m_board->get_col_count();
	const int row_count = m_board->get_row_count();

	// draw up contour
	out_stream << '=';
	for (int col = 0; col < col_count; ++col)
		out_stream << "====";

	// draw table
	for (int row = 0; row < row_count; ++row)
	{
		out_stream << endl;
		
		out_stream << '|';
		for (int col = 0; col < col_count; ++col)
		{
			draw_objects_in_cell(col, row, out_stream);

			if (!draw_column_wall(col, row, out_stream))
				out_stream << '|';
		}		
		out_stream << endl;
		out_stream << '=';
		for (int col = 0; col < col_count; ++col)
		{
			if (draw_row_wall(col, row, out_stream))
				out_stream << "=";
			else
				out_stream << "====";
		}
	}

	out_stream << endl;
}

void BallsAndHolesGame::incline_board_left()
{
	vector<BallPtr> balls;
	get_all_balls(balls);

	for (unsigned i = 0; i < balls.size(); ++i)
	{
		auto pos = m_board->get_object_pos(balls[i]->id());
		move_ball_left(pos.first, pos.second, 0, balls[i]);
	}
}

void BallsAndHolesGame::incline_board_right()
{
	vector<BallPtr> balls;
	get_all_balls(balls);

	for (unsigned i = 0; i < balls.size(); ++i)
	{
		auto pos = m_board->get_object_pos(balls[i]->id());
		const int fin_col = m_board->get_col_count() - 1;

		move_ball_right(pos.first, pos.second, fin_col, balls[i]);
	}
}

void BallsAndHolesGame::incline_board_up()
{
	vector<BallPtr> balls;
	get_all_balls(balls);

	for (unsigned i = 0; i < balls.size(); ++i)
	{
		auto pos = m_board->get_object_pos(balls[i]->id());
		move_ball_up(pos.first, pos.second, 0, balls[i]);
	}
}

void BallsAndHolesGame::incline_board_down()
{
	vector<BallPtr> balls;
	get_all_balls(balls);

	for (unsigned i = 0; i < balls.size(); ++i)
	{
		auto pos = m_board->get_object_pos(balls[i]->id());
		const int fin_row = m_board->get_row_count() - 1;

		move_ball_down(pos.first, pos.second, fin_row, balls[i]);
	}
}

void BallsAndHolesGame::draw_objects_in_cell(int col, int row, std::ostream & out_stream) const
{
	const int obj_count = m_board->get_object_count(col, row);

	if (obj_count == 0)
	{
		out_stream << "   ";
		return;
	}

	vector<BaseObjPtr> objects;
	objects.resize(obj_count);
	m_board->get_objects(col, row, objects.begin());

	if (obj_count == 1)
	{
		out_stream << objects[0]->number();
		//out_stream << ' ';
		objects[0]->draw(out_stream);
		out_stream << ' ';
		return;
	}

	for (unsigned i = 0; i < objects.size(); ++i)
	{
		if (dynamic_pointer_cast<BallPtr>(objects[i]))
		{
			out_stream << objects[i]->number();
			//out_stream << ' ';
			objects[i]->draw(out_stream);
			out_stream << ' ';
			return;
		}

		if (dynamic_pointer_cast<HolePtr>(objects[i]))
		{
			out_stream << objects[i]->number();
			//out_stream << ' ';
			objects[i]->draw(out_stream);
			out_stream << ' ';
			return;
		}
	}
}

void BallsAndHolesGame::get_all_balls(vector<BallPtr>& balls) const
{
	balls.reserve(m_ball_count);
	m_board->get_objects<Ball>(std::back_inserter(balls));
}

bool BallsAndHolesGame::check_bind_ball_with_hole(const int ball_number, const int hole_number) const
{
	auto it = m_balls_holes.find(ball_number);
	if (it != m_balls_holes.end())
		return (hole_number == it->second);

	return false;
}

void BallsAndHolesGame::move_ball_right(const int start_col, const int row, const int fin_col, BallPtr ball)
{
	int next_col = 0;
	for (int col = start_col; col < fin_col; ++col)
	{
		next_col = col + 1;

		bool is_accept, is_cancel, is_push_hole;
		handle_move_ball_in_cell(col, row, next_col, row, ball,
			is_accept, is_cancel, is_push_hole);

		if (is_accept)
			continue;

		if (is_cancel)
		{
			next_col--;
			break;
		}

		if (is_push_hole)
		{
			m_board->delete_object(ball->id());
			return;
		}
	}

	m_board->delete_object(ball->id());
	m_board->add_object(next_col, row, ball);
}

void BallsAndHolesGame::move_ball_left(const int start_col, const int row, const int fin_col, BallPtr ball)
{
	int next_col = 0;
	for (int col = start_col; col > fin_col; --col)
	{
		next_col = col - 1;

		bool is_accept, is_cancel, is_push_hole;
		handle_move_ball_in_cell(col, row, next_col, row, ball,
			is_accept, is_cancel, is_push_hole);

		if (is_accept)
			continue;

		if (is_cancel)
		{
			next_col++;
			break;
		}

		if (is_push_hole)
		{
			m_board->delete_object(ball->id());
			return;
		}
	}

	m_board->delete_object(ball->id());
	m_board->add_object(next_col, row, ball);
}

void BallsAndHolesGame::move_ball_up(const int col, const int start_row, const int fin_row, BallPtr ball)
{
	int next_row = 0;
	for (int row = start_row; row > fin_row; --row)
	{
		next_row = row - 1;

		bool is_accept, is_cancel, is_push_hole;
		handle_move_ball_in_cell(col, row, col, next_row, ball,
			is_accept, is_cancel, is_push_hole);

		if (is_accept)
			continue;

		if (is_cancel)
		{
			next_row++;
			break;
		}

		if (is_push_hole)
		{
			m_board->delete_object(ball->id());
			return;
		}
	}

	m_board->delete_object(ball->id());
	m_board->add_object(col, next_row, ball);
}

void BallsAndHolesGame::move_ball_down(const int col, const int start_row, const int fin_row, BallPtr ball)
{
	int next_row = 0;
	for (int row = start_row; row < fin_row; ++row)
	{
		next_row = row + 1;

		bool is_accept, is_cancel, is_push_hole;
		handle_move_ball_in_cell(col, row, col, next_row, ball,
			is_accept, is_cancel, is_push_hole);

		if (is_accept)
			continue;

		if (is_cancel)
		{
			next_row--;
			break;
		}

		if (is_push_hole)
		{
			m_board->delete_object(ball->id());
			return;
		}
	}

	m_board->delete_object(ball->id());
	m_board->add_object(col, next_row, ball);
}

void BallsAndHolesGame::handle_move_ball_in_cell(int col, int row, int next_col, int next_row, BallPtr ball, 
	bool & out_is_accept, bool & out_is_cancel, bool & out_is_push_hole)
{
	out_is_accept = false;
	out_is_cancel = false;
	out_is_push_hole = false;

	// check wall
	if (check_wall(col, row, next_col, next_row))
	{
		out_is_cancel = true;
		return;
	}

	// check objects
	const int obj_count = m_board->get_object_count(next_col, next_row);
	if (obj_count > 0)
	{
		// check balls
		if (m_board->get_object_count<Ball>(next_col, next_row) > 0)
		{
			out_is_cancel = true;
			return;
		}

		// check holes
		vector<HolePtr> holes;
		holes.reserve(obj_count);
		m_board->get_objects<Hole>(next_col, next_row, back_inserter(holes));
		if (!holes.empty())
		{
			HolePtr hole = holes[0];
			if (!hole->is_closed())
			{
				hole->push_ball(ball);

				out_is_push_hole = true;
				return;
			}
		}
	}

	out_is_accept = true;
}

inline int BallsAndHolesGame::get_new_id()
{
	return m_id_counter++;
}

bool BallsAndHolesGame::draw_column_wall(int col, int row, std::ostream & out_stream) const
{
	if (col < m_board->get_col_count() - 1)
	{
		WallPtr wall;
		if (check_wall(col, row, col + 1, row, &wall))
		{
			wall->draw(out_stream);
			return true;
		}
	}

	return false;
}

bool BallsAndHolesGame::draw_row_wall(int col, int row, std::ostream & out_stream) const
{
	if (row < m_board->get_row_count() - 1)
	{
		WallPtr wall;
		if (check_wall(col, row, col, row + 1, &wall))
		{
			wall->draw(out_stream);
			wall->draw(out_stream);
			wall->draw(out_stream);
			return true;
		}
	}

	return false;
}

bool BallsAndHolesGame::check_wall(int col_1, int row_1, int col_2, int row_2,
	WallPtr* out_wall_ptr) const
{
	const int wall_id = calculate_wall_id(col_1, row_1, col_2, row_2);

	const WallPtr wall = std::dynamic_pointer_cast<Wall>(m_board->get_object(wall_id));
	
	if (out_wall_ptr)
		*out_wall_ptr = wall;

	return wall == nullptr ? false : true;
}

inline int BallsAndHolesGame::calculate_wall_id(int col_1, int row_1, int col_2, int row_2)
{
	stringstream ss;
	
	ss << col_1 << row_1 << col_2 << row_2;
	
	int new_id;
	ss >> new_id;

	return new_id;
}

