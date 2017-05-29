#include "Graph.h"

using namespace grp;
using namespace std;

// constructor
Graph::Graph() : m_id_counter(0) {}

// create node
int Graph::create_node(const DataPtr data)
{
	shared_ptr<Node> new_node = make_shared<Node>();
	new_node->data = data;
	new_node->id = get_new_id();

	m_nodes[new_node->id] = new_node;

	return new_node->id;
}

// delete node
void Graph::delete_node(int node_id)
{
	m_nodes.erase(node_id);
}

// delete all nodes
void Graph::delete_all_nodes()
{
	m_nodes.clear();
}

// delete node all links
void Graph::delete_node_all_links(int node_id)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		it->second->links.clear();
}

// set node data
void Graph::set_node_data(int node_id, const DataPtr data)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		it->second->data = data;
}

// get node data
Graph::DataPtr Graph::get_node_data(int node_id)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		return it->second->data;

	return DataPtr();
}

// get node count
unsigned Graph::get_node_count()
{
	return 0;
}

// get node link count
unsigned Graph::get_node_link_count(int node_id)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		return it->second->links.size();

	return 0;
}

// get new id
inline int Graph::get_new_id()
{
	return m_id_counter++;
}
