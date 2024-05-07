#pragma once
#include "../../../../L2/S2L2/MutableListSequence.hpp"
#include "../../../../L2/S2L2/ListSequence.hpp"
#include "../../../../L2/S2L2/Sequence.hpp"



template <typename T>
struct BTreeNode {
	T value;
	BTreeNode* left;
	BTreeNode* right;
	BTreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
	BTreeNode(int x, BTreeNode<T>* left, BTreeNode<T>* right) : value(x), left(left), right(right) {}
};



template <typename T>
class BTree {
private:
	BTreeNode<T>* root;
public:
	BTree(BTreeNode<T>* node) : root(node) {}

	// Iterative realization
	Sequence<T> PLR() const; // Parent - Left   - Right
	Sequence<T> PRL() const; // Parent - Right  - Left
	Sequence<T> LRP() const; // Left   - Right  - Parent
	Sequence<T> LPR() const; // Left   - Parent - Right
	Sequence<T> RLP() const; // Right  - Left   - Parent
	Sequence<T> RPL() const; // Right  - Parent - Left

	// Recursive realization
	Sequence<T> _PLR() const; // Parent - Left   - Right
	Sequence<T> _PRL() const; // Parent - Right  - Left
	Sequence<T> _LRP() const; // Left   - Right  - Parent
	Sequence<T> _LPR() const; // Left   - Parent - Right
	Sequence<T> _RLP() const; // Right  - Left   - Parent
	Sequence<T> _RPL() const; // Right  - Parent - Left

	// Basic operations
	void insert();
	T search_node(); // поиск по значению
	BTree<T>* search_subtree(); // поиск поддерева
	BTree<T>* get_subtree(); // получение поддерева по узлу
	void erase(); 
	void balance();

	BTree<T>* map(T (*modifier)(const T&));
	BTree<T>* where(bool (*predicate)(const T&));
	T reduce(BTreeNode<T>* root, T(*reduceFunc)(T, T), T accumulator);

	// Work with string
	
	// Прошивка?
};



#include "BTree.cpp"