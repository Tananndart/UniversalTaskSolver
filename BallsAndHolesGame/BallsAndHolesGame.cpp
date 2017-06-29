#include "BallsAndHolesGame.h"

#include <sstream>
#include <algorithm>

using namespace std;

BallsAndHolesGame::BallsAndHolesGame()
{
	m_board = nullptr;
	m_id_counter = 0;
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
}

void BallsAndHolesGame::create_ball(int number, int col, int row)
{
	const int ball_id = get_new_id();
	BallPtr ball = make_shared<Ball>(ball_id, number);
	m_board->add_object(col, row, ball);
}

void BallsAndHolesGame::create_hole(int number, int col, int row)
{
	const int hole_id = get_new_id();
	HolePtr hole = make_shared<Hole>(hole_id, number);
	m_board->add_object(col, row, hole);
}

void BallsAndHolesGame::bind_ball_with_hole(int ball_number, int hole_number)
{
	m_balls_holes[ball_number] = hole_number;
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
		out_stream << ' ';
		objects[0]->draw(out_stream);
		out_stream << ' ';
		return;
	}

	for (unsigned i = 0; i < objects.size(); ++i)
	{
		if (dynamic_pointer_cast<BallPtr>(objects[i]))
		{
			out_stream << ' ';
			objects[i]->draw(out_stream);
			out_stream << ' ';
			return;
		}

		if (dynamic_pointer_cast<HolePtr>(objects[i]))
		{
			out_stream << ' ';
			objects[i]->draw(out_stream);
			out_stream << ' ';
			return;
		}
	}
	
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

