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
#include <cstdint>

namespace {
    using TestData = std::vector<int8_t>;

    template <typename T>
    void print_container(const std::string& name, T&& data) {
        std::cout << std::setw(10) << name << ": ";
        for (const auto& val : data)
            std::cout << int(val) << ' ';
        std::cout << '\n';
    }

    TestData generate_random_data(int size) {
        TestData data(size);
        auto engine = std::mt19937{ std::random_device{}() };
        std::uniform_int_distribution<int> dist{ 0, 100 };
        std::generate(data.begin(), data.end(), [&dist, &engine]() { return dist(engine); });
        return data;
    }

    TestData generate_shuffled_uniques(int size) {
        TestData data(size);
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

    auto quick_data = data_to_sort;
    quick_sort(quick_data.begin(), quick_data.end());
    print_container("quick", quick_data);

    auto counting_data = data_to_sort;
    counting_sort(counting_data.begin(), counting_data.end());
    print_container("counting", counting_data);

    auto counting_compact_data = data_to_sort;
    counting_compact_sort(counting_compact_data.begin(), counting_compact_data.end());
    print_container("counting compact", counting_compact_data);

    return 0;
}

