

#include "../../Data Structures/VanEmdeBoasTree.h"

#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <exception>


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

	class VebTestClass {
		VanEmdeBoasTree<int, DataNode> VebTree;
		int uBits;
		int MaxVal;
		std::vector<std::pair<int, std::shared_ptr<DataNode>>> TreeElements;
	public:

		VebTestClass(int uBitsInit) : VebTree(uBits), uBits(uBitsInit) {
			MaxVal = 2 << uBits;
		}

		void Insert(int n) {
			for (int i = 0; i < n; ++i) {
				std::shared_ptr<DataNode> dataNodePtr = std::make_shared<DataNode>("a" + std::to_string(n));
				int keyVal = rand() % MaxVal;
				VebTree.Insert(keyVal, dataNodePtr);
				std::pair<int, std::shared_ptr<DataNode>> element(keyVal, dataNodePtr);
				TreeElements.push_back(element);
			}
		}

		bool SearchCheck() {
			for (auto node_i : TreeElements) {
				if (*(node_i.second) != *(VebTree.Search(node_i.first)))
					throw std::exception();
			}
		}
		


	};

	int main(int argc, char** argv) {
		VebTestClass test(16);
		test.Insert(1);
		if (!test.SearchCheck())
			throw std::exception();
	}

}//algospp

