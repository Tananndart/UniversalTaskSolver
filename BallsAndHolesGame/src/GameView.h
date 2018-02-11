#pragma once

#include "I_GameView.h"

class GameView : public IGameView
{
public:

	GameView(IGameModelPtr model, IGameControllerPtr controller, std::ostream & out_stream, std::istream & in_stream);

	void start_game_loop() override;

private:
	IGameModelPtr m_model;
	IGameControllerPtr m_controller;
	std::ostream & m_ostream;
	std::istream & m_istream;

	void draw_board() const;
	void show_win_msg() const;
	void show_loose_msg() const;

	void draw_objects_in_cell(const int col, const int row) const;
	bool draw_column_wall(const int col, const int row) const;
	bool draw_row_wall(const int col, const int row) const;
};

IGameViewPtr IGameView::create(IGameModelPtr model, IGameControllerPtr controller, std::ostream & out_stream, std::istream & in_stream)
{
	return std::make_shared<GameView>(model, controller, out_stream, in_stream);
}