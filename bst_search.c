#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

void inorder(Node* r)   { if (r) { inorder(r->left); printf("%d ", r->key); inorder(r->right); } }
void preorder(Node* r)  { if (r) { printf("%d ", r->key); preorder(r->left); preorder(r->right); } }
void postorder(Node* r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->key); } }

/* Height in edges; empty tree = -1 */
int height(Node* r) {
    if (!r) return -1;
    int l = height(r->left), rt = height(r->right);
    return 1 + (l > rt ? l : rt);
}

/* BST search: one comparison counted per node visited */
int bstSearch(Node* root, int key, int* cmp) {
    *cmp = 0;
    while (root) {
        (*cmp)++;
        if (key == root->key) return 1;
        root = (key < root->key) ? root->left : root->right;
    }
    return 0;
}

/* Linear search over the array in insertion order */
int linearSearch(int a[], int n, int key, int* cmp) {
    *cmp = 0;
    for (int i = 0; i < n; i++) {
        (*cmp)++;
        if (a[i] == key) return 1;
    }
    return 0;
}

void freeTree(Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

int main() {
    int keys[] = {45, 20, 60, 10, 30, 50, 70, 25, 55};
    int n = sizeof(keys) / sizeof(keys[0]);
    int targets[] = {25, 55, 90};
    Node* root = NULL;

    for (int i = 0; i < n; i++) root = insert(root, keys[i]);

    printf("Inorder   : "); inorder(root);   printf("\n");
    printf("Preorder  : "); preorder(root);  printf("\n");
    printf("Postorder : "); postorder(root); printf("\n");
    printf("Height of BST = %d\n\n", height(root));

    printf("%-8s %-10s %-10s %-10s %-10s\n", "Key", "BST found", "BST cmp", "Lin found", "Lin cmp");
    int tb = 0, tl = 0;
    for (int i = 0; i < 3; i++) {
        int cb, cl;
        int fb = bstSearch(root, targets[i], &cb);
        int fl = linearSearch(keys, n, targets[i], &cl);
        printf("%-8d %-10s %-10d %-10s %-10d\n", targets[i],
               fb ? "Yes" : "No", cb, fl ? "Yes" : "No", cl);
        tb += cb; tl += cl;
    }
    printf("Total comparisons: BST = %d, Linear = %d\n", tb, tl);

    freeTree(root);
    return 0;
}
