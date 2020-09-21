#include "../../src/Data Structures/FibonacciHeap.h"
#include "gtest/gtest.h"

#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <exception>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <ctime>


namespace algospp {

void RandNum(int& randomNumber, int& uBits, int& counter, int& seed) {
	if (counter > RAND_MAX) {
		++seed;
		srand(seed);
		counter = 0;
	}

	int bitToFlip = rand() * (uBits - 1) / RAND_MAX;
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

struct DataNode : DoublyLinkedNode{
	std::string Name;
	DataNode(std::string name) : Name(name) {

	}
};
bool operator== (const DataNode& lhs, const DataNode& rhs) {
	return lhs.Name == rhs.Name;
}
bool operator!= (const DataNode& lhs, const DataNode& rhs) {
	return lhs.Name != rhs.Name;
}

struct nodeComp {
	bool operator() (const std::shared_ptr<DoublyLinkedNode>& lhs, const std::shared_ptr<DoublyLinkedNode>& rhs) const
	{
		return lhs->key < rhs->key;
	}
};

class FibonacciHeapTest : public ::testing::Test {
	FibHeap heap;
	int uBits = 20;
	std::set<std::shared_ptr<DoublyLinkedNode>, nodeComp> bstNodes;
	std::vector<std::shared_ptr<DoublyLinkedNode>> nodeList;
	int counter = 0;
	int seed = 0;
	int randomNumber = 0;

protected:

	FibonacciHeapTest() {}
	~FibonacciHeapTest() override {}
	void SetUp() override {}
	void TearDown() override {}

public:

	void Insert(int n, bool takeUnion = false) {
		FibHeap heapMerge;
		for (int i = 0; i < n; ++i) {
			std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));
			RandNum(randomNumber, uBits, counter, seed);
			dataNodePtr->key = randomNumber;
			//FibHeap does not require unique pointers but the balanced BST std::set does
			//need std::set to compare balanced BST to fib heap
			if (bstNodes.find(dataNodePtr) == bstNodes.end()) {
				if (takeUnion)
					heapMerge.insert(dataNodePtr);
				else
					heap.insert(dataNodePtr);
				bstNodes.insert(dataNodePtr);
				nodeList.push_back(dataNodePtr);
			}
		}
		if (takeUnion)
			heap.fibHeapUnion(heapMerge);
		std::cout << "num unique elements: " << bstNodes.size() << std::endl;
	}

	bool CheckMin(){
		for (auto setIter = bstNodes.begin(); setIter != bstNodes.end(); ++setIter) {
			std::shared_ptr<DoublyLinkedNode> heapMin_minFxn = heap.min();
			std::shared_ptr<DoublyLinkedNode> heapMin_i = heap.extractMin();
			if ((heapMin_i->key != (*setIter)->key) || (heapMin_minFxn->key != heapMin_i->key))
				return false;
		}
		if (heap.extractMin() != nullptr)
			return false;
		return true;
	}

	bool DecreaseKeys(int n) {
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, uBits, counter, seed);
			randomNumber %= bstNodes.size();
			std::shared_ptr<DoublyLinkedNode> randElement = nodeList[randomNumber];

			long long keyTemp = randElement->key;
			int firstZeroBitIndex = 0;
			while (keyTemp != 0) {
				keyTemp >> 1;
				++firstZeroBitIndex;
			}

			RandNum(randomNumber, uBits, counter, seed);
			auto newKey = randElement->key - randomNumber % (2 << (32 - uBits));
			heap.decreaseKey(randElement, newKey);

			bstNodes.erase(randElement);
			bstNodes.insert(randElement);
			if (!CheckMin())
				return false;
		}
		return true;
	}

	bool RandomDelete(int n) {
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, uBits, counter, seed);
			randomNumber %= bstNodes.size();
			std::shared_ptr<DoublyLinkedNode> randElement = nodeList[randomNumber];

			heap.deleteNode(randElement);
			nodeList.erase(nodeList.begin() + randomNumber);
			bstNodes.erase(randElement);
			if (!CheckMin())
				return false;
		}
		return true;
	}
};

TEST_F(FibonacciHeapTest, InsertTest) {
	Insert(pow(10, 2));
	EXPECT_TRUE(CheckMin());
}
TEST_F(FibonacciHeapTest, InsertDecreaseTest) {
	Insert(pow(10, 2));
	EXPECT_TRUE(DecreaseKeys(pow(10, 2)));
}
TEST_F(FibonacciHeapTest, InsertTest) {
	Insert(pow(10, 2));
	EXPECT_TRUE(RandomDelete(pow(10, 2)));
}
}