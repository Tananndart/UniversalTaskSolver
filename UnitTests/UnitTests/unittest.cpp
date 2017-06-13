#include "stdafx.h"

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "Graph.h"

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
			LinkPtr<int> link_n1_n2 = g->create_link();
			link_n1_n2->set_nodes(std::make_pair(node_1, node_2));
			link_n1_n2->set_weight(1);

			LinkPtr<int> link_n2_n3 = g->create_link(node_2->id(), node_3->id(), 2);

			LinkPtr<int> link_n1_n3 = g->create_link(node_1, node_3, 3);

			// check
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
				local_links[i] = g->create_link();

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
			LinkPtr<int> link_3 = g->create_link();

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
}