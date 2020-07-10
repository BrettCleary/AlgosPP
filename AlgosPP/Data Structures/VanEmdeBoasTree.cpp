#include "VanEmdeBoasTree.h"

#include <cmath>

#include <vector>




namespace algospp {

	template <typename KEY, typename VAL> VanEmdeBoasTree<KEY, VAL>::VanEmdeBoasTree(const KEY maxBits): uBits(maxBits), Summary(High(maxBits)) {
		
	}

	template <typename KEY, typename VAL> std::shared_ptr<VAL> VanEmdeBoasTree<KEY, VAL>::Search(const KEY& key) {
		if (NodeEmpty)
			return nullptr;

		if (key == MinPair->first)
			return MinPair->second;
		else if (key == MaxPair->first)
			return MaxPair->second;
		else if (uBits == 1)
			return nullptr;
		else {
			auto cluster_i = Clusters.find(highKey);
			if (cluster_i != Clusters.end()) {
				return cluster_i->Search(Low(x));
			}
		}

		return nullptr;
	}

	template <typename KEY, typename VAL> void VanEmdeBoasTree<KEY, VAL>::Insert(KEY key, std::shared_ptr<VAL> val) {
		Insert(pair<KEY, std::shared_ptr<VAL>>(key, val));
	}

	//NEEDS TO BE pair<KEY, VAL*> element so that I can have diff keys with ptr to same val object and the val needs to be shared ptr
	template <typename KEY, typename VAL> void VanEmdeBoasTree<KEY, VAL>::Insert(std::pair<KEY, std::shared_ptr<VAL>> element) {
		if (key < 0 || key > (2 << uBits) - 1)
			return;

		if (NodeEmpty) 
			EmptyTreeInsert(element);
		else {
			if (element->first < MinPair->first) {
				auto temp = MinPair;
				MinPair = element;
				element = temp;
			}

			KEY highKey = high(element->first);
			KEY lowKey = low(element->first);

			if (uBits > 1) {
				auto cluster_i = Clusters.find(highKey);
				if (cluster_i != Clusters.end() && !cluster_i->Empty()) {
					std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element->second);
					cluster_i->Insert(elementLow);
				}
				else {
					std::pair<KEY, std::shared_ptr<VAL>> elementHigh(highKey, element->second);
					Summary->Insert(elementHigh);
					if (cluster_i == Clusters.end()) {
						//make new veb tree
						cluster_i = (Clusters.emplace(highKey, uBits >> 1)).first;
					}
					std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element->second);
					cluster_i->EmptyTreeInsert(elementLow);
				}
			}
			if (element->first > MaxPair->first) {
				MaxPair = element;
			}
		}

	}

	template <typename KEY, typename VAL> bool VanEmdeBoasTree<KEY, VAL>::Empty() {
		return NodeEmpty;
	}

	template <typename KEY, typename VAL> std::pair<KEY, VAL*> VanEmdeBoasTree<KEY, VAL>::Min() {
		return MinPair;
	}

	template <typename KEY, typename VAL> KEY VanEmdeBoasTree<KEY, VAL>::High(const KEY x) {
		//bit shift right to get uHigh bits only
		KEY uLowBits = uBits >> 1;
		return x >> uLowBits;
	}

	template <typename KEY, typename VAL> KEY VanEmdeBoasTree<KEY, VAL>::Low(const KEY x) {
		//use bitwise operators to clear all bits except uLow
		KEY uLowBits = uBits >> 1;
		KEY uLowOnes = (2 << uLowBits) - 1;
		return x & xLowOnes;
	}

	template <typename KEY, typename VAL> KEY VanEmdeBoasTree<KEY, VAL>::Index(const KEY x, const KEY y) {
		KEY uLowBits = uBits >> 1;
		return (x << uLowBits) | y;
	}

	/*template <typename KEY, typename VAL> void VanEmdeBoasTree<KEY, VAL>::EmptyTreeInsert(KEY key, VAL val) {
		MinPair = std::make_shared<pair<KEY, VAL>>(key, val);
		MaxPair = MinPair;
		NodeEmpty = false;
	}*/

	template <typename KEY, typename VAL> void VanEmdeBoasTree<KEY, VAL>::EmptyTreeInsert(const std::pair<KEY, std::shared_ptr<VAL>>& element) {
		MinPair = element;
		MaxPair = element;
	}


} //algospp