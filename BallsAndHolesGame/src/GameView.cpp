#include "GameView.h"

#include <iostream>
#include <string>

using namespace std;

GameView::GameView(IGameModelPtr model, IGameControllerPtr controller, std::ostream & out_stream, std::istream & in_stream)
	: m_model(model), m_controller(controller), m_ostream(out_stream), m_istream(in_stream)
{}

void GameView::start_game_loop()
{
	m_ostream << "Let's go!" << endl;

	m_ostream << "Commands:" << endl;
	m_ostream << "W - up board" << endl;
	m_ostream << "S - down board" << endl;
	m_ostream << "A - left board" << endl;
	m_ostream << "D - right board" << endl;

	draw_board();

	string input_str = "";

	while (!m_model->is_win())
	{
		if (m_model->is_loose())
		{
			show_loose_msg();
			return;
		}

		getline(m_istream, input_str);
		m_ostream << endl;

		if (m_controller->handle_input_command(input_str))
			draw_board();
	}

	show_win_msg();
}

void GameView::draw_board() const
{
	const BoardPtr board = m_model->get_board();

	const int col_count = board->get_col_count();
	const int row_count = board->get_row_count();

	// draw up contour
	m_ostream << '=';
	for (int col = 0; col < col_count; ++col)
		m_ostream << "====";

	// draw table
	for (int row = 0; row < row_count; ++row)
	{
		m_ostream << endl;

		m_ostream << '|';
		for (int col = 0; col < col_count; ++col)
		{
			draw_objects_in_cell(col, row);

			if (!draw_column_wall(col, row))
				m_ostream << '|';
		}
		m_ostream << endl;
		m_ostream << '=';
		for (int col = 0; col < col_count; ++col)
		{
			if (draw_row_wall(col, row))
				m_ostream << "=";
			else
				m_ostream << "====";
		}
	}

	m_ostream << endl;
}

void GameView::show_win_msg() const
{
	m_ostream << "YOU WIN!!!" << endl;
}

void GameView::show_loose_msg() const
{
	m_ostream << "YOU LOOSE!!!" << endl;
}

void GameView::draw_objects_in_cell(const int col, const int row) const
{
	const BoardPtr board = m_model->get_board();
	const int obj_count = board->get_object_count(col, row);

	if (obj_count == 0)
	{
		m_ostream << "   ";
		return;
	}

	vector<BaseObjPtr> objects;
	objects.resize(obj_count);
	board->get_objects(col, row, objects.begin());

	if (obj_count == 1)
	{
		m_ostream << objects[0]->number();
		objects[0]->draw(m_ostream);
		m_ostream << ' ';
		return;
	}

	for (unsigned i = 0; i < objects.size(); ++i)
	{
		if (dynamic_pointer_cast<BallPtr>(objects[i]))
		{
			m_ostream << objects[i]->number();
			objects[i]->draw(m_ostream);
			m_ostream << ' ';
			return;
		}

		if (dynamic_pointer_cast<HolePtr>(objects[i]))
		{
			m_ostream << objects[i]->number();
			objects[i]->draw(m_ostream);
			m_ostream << ' ';
			return;
		}
	}
}

bool GameView::draw_column_wall(const int col, const int row) const
{
	const BoardPtr board = m_model->get_board();
	const int col_count = board->get_col_count();

	if (col < col_count - 1)
	{
		WallPtr wall;
		if (board->check_wall(col, row, col + 1, row, &wall))
		{
			wall->draw(m_ostream);
			return true;
		}
	}

	return false;
}

bool GameView::draw_row_wall(const int col, const int row) const
{
	const BoardPtr board = m_model->get_board();
	const int row_count = board->get_row_count();

	if (row < row_count - 1)
	{
		WallPtr wall;
		if (board->check_wall(col, row, col, row + 1, &wall))
		{
			wall->draw(m_ostream);
			wall->draw(m_ostream);
			wall->draw(m_ostream);
			return true;
		}
	}

	return false;
}