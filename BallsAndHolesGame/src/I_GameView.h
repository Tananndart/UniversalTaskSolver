#pragma once

#include "I_GameModel.h"
#include "I_GameController.h"

#include <ostream>

class IGameView;
typedef std::shared_ptr<IGameView> IGameViewPtr;

class IGameView
{
public:

	static IGameViewPtr create(IGameModelPtr model, IGameControllerPtr controller, 
		std::ostream & out_stream, std::istream & in_stream);

	virtual void start_game_loop() = 0;
};