// main.cpp : Defines the entry point for the console application.
//
#include "sorting_algorithms.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include <iomanip>

namespace {
    template <typename T>
    void print_container(const std::string& name, T&& data) {
        std::cout << std::setw(10) << name << ": ";
        for (const auto& val : data)
            std::cout << val << ' ';
        std::cout << '\n';
    }
}

int main()
{
    const auto data_size = 20;
    std::vector<int> data_to_sort(data_size);
    std::iota(data_to_sort.begin(), data_to_sort.end(), 1);
    std::shuffle(data_to_sort.begin(), data_to_sort.end(), std::mt19937{ std::random_device{}() });

    auto bubble_res = bubble_sort(data_to_sort);
    print_container("bubble", bubble_res);

    auto insertion_res = insertion_sort(data_to_sort);
    print_container("insertion", insertion_res);

    return 0;
}

