#pragma once

#include "I_GameController.h"

class GameController : public IGameController
{
public:
	GameController(IGameModelPtr model);

	bool handle_input_command(const std::string & command_str) override;

private:
	IGameModelPtr m_model;
};

IGameControllerPtr IGameController::create(IGameModelPtr model)
{
	return std::make_shared<GameController>(model);
}