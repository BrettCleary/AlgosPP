
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

	VanEmdeBoasTree Summary;
	
	std::map<KEY, VanEmdeBoasTree> Clusters;


	inline KEY High(const KEY x);
	inline KEY Low(const KEY x);
	inline KEY Index(const KEY x, const KEY y);

	//void EmptyTreeInsert(KEY key, VAL val);
	void EmptyTreeInsert(const std::pair<KEY, std::shared_ptr<VAL>>& element);

public:
	VanEmdeBoasTree(const KEY maxBits);

	std::shared_ptr<VAL> Search(const KEY& key);

	void Insert(std::pair<KEY, std::shared_ptr<VAL>> element);
	void Insert(KEY key, std::shared_ptr<VAL> val);

	//void Delete(const KEY key);

	std::pair<KEY, VAL*> Min();

	//std::pair<KEY, VAL> Successor(const KEY key);

	//std::pair<KEY, VAL> Predecessor(const KEY key);

	bool Empty();




};

} //algospp