template <typename T>
struct BTreeNode {
	T value;
	BTreeNode* left;
	BTreeNode* right;
	BTreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
	BTreeNode(int x, BTreeNode* left, BTreeNode* right) : value(x), left(left), right(right) {}
};



template <typename T>
class BTree {
private:
	BTreeNode* root;
public:
	void PLR(); // Parent - Left   - Right
	void PRL(); // Parent - Right  - Left
	void LRP(); // Left   - Right  - Parent
	void LPR(); // Left   - Parent - Right
	void RLP(); // Right  - Left   - Parent
	void RPL(); // Right  - Parent - Left

	void insert();
	void search();
	void erase();
	void balance();

	void readString();
};
