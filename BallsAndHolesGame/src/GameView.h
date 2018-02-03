#pragma once

#include "GameModel.h"
#include "GameController.h"

#include <ostream>

class IGameView;
typedef std::shared_ptr<IGameView> IGameViewPtr;

class IGameView
{
public:

	static IGameViewPtr create(std::ostream& out_stream, IGameModelPtr model, IGameControllerPtr controller);

	virtual void start_game_loop() = 0;
	virtual void stop_game_loop() = 0;

	virtual void draw_board(std::ostream& out_stream) const = 0;

	virtual void show_win_msg(std::ostream& out_stream) const = 0;

	virtual void show_loose_msg(std::ostream& out_stream) const = 0;
};