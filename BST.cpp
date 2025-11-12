#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdlib>

using namespace std;

// ===============================
// Binary Search Tree (BST) Node
// ===============================
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// =============================================
// Create a new node with the given integer data
// =============================================
struct node* newNode(int data) {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ==============================================
// Insert a new value into the BST (recursive)
// ==============================================
void insert(struct node** rootRef, int data) {
    if (*rootRef == NULL) {
        *rootRef = newNode(data);
    } else if (data <= (*rootRef)->data) {
        insert(&((*rootRef)->left), data);
    } else {
        insert(&((*rootRef)->right), data);
    }
}

// ===============================================
// Compute total number of nodes in the BST
// ===============================================
int size(struct node* root) {
    if (root == NULL) return 0;
    return size(root->left) + size(root->right) + 1;
}

// ===============================================
// Compute maximum depth (height) of the BST
// ===============================================
int maxDepth(struct node* root) {
    if (root == NULL) return 0;
    int lheight = maxDepth(root->left);
    int rheight = maxDepth(root->right);
    return (lheight > rheight ? lheight : rheight) + 1;
}

// ===============================================
// In-order traversal
// ===============================================
void printTreeInOrder(struct node* root) {
    if (root == NULL) return;
    printTreeInOrder(root->left);
    cout << root->data << " ";
    printTreeInOrder(root->right);
}

// ===============================================
// Pre-order traversal
// ===============================================
void printTreePreOrder(struct node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
}

// ===============================================
// Post-order traversal
// ===============================================
void printTreePostOrder(struct node* root) {
    if (root == NULL) return;
    printTreePostOrder(root->left);
    printTreePostOrder(root->right);
    cout << root->data << " ";
}

// ===============================================
// Lookup a value in the BST
// ===============================================
bool lookup(struct node* root, int target) {
    if (root == NULL) return false;
    if (root->data == target)
        return true;
    else if (target < root->data)
        return lookup(root->left, target);
    else
        return lookup(root->right, target);
}

// ===============================================
// Find maximum and minimum values
// ===============================================
int findMaxValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->right == NULL) return root->data;
    return findMaxValue(root->right);
}

int findMinValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->left == NULL) return root->data;
    return findMinValue(root->left);
}

struct node* findMinValueNode(struct node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return findMinValueNode(root->left);	
}

int findMinValueNoRecursive(struct node* root) {
    if (root == NULL) return -1;
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}

// ===============================================
// 1. Find the kth largest element in the BST
// ===============================================
// @param root: pointer to BST root
// @param k: order number (1 = largest, 2 = 2nd largest, etc.)
// @return pointer to node that holds the kth largest value,
//         or NULL if k > number of nodes

int counter = 0;

struct node* findKthLargest_HELPER(struct node* root, int k) {
	if(root == NULL) return NULL; //base case: k > BST size : k is out of bounds

	struct node* right = findKthLargest_HELPER(root->right, k); //traverse right
	if(right != NULL) return right; //keep traversing right

	counter++; //increments counter by 1
	if(counter == k) return root; //kth largest element found

	return findKthLargest_HELPER(root->left, k); //traverse left
}

struct node* findKthLargest(struct node* root, int k) {
        counter = 0; //reset counter
        return findKthLargest_HELPER(root, k);
}

// ===============================================
// 2. Find minimum absolute difference between any
//     two node values in the BST
// ===============================================
// @param root: pointer to BST root
// @return smallest absolute difference between any two nodes

struct node* prevNode = NULL;
int minDiff = INT_MAX;

int getMinimumDifference_HELPER(struct node* root) {
	if(root == NULL) return minDiff; //base case
	
	getMinimumDifference_HELPER(root->left); //traverse left

	if(prevNode != NULL) minDiff = min(minDiff, abs(root->data - prevNode->data)); //set minDiff to smallest between previous value (minDiff) and current value (current - previous)
	prevNode = root; //set prevNode to current node (root)

	getMinimumDifference_HELPER(root->right); //traverse right
	
	return minDiff; //minDiff found
}

int getMinimumDifference(struct node* root) {
        prevNode = NULL; //reset prevNode
        minDiff = INT_MAX; //reset minDiff
        return getMinimumDifference_HELPER(root);
}

// ===============================================
// 3. Delete a node by value
// ===============================================
// @param rootRef: pointer to pointer to root
// @param data: integer value to delete
// @return pointer to deleted node (if found), otherwise NULL

struct node* findMin(struct node* root) {
	while(root->left != NULL) root = root->left;
	return root;
}

struct node* deleteNode(struct node** rootRef, int data) {
	if(*rootRef == NULL) return NULL; //base case
	
	//search for node	
	if(data < (*rootRef)->data) return deleteNode(&(*rootRef)->left, data);
	else if(data > (*rootRef)->data) return deleteNode(&(*rootRef)->right, data);
	else
	{
		//no child : delete directly
		if((*rootRef)->left == NULL && (*rootRef)->right == NULL)
		{
			delete *rootRef;
			*rootRef = NULL;
		}
		//one child : replace node with child
		else if((*rootRef)->left == NULL)
		{
			struct node* temp = *rootRef;
			*rootRef = (*rootRef)->right;
			delete temp;
		}
		else if((*rootRef)->right == NULL)
		{
                        struct node* temp = *rootRef;
                        *rootRef = (*rootRef)->left;
                        delete temp;
		}
		//two children : find inorder successor ; copy and delete successor
		else 
		{
			struct node* temp = findMin((*rootRef)->right);
			(*rootRef)->data = temp->data;
			deleteNode(&(*rootRef)->right, temp->data);
		}
	}
	
	return *rootRef;
}

// ===============================================
// 4. Delete all nodes
// ===============================================
// @param rootRef: pointer to pointer to root
// @return void
void deleteTree(struct node** rootRef) {
	if(*rootRef == NULL) return; //base case
	
	deleteTree(&(*rootRef)->left); //delete left subtree
        deleteTree(&(*rootRef)->right); //delete right subtree
	
	delete *rootRef; //delete current node
	*rootRef = NULL; //set root to NULL
}

int main() {
    struct node* root = NULL;

    int values[] = { -5, -4, -1, 1, 41, 20, 11, 90, 29, 32, 65, 70, 30, 75};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i)
        insert(&root, values[i]);

    cout << "In-Order: ";  printTreeInOrder(root);  cout << endl;
    cout << "Tree size: " << size(root) << ", Height: " << maxDepth(root) << endl;

    // Find kth largest
    int k = 3;
    struct node* kth = findKthLargest(root, k);
    if (kth) cout << "\n3rd largest value: " << kth->data << endl;
    else cout << "\nk is out of bounds" << endl;

    // Minimum absolute difference
    cout << "Minimum absolute difference: " << getMinimumDifference(root) << endl;

    // Delete node
    cout << "\nDeleting node with value 20..." << endl;
    struct node* deleted = deleteNode(&root, 20);
    if (deleted != NULL){
      cout << "Deleted node had value: " << deleted->data << endl;
      cout << "After deletion (In-Order): ";  printTreeInOrder(root);  cout << endl;
    }

    // Cleanup all nodes
    cout << "\nDeleting all nodes..." << endl;
    deleteTree(&root);
    if(root == NULL)
      cout << "Tree successfully cleared." << endl;
    else
      cout << "Error: Tree not cleared." << endl;

    return 0;
}
