#pragma once

#include <vector>
#include <tuple>

template <typename T>
T bubble_sort(T data) {
    for (auto i = 0u; i < data.size(); ++i) {
        bool sorted = true;
        for (auto j = 1u; j < data.size(); ++j)
            if (data[j - 1] > data[j]) {
                std::swap(data[j - 1], data[j]);
                sorted = false;
            }
        if (sorted)
            break;
    }

    return data;
}

template <typename T>
T insertion_sort(const T& data) {
    T res{};
    for (auto cit = data.begin(); cit != data.end(); ++cit) {
        auto it = std::find_if(res.begin(), res.end(), [ref = *cit](const auto& val) { return val > ref; });
        if (it == res.end())
            res.push_back(*cit);
        else
            res.insert(it, *cit);
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
        auto res_it = res.begin();
        while (bit != left_end && mit != eit) {
            if (*bit <= *mit)
                *(res_it++) = *(bit++);
            else
                *(res_it++) = *(mit++);
        }
        
        std::copy(bit, left_end, res_it);
        std::copy(mit, eit, res_it);
        std::copy(res.begin(), res.end(), left_begin);
    }

    template <typename T>
    void m_sort(iter<T> bit, iter<T> eit) {
        if (std::next(bit) != eit) {
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

template <typename T>
T selection_sort(T data) {
    for (auto i_it = data.begin(); i_it != data.end(); ++i_it) {
        auto min_it = std::min_element(std::next(i_it), data.end());
        if (min_it != data.end())
            std::swap(*i_it, *min_it);
    }
    return data;
}