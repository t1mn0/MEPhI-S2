#include <cassert>
#include "BTree.hpp"

void TestBoundaryCases() {
	
	// Test empty tree
	
	BTree<int> tree0;
	assert(tree0.getRoot() == nullptr);
	assert(tree0.max_depth() == 0);
	
	MutableListSequence<int> lrp = tree0.LRP();
	MutableListSequence<int> rlrp = tree0.rLRP();
	MutableListSequence<int> lpr = tree0.LPR();
	MutableListSequence<int> rlpr = tree0.rLPR();
	MutableListSequence<int> rlp = tree0.RLP();
	MutableListSequence<int> rrlp = tree0.rRLP();
	MutableListSequence<int> rpl = tree0.RPL();
	MutableListSequence<int> rrpl = tree0.rRPL();
	MutableListSequence<int> plr = tree0.PLR();
	MutableListSequence<int> rplr = tree0.rPLR();
	MutableListSequence<int> prl = tree0.PRL();
	MutableListSequence<int> rprl = tree0.rPRL();

	MutableListSequence<int> levelorder = tree0.LevelOrderTraversal();

	assert(lrp.get_size() == 0);
	assert(rlrp.get_size() == 0);
	assert(lpr.get_size() == 0);
	assert(rlpr.get_size() == 0);
	assert(rlp.get_size() == 0);
	assert(rrlp.get_size() == 0);
	assert(rpl.get_size() == 0);
	assert(rrpl.get_size() == 0);
	assert(plr.get_size() == 0);
	assert(rplr.get_size() == 0);
	assert(prl.get_size() == 0);
	assert(rprl.get_size() == 0);
	assert(levelorder.get_size() == 0);


	assert(tree0.search_node(1) == nullptr);
	assert(tree0.search_node(153131) == nullptr);
	assert(tree0.search_node(0) == nullptr);

	tree0.insert(100);
	assert(tree0.getRoot()->value == 100);
	tree0.erase(100);
	assert(tree0.getRoot() == nullptr);
	tree0.rinsert(52);
	assert(tree0.getRoot()->value == 52);

	tree0.erase(52);
	assert(tree0.getRoot() == nullptr);

	for (int i = 50; i < 101; ++i) {
		tree0.erase(i);
	}

	BTree<int> tree1;
	for (int i = 1; i <= 30; ++i) {
		tree1.insert(i);
	}

	for (int i = 25; i <= 50; ++i) {
		tree1.erase(i);
	}

	tree1.insert(25);
	tree1.insert(22);
	tree1.insert(12);

	tree1.balance();
	// 25 + 3 = 28
	// [log28] + 1 = 5 + 1 = 6
	assert(tree1.max_depth() == 5);

	for (int i = 100; i < 111; ++i) {
		assert(tree1.search_node(i) == nullptr);
	}

	MutableListSequence<int> preorder = tree1.PRL();
	MutableListSequence<int> inorder = tree0.LRP();

	// (!) buildByTraversals 
}