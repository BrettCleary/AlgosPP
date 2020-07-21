#ifndef ALGOSPP_SRC_SORTING_INSERTIONSORT_H_
#define ALGOSPP_SRC_SORTING_INSERTIONSORT_H_

#include <functional>

namespace algospp {

    template <class RandomAccessIterator>
    void insertionSort(RandomAccessIterator first, RandomAccessIterator last) {
        insertionSort(first, last, std::less<decltype(*first)>());
    }

    template <class RandomAccessIterator, class Compare>
    void insertionSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        for (auto iter = first + 1; iter != last; ++iter) {
            auto key(std::move(*iter));

            auto sortedIter = iter;

            while (sortedIter != first && comp(key, *(sortedIter - 1))) {
                *(sortedIter) = std::move(*(sortedIter - 1));
                --sortedIter;
            }

            *sortedIter = std::move(key);
        }
    }
}//algospp
#endif // !ALGOSPP_SRC_SORTING_INSERTIONSORT_H_