#pragma once

#include <vector>
#include <iterator>
#include <map>

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
    for (auto it = first; it != last; ++it) {
        auto greater = std::find_if(first, it, [ref = *it](const auto& val) { return val > ref; });
        if (greater != it) {
            const auto val = *it;
            std::copy_backward(greater, it, std::next(it));
            *greater = val;
        }
    }
}

namespace _merge_detail {
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
}

template <typename T>
void merge_sort(T first, T last) {
    if (std::next(first) != last) {
        auto mit = std::next(first, std::distance(first, last) / 2);
        merge_sort<T>(first, mit);
        merge_sort<T>(mit, last);
        _merge_detail::merge<T>(first, mit, last);
    }
}

template <typename T>
void selection_sort(T first, T last) {
    for (; first != last; ++first) {
        auto min_it = std::min_element(first, last);
        if (min_it != last)
            std::swap(*first, *min_it);
    }
}

namespace _shell_detail {
    int calculate_interval(const size_t len) {
        auto interval = 1;
        while (size_t(interval) < len)
            interval = interval * 3 + 1;
        return (interval - 1) / 3;
    }
}

template <typename T>
void shell_sort(T first, T last) {
    const auto len = std::distance(first, last);
    if (!len)
        return;

    auto interval = _shell_detail::calculate_interval(len);
    while (interval) {
        for (auto it = std::next(first, interval); it != last; ++it) {
            auto curr_it = it;
            auto prev_it = std::prev(it, interval);
            while (*prev_it > *curr_it) {
                std::swap(*prev_it, *curr_it);
                curr_it = prev_it;

                if (std::distance(first, prev_it) < interval)
                    break;
                prev_it = std::prev(prev_it, interval);
            }
        }
        interval /= 3;
    }
}

template <typename T>
void quick_sort(T first, T last) {
    const auto len = std::distance(first, last);
    if (len > 1) {
        auto piv = std::prev(last);
        auto lo = first;
        auto hi = std::prev(piv);
        while (lo != hi) {
            if (*lo > *piv && *piv >= *hi) {
                std::swap(*lo, *hi);
                continue;
            }

            if (*lo <= *piv)
                ++lo;
            else if (*piv < *hi)
                --hi;
        }
        if (*piv < *lo)
            std::swap(*piv, *lo); // to avoid the need of merge stage

        if (first != lo)
            quick_sort(first, std::next(lo));
        if (hi != std::prev(piv))
            quick_sort(hi, std::next(piv));
    }
}

template <typename T, typename Limits = std::numeric_limits<T::value_type>>
void counting_sort(T first, T last, const typename T::value_type min = Limits::min(), const typename T::value_type max = Limits::max()) {
    std::vector<T::value_type> cache(max - min);
    for (auto it = first; it != last; ++it) {
        const int& idx = *it - min;
        ++cache[idx];
    }

    auto curr = first;
    T::value_type val = 0;
    for (auto it = cache.cbegin(); it != cache.cend(); ++it) {
        for (T::value_type i = *it; i != 0; --i) {
            *curr = val + min;
            ++curr;
        }
        ++val;
    }
}

template <typename T>
void counting_compact_sort(T first, T last) {
    std::map<T::value_type, uint32_t> cache;
    for (auto it = first; it != last; ++it) {
        const auto found = cache.find(*it);
        if (found != cache.end())
            ++(found->second);
        else
            cache[*it] = 1;
    }
    
    auto curr = first;
    for (auto entry = cache.begin(); entry != cache.end(); ++entry) {
        std::fill_n(curr, entry->second, entry->first);
        std::advance(curr, entry->second);
    }
}