#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct  tree_t {
    data_t data;
    struct tree_t *left;
    struct tree_t *right;
}tree_t;

tree_t* createNode(data_t data){
    tree_t *newNode = (tree_t *)malloc(sizeof(tree_t));
    if(newNode == NULL){
        printf("Khong du bo nho!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertNode(tree_t **root, data_t data) {
    tree_t *newNode = createNode(data);
    if(*root == NULL){
        *root = newNode;
        return ;
    }
    if(data > (*root)->data)
        insertNode(&((*root)->right),data);
    else insertNode(&((*root)->left), data);
}

tree_t* searchBST(tree_t **root, data_t data) {
    if(*root == NULL) 
        return NULL;    //Not found
    if((*root)->data == data) return *root;    //found
    else if ((*root)->data < data) return searchBST(&((*root)->right), data);
    else return searchBST(&((*root)->left), data);
}

tree_t* find_min(tree_t **root){
    if((*root) == NULL) return NULL;
    if((*root)->left == NULL && (*root)->right == NULL) return *root;
    else find_min(&(*root)->left);
}

tree_t* find_max(tree_t **root){
    if((*root) == NULL) return NULL;
    if((*root)->left == NULL && (*root)->right == NULL) return *root;
    else find_max(&(*root)->right);
}

void deleteNode(tree_t **root, data_t data){
    if((*root) == NULL) return ;
    if(data > (*root)->data) deleteNode(&(*root)->right, data);
    else if(data < (*root)->data) deleteNode(&(*root)->left, data);
    else if((*root)->right != NULL && (*root)->left != NULL){
        tree_t *tmp = find_min(&((*root)->right));
        (*root)->data = tmp->data;
        deleteNode(&((*root)->right), data);
        free(tmp); 
    }
    else {
        tree_t* tmp = *root;
        if((*root)->left == NULL)
            *root = (*root)->right;
        else if((*root)->right == NULL)
             *root = (*root)->left;
        free(tmp);
    }
}

void freeTree(tree_t **root){
    if(root == NULL) return;
    if((*root)->left == NULL && (*root)->right == NULL) free(*root);
    else{
        freeTree(&((*root)->left));
        freeTree(&((*root)->right));
        free(*root);
    }
}

void order(tree_t *root){
    if(root == NULL) return;
    else{
        order(root->left);
        printf("%d ",root->data);
        order(root->right);
    }
}

// duyệt theo chiều rộng --> stack
// typedef struct stack_t{
//     tree_t s[10];
//     int top;
// }stack_t;

// int isFull(stack_t *stack){
//     return stack->top == 9; 
// }
// int isEmpty(stack_t *stack){
//     return stack->top == -1;
// }

// void push(stack_t **stack, tree_t *tree){
//     if(isFull(*stack)) {
//         printf("Stack is full\n");
//         return;
//     }
//     (*stack)->s[++(*stack)->top].data = tree->data; 
//     printf("%d -\n",(*stack)->s[(*stack)->top].data);
// }

// tree_t* pop(stack_t **stack){
//     if(isEmpty(stack)){
//         printf("stack is empty\n");
//         return -99999;
//     }
//     printf("==>1\n");
//     return (*stack)->s[(*stack)->top--];
// }

// stack_t* createStack(){
//     stack_t *newNode = (stack_t *)malloc(sizeof(stack_t));
//     newNode->top = -1;
//     return newNode;
// }

// void DFS(tree_t *root){
//     stack_t *stack = createStack();
//     tree_t *tmp = root;
//     if(root == NULL) return;
//     push(&stack, root);
//     while (!isEmpty(stack)) {
//         printf("==>1\n");
//         tmp = pop(stack);
//         printf("%d \n",tmp->data);
//         if(tmp->left != NULL) push(&stack, tmp->left);
//         if(tmp->right != NULL) push(&stack, tmp->right);
//         printf("%d --==\n", pop(stack));
//     }
// }

int main(){
    tree_t *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 2);
    insertNode(&root, 7);
    insertNode(&root, 15);
    insertNode(&root, 12);
    order(root);
    //DFS(root);
    printf("\n=============\n");
    deleteNode(&root, 15);
    deleteNode(&root, 7);
    deleteNode(&root, 10);
    order(root);
    freeTree(&root);
    order(root);
}