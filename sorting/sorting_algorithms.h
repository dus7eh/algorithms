#pragma once

#include <vector>

namespace sort {

    template <typename T>
    std::vector<T> bubble_sort(std::vector<T> data) {
        for (auto i = 0u; i < data.size(); ++i)
            for (auto j = i + 1; j < data.size(); ++j)
                if (data[i] > data[j])
                    std::swap(data[i], data[j]);

        return data;
    }

    template <typename T>
    std::vector<T> insertion_sort(const std::vector<T>& data) {
        std::vector<T> res{};
        for (auto i = 0u; i < data.size(); ++i) {
            auto it = std::find_if(res.begin(), res.end(), [ref = data[i]](auto val) { return val > ref; });
            if (it == res.end())
                res.push_back(data[i]);
            else
                res.insert(it, data[i]);
        }

        return res;
    }

}