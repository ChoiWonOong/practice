#include <stdio.h>
#include <stdlib.h>
#define max(a,b)  (((a) > (b)) ? (a) : (b)) // find bigger value

struct Node* rebalance(struct Node* node);
struct Node* setDepth(struct Node* node, int depth);

// Node structure
struct Node {   
    int data;
    int depth;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

// Create new Node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));   //dynamic allocation
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Insert Node
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* temp = createNode(data);
        return temp;
    } else if (data < root->data) {     // if inserted node's data is less than parent's data
        root->left = insertNode(root->left, data);
        root->left->parent = root;      // connect child node with parent node      
        root = rebalance(root);
    } else if (data > root->data) {     // if inserted node's data is bigger than parent's data
        root->right = insertNode(root->right, data);
        root->right->parent = root;     // connect child node with parent node
        root = rebalance(root);
        root = setDepth(root, 0);              // depth reassign
    } else {}                           // data duplicated
    return root;
}

// Binary Search
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {   // if data equals node's data
        return root;
    }
    if (data < root->data) {                    // if data is less than node's data
        return search(root->left, data);        // left branch recursive implement
    } 
    else {                                      // if data is OR is bigger than node's data
        return search(root->right, data);       // right branch recursive implement
    }
}

// Find the minimum value in a tree/subtree. It is used in balancing function.
struct Node* findMin(struct Node* node)
{
    while(node->left!=NULL){    // if left child is not null
        node = node->left;      // go to left node
    }
    return node;
}

// Delete Node (Binary Search Tree)
struct Node* deleteNode(struct Node* root, int data) {
    //Find the Node with data to be deleted
    if (root == NULL) {
        printf("NULL node");
        return root;
    }
    //left child
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
        root = setDepth(root, 0);          // depth assign
        root = rebalance(root);     // rebalance after the delete function
    }
    //right child
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
        root = setDepth(root, 0);          // depth assign
        root = rebalance(root);     // rebalance after the delete function
    } 
    else { 
        // Node to be deleted found
        // Case 1: No child or only one child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);     // memory deallocate
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);     // memory deallocate
            return temp;
        }
        // Case 2: Two children
        else{
            struct Node* temp = findMin(root->right);       // find minimum node from right branch
            root->data = temp->data;                        // change data
            root->right = deleteNode(root->right, temp->data);  // right node recursive 

            temp->parent = root->parent;                    // connect minimum node
			temp->left = root->left;
            
            if (root->left != NULL)
            {root->left->parent = temp;}
		    
            temp->right = root->right;
            
            if (root->right != NULL)
            {root->right->parent = temp;}
			
            root = temp;
            free(temp); //deallocate node
        }
    }
    return root;
}
struct Node* setDepth(struct Node* node, int depth){    // depth assign function
    if (node == NULL)                   // if null node
        return 0;
    else{
        node->depth = depth;            // set depth
        setDepth(node->left, depth+1);  // go to left child node with dept + 1
        setDepth(node->right, depth+1); // go to right child node with dept + 1
    }
    return node;
}

// Calculate the depth of tree/subtree
int GetDepth(struct Node* node)
{
    if (node == NULL) return 0;             // if null node
	
    int leftDepth = GetDepth(node->left);   // left child node recursive function
    int rightDepth = GetDepth(node->right); // right child node recursive function
	
    return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1; // return bigger value of depth
}

int balanceFactor(struct Node* node){       // get balance factor
    return GetDepth(node->left) - GetDepth(node->right);
}

//Fucntion implements left Rotate Excution
struct Node* Left_Rotate(struct Node* node)
{
    struct Node* childNode = node->right;
    node->right = childNode->left;
    if (childNode->left != NULL)
        childNode->left->parent = node;
	
    childNode->left = node;
    childNode->parent = node->parent;
    node->parent = childNode;
	
    return childNode;
}

//Fucntion implements right Rotate Excution
struct Node* Right_Rotate(struct Node* node)
{
    struct Node* childNode = node->left;
    node->left = childNode->right;
    if (childNode->right != NULL){
        childNode->right->parent = node;
        }   
    childNode->right = node;
    childNode->parent = node->parent;
    node->parent = childNode;
    return childNode;
}

struct Node* LL(struct Node* node){     // LL case
    return Right_Rotate(node);
}

struct Node* RR(struct Node* node){     // RR case
    return Left_Rotate(node);
}

struct Node* LR(struct Node* node){     // LR case
    node->left = Left_Rotate(node->left);
    return Right_Rotate(node);
}

struct Node* RL(struct Node* node){     // RL case
    node->right = Right_Rotate(node->right);
    return Left_Rotate(node);
}

// 트리의 높이 균형을 유지하는 함수.
// 4가지 케이스를 가지고 rotate를 수행함.
struct Node* rebalance(struct Node* node){
    int bf = balanceFactor(node);
    if (bf > 1)
    {
        bf = balanceFactor(node->left);
        if (bf > 0)
        {
            //Right_Rotate : left left
            node = LL(node);
        }
        else
        {
            //LR : left right
            node = LR(node);
        }
    }
    else if (bf < -1)
    {
        bf = balanceFactor(node->right);
        if (bf < 0)
        {
            //Left_Rotate : right right
            node = RR(node);
        }
        else
        {
            //RL : right left
            node = RL(node);
        }
    }
    return setDepth(node,0);
}

// Function to traverse the tree in-order
void inorderTraversal(struct Node* root) {  
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("data : %d, depth : %d\n", root->data, root->depth);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insertNode(root, 45);
    root = insertNode(root, 15);
    root = insertNode(root, 79);
    root = insertNode(root, 10);
    root = insertNode(root, 12);
    root = insertNode(root, 20);
    root = insertNode(root, 55);
    root = insertNode(root, 50);
    root = insertNode(root, 90);



    inorderTraversal(root);

    int bf = balanceFactor(root);
    printf("BF : %d\n", bf);

}
