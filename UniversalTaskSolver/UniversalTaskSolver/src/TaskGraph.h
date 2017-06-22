#pragma once

#include "Graph.h"

namespace slv
{
	class TaskGraph;
	typedef std::shared_ptr<TaskGraph> TaskGraphPtr;

	class TaskGraph
	{
	public:

	private:
		grp::GraphPtr<int> m_grpah;
	};
}

