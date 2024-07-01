#include "BTree.hpp"

#define RESET	"\033[0m"
#define BLUE	"\033[1;34m"

//Operator '==' for BTreeNode
template <typename T>
bool BTreeNode<T>::operator==(const BTreeNode<T>& other) const {
    if (this == nullptr || &other == nullptr) return this == &other;
    return (value == other.value) &&
        ((left == nullptr && other.left == nullptr) || (left != nullptr && *left == *other.left)) &&
        ((right == nullptr && other.right == nullptr) || (right != nullptr && *right == *other.right));
}



// For destructor:
template <typename T>
void BTree<T>::destroyTree(BTreeNode<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}



// Balance tree                                                                                                          R
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
BTree<T>* BTree<T>::balance() {
    MutableListSequence<T> list = this->LPR();
    if (list.get_size() == 0) {
        throw Exception(ErrorCode::empty_container_error);
    }
    root = buildBalancedTree(list, 0, list.get_size() - 1);
    return this;
}



// Iterative realization traversal                                                                                                             I

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


template <typename T>
MutableArraySequence<T> BTree<T>::LevelOrderTraversal() const {
    MutableArraySequence<T> result;
    if (!root) return result;

    Queue<BTreeNode<T>*> queue;
    queue.push(root);
    while (!queue.empty()) {
        BTreeNode<T>* node = queue.front();
        queue.pop();
        result.push_back(node->value);
        if (node->left) queue.push(node->left);
        if (node->right) queue.push(node->right);
    }
    return result;
}



// Recursive realization traversal                                                                                                                R

template <typename T>
void BTree<T>::_rPLR(BTreeNode<T>* node, MutableListSequence<T>* list) {
    if (node == nullptr) return;
    list->push_back(node->value); 
    _rPLR(node->left, list);       
    _rPLR(node->right, list);      
}

template <typename T>
MutableListSequence<T> BTree<T>::rPLR() {
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
MutableListSequence<T> BTree<T>::rPRL() {
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
MutableListSequence<T> BTree<T>::rLRP() {
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
MutableListSequence<T> BTree<T>::rLPR() {
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
MutableListSequence<T> BTree<T>::rRLP() {
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
MutableListSequence<T> BTree<T>::rRPL() {
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



// Subtree                                                                                                                 I
template <typename T>
BTree<T>* BTree<T>::search_subtree(BTree<T>* subtree) const {
    if (subtree == nullptr || subtree->getRoot() == nullptr) {
        throw Exception(ErrorCode::invalid_argument);
    }
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
bool BTree<T>::is_subtree(BTreeNode<T>* root, BTreeNode<T>* subroot) const {
    if (subroot == nullptr) {
        return true;
    }
    if (root == nullptr) {
        return false;
    }
    if (*root == *subroot) {
        return true;
    }
    return is_subtree(root->left, subroot) || is_subtree(root->right, subroot);
}



// Clone (copy) tree
template <typename T>
BTreeNode<T>* BTree<T>::copy_tree(BTreeNode<T>* node) const{
    if (node == nullptr) {
        return nullptr;
    }
    BTreeNode<T>* newNode = new BTreeNode<T>(node->value);
    newNode->left = copy_tree(node->left);
    newNode->right = copy_tree(node->right);
    return newNode;
}

template <typename T>
BTree<T>* BTree<T>::clone_tree(BTreeNode<T>* subtreeRoot) const {
    if (subtreeRoot == nullptr) {
        return new BTree<T>(nullptr);
    }

    BTreeNode<T>* newRoot = new BTreeNode<T>(subtreeRoot->value);
    newRoot->left = copy_tree(subtreeRoot->left);
    newRoot->right = copy_tree(subtreeRoot->right);

    return new BTree<T>(newRoot);
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
    if (root == nullptr) return;

    root = rerase(root, value);
}

template <typename T>
BTreeNode<T>* BTree<T>::rerase(BTreeNode<T>* currentNode, const T& value) {
    if (currentNode == nullptr) return currentNode; // Не нашли узел, возвращаем текущий

    if (value < currentNode->value) {
        currentNode->left = rerase(currentNode->left, value);
    }
    else if (value > currentNode->value) {
        currentNode->right = rerase(currentNode->right, value);
    }
    else {
        if (currentNode->left == nullptr) {
            BTreeNode<T>* temp = currentNode->right;
            delete currentNode;
            return temp;
        }
        else if (currentNode->right == nullptr) {
            BTreeNode<T>* temp = currentNode->left;
            delete currentNode;
            return temp;
        }

        BTreeNode<T>* minNode = min_value(currentNode->right);
        currentNode->value = minNode->value;
        currentNode->right = rerase(currentNode->right, minNode->value);
    }
    return currentNode;
}

template <typename T>
BTreeNode<T>* BTree<T>::min_value(BTreeNode<T>* node) {
    BTreeNode<T>* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}



// Reduce

template <typename T>
template <typename U>
U BTree<T>::reduce(const U accumulator, U(*reduceFunc)(const U&, const T&)) const {
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
