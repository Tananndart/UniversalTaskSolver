#pragma once

#include "I_GameModel.h"

class IGameController;
typedef std::shared_ptr<IGameController> IGameControllerPtr;

class IGameController
{
public:
	static IGameControllerPtr create(IGameModelPtr model);

	virtual bool handle_input_command(const std::string & command_str) = 0;
};