#ifndef ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_
#define ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_

#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "..\Graph Algorithms\Graph.h"

namespace algospp {

struct DoublyLinkedNode {

	std::shared_ptr<Node> node;
	long long key = 0;

	std::shared_ptr<DoublyLinkedNode> next = nullptr;
	std::shared_ptr<DoublyLinkedNode> prev = nullptr;
	std::shared_ptr<DoublyLinkedNode> parent = nullptr;
	std::shared_ptr<DoublyLinkedNode> child = nullptr;
	bool mark = false;
	unsigned long long degree = 0;

};

class FibHeap {

	void removeNodeFromRootList(std::shared_ptr<DoublyLinkedNode> node) {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}

	//lists are the same afterwards, min ptrs for each heap not changed
	void concatenateLinkedLists(std::shared_ptr<DoublyLinkedNode> head1, std::shared_ptr<DoublyLinkedNode> head2) {
		if ((head1 == nullptr) || (head2 == nullptr))
			return;

		//concatenate root lists
		auto tempH1MinNext = head1->next;
		head1->next = head2;
		auto tempH2MinPrev = head2->prev;
		head2->prev = head1;

		tempH2MinPrev->next = tempH1MinNext;
		tempH1MinNext->prev = tempH2MinPrev;
	}

	//inserts nodeToInsert after nodeInList in horizontal node list
	void insertInto(std::shared_ptr<DoublyLinkedNode> nodeToInsert, std::shared_ptr<DoublyLinkedNode> nodeInList) {
		auto tempMinNext = nodeInList->next;
		nodeInList->next = nodeToInsert;
		nodeToInsert->prev = nodeInList;
		nodeToInsert->next = tempMinNext;
		nodeToInsert->parent = nodeInList->parent;
		if (nodeInList->parent != nullptr)
			++nodeInList->parent->degree;
	}

	void consolidate() {
		//get unique nodes for each node in the root list
		std::unordered_map<int, std::shared_ptr<DoublyLinkedNode>> degreeSet;
		auto rootList_i = min;
		while ((rootList_i != nullptr) && (rootList_i != min)) {
			std::shared_ptr<DoublyLinkedNode> x = rootList_i;
			auto d = x->degree;
			while (degreeSet.find(d) != degreeSet.end()) {
				std::shared_ptr<DoublyLinkedNode> y = degreeSet.find(d)->second;
				if (x->key > y->key) {
					auto temp = x;
					x = y;
					y = temp;
				}
				heapLink(y, x);
				degreeSet.erase(degreeSet.find(d));
				++d;
			}
			degreeSet[d] = x;
			rootList_i = rootList_i->next;
		}

		//create new root list
		min = nullptr;
		for (auto& degreeSet_i : degreeSet) {
			insert(degreeSet_i.second);
			--n;
		}
	}

	//x and y are in root list, makes y child of x
	void heapLink(std::shared_ptr<DoublyLinkedNode> y, std::shared_ptr<DoublyLinkedNode> x) {
		removeNodeFromRootList(y);
		insertInto(y, x->child);
		y->mark = false;
	}
	
	void cut(std::shared_ptr<DoublyLinkedNode> yChild, std::shared_ptr<DoublyLinkedNode> y) {
		//remove from y child list
		yChild->next->prev = yChild->prev;
		yChild->prev->next = yChild->next;
		--y->degree;
		//insert into root list
		insert(yChild);
		yChild->parent = nullptr;
		yChild->mark = false;
	}

	void cascadingCut(std::shared_ptr<DoublyLinkedNode> y) {
		auto z = y->parent;
		if (z != nullptr) {
			if (y->mark == false)
				y->mark = true;
			else {
				cut(y, z);
				cascadingCut(z);
			}
		}
	}

	std::shared_ptr<DoublyLinkedNode> min = nullptr;
	unsigned long long n = 0;

public:
	void insert(std::shared_ptr<DoublyLinkedNode> node) {
		if (min == nullptr) {
			min = node;
			min->next = min;
			min->prev = min;
		}
		else {
			insertInto(node, min);
			if (node->key < min->key)
				min = node;
		}
		++n;
	}

	std::shared_ptr<DoublyLinkedNode> min() {
		return min;
	}

	//merges h2 into this heap, h2 unusable afterwards
	void fibHeapUnion(FibHeap& h2) {
		concatenateLinkedLists(min, h2.min);

		n += h2.n;

		if ((min == nullptr) || (h2.min != nullptr) && (h2.min->key < min->key))
			min = h2.min;
	}

	std::shared_ptr<DoublyLinkedNode> extractMin() {
		if (min == nullptr)
			return nullptr;

		auto minChild = min->child;
		auto minChild_i = minChild;
		while ((minChild_i != nullptr) && (minChild_i != minChild)) {
			minChild_i->parent = nullptr;
			minChild_i = minChild_i->next;
		}
		concatenateLinkedLists(min->child, min);
		auto extractedMin = min;
		removeNodeFromRootList(min);
		if (min = min->next)
			min = nullptr;
		else {
			min = min->next;
			consolidate();
		}
		extractedMin->next = nullptr;
		extractedMin->prev = nullptr;
		extractedMin->child = nullptr;
		--n;
		return extractedMin;
	}

	void decreaseKey(std::shared_ptr<DoublyLinkedNode> x, long long newKey) {
		if (newKey > x->key)
			throw;

		x->key = newKey;
		auto y = x->parent;
		if (y != nullptr && x->key < y->key) {
			cut(x, y);
			cascadingCut(y);
		}
		if (x->key <= min->key)
			min = x;
	}

	std::shared_ptr<DoublyLinkedNode> deleteNode(std::shared_ptr<DoublyLinkedNode> x) {
		decreaseKey(x, LLONG_MIN);
		return extractMin();
	}
};
} //algospp
#endif //ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_