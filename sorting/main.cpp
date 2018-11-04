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

    auto bubble_data = data_to_sort;
    bubble_sort(bubble_data.begin(), bubble_data.end());
    print_container("bubble", bubble_data);

    auto insertion_data = data_to_sort;;
    insertion_sort(insertion_data.begin(), insertion_data.end());
    print_container("insertion", insertion_data);

    auto merge_data = data_to_sort;
    merge_sort(merge_data.begin(), merge_data.end());
    print_container("merge", merge_data);

    auto selection_data = data_to_sort;
    selection_sort(selection_data.begin(), selection_data.end());
    print_container("selection", selection_data);

    auto shell_data = data_to_sort;
    shell_sort(shell_data.begin(), shell_data.end());
    print_container("shell", shell_data);

    return 0;
}

