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

            auto sortedIter = iter - 1;

            while (sortedIter != first && comp(key, *sortedIter)) {
                *(sortedIter + 1) = std::move(*sortedIter);
                --sortedIter;
            }

            if (sortedIter == first && comp(key, *sortedIter)) {
                *(sortedIter + 1) = std::move(*sortedIter);
                *sortedIter = std::move(key);
            }
            else {
                *(sortedIter + 1) = std::move(key);
            }
        }
    }
}//algospp