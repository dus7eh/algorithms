#pragma once

#include <vector>

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

namespace _merge_detail {
    template <typename T>
    using iter = typename std::vector<T>::iterator;

    template <typename T>
    void merge(iter<T> bit, iter<T> mit, iter<T> eit) {
        std::vector<T> res(std::distance(bit, eit));
        const auto left_begin = bit;
        const auto left_end = mit;
        auto i = 0;
        while (bit != left_end && mit != eit) {
            if (*bit <= *mit) {
                res[i++] = *bit;
                ++bit;
            }
            else {
                res[i++] = *mit;
                ++mit;
            }
        }
        
        while (bit != left_end) {
            res[i++] = *bit;
            ++bit;
        }

        while (mit != eit) {
            res[i++] = *mit;
            ++mit;
        }

        std::copy(res.begin(), res.end(), left_begin);
    }

    template <typename T>
    void m_sort(iter<T> bit, iter<T> eit) {
        if (bit + 1 != eit) {
            auto mit = std::next(bit, std::distance(bit, eit) / 2);
            m_sort<T>(bit, mit);
            m_sort<T>(mit, eit);
            merge<T>(bit, mit, eit);
        }
    }
}

template <typename T>
std::vector<T> merge_sort(std::vector<T> data) {
    if (!data.size())
        return {};

    _merge_detail::m_sort<T>(data.begin(), data.end());
    return data;
}