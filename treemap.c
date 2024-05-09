#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* newMap = (TreeMap* )malloc(sizeof(TreeMap));
    newMap->root = NULL;
    newMap->current = NULL;
    newMap->lower_than = lower_than;
    return newMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    
    TreeNode *element = createTreeNode(key, value);
    if(tree->root == NULL)
    {
        tree->root = element;
    }
    else
    {
        TreeNode *aux = tree->root;
        while(true)
        {
            if(tree->lower_than(key, aux->pair->key))
            {
                if(aux->left == NULL)
                {
                    aux->left = element;
                    aux->left->parent = aux;
                    tree->current = element;
                    break;
                }
                else aux = aux->left;
            }
            else if(tree->lower_than(aux->pair->key, key))
            {
                if(aux->right == NULL)
                {
                    aux->right = element;
                    aux->right->parent = aux;
                    tree->current = element;
                    break;
                }
                else aux = aux->right;
            }
            else if(is_equal(tree, key, aux->pair->key))
            {
                aux->pair->value = value;
                tree->current = aux;
                break;
            }
        }
        
    }
}

TreeNode * minimum(TreeNode * x){

    if(x->left == NULL) return x;
    else return minimum(x->left);
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if(node->left == NULL && node->right == NULL)
    {
        node->parent = NULL;
        free(node);
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    TreeNode *aux = tree->root;
    while(aux != NULL)
    {
        if(is_equal(tree, key, aux->pair->key))
        {
            tree->current = aux;
            return aux->pair;
        }
        else if(tree->lower_than(key, aux->pair->key))
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
