#include "stdafx.h"
#include "CppUnitTest.h"

#include "Board.h"

#include <list>
#include <set>
#include <iterator>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BallsAndHolesTests
{		
	TEST_CLASS(TestBoard)
	{
	public:
		
		TEST_METHOD(tst_add_object)
		{	
			// init
			BoardPtr board = std::make_shared<Board>(4, 4);
			
			BallPtr ball_1 = std::make_shared<Ball>(2);
			BallPtr ball_2 = std::make_shared<Ball>(3);
			HolePtr hole = std::make_shared<Hole>(4);
			WallPtr wall = std::make_shared<Wall>(5);

			// execute
			board->add_object(0, 0, ball_1);
			board->add_object(3, 3, ball_2);
			board->add_object(0, 0, hole);
			board->add_object(wall);

			// check
			Assert::AreEqual(4, board->get_object_count());
			Assert::AreEqual(2, board->get_object_count(0, 0));
		}

		TEST_METHOD(tst_delete_object)
		{
			// init
			BoardPtr board = std::make_shared<Board>(4, 4);

			BallPtr ball_1 = std::make_shared<Ball>(2);
			BallPtr ball_2 = std::make_shared<Ball>(3);
			HolePtr hole = std::make_shared<Hole>(4);
			WallPtr wall = std::make_shared<Wall>(5);

			board->add_object(0, 0, ball_1);
			board->add_object(3, 3, ball_2);
			board->add_object(0, 0, hole);
			board->add_object(wall);

			// execute & check
			board->delete_object(wall->id());
			Assert::AreEqual(3, board->get_object_count());

			board->delete_all_objects(0, 0);
			Assert::AreEqual(0, board->get_object_count(0, 0));
			Assert::AreEqual(1, board->get_object_count());

			board->delete_all_objects();
			Assert::AreEqual(0, board->get_object_count());
		}

		TEST_METHOD(tst_get_objects)
		{
			// init
			BoardPtr board = std::make_shared<Board>(4, 4);

			BallPtr ball_1 = std::make_shared<Ball>(2);
			BallPtr ball_2 = std::make_shared<Ball>(3);

			HolePtr hole_1 = std::make_shared<Hole>(4);
			HolePtr hole_2 = std::make_shared<Hole>(5);

			WallPtr wall_1 = std::make_shared<Wall>(6);
			WallPtr wall_2 = std::make_shared<Wall>(7);

			board->add_object(0, 0, ball_1);
			board->add_object(0, 0, ball_2);
			board->add_object(0, 0, hole_1);

			board->add_object(3, 3, hole_2);

			board->add_object(wall_1);
			board->add_object(wall_2);

			// get object
			HolePtr hole = std::dynamic_pointer_cast<Hole>(board->get_object(4));
			Assert::AreEqual(true, hole != nullptr);

			// get objects
			{
				std::vector<BaseObjPtr> base_objects;
				base_objects.resize(board->get_object_count());

				board->get_objects(base_objects.begin());

				Assert::AreEqual(6, (int)base_objects.size());
				for (unsigned i = 0; i < base_objects.size(); ++i)
					Assert::AreEqual(true, base_objects[i] != nullptr);
			}
			
			// get objects by type
			{
				std::list<BallPtr> list_balls;
				board->get_objects<Ball>(std::inserter(list_balls, list_balls.begin()));

				Assert::AreEqual(2, (int)list_balls.size());
				for (auto it = list_balls.begin(); it != list_balls.end(); ++it)
					Assert::AreEqual(true, *it != nullptr);
			}
			
			// get objects in cell
			{
				std::set<BaseObjPtr> base_objects;
				board->get_objects(0, 0, std::inserter(base_objects, base_objects.begin()));

				Assert::AreEqual(3, (int)base_objects.size());
				for (auto it = base_objects.begin(); it != base_objects.end(); ++it)
					Assert::AreEqual(true, *it != nullptr);
			}
			
			// get objects by type in cell
			{
				std::vector<BallPtr> balls;
				balls.reserve(board->get_object_count(0, 0));
				board->get_objects<Ball>(0, 0, std::back_inserter(balls));

				Assert::AreEqual(2, (int)balls.size());
				for (unsigned i = 0; i < balls.size(); ++i)
					Assert::AreEqual(true, balls[i] != nullptr);
			}
		}
	};
}