#include "BTree.hpp"

// Balance tree with building                                                                                                           R

template <typename T>
BTreeNode<T>* BTree<T>::buildBalancedTree(MutableListSequence<T>& list, int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    BTreeNode<T>* node = new BTreeNode<T>(list.get(mid));
    node->left = buildBalancedTree(list, start, mid - 1);
    node->right = buildBalancedTree(list, mid + 1, end);
    return node;
}

template <typename T>
void BTree<T>::balance() {
    MutableListSequence<T> list = this->LPR();
    root = buildBalancedTree(list, 0, list.get_size() - 1);
}



// Iterative realization                                                                                                                I

template <typename T>
MutableListSequence<T> BTree<T>::PLR() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    stack.push(root);

    while (!stack.empty()) {
        BTreeNode<T>* node = stack.top();
        stack.pop();

        list->push_back(node->value);

        if (node->right != nullptr) {
            stack.push(node->right);
        }

        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }

    return *list;
}

template <typename T>
MutableListSequence<T> BTree<T>::PRL() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    stack.push(root);

    while (!stack.empty()) {
        BTreeNode<T>* node = stack.top();
        stack.pop();

        list->push_back(node->value);

        if (node->left != nullptr) {
            stack.push(node->left);
        }

        if (node->right != nullptr) {
            stack.push(node->right);
        }
    }

    return *list;
}

template <typename T>
MutableListSequence<T> BTree<T>::LRP() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    BTreeNode<T>* lastVisited = nullptr;

    BTreeNode<T>* current = root;
    while (!stack.empty() || current != nullptr) {
        if (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        else {
            BTreeNode<T>* nodePeek = stack.top();
            if (nodePeek->right != nullptr && lastVisited != nodePeek->right) {
                current = nodePeek->right;
            }
            else {
                list->push_back(nodePeek->value);
                lastVisited = nodePeek;
                stack.pop();
            }
        }
    }

    return *list;
}


template <typename T>
MutableListSequence<T> BTree<T>::LPR() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    BTreeNode<T>* current = root;

    while (!stack.empty() || current != nullptr) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();
        list->push_back(current->value);

        current = current->right;
    }

    return *list;
}


template <typename T>
MutableListSequence<T> BTree<T>::RLP() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    BTreeNode<T>* lastVisited = nullptr;

    BTreeNode<T>* current = root;
    while (!stack.empty() || current != nullptr) {
        if (current != nullptr) {
            stack.push(current);
            current = current->right;
        }
        else {
            BTreeNode<T>* nodePeek = stack.top();
            if (nodePeek->left != nullptr && lastVisited != nodePeek->left) {
                current = nodePeek->left;
            }
            else {
                list->push_back(nodePeek->value);
                lastVisited = nodePeek;
                stack.pop();
            }
        }
    }

    return *list;
}


template <typename T>
MutableListSequence<T> BTree<T>::RPL() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();

    if (root == nullptr) return *list;

    Stack<BTreeNode<T>*> stack;
    BTreeNode<T>* current = root;

    while (!stack.empty() || current != nullptr) {
        while (current != nullptr) {
            stack.push(current);
            current = current->right;
        }

        current = stack.top();
        stack.pop();
        list->push_back(current->value);

        current = current->left;
    }

    return *list;
}



// Recursive realization                                                                                                                R

template <typename T>
void BTree<T>::_rPLR(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    list->push_back(node->value); 
    _rPLR(node->left, list);       
    _rPLR(node->right, list);      
}

template <typename T>
MutableListSequence<T> BTree<T>::rPLR() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rPLR(root, list);
    return *list;
}

template <typename T>
void BTree<T>::_rPRL(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    list->push_back(node->value); 
    _rPRL(node->right, list);      
    _rPRL(node->left, list);       
}

template <typename T>
MutableListSequence<T> BTree<T>::rPRL() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rPRL(root, list);
    return *list;
}

template <typename T>
void BTree<T>::_rLRP(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    _rLRP(node->left, list);;     
    _rLRP(node->right, list);     
    list->push_back(node->value); 
}

template <typename T>
MutableListSequence<T> BTree<T>::rLRP() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rLRP(root, list);
    return *list;
}

template <typename T>
void BTree<T>::_rLPR(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    _rLPR(node->left, list);       
    list->push_back(node->value); 
    _rLPR(node->right, list);
}

template <typename T>
MutableListSequence<T> BTree<T>::rLPR() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rLPR(root, list);
    return *list;
}

template <typename T>
void BTree<T>::_rRLP(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    _rRLP(node->right, list);      
    _rRLP(node->left, list);       
    list->push_back(node->value); 
}

template <typename T>
MutableListSequence<T> BTree<T>::rRLP() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rRLP(root, list);
    return *list;
}

template <typename T>
void BTree<T>::_rRPL(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    _rRPL(node->right, list);      
    list->push_back(node->value); 
    _rRPL(node->left, list);       
}

template <typename T>
MutableListSequence<T> BTree<T>::rRPL() const {
    MutableListSequence<T>* list = new MutableListSequence<T>();
    _rRPL(root, list);
    return *list;
}



// Max depth                                                                                                                            R
template <typename T>
int BTree<T>::max_depth(BTreeNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftDepth = this->max_depth(node->left);
    int rightDepth = this->max_depth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
}

template <typename T>
int BTree<T>::max_depth() const {
    return this->max_depth(root);
}



// Search node                                                                                                                          I
template <typename T>
BTreeNode<T>* BTree<T>::search_node(const T& value) const {
    BTreeNode<T>* current = root;
    while (current != nullptr) {
        if (value == current->value) {
            return current;
        }
        else if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}



// Search & get subtree                                                                                                                 I
template <typename T>
BTree<T>* BTree<T>::search_subtree(BTree<T>* subtree) const {
    BTreeNode<T>* current = root;
    while (current != nullptr) {
        if (current == subtree->getRoot()) {
            return new BTree<T>(current);
        }
        current = (subtree->getRoot()->value < current->value) ? current->left : current->right;
    }
    return nullptr;
}

template <typename T>
BTree<T>* BTree<T>::get_subtree(const T& value) const {
    BTreeNode<T>* node = search_node(value);
    if (node) {
        return new BTree<T>(node);
    }
    return nullptr;
}



// Insert & erase                                                                                                                       I
template <typename T>
void BTree<T>::insert(const T& value) {
    if (root == nullptr) {
        root = new BTreeNode<T>(value);
        return;
    }

    BTreeNode<T>* current = root;
    BTreeNode<T>* parent = nullptr;

    while (true) {
        parent = current;
        if (value < current->value) {
            current = current->left;
            if (current == nullptr) {
                parent->left = new BTreeNode<T>(value);
                return;
            }
        }
        else {
            current = current->right;
            if (current == nullptr) {
                parent->right = new BTreeNode<T>(value);
                return;
            }
        }
    }
}

template <typename T>
void BTree<T>::_rinsert(BTreeNode<T>*& node, const T& value) {
    if (node == nullptr) {
        node = new BTreeNode<T>(value);
    }
    else if (value < node->value) {
        _rinsert(node->left, value);
    }
    else {
        _rinsert(node->right, value);
    }
}

template <typename T>
void BTree<T>::rinsert(const T& value) {
    _rinsert(root, value);
}

template <typename T>
void BTree<T>::erase(const T& value) {
    BTreeNode<T>* current = root;
    BTreeNode<T>* parent = nullptr;
    bool isLeftChild = false;

    while (current != nullptr && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
            isLeftChild = true;
        }
        else {
            current = current->right;
            isLeftChild = false;
        }
    }

    if (current == nullptr) return;

    if (current->left == nullptr && current->right == nullptr) {
        if (current != root) {
            if (isLeftChild) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else {
            root = nullptr;
        }
        delete current;
    }
    else if (current->left == nullptr || current->right == nullptr) {
        BTreeNode<T>* child = current->left ? current->left : current->right;
        if (current != root) {
            if (isLeftChild) parent->left = child;
            else parent->right = child;
        }
        else {
            root = child;
        }
        delete current;
    }
    else {
        BTreeNode<T>* successor = current->right;
        BTreeNode<T>* successorParent = current;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        if (successorParent != current) {
            successorParent->left = successor->right;
        }
        else {
            successorParent->right = successor->right;
        }

        current->value = successor->value;

        current = successor;
    }

    if (current != nullptr) delete current;
}



// Methods
template <typename T>
void BTree<T>::map(T(*modifier)(T)) {
    if (root == nullptr) return;

    // BFS
    Queue<BTreeNode<T>*> queue;
    queue.push(root);

    while (!queue.empty()) {
        BTreeNode<T>* current = queue.front();
        queue.pop();

        current->value = modifier(current->value);

        if (current->left != nullptr) queue.push(current->left);
        if (current->right != nullptr) queue.push(current->right);
    }
}

template <typename T>
T BTree<T>::reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const {
    if (root == nullptr) return accumulator;

    // DFS
    Stack<BTreeNode<T>*> stack;
    stack.push(root);
    T result = accumulator;

    while (!stack.empty()) {
        BTreeNode<T>* node = stack.top();
        stack.pop();

        result = reduceFunc(result, node->value);

        if (node->right != nullptr) stack.push(node->right);
        if (node->left != nullptr) stack.push(node->left);
    }

    return result;
}



//Operators
template <typename T>
bool BTree<T>::operator==(const BTree<T>& other) const {
    if (this->root == nullptr && other.getRoot() == nullptr) return true;
    if (this->root == nullptr || other.getRoot() == nullptr) return false;
    return (this->root->value == other.getRoot()->value) && (this->root->left, other.getRoot()->left) && (this->root->right, other.getRoot()->right);
}