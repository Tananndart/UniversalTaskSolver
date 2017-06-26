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

		bool execute(TaskGraphPtr graph, std::vector<int>& out_commands, 
			int max_execute_commands,
			std::ostream* dbg_stream = nullptr);

	private:
		slv::TaskGraphPtr m_graph;
		int m_old_node_id;

		std::pair<int, int> find_max_weight_neighbor(const int node_id, const std::vector<int>& neighbors);
	};
}

