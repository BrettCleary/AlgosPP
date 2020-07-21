#ifndef ALGOSPP_SRC_SORTING_INTROSORT_H_
#define ALGOSPP_SRC_SORTING_INTROSORT_H_

#include "Quicksort.h"
#include "Heapsort.h"
#include "InsertionSort.h"
#include <functional>
#include <cmath>

namespace algospp {

    template <class RandomAccessIterator>
    void introsort(RandomAccessIterator first, RandomAccessIterator last) {
        introsort(first, last, std::less<decltype(*first)>());
    }

    template <class RandomAccessIterator, class Compare>
    void introsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        if (first == last)
            return;
        unsigned long long maxDepth = log2(last - first);
        maxDepth <<= 1;
        introsortRecursive(first, last, comp, maxDepth);
    }


namespace {
template <class RandomAccessIterator, class Compare>
void introsortRecursive(RandomAccessIterator first, RandomAccessIterator last, Compare& comp, unsigned long long maxDepth) {

    if (last - first < 101) {
        insertionSort(first, last, comp);
    }
    else if (maxDepth == 0) {
        heapsort(first, last, comp);
    }
    else {
        RandomAccessIterator p = partitionIntrosort(first, last, comp);
        introsortRecursive(first, p, comp, maxDepth - 1);
        introsortRecursive(p + 1, last, comp, maxDepth - 1);
    }
}

template <class RandomAccessIterator, class Compare>
RandomAccessIterator partitionIntrosort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    RandomAccessIterator i = first;
    for (RandomAccessIterator j = first + 1; j != last; ++j) {
        if (comp(*j, *first)) {
            ++i;
            std::swap(*i, *j);
        }
    }

    if (first != i) {
        std::swap(*first, *i);
    }
    return i;
}
}//unnamed namespace
}//algospp
#endif // !ALGOSPP_SRC_SORTING_INTROSORT_H_

