//#include "../../Data Structures/VanEmdeBoasTree.h"
#include "VanEmdeBoasTree.h"
#include "gtest/gtest.h"
//#include "simple_lib.h"

#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <exception>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>


namespace algospp {
	
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

	class VanEmbdeBoasTreeTest : public ::testing::Test {
		VanEmdeBoasTree<int, DataNode>* VebTree = nullptr;
		//VanEmdeBoasTree<int, DataNode> VebTree;
		int uBits = 0;
		int MaxVal = 0;
		std::unordered_map<int, std::shared_ptr<DataNode>> TreeElements;

	protected:

		VanEmbdeBoasTreeTest(){
		}
		~VanEmbdeBoasTreeTest() override {

		}
		void SetUp() override {

		}
		void TearDown() override {

		}

	public:

		void CreateTree(int uBitsInit) {
			uBits = uBitsInit;
			VebTree = new algospp::VanEmdeBoasTree<int, DataNode>(uBitsInit);
			MaxVal = 2 << uBits;
		}

		void Insert(int n) {
			for (int i = 0; i < n; ++i) {
				std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));
				int keyVal = rand() % MaxVal;
				VebTree->Insert(keyVal, dataNodePtr);
				TreeElements[keyVal] = dataNodePtr;
			}
		}

		bool SearchCheck() {
			for (auto node_i : TreeElements) {
				if (*(node_i.second) != *(VebTree->Search(node_i.first)))
					return false;
			}
			return true;
		}
	};
	
	/*TEST_F(VanEmbdeBoasTreeTest, InsertTest) {
		CreateTree(28);
		Insert(pow(10, 7));
		EXPECT_TRUE(true);
	}*/

	TEST_F(VanEmbdeBoasTreeTest, InsertSearchTest) {
		CreateTree(28);
		Insert(pow(10,6));
		EXPECT_TRUE(SearchCheck());
	}

	

	
	TEST(MapBenchmarking, InsertSearchMapTest) {
		int uBits = 28;
		int n = pow(10, 6);
		std::map<int, std::shared_ptr<DataNode>> testMap;
		std::unordered_map<int, std::shared_ptr<DataNode>> TreeElements;
		

		int MaxVal = 2 << uBits;
		//Insert
		for (int i = 0; i < n; ++i) {
			std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(i));
			int keyVal = rand() % MaxVal;
			testMap[keyVal] = dataNodePtr;
			TreeElements[keyVal] = dataNodePtr;
		}

		//search check
		bool ret = true;
		for (auto node_i : TreeElements) {
			auto iter = testMap.find(node_i.first);
			if (iter != testMap.end() && *(node_i.second) != *(iter->second))
				ret = false;
		}
		EXPECT_TRUE(ret);
	}

	/*TEST(MapBenchmarking, InsertMapTest) {
		int uBits = 28;
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