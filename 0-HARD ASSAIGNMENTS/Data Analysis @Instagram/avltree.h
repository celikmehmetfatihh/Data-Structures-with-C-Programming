struct AVLTreeNode{
	char postId[35], permaLink[75], type[10], posted[35];
	int totalReach, engagedUser;
	int height;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
	struct AVLTreeNode *side;
};
typedef struct AVLTreeNode *AVLTree;

int HeightAvlTree(AVLTree);
AVLTree RightRotation(AVLTree);
AVLTree LeftRotation(AVLTree);
AVLTree DoubleRightRotation(AVLTree);
AVLTree DoubleLeftRotation(AVLTree);
int MaxOfTwo(int, int);
