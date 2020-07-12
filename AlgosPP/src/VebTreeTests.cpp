

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
		std::vector<std::pair<int, std::shared_ptr<DataNode>>> TreeElements;

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
				std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(n));
				int keyVal = rand() % MaxVal;
				VebTree->Insert(keyVal, dataNodePtr);
				std::pair<int, std::shared_ptr<DataNode>> element(keyVal, dataNodePtr);
				TreeElements.push_back(element);
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

	TEST_F(VanEmbdeBoasTreeTest, InsertSearchTest) {
		CreateTree(16);
		Insert(1);
		EXPECT_TRUE(SearchCheck());
	}

	/*int main(int argc, char** argv) {
		VebTestClass test(16);
		test.Insert(1);
		if (!test.SearchCheck())
			throw std::exception();
		return 0;
	}*/

	

}//algospp
/*
int main() {

	std::cout << "Simple example C++ compiled correctly and ran." << std::endl;

	int uBits = 16;
	algospp::VanEmdeBoasTree<int, algospp::DataNode>*  VebTree = new algospp::VanEmdeBoasTree<int, algospp::DataNode>(uBits);
	//algospp::TestClass<int> tc;
	//std::cout << tc.simple_lib_function() << std::endl;
	//std::cout << tc.simpleKey(100) << std::endl;

	int MaxVal = 2 << uBits;

	return 0;
}*/

