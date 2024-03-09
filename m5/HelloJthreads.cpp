/*This program revises using thread to using jthread (RAII) for a better join, because
programmers can forget to join a thread or the join might be prevented by exceptions. */
#include <iostream>
#include <thread>

void hello_jthreads() {
    std::cout << "Hello Concurrent World\n";
}

int
main() {
    // Pr