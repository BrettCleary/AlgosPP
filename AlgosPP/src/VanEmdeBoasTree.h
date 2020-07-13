
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
	const KEY MaxVal;

	std::shared_ptr<VanEmdeBoasTree> Summary = nullptr;
	
	std::map<KEY, VanEmdeBoasTree> Clusters;


	KEY High(const KEY& x) {
		//bit shift right to get uHigh bits only
		KEY uLowBits = uBits >> 1;
		return x >> uLowBits;
	}

	KEY Low(const KEY& x) {
		//use bitwise operators to clear all bits except uLow
		KEY uLowBits = uBits >> 1;
		KEY xLowOnes = (1 << uLowBits) - 1;
		return x & xLowOnes;
	}

	KEY Index(const KEY& x, const KEY& y) {
		KEY uLowBits = uBits >> 1;
		return (x << uLowBits) | y;
	}

	void EmptyTreeInsert(const std::pair<KEY, std::shared_ptr<VAL>>& element) {
		MinPair = element;
		MaxPair = element;
		NodeEmpty = false;
	}

public:
	VanEmdeBoasTree(const KEY maxBits) : uBits(maxBits), MaxVal((1 << uBits) - 1) {
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(maxBits - (maxBits >> 1));
		}
	}

	VanEmdeBoasTree(const KEY maxBits, const std::pair<KEY, std::shared_ptr<VAL>>& element) : uBits(maxBits), MaxVal((1 << uBits) - 1), MinPair(element), MaxPair(element), NodeEmpty(false) {
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(maxBits - (maxBits >> 1));
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

	//subtrees will be deleted when empty
	void Insert(std::pair<KEY, std::shared_ptr<VAL>>& element) {
		//handle root case when instantiated empty
		if (NodeEmpty) {
			MinPair = element;
			MaxPair = element;
			NodeEmpty = false;
			return;
		}

		//KEY key = element.first;
		if (element.first < 0 || element.first > MaxVal)
			return;

		if (element.first <= MinPair.first) {
			auto temp = MinPair;
			MinPair = element;
			element = temp;

			//handles 0,0 and 1,1 min,max pair keys by replacement
			if (uBits == 1) {
				if (MinPair.first == MaxPair.first) {
					MaxPair = MinPair;
				}
				return;
			}
		}

		if (uBits > 1) {
			KEY highKey = High(element.first);
			KEY lowKey = Low(element.first);
			auto cluster_i = Clusters.find(highKey);
			if (cluster_i != Clusters.end()){// && !cluster_i->second.Empty()) {
				std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element.second);
				cluster_i->second.Insert(elementLow);
			}
			else {
				std::pair<KEY, std::shared_ptr<VAL>> elementHigh(highKey, element.second);
				Summary->Insert(elementHigh);

				//make new veb tree
				std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element.second);
				Clusters.emplace(highKey, VanEmdeBoasTree(uBits >> 1, elementLow));
				//cluster_i = (Clusters.insert(std::pair<KEY, VanEmdeBoasTree> ()).first;
			}
		}
		if (element.first >= MaxPair.first) {
			MaxPair = element;
		}

	}

	bool Empty() {
		return NodeEmpty;
	}

	std::pair<KEY, VAL*> Min() {
		return MinPair;
	}
};
} //algospp