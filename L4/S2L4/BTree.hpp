#pragma once

#include "../../L2/S2L2/MutableListSequence.hpp"
#include "../../L2/S2L2/MutableArraySequence.hpp"
#include "../../L2/S2L2/ListSequence.hpp"
#include "../../L2/S2L2/Sequence.hpp"
#include "../../L3/S2L3/Stack.hpp"
#include "../../L3/S2L3/Queue.hpp"
#include "../../L3/S2L3/Pair.hpp"

#include <fstream>

template <typename T>
struct BTreeNode {
	T value;
	BTreeNode* left;
	BTreeNode* right;
	BTreeNode(T x) : value(x), left(nullptr), right(nullptr) {}
	BTreeNode(T x, BTreeNode<T>* left, BTreeNode<T>* right) : value(x), left(left), right(right) {};
	bool operator==(const BTreeNode<T>& other) const;
};



template <typename T>
class BTree {
private:
	BTreeNode<T>* root;
	
	// SUPPORT METHOD for build balance tree
	BTreeNode<T>* buildBalancedTree(MutableListSequence<T>& list, int start, int end);

	int max_depth(BTreeNode<T>* node) const; // SUPPORT METHOD for max_depth
	void _rinsert(BTreeNode<T>*& node, const T& value); // SUPPORT METHOD for recursive insert

	// SUPPORT METHOD for recursive traversals
	void _rPLR(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rPRL(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rLRP(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rLPR(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rRLP(BTreeNode<T>* node, MutableListSequence<T>* list);
	void _rRPL(BTreeNode<T>* node, MutableListSequence<T>* list);


	BTreeNode<T>* rerase(BTreeNode<T>* node, const T& value); // SUPPORT METHOD for erase
	BTreeNode<T>* min_value(BTreeNode<T>* node); // SUPPORT METHOD for erase

	void destroyTree(BTreeNode<T>* node); // SUPPORT METHOD for destructor
	BTreeNode<T>* copy_tree(BTreeNode<T>* node) const; // SUPPORT METHOD for clone_tree

public:
	BTree() : root(nullptr) {}
	BTree(BTreeNode<T>* node) : root(node) {} 
	BTree(const BTree<T>& other) { root = copy_tree(other.root); }
	~BTree() { destroyTree(root); }

	// Balance tree
	void balance();

	// Iterative realization
	MutableListSequence<T> PLR() const; // Parent - Left   - Right
	MutableListSequence<T> PRL() const; // Parent - Right  - Left
	MutableListSequence<T> LRP() const; // Left   - Right  - Parent
	MutableListSequence<T> LPR() const; // Left   - Parent - Right
	MutableListSequence<T> RLP() const; // Right  - Left   - Parent
	MutableListSequence<T> RPL() const; // Right  - Parent - Left

	MutableArraySequence<T> LevelOrderTraversal() const; // Traversal by level

	// Recursive realization
	MutableListSequence<T> rPLR(); // Parent - Left   - Right
	MutableListSequence<T> rPRL(); // Parent - Right  - Left
	MutableListSequence<T> rLRP(); // Left   - Right  - Parent
	MutableListSequence<T> rLPR(); // Left   - Parent - Right
	MutableListSequence<T> rRLP(); // Right  - Left   - Parent
	MutableListSequence<T> rRPL(); // Right  - Parent - Left

	// Basic operations
	BTreeNode<T>* getRoot() const { return root; }
	int max_depth() const;
	BTreeNode<T>* search_node(const T& value) const; // search node by value
	BTree<T>* search_subtree(BTree<T>* subtree) const; // search subtree (check full structure of subtree)
	bool is_subtree(BTreeNode<T>* root, BTreeNode<T>* subroot) const; // check argument is subtree                         
	BTree<T>* clone_tree(BTreeNode<T>* root_subtree) const; // clone tree from argument-node (every node)

	void insert(const T& value); // Iterative realization 
	void rinsert(const T& value); // Recursive realization
	void erase(const T& value); // Recursive realization

	void map(T(*modifier)(T)); 

	template <typename U>
	U reduce(U accumulator, U(*reduceFunc)(const U&, const T&)) const;
};



#include "BTree.cpp"