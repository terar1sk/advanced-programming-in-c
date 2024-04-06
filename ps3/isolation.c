#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int data;              
    struct tree *left;  
    struct tree *right; 
} Tree;

Tree *addtree(Tree *root, int nv){
    if(root == NULL){
        root = (Tree*)malloc(sizeof(Tree));
        root->data = nv;
        root->left = root->right = NULL;
        return root;
    }
    if(root->data < nv){
        root->right = addtree(root->right, nv);
    }
    else{
    	root->left = addtree(root->left, nv);
    }
    return root;
}

void arraytree(Tree *root, int arr[]){
    static int md = 0;
    if(root == NULL){
    return;
    }             
    arraytree(root->left, arr);     
    arr[md++] = root->data;
    arraytree(root->right, arr);      
    free(root);
}

void sorttree(int arr[], int tt){
    Tree *root;
    int a;
    root = NULL;
    for(a = 0; a < tt; a++){
    	root = addtree(root, arr[a]);
    }
    arraytree(root, arr);             
}

int main(){
    int a;
    int arr[19] = { 0, 7, 8, 3, 52, 14, 16, 18, 15, 13, 42, 30, 35, 26, 456, 5, 78, 99, 12345 };

    sorttree(arr, 19);
    for(a = 0; a < 19; a++) 
        printf("%d ", arr[a]);
    
    return 0;
}

