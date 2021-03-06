#ifndef ALGOSPP_SRC_SORTING_HEAPSORT_H_
#define ALGOSPP_SRC_SORTING_HEAPSORT_H_


#include <functional>

namespace algospp{

template <class RandomAccessIterator>
void heapsort(RandomAccessIterator first, RandomAccessIterator last) {
    heapsort(first, last, std::less<decltype(*first)>());
}

template <class RandomAccessIterator, class Compare>
void heapsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    if (first == last)
        return;

    int heapSize = last - first;
    buildMaxHeap(first, last, comp, heapSize);

    for (auto iter = last - 1; iter != first; --iter) {
        std::swap(*first, *iter);
        --heapSize;
        maxHeapify(first, last, comp, 1, heapSize);
    }
}


namespace {
template <class RandomAccessIterator, class Compare>
void buildMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare comp, const int& heapSize) {
    //indexing starting from 1
    int firstInternalIndex = floor((last - first) / 2);

    for (int i = firstInternalIndex; i > 0; --i) {
        maxHeapify(first, last, comp, i, heapSize);
    }
}

//all four indices start from 1 to correlate with heap
template <class RandomAccessIterator, class Compare>
void maxHeapify(RandomAccessIterator first, RandomAccessIterator last, Compare comp, const int& index, const int& heapSize) {
    int leftIndex = left(index);
    int rightIndex = right(index);
    int largestIndex = index;
    if (leftIndex <= heapSize && comp(first[index - 1], first[leftIndex - 1])) {
        largestIndex = leftIndex;
    }
    if (rightIndex <= heapSize && comp(first[largestIndex - 1], first[rightIndex - 1])) {
        largestIndex = rightIndex;
    }
    if (largestIndex != index) {
        std::swap(first[index - 1], first[largestIndex - 1]);
        maxHeapify(first, last, comp, largestIndex, heapSize);
    }
}

int left(const int& index) {
    return (index) * 2;
}

int right(const int& index) {
    return (index) * 2 + 1;
}

}//unnamed namespace
}//algospp
#endif // !ALGOSPP_SRC_SORTING_HEAPSORT_H_