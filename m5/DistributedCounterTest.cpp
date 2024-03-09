/* This program tests the distributed counter using jthread, which is an improved
RAII version of thread to foster a better management of thread join. */
#include"DistributedCounter.h"
#include<thread>
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace mpcs;
using namespace std;
size_t const reps{100'000'000};
size_t const jthreadCount{10};
DistributedCounter c;

void countALot()
{
  for (size_t s = 0; s < reps; s++)
    c++;
}

void jthreadCounter() {
  vector<jthread> jthreads;
  for (size_t s = 0; s < jthreadCount; s++)
    jthreads.push_back(jthread(countALot));
  //for (auto &jthr : jthreads)
  //  jthr.join();
  // We don't need the above lines since jthread will be joined automatically upon destrution,
  // where it goes out of scope, in this case when the function returns.
}

int main()
{
  auto start = chrono::high_resolution_clock::now();
  jthreadCounter();
  auto end = chrono::high_resolution_clock::now();
  cout << "Count 