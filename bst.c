#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createnode(int data){
    struct node *n = malloc(sizeof(struct node));
    n->data=data;
    n->left=NULL;
    n->right=NULL;
}; 

void preorder(struct node* root){
    if (root!=NULL){
        printf("%d " , root->data);
        preorder(root->left);
        preorder(root->right);
    }
};

void postorder(struct node* root){
    if (root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void inorder(struct node* root){
    if (root!=NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
        
    }
}


int isbst(struct node* root){
    static struct node * prev = NULL;
    if(root!=NULL){
        if(!isbst(root->left)){
            return 0;
        }
        if (prev!=NULL && root->data <= prev->data){
            return 0;
        }
        prev=root;
        return isbst(root->right);
        }
    else{
        return 1;
        }
    };

    struct node* search(struct node* root, int key){
        // if (root==NULL){
        //     return NULL;
        // }
        // if (key==root->data){
        //     return root;
        // }
        // else if (key<root->data){
        //     return search(root->left, key);
        // }
        // else if (key>root->data){
        //     return search(root->right, key);
        // }
        while (root!=NULL){
            if (key==root->data){
                return root;
            }
            else if(key<root->data){
                root=root->left;
            }
            else{
                root=root->right;
            }
        }
        return NULL;
        
    }

int main(){

    //      4
    //     / \                 // 
    //    2   6             preorder 41526 postorder 52164 inorder 51246
    //   / \                   
    //  1   3                  //
    
    struct node* p1 = createnode(4);
    struct node* p2 = createnode(2);
    struct node* p3 = createnode(6);
    struct node* p4 = createnode(1);
    struct node* p5 = createnode(3);

    p1->left=p2;
    p1->right=p3;
    p2->left=p4;
    p2->right=p5;

    preorder(p1);
    printf("\n");
    postorder(p1);
    printf("\n");
    inorder(p1);
    printf("\n");
    printf("%d", isbst(p1));
    printf("\n");
    struct node* n=search(p1, 6);
    if (n==NULL){
        printf("not found");
    }
    else {
        printf("found  : %d", n->data);
    }

    return 0;


}