#include "../../src/Sorting/Heapsort.h"
#include "../../src/Sorting/InsertionSort.h"
#include "../../src/Sorting/Quicksort.h"
#include "../../src/Sorting/Introsort.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>


namespace algospp {

void RandNum(int& randomNumber, int& counter, int& seed) {
	if (counter > RAND_MAX) {
		++seed;
		srand(seed);
		counter = 0;
	}

	int bitToFlip = rand() * (sizeof(int)*8 - 1) / RAND_MAX;
	if ((1 << bitToFlip) & randomNumber) {
		//clear bit
		randomNumber &= ~(1 << bitToFlip);
	}
	else {
		//set bit
		randomNumber |= 1 << bitToFlip;
	}

	++counter;
}

class SortTest : public ::testing::Test {
	std::vector<int> testVectorStd;
	std::vector<int> testVectorAlgoPP;


protected:

	SortTest() {

	}
	~SortTest() override {

	}
	void SetUp() override {

	}
	void TearDown() override {

	}


public:
	void CreateRandomVector(int n) {
		testVectorStd.clear();
		testVectorAlgoPP.clear();
		int randomNumber = 0, counter = 0, seed = 0;
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, counter, seed);
			testVectorStd.push_back(randomNumber);
			testVectorAlgoPP.push_back(randomNumber);
		}
	}

	void UseGivenVector(std::vector<int> vec) {
		testVectorStd = vec;
		testVectorAlgoPP = vec;
	}

	bool SortIsCorrect(void anysort(std::vector<int>::iterator, std::vector<int>::iterator)) {
		std::sort(testVectorStd.begin(), testVectorStd.end());
		anysort(testVectorAlgoPP.begin(), testVectorAlgoPP.end());
		for (int i = 0; i < testVectorStd.size(); ++i) {
			if (i >= testVectorStd.size() || i >= testVectorAlgoPP.size() || testVectorStd[i] != testVectorAlgoPP[i])
				return false;
		}
		return true;
	}

	void Sort(void anysort(std::vector<int>::iterator, std::vector<int>::iterator)) {
		anysort(testVectorAlgoPP.begin(), testVectorAlgoPP.end());
	}
};

TEST_F(SortTest, HeapsortCorrectTest) {
	CreateRandomVector(pow(10, 4));
	auto pHeapsort = heapsort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pHeapsort));
}

TEST_F(SortTest, InsertionSortCorrectTest) {
	CreateRandomVector(pow(10, 3));
	auto pInsertionSort = insertionSort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pInsertionSort));
}

TEST_F(SortTest, InsertionSortCorrectTest2) {
	std::vector<int> testSeq{ 5, 2, 4, 6, 1, 3 };
	UseGivenVector(testSeq);
	auto pInsertionSort = insertionSort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pInsertionSort));
}

TEST_F(SortTest, QuicksortCorrectTest) {
	CreateRandomVector(pow(10, 4));
	auto pQuicksort = quicksort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pQuicksort));
}

TEST_F(SortTest, QuicksortCorrectTest2) {
	std::vector<int> testSeq{ 5, 2, 4, 6, 1, 3 };
	UseGivenVector(testSeq);
	auto pQuicksort = quicksort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pQuicksort));
}

TEST_F(SortTest, RandomQuicksortCorrectTest) {
	CreateRandomVector(pow(10, 4));
	auto pQuicksort = randomQuicksort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pQuicksort));
}

TEST_F(SortTest, RandomQuicksortCorrectTest2) {
	std::vector<int> testSeq{ 5, 2, 4, 6, 1, 3 };
	UseGivenVector(testSeq);
	auto pQuicksort = randomQuicksort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pQuicksort));
}

TEST_F(SortTest, IntrosortCorrectTest) {
	CreateRandomVector(pow(10, 2));
	auto pIntrosort = introsort<std::vector<int>::iterator>;
	EXPECT_TRUE(SortIsCorrect(pIntrosort));
}

TEST_F(SortTest, ProfileSorts) {
	auto pHeapsort = heapsort<std::vector<int>::iterator>;
	auto pInsertionSort = insertionSort<std::vector<int>::iterator>;
	auto pQuicksort = quicksort<std::vector<int>::iterator>;
	auto pRandQuicksort = randomQuicksort<std::vector<int>::iterator>;
	auto stdSort = std::sort<std::vector<int>::iterator>;
	std::vector<decltype(pHeapsort)> pSortList{ pHeapsort, pQuicksort, pRandQuicksort, pInsertionSort, stdSort };
	std::vector<std::string> sortNames{ "heapsort", "quicksort", "randQuicksort", "insertionSort", "stdSort" };

	std::cout << "\n" << std::endl;
	for (int i = 1; i < 10; ++i) {
		std::cout << "SORTING 10* " << i << " ELEMENTS: " << "\n" << std::endl;
		for (int j = 0; j < pSortList.size(); ++j) {
			CreateRandomVector(10 * i);
			//std::cout << "Beginning sort: " << sortNames[j] << std::endl;
			auto start = std::chrono::system_clock::now();
			Sort(pSortList[j]);
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> milliSeconds = (end - start) * pow(10,3);
			std::cout << "Sort method " << sortNames[j] << " took " << milliSeconds.count() << " ms to execute." << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;



	/*for (unsigned long long i = 0; i < pow(10,5); ++i) {
		CreateRandomVector(50);
		Sort(pSortList[3]);
	}*/
}

}//algospp