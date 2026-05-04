typedef struct bst_node
{ 
	int value;

	struct bst_node* right;
	struct bst_node* left;
}bst_node;

bst_node* create_bst_node(int value);

bst_node* bst_minimum(bst_node* node);

bst_node* bst_maximum(bst_node* node);

void print_bst(bst_node node);

void bst_inorder_traversal(bst_node* HEAD);

void bst_preorder_traversal(bst_node* HEAD);

bst_node* bst_search(bst_node* HEAD, char target_val);

bst_node* bst_insert(bst_node* HEAD, int value);

bst_node* bst_delete(bst_node* root, int target_val);

void treeLevelTraversal(bst_node* node);

void printTree(bst_node* node, int depth);

void delete_bst(bst_node* root);
