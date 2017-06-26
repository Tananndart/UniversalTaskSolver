#include "GreedyAlg.h"

using namespace std;
using namespace slv;

bool GreedyAlg::execute(TaskGraphPtr graph, vector<int>& out_commands, int max_execute_commands,
	std::ostream* dbg_stream)
{
	if (!graph)
		return false;
	m_graph = graph;

	int node_id = graph->get_root_node_id();

	vector<int> neighbors;
	while (!graph->is_solve(node_id))
	{
		graph->get_node_neighbors_ids(node_id, neighbors);

		auto pair_max_weight = find_max_weight_neighbor(node_id, neighbors);
		int max_weight_node_id = pair_max_weight.first;
		int max_weight = pair_max_weight.second;

		const int command_id = graph->get_node_command_id(max_weight_node_id);
		out_commands.push_back(command_id);

		if (dbg_stream)
		{
			*dbg_stream << graph->get_command_name(command_id) << " = " << max_weight << endl;
			_sleep(100);
		}
		
		node_id = max_weight_node_id;

		if (graph->is_loose(node_id))
			break;

		if (out_commands.size() >= max_execute_commands)
			break;
	}

	return graph->is_solve(node_id) ? true : false;
}

pair<int, int> slv::GreedyAlg::find_max_weight_neighbor(const int node_id, const std::vector<int>& neighbors)
{
	int max_weight = -1;
	int max_weight_node = -1;
	for (int i = 0; i < neighbors.size(); ++i)
	{
		if (neighbors[i] == m_old_node_id)
			continue;

		int weight = m_graph->get_link_weight(node_id, neighbors[i]);
		if (weight > max_weight)
		{
			max_weight = weight;
			max_weight_node = neighbors[i];
		}
	}

	m_old_node_id = node_id;

	return make_pair(max_weight_node, max_weight);
}
