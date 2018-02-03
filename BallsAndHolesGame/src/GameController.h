#pragma once

#include "GameModel.h"

class IGameController;
typedef std::shared_ptr<IGameController> IGameControllerPtr;

class IGameController
{
public:
	static IGameControllerPtr create(IGameModelPtr model);
};