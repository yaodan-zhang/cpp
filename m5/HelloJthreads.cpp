/*This program revises using thread to using jthread (RAII) for a better join, because
programmers can forget to join a thread or the join might be prevented by exceptions. */
#include <iostream>
#include <thread>

void hello_jthreads() {
    std::cout << "Hello Concurrent World\n";
}

int
main() {
    // Print in a different thread
    std::jthread t(hello_jthreads);
    // jthread will automatically join upon destruction.
}