#ifndef ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_
#define ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_

#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <exception>

#include "..\Graph Algorithms\Graph.h"

namespace algospp {

class myexception : public std::exception
{
	std::string explanation;
public:
	myexception(std::string whatHappened) : explanation(whatHappened) {

	}

	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
};


class FibHeap {

	std::shared_ptr<DoublyLinkedNode> min = nullptr;
	unsigned long long n = 0;
	long long rootListSize = 0;


	void removeNodeFromRootList(std::shared_ptr<DoublyLinkedNode> node) {
		node->next->prev = node->prev;
		node->prev->next = node->next;
		--rootListSize;
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
		tempMinNext->prev = nodeToInsert;
		nodeToInsert->parent = nodeInList->parent;
		//if (nodeInList == nodeInList->prev)
		//	nodeInList->prev = nodeToInsert;
		if (nodeInList->parent != nullptr)
			++(nodeInList->parent->degree);
	}

	void consolidate() {
		if (min->next == min || min->prev == min)
			return;
		//get unique nodes for each node in the root list
		std::unordered_map<int, std::shared_ptr<DoublyLinkedNode>> degreeSet;
		auto rootList_i = min;
		//bool minNotConsolidated = true;
		long long rootIndex = rootListSize;
		while ((rootList_i != nullptr) && --rootIndex >= 0){//rootList_i != min || minNotConsolidated)) {
			auto rootList_iNext = rootList_i->next;
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
			rootList_i = rootList_iNext;
			//minNotConsolidated = false;
		}

		//create new root list
		min = nullptr;
		for (auto& degreeSet_i : degreeSet) {
			degreeSet_i.second->parent = nullptr;
			insert(degreeSet_i.second);
			--n;
			--rootListSize;
		}
	}

	//x and y are in root list, makes y child of x
	void heapLink(std::shared_ptr<DoublyLinkedNode> y, std::shared_ptr<DoublyLinkedNode> x) {
		removeNodeFromRootList(y);
		if (x->child == nullptr) {
			x->child = y;
			y->parent = x;
			++(x->degree);
			y->next = y;
			y->prev = y;
		}
		else
			insertInto(y, x->child);
		y->mark = false;
	}
	
	void cut(std::shared_ptr<DoublyLinkedNode> yChild, std::shared_ptr<DoublyLinkedNode> y) {
		if (yChild->next == yChild || yChild->prev == yChild)
			y->child = nullptr;
		else if (yChild == y->child)
			y->child = yChild->next;
		//remove from y child list
		yChild->next->prev = yChild->prev;
		yChild->prev->next = yChild->next;
		--y->degree;
		//insert into root list
		insert(yChild);
		--n;
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

	void printNodeList(std::shared_ptr<DoublyLinkedNode> node) {
		bool nodePrinted = false;
		auto node_i = node;
		std::cout << "printing node" << std::endl;
		while (node_i != nullptr && (node_i != node || !nodePrinted)) {
			nodePrinted = true;
			std::cout << node_i->key << std::endl;
			node_i = node_i->next;
		}
	}

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
		++rootListSize;
	}

	std::shared_ptr<DoublyLinkedNode> minNode() {
		return min;
	}

	bool empty() {
		if (min == nullptr)
			return true;
		return false;
	}

	//merges h2 into this heap, h2 unusable afterwards
	void fibHeapUnion(FibHeap& h2) {
		concatenateLinkedLists(min, h2.min);

		n += h2.n;

		if ((min == nullptr) || (h2.min != nullptr) && (h2.min->key < min->key))
			min = h2.min;
	}

	void checkRootListCorrectSize() {
		auto root_i = min;
		if (min == nullptr && rootListSize > 0)
			throw myexception("Fib heap root list is not the correct size or has incorrect linkages.");
		for (int i = 0; i < rootListSize - 1; ++i) {
			root_i = root_i->next;
			if (root_i == min)
				throw myexception("Fib heap root list is incorrect. Min node appears before end of root list size.");
		}
		if (root_i != nullptr && root_i->next != min)
			throw myexception("Fib heap root list is not the correct size or has incorrect linkages.");
	}

	std::shared_ptr<DoublyLinkedNode> extractMin() {
		checkRootListCorrectSize();
		if (min == nullptr)
			return nullptr;

		auto minChild = min->child;
		auto minChild_i = minChild != nullptr ? minChild : nullptr;
		bool minChildCut = false;
		while (	minChild_i != nullptr && 
				(minChild_i != minChild ||
				!minChildCut)) {
			minChildCut = true;
			minChild_i->parent = nullptr;
			minChild_i = minChild_i->next;
		}
		concatenateLinkedLists(min->child, min);
		rootListSize += min->degree;
		auto extractedMin = min;
		removeNodeFromRootList(min);
		if (min == min->next)
			min = nullptr;
		else {
			min = min->next;
			consolidate();
		}
		extractedMin->next = nullptr;
		extractedMin->prev = nullptr;
		extractedMin->child = nullptr;
		--n;
		checkRootListCorrectSize();
		return extractedMin;
	}

	void decreaseKey(std::shared_ptr<DoublyLinkedNode> x, long long newKey) {
		checkRootListCorrectSize();
		if (min == nullptr) {
			std::cout << "Fib heap is empty. Cannot decrease key." << std::endl;
			throw myexception("Fib heap is empty. Cannot decrease key.");
		}
		if (newKey > x->key)
			throw myexception("newKey is greater than key to be decreased");

		x->key = newKey;
		auto y = x->parent;
		if (y != nullptr && x->key < y->key) {
			cut(x, y);
			cascadingCut(y);
		}
		//can't be <= because x is only cut if key is < y key
		if (x->key < min->key)
			min = x;
		checkRootListCorrectSize();
	}

	std::shared_ptr<DoublyLinkedNode> deleteNode(std::shared_ptr<DoublyLinkedNode> x) {
		decreaseKey(x, LLONG_MIN);
		return extractMin();
	}
};
} //algospp
#endif //ALGOSPP_SRC_GRAPH_FIBONACCIHEAP_H_