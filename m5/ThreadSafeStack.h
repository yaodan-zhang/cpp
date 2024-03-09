/* This program implements a thread-safe stack based on mutex that supports the push and pop operation,
 userful functionalities are also included, such as an initializer list constructor. */
#ifndef THREAD_SAFE_STACK_H
#define THREAD_SAFE_STACK_H
#include<shared_mutex>
#include<vector>
#include<iostream>
namespace mpcs51044 {
    template<typename T>
    class stack
    {
        public:
        stack(std::initializer_list<T> init) {
            for (auto e : init) {
                push(e);
            }
        }
        // Check if the stack is empty.
        bool empty() {
            return data.size() == 0;
        }
        // Push the element to the back of the vector.
        void push(T e) {
            std::unique_lock lock(mtx);
            data.push_back(e);
        }

        // Pop and return the 0-th element of the vector by value if it is not empty.
        // Otherwise print a warning message to stdout and return 0.
        T pop() {
            std::unique_lock lock(mtx);
            if (this->empty()) {
                std::cout << "The stack is empty!" << std::endl;
                return 0;
            }
            T top_e = data.at();
            data.erase(data.end()-1);
            return top_e;
        }
        private:
        std::vector<T> data;
        std::shared_mutex mtx;
    };
}

#endif