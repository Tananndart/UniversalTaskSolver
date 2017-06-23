#pragma once

#include "UniversalTaskSolver.h"
#include "TaskGraph.h"

#include <vector>

namespace slv
{
	class GreedyAlg;
	typedef std::shared_ptr<GreedyAlg> GreedyAlgPtr;

	class GreedyAlg
	{
	public:
		GreedyAlg() {}

		std::vector<int> execute(TaskGraphPtr graph);

	private:
		TaskGraphPtr m_graph;
	};
}

