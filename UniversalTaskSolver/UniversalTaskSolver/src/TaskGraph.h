#pragma once

#include "Graph.h"
#include "UniversalTaskSolver.h"

namespace slv
{
	class TEST_API TaskGraph;
	typedef std::shared_ptr<TaskGraph> TaskGraphPtr;

	class TEST_API TaskGraph
	{
	public:
		TaskGraph();

		bool init(ITaskPtr task);

		int get_root_node_id() const;

		int get_node_command_id(int node_id) const;
		void get_node_neighbors_ids(int node_id, std::vector<int>& out_neighbors_ids);

		int get_link_weight(int node_id_1, int node_id_2) const;

	private:
		struct NodeData;
		typedef grp::Node<NodeData> TNode;
		typedef grp::NodePtr<NodeData> TNodePtr;
		typedef grp::Link<NodeData> TLink;
		typedef grp::LinkPtr<NodeData> TLinkPtr;

	private:
		TNodePtr m_root_node;
		ITaskPtr m_task;
		grp::GraphPtr<NodeData> m_grpah;

		bool exist_neighbors(const TNodePtr node) const;
		void create_neighbors(TNodePtr node);
	};
}

