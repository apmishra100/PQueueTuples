// Copyright 2015 Aman Mishra
// ============================================================================
// Name        : PQueueTuples.cpp
// Author      : Aman Mishra
// Description : Using a priority queue with the std::tuple class
// ============================================================================

#include <iostream>
#include <queue>
#include <cstdlib>
#include <functional>
#include <vector>
#include <tuple>
#include <ctime>

// Comparison function type
typedef bool (*comp)(std::tuple<int, int>, std::tuple<int, int>);

/*
 * Comparison function to allow for a min queue ordered off the
 * first element in the tuple.
 */
bool compare(std::tuple<int, int> a , std::tuple<int, int> b) {
  return ((std::get<0> (a)) > (std::get<0> (b)));
}

int main() {
  // Tuple is of form (weight, vertex number)
  /*
   * Note, the compare function is passed as a pointer to the constructor
   * whereas the type is fed into the template parameter list.
   */
  std::priority_queue<std::tuple<int, int>,
                      std::vector<std::tuple<int, int>>, comp> mypq(&compare);
  /*
   * Generating tuples. Note, the tuples will be ordered as a min heap
   * by their weight because of the compare function used.
   */
  for (int i = 0; i < 10; i++) {
    auto a = std::make_tuple(i+1, i);
    std::cout << "Vertex " << std::get<1> (a) << " , ";
    std::cout << "Weight " << std::get<0> (a) << std::endl;
    mypq.push(a);
  }

  unsigned int seed = time(NULL);

  /*
   * Delta array that shows how much each vertex has changed.
   * The indices correspond to the vertex number whereas the value
   * at the index is determines the change in the weight.
   */
  int delta_arr[10];
  for (auto &x : delta_arr) {
    x = rand_r(&seed) % 10;
  }

  for (auto &x : delta_arr) {
    std::cout << x << std::endl;
  }

  /*
   * In this while loop, we first look at the root element of the queue,
   * as this is the current minimum of all elements in the queue.. Then,
   * if the corresponding delta value is greater than 0, we update the
   * weight, reinsert the vertex into the queue, and update the delta
   * value to 0. It is not necessary to reinsert vertices that have a
   * delta value of 0 if they are at the root node of the queue as these
   * vertices would again become the root node of the queue again. In this
   * way, we have a lower bound on the elements of the queue. If we let
   * w(r(i)) denote the root element's weight and d[i]  be the delta value
   * that corresponds to vertex i, and w(i) denote the weight of vertex i
   * then we can say that w(r(i)) <= w(i) + d[i] for any vertex i that exists
   * in our graph.
   */
  while (!mypq.empty()) {
    std::tuple<int, int> temp = mypq.top();
    mypq.pop();
    if (delta_arr[std::get<1> (temp)] == 0) {
      std::cout << "Vertex " << std::get<1> (temp) << ' ';
      std::cout << "Weight " << std::get<0> (temp) << std::endl;
    } else {
      auto a = std::make_tuple(std::get<0> (temp) + delta_arr[std::get<1> (temp)],
                                std::get<1> (temp));

      delta_arr[std::get<1> (temp)] = 0;
      mypq.push(a);
    }
  }
  return 0;
}


