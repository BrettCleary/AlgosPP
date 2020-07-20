#include "../../src/Sorting/Heapsort.h"
#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>


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
	void CreateVector(int n) {
		int randomNumber = 0, counter = 0, seed = 0;
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, counter, seed);
			testVectorStd.push_back(randomNumber);
			testVectorAlgoPP.push_back(randomNumber);
		}
	}

	template <class Compare>
	bool SortIsCorrect(Compare comp) {
		std::sort(testVectorStd.begin(), testVectorStd.end());
		heapsort(testVectorAlgoPP.begin(), testVectorAlgoPP.end());
		for (int i = 0; i < testVectorStd.size(); ++i) {
			if (i >= testVectorStd.size() || i >= testVectorAlgoPP.size() || testVectorStd[i] != testVectorAlgoPP[i])
				return false;
		}
		return true;
	}
};

TEST_F(SortTest, HeapsortCorrectTest) {
	CreateVector(pow(10,6));

	EXPECT_TRUE(SortIsCorrect(std::less<int>()));
}

}//algospp