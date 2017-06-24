#include "CppUnitTest.h"

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "Graph.h"
#include "TaskGraph.h"
#include "../../LetterRotateGame/src/LetterRotateGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace grp;

namespace UnitTests
{		
	TEST_CLASS(GraphClass)
	{
	public:
		
		TEST_METHOD(f_create_node)
		{	
			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			// execute
			NodePtr<int> node_1 = g->create_node(10);
			NodePtr<int> node_2 = g->create_node(20);
			NodePtr<int> node_3 = g->create_node(30);

			// check
			Assert::AreEqual(3, (int)g->get_node_count());
			Assert::AreEqual(10, node_1->get_data());
			Assert::AreEqual(20, node_2->get_data());
			Assert::AreEqual(30, node_3->get_data());
		}

		TEST_METHOD(f_create_link)
		{
			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			NodePtr<int> node_1 = g->create_node(10);
			NodePtr<int> node_2 = g->create_node(20);
			NodePtr<int> node_3 = g->create_node(30);

			// execute
			LinkPtr<int> link_n1_n2 = g->create_link(node_1, node_2, 1);
			LinkPtr<int> link_n2_n3 = g->create_link(node_2->id(), node_3->id(), 2);
			LinkPtr<int> link_n1_n3 = g->create_link(node_1, node_3, 3);

			// check links in nodes
			Assert::AreEqual(2, (int)node_1->get_links().size());
			Assert::AreEqual(2, (int)node_2->get_links().size());
			Assert::AreEqual(2, (int)node_3->get_links().size());

			// check links in graph
			Assert::AreEqual(3, (int)g->get_link_count());

			Assert::AreEqual(1, link_n1_n2->get_weight());
			Assert::AreEqual(2, link_n2_n3->get_weight());
			Assert::AreEqual(3, link_n1_n3->get_weight());

			Assert::AreEqual(node_1->id(), link_n1_n2->get_first_node()->id());
			Assert::AreEqual(node_2->id(), link_n1_n2->get_second_node()->id());

			Assert::AreEqual(node_2->id(), link_n2_n3->get_first_node()->id());
			Assert::AreEqual(node_3->id(), link_n2_n3->get_second_node()->id());

			Assert::AreEqual(node_1->id(), link_n1_n3->get_first_node()->id());
			Assert::AreEqual(node_3->id(), link_n1_n3->get_second_node()->id());
		}

		TEST_METHOD(f_delete_node)
		{
			const int NODE_CNT = 20; // warning: > 10

			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			std::vector<NodePtr<int>> local_nodes(NODE_CNT, nullptr);
			for (int i = 0; i < NODE_CNT; ++i)
				local_nodes[i] = g->create_node(i);
			
			// execute & check
			g->delete_node(local_nodes[5]->id());
			g->delete_node(local_nodes[10]->id());
			Assert::AreEqual(false, g->exist_node(local_nodes[5]->id()));
			Assert::AreEqual(false, g->exist_node(local_nodes[10]->id()));
			Assert::AreEqual(NODE_CNT - 2, (int)g->get_node_count());

			g->delete_all_nodes();
			Assert::AreEqual(0, (int)g->get_node_count());

		}

		TEST_METHOD(f_delete_link)
		{
			const int LINK_CNT = 20; // warning: > 10

			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			NodePtr<int> node_1 = g->create_node(10);
			NodePtr<int> node_2 = g->create_node(20);
			NodePtr<int> node_3 = g->create_node(30);
			
			LinkPtr<int> lnk_12 = g->create_link(node_1, node_2, 1);
			LinkPtr<int> lnk_23 = g->create_link(node_2, node_3, 2);

			std::vector<LinkPtr<int>> local_links(LINK_CNT, nullptr);
			for (int i = 0; i < LINK_CNT; ++i)
				local_links[i] = g->create_link(node_1, node_2, 10);

			// execute & check
			g->delete_link(local_links[5]->id());
			g->delete_link(local_links[10]->id());
			Assert::AreEqual(false, g->exist_link(local_links[5]->id()));
			Assert::AreEqual(false, g->exist_link(local_links[10]->id()));

			g->delete_all_links();
			Assert::AreEqual(0, (int)g->get_link_count());
			Assert::AreEqual(true, g->exist_node(node_1));
			Assert::AreEqual(true, g->exist_node(node_2));
			Assert::AreEqual(true, g->exist_node(node_3));

			// check del links in nodes
			Assert::AreEqual(0, (int)node_1->get_links().size());
			Assert::AreEqual(0, (int)node_2->get_links().size());
			Assert::AreEqual(0, (int)node_3->get_links().size());
		}

		TEST_METHOD(f_get_nodes)
		{
			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			NodePtr<int> node_1 = g->create_node(10);
			NodePtr<int> node_2 = g->create_node(20);
			NodePtr<int> node_3 = g->create_node(30);

			// check std gets
			Assert::AreEqual(true, g->get_node(100500) == nullptr);
			Assert::AreEqual(true, g->get_node(node_1->id()) != nullptr);

			// check template getters
			std::vector<NodePtr<int>> nodes;
			nodes.resize(g->get_node_count());
			g->get_all_nodes_ptr(nodes.begin());

			Assert::AreEqual(g->get_node_count(), nodes.size());
			Assert::AreEqual(true, (nodes[0]->id() == node_1->id()) ||
				(nodes[0]->id() == node_2->id()) || (nodes[0]->id() == node_3->id()));

			// check template getters with  inserter
			std::set<int> node_ids;		
			g->get_all_nodes_id(std::inserter(node_ids, node_ids.begin()));

			Assert::AreEqual(g->get_node_count(), node_ids.size());
			Assert::AreEqual(true, node_ids.find(node_2->id()) != node_ids.end());
		}

		TEST_METHOD(f_get_links)
		{
			// init
			GraphPtr<int> g = std::make_shared<Graph<int>>();

			NodePtr<int> node_1 = g->create_node(10);
			NodePtr<int> node_2 = g->create_node(20);
			NodePtr<int> node_3 = g->create_node(30);

			LinkPtr<int> link_1 = g->create_link(node_1, node_2, 1);
			LinkPtr<int> link_2 = g->create_link(node_2, node_3, 2);
			LinkPtr<int> link_3 = g->create_link(node_1, node_3, 3);

			// check std gets
			Assert::AreEqual(true, g->get_link(100500) == nullptr);
			Assert::AreEqual(true, g->get_link(link_1->id()) != nullptr);

			// check template getters
			std::vector<LinkPtr<int>> links;
			links.resize(g->get_link_count());
			g->get_all_link_ptr(links.begin());

			Assert::AreEqual(g->get_link_count(), links.size());
			Assert::AreEqual(true, (links[0]->id() == link_1->id()) ||
				(links[0]->id() == link_2->id()) || (links[0]->id() == link_3->id()));

			// check template getters with back inserter
			std::set<int> link_ids;
			g->get_all_link_id(std::inserter(link_ids, link_ids.begin()));

			Assert::AreEqual(g->get_link_count(), link_ids.size());
			Assert::AreEqual(true, link_ids.find(link_2->id()) != link_ids.end());
		}
	};

	TEST_CLASS(TaskGraphClass)
	{
	public:
		TEST_METHOD(f_get_node_neighbors)
		{
			using namespace slv;
			using namespace std;

			// init
			LetRotGame::Ptr task = create_game();
			TaskGraphPtr graph = make_shared<TaskGraph>();
			graph->init(task);
			const int root_id = graph->get_root_node_id();
			
			// get root neighbors
			vector<int> root_neighbors;
			graph->get_node_neighbors_ids(root_id, root_neighbors);

			// check root neighbors
			Assert::AreEqual((int)root_neighbors.size(), task->get_command_count());
			Assert::AreEqual(true, 
				find(root_neighbors.begin(), root_neighbors.end(), -1) == root_neighbors.end());

			// get random node neighbors
			const int node_id = root_neighbors.front();
			vector<int> node_neighbors;
			graph->get_node_neighbors_ids(node_id, node_neighbors);

			// check random node neighbors
			Assert::AreEqual((int)node_neighbors.size(), task->get_command_count());
			Assert::AreEqual(true,
				find(node_neighbors.begin(), node_neighbors.end(), -1) == node_neighbors.end());
		}

		TEST_METHOD(f_get_link_weight)
		{
			using namespace slv;
			using namespace std;

			// init
			LetRotGame::Ptr task = create_game();
			TaskGraphPtr graph = make_shared<TaskGraph>();
			graph->init(task);
			const int root_id = graph->get_root_node_id();

			// get root neighbors
			vector<int> root_neighbors;
			graph->get_node_neighbors_ids(root_id, root_neighbors);

			// get all link weight root_neighbors
			vector<int> links_weight(root_neighbors.size(), -1);
			for (int i = 0; i < root_neighbors.size(); ++i)
				links_weight[i] = graph->get_link_weight(root_id, root_neighbors[i]);

			// check all links weight
			Assert::AreEqual(true,
				find(links_weight.begin(), links_weight.end(), -1) == links_weight.end());

			// find min weight and max weight in links_weight
			sort(links_weight.begin(), links_weight.end());
			const int min_weight = links_weight.front();
			const int max_weight = links_weight.back();

			// check min and max weight
			Assert::AreEqual(0, min_weight);
			Assert::AreEqual(3, max_weight);
		}

	private:
		LetRotGame::Ptr create_game();
	};


	inline LetRotGame::Ptr TaskGraphClass::create_game()
	{
		char word_1[5] = "3E1D";
		char word_2[5] = "L7T3";
		char win_word_1[5] = "1E7T";
		char win_word_2[5] = "3L3D";
		return std::make_shared<LetRotGame>(word_1, word_2, win_word_1, win_word_2, 100);
	}
}