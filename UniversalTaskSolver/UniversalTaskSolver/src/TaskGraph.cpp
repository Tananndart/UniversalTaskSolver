#include "TaskGraph.h"

struct slv::TaskGraph::NodeData
{
	NodeData() : comm_id(-1), cast_id(-1) {}
	NodeData(int comm, int cast) : comm_id(comm), cast_id(cast) {}
	int comm_id = -1, cast_id = -1;
};

slv::TaskGraph::TaskGraph()
{
	m_grpah = std::make_shared<grp::Graph<NodeData>>();
	m_root_node = m_grpah->create_node(NodeData(-1, -1));
}

bool slv::TaskGraph::init(ITaskPtr task)
{
	if (!task)
		return false;

	m_task = task;

	// create cast from root node
	const int root_cast_id = m_task->create_cast();
	m_root_node->set_data(NodeData(-1, root_cast_id));
	
	// create neighbors from root node
	create_neighbors(m_root_node);

	return true;
}

int slv::TaskGraph::get_root_node_id() const
{
	return m_root_node ? m_root_node->id() : -1;
}

int slv::TaskGraph::get_node_command_id(int node_id) const
{
	TNodePtr node = m_grpah->get_node(node_id);
	return node ? node->get_data().comm_id : -1;
}

void slv::TaskGraph::get_node_neighbors_ids(int node_id, std::vector<int>& out_neighbors_ids)
{
	TNodePtr node = m_grpah->get_node(node_id);
	if (!node)
		return;

	// check or create neighbors
	if (!exist_neighbors(node))
		create_neighbors(node);

	// copy links id in out_neighbors_ids
	const TNode::Links<NodeData>& node_links = node->get_links();	
	out_neighbors_ids.clear();
	out_neighbors_ids.reserve(node_links.size());
	for (auto it = node_links.cbegin(); it != node_links.cend(); ++it)
	{
		const TLinkPtr link = *it;
		const int link_node_1_id = link->get_first_node()->id();
		const int link_node_2_id = link->get_second_node()->id();

		if (link_node_1_id != node_id)
			out_neighbors_ids.push_back(link_node_1_id);
		else
			out_neighbors_ids.push_back(link_node_2_id);
	}
}

int slv::TaskGraph::get_link_weight(int node_id_1, int node_id_2) const
{
	const TNodePtr node_1 = m_grpah->get_node(node_id_1);
	const TNodePtr node_2 = m_grpah->get_node(node_id_2);
	if (!node_1 || !node_2)
		return -1;

	// helper
	auto find_functor = [node_id_1, node_id_2](const TLinkPtr& link)
	{
		return (link->get_first_node_id() == node_id_1 ||
			link->get_first_node_id() == node_id_2) 
			&&
			(link->get_second_node_id() == node_id_1 ||
				link->get_second_node_id() == node_id_2);
	};

	// find link
	const auto node_1_links = node_1->get_links();
	auto it = std::find_if(node_1_links.begin(), node_1_links.end(), find_functor);
	if (it != node_1_links.end())
		return (*it)->get_weight();

	return -1;
}


bool slv::TaskGraph::exist_neighbors(const TNodePtr node) const
{
	return (node->get_links().size() == m_task->get_command_count());
}

void slv::TaskGraph::create_neighbors(TNodePtr node)
{
	const int node_cast = node->get_data().cast_id;
	const int node_command = node->get_data().comm_id;
	
	NodeData data;

	// create nodes
	for (int i = 0; i < m_task->get_command_count(); ++i)
	{
		// check dublicate commands
		if (i == node_command)
			continue;

		// execute command
		m_task->execute_command(i);
		data.comm_id = i;

		// create cast
		data.cast_id = m_task->create_cast();

		// create node
		TNodePtr new_node = m_grpah->create_node(data);

		// create link, bind root <-> new_node
		const int link_weight = m_task->get_solve_k();
		m_grpah->create_link(node, new_node, link_weight);

		// back to origin cast
		m_task->activate_cast(node_cast);
	}
}
