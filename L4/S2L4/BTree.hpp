#pragma once
#include "../../../../L2/S2L2/MutableListSequence.hpp"
#include "../../../../L2/S2L2/MutableArraySequence.hpp"
#include "../../../../L2/S2L2/ListSequence.hpp"
#include "../../../../L2/S2L2/Sequence.hpp"
#include "../../../../L3/S2L3/Stack.hpp"
#include "../../../../L3/S2L3/Queue.hpp"
#include "../../../../L3/S2L3/Pair.hpp"



template <typename T>
struct BTreeNode {
	T value;
	BTreeNode* left;
	BTreeNode* right;
	BTreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
	BTreeNode(int x, BTreeNode<T>* left, BTreeNode<T>* right) : value(x), left(left), right(right) {};
};



template <typename T>
class BTree {
private:
	BTreeNode<T>* root;

	BTreeNode<T>* buildBalancedTree(MutableListSequence<T>& list, int start, int end);

	int max_depth(BTreeNode<T>* node) const;
	void _rinsert(BTreeNode<T>*& node, const T& value);

	void _rPLR(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rPRL(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rLRP(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rLPR(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rRLP(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rRPL(BTreeNode<T>* node, MutableListSequence<T>* list);

public:
	BTree(BTreeNode<T>* node) : root(node) {}
	BTreeNode<T>* getRoot() const { return root; }

	// Balance tree
	void balance();


	// Iterative realization
	MutableListSequence<T> PLR() const; // Parent - Left   - Right
	MutableListSequence<T> PRL() const; // Parent - Right  - Left
	MutableListSequence<T> LRP() const; // Left   - Right  - Parent
	MutableListSequence<T> LPR() const; // Left   - Parent - Right
	MutableListSequence<T> RLP() const; // Right  - Left   - Parent
	MutableListSequence<T> RPL() const; // Right  - Parent - Left


	// Recursive realization
	MutableListSequence<T> rPLR() const; // Parent - Left   - Right
	MutableListSequence<T> rPRL() const; // Parent - Right  - Left
	MutableListSequence<T> rLRP() const; // Left   - Right  - Parent
	MutableListSequence<T> rLPR() const; // Left   - Parent - Right
	MutableListSequence<T> rRLP() const; // Right  - Left   - Parent
	MutableListSequence<T> rRPL() const; // Right  - Parent - Left


	// Basic operations
	int max_depth() const;
	BTreeNode<T>* search_node(const T& value) const;
	BTree<T>* search_subtree(BTree<T>* subtree) const;
	BTree<T>* get_subtree(const T& value) const;

	void insert(const T& value);
	void rinsert(const T& value);
	void erase(const T& value);

	void map(T(*modifier)(T));
	T reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const;

	// Operators
	bool operator==(const BTree<T>& other) const;
};



#include "BTree.cpp"