#include <cassert>
#include "BTree.hpp"


void TestTraversals() {
    BTree<int> tree(new BTreeNode<int>(1));

    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);

    tree.balance();

    MutableListSequence<int> lrp = tree.LRP();
    MutableListSequence<int> rlrp = tree.rLRP();
    assert(lrp.get_size() == rlrp.get_size());
    for (int i = 0; i < lrp.get_size(); ++i) {
        assert(lrp[i] == rlrp[i]);
    }

    assert(lrp[0] == 1);
    assert(lrp[1] == 4);
    assert(lrp[2] == 3);
    assert(lrp[3] == 2);
    assert(lrp[4] == 7);
    assert(lrp[5] == 6);
    assert(lrp[6] == 10);
    assert(lrp[7] == 9);
    assert(lrp[8] == 8);
    assert(lrp[9] == 5);

    MutableListSequence<int> lpr = tree.LPR();
    MutableListSequence<int> rlpr = tree.rLPR();
    assert(lpr.get_size() == rlpr.get_size());
    for (int i = 0; i < lpr.get_size(); ++i) {
        assert(lpr[i] == rlpr[i]);
    }

    assert(lpr[0] == 1);
    assert(lpr[1] == 2);
    assert(lpr[2] == 3);
    assert(lpr[3] == 4);
    assert(lpr[4] == 5);
    assert(lpr[5] == 6);
    assert(lpr[6] == 7);
    assert(lpr[7] == 8);
    assert(lpr[8] == 9);
    assert(lpr[9] == 10);

    MutableListSequence<int> prl = tree.PRL();
    MutableListSequence<int> rprl = tree.rPRL();
    assert(prl.get_size() == rprl.get_size());
    for (int i = 0; i < prl.get_size(); ++i) {
        assert(prl[i] == rprl[i]);
    }

    assert(prl[0] == 5);
    assert(prl[1] == 8);
    assert(prl[2] == 9);
    assert(prl[3] == 10);
    assert(prl[4] == 6);
    assert(prl[5] == 7);
    assert(prl[6] == 2);
    assert(prl[7] == 3);
    assert(prl[8] == 4);
    assert(prl[9] == 1);

    MutableListSequence<int> plr = tree.PLR();
    MutableListSequence<int> rplr = tree.rPLR();
    assert(plr.get_size() == rplr.get_size());
    for (int i = 0; i < plr.get_size(); ++i) {
        assert(plr[i] == rplr[i]);
    }

    assert(plr[0] == 5);
    assert(plr[1] == 2);
    assert(plr[2] == 1);
    assert(plr[3] == 3);
    assert(plr[4] == 4);
    assert(plr[5] == 8);
    assert(plr[6] == 6);
    assert(plr[7] == 7);
    assert(plr[8] == 9);
    assert(plr[9] == 10);

    MutableListSequence<int> rlp = tree.RLP();
    MutableListSequence<int> rrlp = tree.rRLP();
    assert(rlp.get_size() == rrlp.get_size());
    for (int i = 0; i < rlp.get_size(); ++i) {
        assert(rlp[i] == rrlp[i]);
    }

    assert(rlp[0] == 10);
    assert(rlp[1] == 9);
    assert(rlp[2] == 7);
    assert(rlp[3] == 6);
    assert(rlp[4] == 8);
    assert(rlp[5] == 4);
    assert(rlp[6] == 3);
    assert(rlp[7] == 1);
    assert(rlp[8] == 2);
    assert(rlp[9] == 5);
    
    MutableListSequence<int> rpl = tree.RPL();
    MutableListSequence<int> rrpl = tree.rRPL();
    assert(rpl.get_size() == rrpl.get_size());
    for (int i = 0; i < rpl.get_size(); ++i) {
        assert(rpl[i] == rrpl[i]);
    }

    assert(rpl[0] == 10);
    assert(rpl[1] == 9);
    assert(rpl[2] == 8);
    assert(rpl[3] == 7);
    assert(rpl[4] == 6);
    assert(rpl[5] == 5);
    assert(rpl[6] == 4);
    assert(rpl[7] == 3);
    assert(rpl[8] == 2);
    assert(rpl[9] == 1);

    /*
    tree.generateDotRepresentation("tree.dot");
    std::system("dot -Tpng tree.dot -o tree.png");
    */
}