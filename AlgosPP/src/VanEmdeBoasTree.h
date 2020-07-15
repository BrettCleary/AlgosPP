
#ifndef ALGOSPP_DS_VEBTREE_H_
#define ALGOSPP_DS_VEBTREE_H_
#endif // !ALGOSPP_DS_VEBTREE_H_

#include <utility>
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>


namespace algospp {

	//KEY should be unsigned integer type
template <typename KEY, typename VAL> class VanEmdeBoasTree {

	bool NodeEmpty = true;
	std::pair<KEY, std::shared_ptr<VAL>> MinPair; //key is bitvector for ubits <= sizeof(key) * 8
	std::pair<KEY, std::shared_ptr<VAL>> MaxPair;
	KEY uBits;
	const KEY MaxVal;

	std::shared_ptr<VanEmdeBoasTree> Summary = nullptr;
	
	std::unordered_map<KEY, VanEmdeBoasTree> Clusters;

	//KEY bitVector;
	bool isBottomNode = false;
	std::shared_ptr<std::vector<std::shared_ptr<VAL>>> ValVector;


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

	KEY Index(const KEY& high, const KEY& low) {
		KEY uLowBits = uBits >> 1;
		return (high << uLowBits) | low;
	}

	void EmptyTreeInsert(const std::pair<KEY, std::shared_ptr<VAL>>& element) {
		MinPair = element;
		MaxPair = element;
		NodeEmpty = false;
	}

public:
	VanEmdeBoasTree(const KEY maxBits) : uBits(maxBits), MaxVal((1 << uBits) - 1) {
		if (sizeof(KEY) * 8 > MaxVal)
			isBottomNode = true;
		if (isBottomNode) {
			ValVector = std::make_shared<std::vector<std::shared_ptr<VAL>>>(MaxVal + 1, nullptr);
			return;
		}
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(maxBits - (maxBits >> 1));
		}
	}

	VanEmdeBoasTree(const KEY maxBits, const std::pair<KEY, std::shared_ptr<VAL>>& element) : uBits(maxBits), MaxVal((1 << uBits) - 1), MinPair(element), MaxPair(element), NodeEmpty(false) {
		if (sizeof(KEY) * 8 > MaxVal)
			isBottomNode = true;
		if (isBottomNode && element.first <= MaxVal) {
			MinPair = 0;
			MinPair.first |= 1 << element.first;
			ValVector = std::make_shared<std::vector<std::shared_ptr<VAL>>>(MaxVal + 1, nullptr);
			(*ValVector)[element.first] = element.second;
			return;
		}
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(maxBits - (maxBits >> 1));
		}
	}

	VanEmdeBoasTree(const KEY maxBits, const std::pair<KEY, std::shared_ptr<VAL>>&& element) : uBits(maxBits), MaxVal((1 << uBits) - 1), MinPair(element), MaxPair(MinPair), NodeEmpty(false) {
		if (sizeof(KEY) * 8 > MaxVal)
			isBottomNode = true;
		if (isBottomNode && MinPair.first <= MaxVal) {
			ValVector = std::make_shared<std::vector<std::shared_ptr<VAL>>>(MaxVal + 1, nullptr);
			(*ValVector)[MinPair.first] = MinPair.second;
			KEY shift = MinPair.first;
			MinPair.first = 0;
			MinPair.first |= 1 << shift;
			return;
		}
		if (maxBits > 1) {
			Summary = std::make_shared <VanEmdeBoasTree>(maxBits - (maxBits >> 1));
		}
	}

	void Delete(const KEY key) {
		if (isBottomNode) {
			MinPair.first &= ~(1 << key);
			if (MinPair.first == 0)
				NodeEmpty = true;
			return;
		}

		if (key == MinPair.first && key == MaxPair.first) {
			NodeEmpty = true;
			return;
		}

		if (key == MinPair.first) {
			KEY firstClusterKey = Summary->Min().first;
			auto firstCluster = Clusters.find(firstClusterKey);
			std::pair<KEY, std::shared_ptr<VAL>> minLowPair = firstCluster->second.Min();
			minLowPair.first = Index(firstClusterKey, minLowPair.first);
			MinPair = minLowPair;
		}

		KEY highKey = High(key);
		KEY lowKey = Low(key);
		auto cluster_i = Clusters.find(highKey);
		if (cluster_i == Clusters.end())
			return;
		cluster_i->second.Delete(lowKey);

		if (cluster_i->second.Empty()) {
			Clusters.erase(cluster_i);
			Summary->Delete(highKey);
			if (Summary->Empty()) {
				MaxPair = MinPair;
			}
			else {
				std::pair<KEY, std::shared_ptr<VAL>> maxSummaryPair = Summary->Max();
				auto maxCluster = Clusters.find(maxSummaryPair.first);
				MaxPair = maxCluster->second.Max();
				MaxPair.first = Index(maxSummaryPair.first, MaxPair.first);
			}
		}
		else if (key == MaxPair.first) {
			MaxPair = cluster_i->second.Max();
			MaxPair.first = Index(highKey, MaxPair.first);
		}
	}

	std::pair<KEY, std::shared_ptr<VAL>> Successor(const KEY key) {
		if (isBottomNode) {
			for (KEY i = key + 1; i <= MaxVal; ++i) {
				if ((1 << i) & MinPair.first) {
					return std::pair<KEY, std::shared_ptr<VAL>>(i, (*ValVector)[i]);
				}
			}
			return std::pair<KEY, std::shared_ptr<VAL>>(key, nullptr);
		}

		if (key < MinPair.first)
			return MinPair;

		KEY highKey = High(key);
		KEY lowKey = Low(key);
		auto cluster_i = Clusters.find(highKey);
		if (cluster_i != Clusters.end() && lowKey < cluster_i->second.Max().first) {
			std::pair<KEY, std::shared_ptr<VAL>> offset = cluster_i->second.Successor(lowKey);
			offset.first = Index(highKey, offset.first);
			return offset;
		}
		else {
			KEY succCluster = Summary != nullptr ? Summary->Successor(highKey).first : highKey;
			if (succCluster == highKey)
				return std::pair<KEY, std::shared_ptr<VAL>>(key, nullptr);
			else {
				auto cluster_i = Clusters.find(succCluster);
				std::pair<KEY, std::shared_ptr<VAL>> offset = cluster_i->second.Min();
				offset.first = Index(succCluster, offset.first);
				return offset;
			}
		}
		return std::pair<KEY, std::shared_ptr<VAL>>(key, nullptr);
	}

	std::pair<KEY, std::shared_ptr<VAL>> Predecessor(const KEY key) {
		if (isBottomNode) {
			for (KEY i = key - 1; i >= 0; --i) {
				if ((1 << i) & MinPair.first) {
					return std::pair<KEY, std::shared_ptr<VAL>>(i, (*ValVector)[i]);
				}
			}
			return std::pair<KEY, std::shared_ptr<VAL>>(key, nullptr);
		}

		if (key > MaxPair.first)
			return MaxPair;

		KEY highKey = High(key);
		KEY lowKey = Low(key);
		auto cluster_i = Clusters.find(highKey);
		if (cluster_i != Clusters.end() && lowKey > cluster_i->second.Min().first) {
			std::pair<KEY, std::shared_ptr<VAL>> offset = cluster_i->second.Predecessor(lowKey);
			offset.first = Index(highKey, offset.first);
			return offset;
		}
		else {
			KEY predCluster = Summary != nullptr ? Summary->Predecessor(highKey).first : highKey;

			//if MinPair is the predecessor and node is not a leaf, predecessor must be the MinPair
			if (predCluster == highKey) {
				return MinPair;
			}
			else {
				auto cluster_i = Clusters.find(predCluster);
				std::pair<KEY, std::shared_ptr<VAL>> offset = cluster_i->second.Max();
				offset.first = Index(predCluster, offset.first);
				return offset;
			}
		}
		return std::pair<KEY, std::shared_ptr<VAL>>(key, nullptr);
	}

	std::shared_ptr<VAL> Search(const KEY& key) {
		if (NodeEmpty)
			return nullptr;

		if (isBottomNode && (1 << key) & MinPair.first) {
			return key < ValVector->size() ? (*ValVector)[key] : nullptr;
		}

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
		if (isBottomNode) {
			MinPair.first |= 1 << element.first;
			(*ValVector)[element.first] = element.second;
			NodeEmpty = false;
			return;
		}

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

			if (element.first == MinPair.first) {
				element = MinPair;
			}

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
				std::pair<KEY, std::shared_ptr<VAL>> elementHigh(highKey, nullptr);
				Summary->Insert(elementHigh);

				//make new veb tree
				std::pair<KEY, std::shared_ptr<VAL>> elementLow(lowKey, element.second);
				//Clusters.emplace(highKey, VanEmdeBoasTree(uBits >> 1, elementLow));
				std::pair<KEY, VanEmdeBoasTree> newCluster(highKey, VanEmdeBoasTree(uBits >> 1, std::move(elementLow)));
				Clusters.insert(std::move(newCluster));
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

	std::pair<KEY, std::shared_ptr<VAL>> Min() {
		if (isBottomNode) {
			for (KEY i = 0; i <= MaxVal; ++i) {
				if ((1 << i) & MinPair.first) {
					return std::pair<KEY, std::shared_ptr<VAL>>(i, (*ValVector)[i]);
				}
			}
		}

		return MinPair;
	}
	std::pair<KEY, std::shared_ptr<VAL>> Max() {
		if (isBottomNode) {
			for (KEY i = MaxVal; i >= 0; --i) {
				if ((1 << i) & MinPair.first) {
					return std::pair<KEY, std::shared_ptr<VAL>>(i, (*ValVector)[i]);
				}
			}
		}

		return MaxPair;
	}
};
} //algospp