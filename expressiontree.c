#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[10];
    struct Node *left, *right;
};

struct Node *stack[50];
int top = -1;

struct Node* createNode(char *value) {
    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->data, value);
    newNode->left = newNode->right = NULL;

    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' ||
            c == '*' || c == '/');
}

void inorder(struct Node *root) {
    if (root != NULL) {
        if (isOperator(root->data[0]))
            printf("(");

        inorder(root->left);
        printf("%s", root->data);
        inorder(root->right);

        if (isOperator(root->data[0]))
            printf(")");
    }
}

int main() {
    char exp[] = "8 3 2 * + 6 2 / -";
    char *token = strtok(exp, " ");
    struct Node *left, *right, *newNode;

    while (token != NULL) {
        newNode = createNode(token);

        if (isOperator(token[0])) {
            right = stack[top--];
            left = stack[top--];

            newNode->left = left;
            newNode->right = right;
        }

        stack[++top] = newNode;
        token = strtok(NULL, " ");
    }

    struct Node *root = stack[top];

    printf("Infix expression: ");
    inorder(root);

    return 0;
}