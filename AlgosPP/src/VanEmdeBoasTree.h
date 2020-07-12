
#ifndef ALGOSPP_DS_VEBTREE_H_
#define ALGOSPP_DS_VEBTREE_H_
#endif // !ALGOSPP_DS_VEBTREE_H_

#include <utility>
#include <map>
#include <memory>


namespace algospp {

	//KEY should be unsigned integer type
template <typename KEY, typename VAL> class VanEmdeBoasTree {

	bool NodeEmpty = true;
	std::pair<KEY, std::shared_ptr<VAL>> MinPair;
	std::pair<KEY, std::shared_ptr<VAL>> MaxPair;
	KEY uBits;

	std::shared_ptr<VanEmdeBoasTree> Summary = nullptr;
	
	std::map<KEY, VanEmdeBoasTree> Clusters;


	KEY High(const KEY x) {
		//bit shift right to get uHigh bits only
		KEY uLowBits = uBits >> 1;
		return x >> uLowBits;
	}

	KEY Low(const KEY x) {
		//use bitwise operators to clear all bits except uLow
		KEY uLowBits = uBits >> 1;
		KEY xLowOnes = (2 << uLowBits) - 1;
		return x & xLowOnes;
	}

	KEY Index(const KEY x, const KEY y) {
		KEY uLowBits = uBits >> 1;
		return (x << uLowBits) | y;
	}

	void EmptyTreeInsert(const std::pair<KEY, std::shared_ptr<VAL>>& element) {
		MinPair = element;
		MaxPair = element;
	}

public:
	VanEmdeBoasTree(const KEY maxBits) : uBits(maxBits) {
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(High(maxBits));
		}
	}

	//void Delete(const KEY key);

	//std::pair<KEY, VAL> Successor(const KEY key);

	//std::pair<KEY, VAL> Predecessor(const KEY key);

	std::shared_ptr<VAL> Search(const KEY& key) {
		if (NodeEmpty)
			return nullptr;

		if (key == MinPair.first)
			return MinPair.second;
		else if (key == MaxPair.first)
			return MaxPair.second;
		else if (uBits == 1)
			return nullptr;
		else {
			auto cluster_i = Clusters.find(High(key));
			if (cluster_i != Clusters.end()) {
				return cluster_i->second.Search(Low(key));
			}
		}

		return nullptr;
	}

	void Insert(KEY key, std::shared_ptr<VAL> val) {
		Insert(std::pair<KEY, std::shared_ptr<VAL>>(key, val));
	}

	//NEEDS TO BE pair<KEY, VAL*> element so that I can have diff keys with ptr to same val object and the val needs to be shared ptr
	void Insert(std::pair<KEY, std::shared_ptr<VAL>> element) {
		KEY key = element.first;
		if (key < 0 || key >(2 << uBits) - 1)
			return;

		if (NodeEmpty)
			EmptyTreeInsert(element);
		else {
			if (element.first < MinPair.first) {
				auto temp = MinPair;
				MinPair = element;
				element = temp;
			}

			KEY highKey = High(element.first);
			KEY lowKey = Low(element.first);

			if (uBits > 1) {
				auto cluster_i = Clusters.find(highKey);
				if (cluster_i != Clusters.end() && !cluster_i->second.Empty()) {
					std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element.second);
					cluster_i->second.Insert(elementLow);
				}
				else {
					std::pair<KEY, std::shared_ptr<VAL>> elementHigh(highKey, element.second);
					Summary->Insert(elementHigh);
					if (cluster_i == Clusters.end()) {
						//make new veb tree
						cluster_i = (Clusters.emplace(highKey, uBits >> 1)).first;
					}
					std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element.second);
					cluster_i->second.EmptyTreeInsert(elementLow);
				}
			}
			if (element.first > MaxPair.first) {
				MaxPair = element;
			}
		}

	}

	bool Empty() {
		return NodeEmpty;
	}

	std::pair<KEY, VAL*> Min() {
		return MinPair;
	}

	/*template <typename KEY, typename VAL> void VanEmdeBoasTree<KEY, VAL>::EmptyTreeInsert(KEY key, VAL val) {
		MinPair = std::make_shared<pair<KEY, VAL>>(key, val);
		MaxPair = MinPair;
		NodeEmpty = false;
	}*/
};

} //algospp

//#include "VanEmdeBoasTree.cpp"