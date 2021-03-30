#include "catch2/catch.hpp"
#include <map>
#include <memory>
#include <list>
#include <stack>
#include <queue>

TEST_CASE("stl_map")
{
   std::map<std::string, int> test, test2;

   test["one"] = 1;
   test["second"] = 2;

   REQUIRE(test["one"]== 1);
   REQUIRE(test["second"]== 2);

   test.erase("second");
   REQUIRE(test["second"]!= 2);
   
   test2["three"] = 3;
   test.swap(test2);

   REQUIRE(test["three"]== 3);
   REQUIRE(test2["one"]== 1);

   REQUIRE(test.size() == 1);
}

TEST_CASE("stl_list")
{
   std::list<int> test;
   std::list<int>::iterator it;

   test.push_back(2);
   test.push_back(3);
   test.push_front(1);

   REQUIRE(test.front()== 1);
   REQUIRE(test.back()== 3);

   test.push_front(4);
   test.sort();

   REQUIRE(test.back()== 4);

   test.reverse();

   REQUIRE(test.back()== 1);

   it=test.begin();
   it++;
   test.insert(it, 5);
   test.pop_front();
   test.pop_back();

   REQUIRE(test.front()== 5);
   REQUIRE(test.back()== 2);

   test.erase(test.begin());
   REQUIRE(test.front()== 3);

   test.clear();
   REQUIRE(test.size()== 0);
}

TEST_CASE("stl_stack")
{
   std::stack<int> test, test2;

   test.push(1);
   test.push(2);
   test.push(3);

   REQUIRE(test.top()== 3);

   test2.push(4);
   test2.push(5);
   test2.push(6);
   test2.push(7);

   test.swap(test2);
   test.pop();

   REQUIRE(test.top()== 6);
   REQUIRE(test.size()== 3);

   test.pop();
   test.pop();
   test.pop();
   
   REQUIRE(test.empty());
}

TEST_CASE("stl_queue")
{
   std::queue<int> test, test2;

   test.push(1);
   test.push(2);
   test.push(3);

   REQUIRE(test.front()== 1);
   REQUIRE(test.back()== 3);

   test2.push(4);
   test2.push(5);
   test2.push(6);
   test2.push(7);

   test.swap(test2);
   test.pop();

   REQUIRE(test.front()== 5);
   REQUIRE(test.size()== 3);

   test.pop();
   test.pop();
   test.pop();
   
   REQUIRE(test.empty());
}

TEST_CASE("stl_priority_queue")
{
   std::priority_queue<int> test, test2;

   test.push(1);
   test.push(10);
   test.push(5);

   REQUIRE(test.top()== 10);

   test2.push(2);
   test2.push(6);
   test2.push(4);
   test2.push(8);

   test.swap(test2);
   test.pop();

   REQUIRE(test.top()== 6);
   REQUIRE(test.size()== 3);

   test.pop();
   test.pop();
   test.pop();
   
   REQUIRE(test.empty());
}