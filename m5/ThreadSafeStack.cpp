/* This program tests the thread-safe stack interface using jthreads.*/
#include "ThreadSafeStack.h"
#include<thread>
#include<chrono>
size_t const reps{100'000};
size_t const jthreadCount{10};

// Initialize the stack with an initializer list.
mpcs51044::stack<int> s = {1, 2, 3};

void pushAndPopALot(){
    for (size_t i = 0; i < reps; i++) {
        s.push(i);
    }
    for (size_t i = 0; i < reps; i++) {
        s.pop();
    }
}

// Perform pushes and pops using jthreads.
void counter() {
  std::vector<std::jthread> jthreads;
  for (size_t s = 0; s < jthreadCount; s++)
    jthreads.push_back(std::jthread(pushAndPopALot));
}

// Elapsed time is 43332ms on my laptop.
int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  counter();
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Elapsed time is " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
  return 0;
}