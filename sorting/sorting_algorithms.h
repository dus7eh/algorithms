#pragma once

#include <vector>
#include <iterator>

template <typename T>
void bubble_sort(T first, T last) {
    for (auto outer = first; outer != last; ++outer) {
        bool sorted = true;
        for (auto inner = std::next(first); inner != last; ++inner) {
            auto prev_it = std::prev(inner);
            if (*prev_it > *inner) {
                std::swap(*prev_it, *inner);
                sorted = false;
            }
        }
        if (sorted)
            break;
    }
}

template <typename T>
void insertion_sort(T first, T last) {
    std::vector<T::value_type> res{};
    for (auto it = first; it != last; ++it) {
        auto gr_it = std::find_if(res.begin(), res.end(), [ref = *it](const auto& val) { return val > ref; });
        if (gr_it == res.end())
            res.push_back(*it);
        else
            res.insert(gr_it, *it);
    }

    std::copy(res.begin(), res.end(), first);
}

namespace _merge_detail {
    template <typename T>
    using iter = typename std::vector<T>::iterator;

    template <typename T>
    void merge(T bit, T mit, T eit) {
        std::vector<T::value_type> res(std::distance(bit, eit));
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
    void m_sort(T bit, T eit) {
        if (std::next(bit) != eit) {
            auto mit = std::next(bit, std::distance(bit, eit) / 2);
            m_sort<T>(bit, mit);
            m_sort<T>(mit, eit);
            merge<T>(bit, mit, eit);
        }
    }
}

template <typename T>
void merge_sort(T first, T last) {
    if (first == last)
        return;

    _merge_detail::m_sort<T>(first, last);
}

template <typename T>
void selection_sort(T first, T last) {
    for (; first != last; ++first) {
        auto min_it = std::min_element(first, last);
        if (min_it != last)
            std::swap(*first, *min_it);
    }
}