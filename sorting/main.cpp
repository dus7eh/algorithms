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

    std::vector<int> generate_random_data(int size) {
        std::vector<int> data(size);
        auto engine = std::mt19937{ std::random_device{}() };
        std::uniform_int_distribution<int> dist{ 1, 100 };
        std::generate(data.begin(), data.end(), [&dist, &engine]() { return dist(engine); });
        return data;
    }

    std::vector<int> generate_shuffled_uniques(int size) {
        std::vector<int> data(size);
        std::iota(data.begin(), data.end(), 1);
        std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
        return data;
    }
}

int main()
{
    const auto data_size = 20;
    const auto data_to_sort = generate_random_data(data_size);
    print_container("data", data_to_sort);

    auto bubble_res = bubble_sort(data_to_sort);
    print_container("bubble", bubble_res);

    auto insertion_res = insertion_sort(data_to_sort);
    print_container("insertion", insertion_res);

    auto merge_res = merge_sort(data_to_sort);
    print_container("merge", merge_res);

    auto selection_res = selection_sort(data_to_sort);
    print_container("selection", selection_res);

    return 0;
}

