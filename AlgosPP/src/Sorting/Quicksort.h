#ifndef ALGOSPP_SRC_SORTING_QUICKSORT_H_
#define ALGOSPP_SRC_SORTING_QUICKSORT_H_

namespace algospp{
template <class RandomAccessIterator>
void quicksort(RandomAccessIterator first, RandomAccessIterator last) {
    quicksort(first, last, std::less<decltype(*first)>());
}

template <class RandomAccessIterator, class Compare>
void quicksort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    if (first != last && first + 1 != last) {
        RandomAccessIterator p = algospp::partition(first, last, comp);
        quicksort(first, p, comp);
        quicksort(p + 1, last, comp);
    }
}

template <class RandomAccessIterator>
void randomQuicksort(RandomAccessIterator first, RandomAccessIterator last) {
    quicksort(first, last, std::less<decltype(*first)>());
}

template <class RandomAccessIterator, class Compare>
void randomQuicksort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    if (first != last && first + 1 != last) {
        std::swap(first[0], first[RandNum() % (last - first)]);

        RandomAccessIterator p = algospp::partition(first, last, comp);
        randomQuicksort(first, p, comp);
        randomQuicksort(p + 1, last, comp);
    }
}

namespace {
unsigned int randomNumber = 0;
unsigned int counter = 0;
unsigned int seed = 0;

unsigned int RandNum() {
    if (counter > RAND_MAX) {
        ++seed;
        srand(seed);
        counter = 0;
    }

    int bitToFlip = rand() * (sizeof(int) * 8 - 1) / RAND_MAX;
    if ((1 << bitToFlip) & randomNumber) {
        //clear bit
        randomNumber &= ~(1 << bitToFlip);
    }
    else {
        //set bit
        randomNumber |= 1 << bitToFlip;
    }

    ++counter;
    return randomNumber;
}

template <class RandomAccessIterator, class Compare>
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
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
#endif // !ALGOSPP_SRC_SORTING_QUICKSORT_H_