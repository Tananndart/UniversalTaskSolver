#pragma once

#include "UniversalTaskSolver.h"
#include "TaskGraph.h"

#include <vector>

namespace slv
{
	class GreedyAlg
	{
	public:
		GreedyAlg() {}

		std::vector<int> execute(ITaskPtr task);

	private:
		ITaskPtr m_task;
		TaskGraphPtr m_graph;
	};
}

