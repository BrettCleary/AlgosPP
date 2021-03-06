#include "../../src/Data Structures/VanEmdeBoasTree.h"
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

void RandNum(int& randomNumber, int& MaxVal, int& uBits, int& counter, int& seed) {
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
	
struct DataNode {
	std::string Name;
	DataNode(std::string name) :Name(name) {

	}

		
};
bool operator== (const DataNode& lhs, const DataNode& rhs) {
	return lhs.Name == rhs.Name;
}
bool operator!= (const DataNode& lhs, const DataNode& rhs) {
	return lhs.Name != rhs.Name;
}

class VanEmdeBoasTreeTest : public ::testing::Test {
	VanEmdeBoasTree<int, DataNode>* VebTree = nullptr;
	int uBits = 0;
	int MaxVal = 0;
	std::map<int, std::shared_ptr<DataNode>> TreeElements;

protected:

	VanEmdeBoasTreeTest(){}
	~VanEmdeBoasTreeTest() override {}
	void SetUp() override {}
	void TearDown() override {}

public:

	bool TreeEmpty() {
		return VebTree->Empty();
	}

	void CreateTree(int uBitsInit) {
		uBits = uBitsInit;
		VebTree = new algospp::VanEmdeBoasTree<int, DataNode>(uBitsInit);
		MaxVal = 2 << uBits;
	}

	void Insert(int n, bool insertMap) {
		int counter = 0, randomNumber = rand() % MaxVal, seed = 0;
		for (int i = 0; i < n; ++i) {
			std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));
			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			VebTree->Insert(randomNumber, dataNodePtr);
			if (insertMap)
				TreeElements[randomNumber] = dataNodePtr;
		}
		std::cout << "num unique elements: " << TreeElements.size() << std::endl;
	}

	void RandomSearch(int n) {
		int counter = 0, randomNumber = rand() % MaxVal, seed = 0;
		while (n > 0) {
			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			VebTree->Search(randomNumber);
			--n;
		}
	}

	std::shared_ptr<DataNode> Search(int key) {
		return VebTree->Search(key);
	}

	bool SearchCheck() {
		//check that TreeElements is a subset of VebTree
		for (auto node_i : TreeElements) {
			if (*(node_i.second) != *(VebTree->Search(node_i.first)))
				return false;
		}

		//check that VebTree is a subset of TreeElements
		for (auto pairIter = VebTree->Min(); pairIter < VebTree->Max(); pairIter = VebTree->Successor(pairIter.first)) {
			auto nodeStdMap = TreeElements.find(pairIter.first);

			if (nodeStdMap == TreeElements.end() || pairIter.second->Name != nodeStdMap->second->Name) {
				return false;
			}
		}

		return true;
	}

	bool SuccessorCheck() {
		if (TreeElements.empty() && VebTree->Empty())
			return true;
		else if (TreeElements.empty() || VebTree->Empty())
			return false;

		auto endIter = --TreeElements.end();
		int firstKey = TreeElements.begin()->first;
		std::string nextName = (VebTree->Successor(firstKey)).second->Name;
		for (auto iter = ++TreeElements.begin(); iter != endIter; ++iter) {

			if (nextName != iter->second->Name) {
				return false;
			}

			auto succElement = VebTree->Successor(iter->first);
			if (succElement.second == nullptr) {
				return false;
			}
			nextName = succElement.second->Name;
				
		}
		return true;
	}

	bool PredecessorCheck() {
		if (TreeElements.empty() && VebTree->Empty())
			return true;
		else if (TreeElements.empty() || VebTree->Empty())
			return false;

		auto firstIter = ++TreeElements.begin();
		auto endIter = --TreeElements.end();
		int firstKey = endIter->first;
		std::string nextName = (VebTree->Predecessor(firstKey)).second->Name;
		for (auto iter = --endIter; iter != firstIter; --iter) {

			if (nextName != iter->second->Name) {
				return false;
			}

			auto succElement = VebTree->Predecessor(iter->first);
			if (succElement.second == nullptr) {
				return false;
			}
			nextName = succElement.second->Name;

		}
		return true;
	}

	void RandomDelete(int n) {
		int counter = 0, seed = 0, maxNum = TreeElements.size();

		int randomNumber = 0;
		auto deletePairIter = TreeElements.lower_bound(randomNumber);
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			deletePairIter = TreeElements.lower_bound(randomNumber);
			if (deletePairIter == TreeElements.end())
				continue;
			VebTree->Delete(deletePairIter->first);
			TreeElements.erase(deletePairIter->first);
		}
	}

	void Delete(int n) {
		int i = 0;
		auto pairIter = TreeElements.begin();
		while (pairIter != TreeElements.end() && i < n) {
			auto pairIterCopy = pairIter;
			++pairIter;
			VebTree->Delete(pairIterCopy->first);
			TreeElements.erase(pairIterCopy);
			++i;
		}
	}
};
	
TEST_F(VanEmdeBoasTreeTest, InsertTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
	EXPECT_TRUE(true);
}
	
TEST_F(VanEmdeBoasTreeTest, SearchTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
 	EXPECT_TRUE(SearchCheck());
}

TEST_F(VanEmdeBoasTreeTest, SuccessorTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
	EXPECT_TRUE(SuccessorCheck());
}

TEST_F(VanEmdeBoasTreeTest, PredecessorTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
	EXPECT_TRUE(PredecessorCheck());
}

TEST_F(VanEmdeBoasTreeTest, DeleteTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
	Delete(pow(10, 4)/2);
	EXPECT_TRUE(SuccessorCheck());
	EXPECT_TRUE(PredecessorCheck());
	EXPECT_TRUE(SearchCheck());
}

TEST_F(VanEmdeBoasTreeTest, RandomDeleteTest) {
	CreateTree(20);
	Insert(pow(10, 4), true);
	RandomDelete(pow(10, 4) / 2);
	EXPECT_TRUE(SuccessorCheck());
	EXPECT_TRUE(PredecessorCheck());
	EXPECT_TRUE(SearchCheck());
}
	
/*TEST_F(VanEmdeBoasTreeTest, InsertSearchProfileTest) {
	int uBits = 20;

	std::cout << "\n" << std::endl;
	for (int i = 1; i < 10; ++i) {
		std::cout << "INSERTING/SEARCHING FOR 10^ " << i << " ELEMENTS: " << "\n" << std::endl;
		CreateTree(uBits);
		auto start = std::chrono::system_clock::now();
		Insert(pow(10, i), true);
		RandomSearch(pow(10, i));
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> milliSeconds = (end - start) * pow(10, 3);
		std::cout << "VebTree Search Insert took " << milliSeconds.count() << " ms to execute." << std::endl;

		Delete(pow(10,i));
		//EXPECT_TRUE(TreeEmpty());
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}*/

class MapTest : public ::testing::Test {
	std::map<int, std::shared_ptr<DataNode>> testMap;

protected:

	MapTest() {
	}
	~MapTest() override {

	}
	void SetUp() override {

	}
	void TearDown() override {

	}

public:
	void mapInsertSearch(int&& n, int&& uBits) {
		int MaxVal = (1 << uBits) - 1;
		int counter = 0;
		int randomNumber = rand() % MaxVal;
		int seed = 0;
		//Insert
		for (int i = 0; i < n; ++i) {
			std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));

			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			testMap[randomNumber] = dataNodePtr;
		}
		std::cout << "num unique elements: " << testMap.size() << std::endl;

		//search
		for (int i = 0; i < n; ++i) {
			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			auto iter = testMap.find(randomNumber);
		}
	}

	void ClearMap() {
		testMap.clear();
	}


	bool mapInsertSearchCorrect(int&& n, int&& uBits) {
		std::map<int, std::shared_ptr<DataNode>> testMap;
		std::unordered_map<int, std::shared_ptr<DataNode>> TreeElements;

		int MaxVal = (1 << uBits) - 1;
		int counter = 0;
		int randomNumber = rand() % MaxVal;
		int seed = 0;
		//Insert
		for (int i = 0; i < n; ++i) {
			std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));

			RandNum(randomNumber, MaxVal, uBits, counter, seed);
			testMap[randomNumber] = dataNodePtr;
			TreeElements[randomNumber] = dataNodePtr;
		}

		//search check
		bool ret = true;
		for (auto node_i : TreeElements) {
			auto iter = testMap.find(node_i.first);
			if (iter != testMap.end() && *(node_i.second) != *(iter->second))
				ret = false;
		}
		return ret;
	}

};

/*TEST_F(MapTest, InsertSearchMapTest) {
	std::cout << "\n" << std::endl;
	for (int i = 1; i < 10; ++i) {
		std::cout << "INSERTING/SEARCHING FOR 10^ " << i << " ELEMENTS: " << "\n" << std::endl;

		auto start = std::chrono::system_clock::now();
		mapInsertSearch(pow(10, i), 20);
		auto end = std::chrono::system_clock::now();
		ClearMap();
		std::chrono::duration<double> milliSeconds = (end - start) * pow(10, 3);
		std::cout << "std::map Search Insert took " << milliSeconds.count() << " ms to execute." << std::endl;
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}*/

/*
TEST(MapBenchmarking, InsertMapTest) {
	int uBits = 20;
	int n = pow(10, 6);
	std::map<int, std::shared_ptr<DataNode>> testMap;
	std::unordered_map<int, std::shared_ptr<DataNode>> TreeElements;


	int MaxVal = 2 << uBits;
	//Insert
	for (int i = 0; i < n; ++i) {
		std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));
		int keyVal = rand() % MaxVal;
		testMap.insert(std::pair<int, std::shared_ptr<DataNode>>(keyVal, dataNodePtr));
		TreeElements[keyVal] = dataNodePtr;
	}
	EXPECT_TRUE(true);
}*/
	


/*TEST(MapBenchmarking, InsertSearchUnorderedMapTest) {
	int uBits = 16;
	int n = pow(10, 7);
	std::unordered_map<int, std::shared_ptr<DataNode>> testMap;
	std::vector<std::pair<int, std::shared_ptr<DataNode>>> TreeElements;


	int MaxVal = 2 << uBits;
	//Insert
	for (int i = 0; i < n; ++i) {
		std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(n));
		int keyVal = rand() % MaxVal;
		testMap.insert(std::pair<int, std::shared_ptr<DataNode>>(keyVal, dataNodePtr));
		std::pair<int, std::shared_ptr<DataNode>> element(keyVal, dataNodePtr);
		TreeElements.push_back(element);
	}

	//search check
	bool ret = true;
	for (auto node_i : TreeElements) {
		auto iter = testMap.find(node_i.first);
		if (iter != testMap.end() && *(node_i.second) != *(iter->second))
			ret = false;
	}
	EXPECT_TRUE(ret);
}*/

}//algospp