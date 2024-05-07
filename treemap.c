#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    TreeMap *nuevo_arbol = (TreeMap *)malloc(sizeof(TreeMap));
    if(nuevo_arbol == NULL)
    {
        return NULL;
    }
    nuevo_arbol->root = NULL;
    nuevo_arbol->current = NULL;
    nuevo_arbol->lower_than = lower_than;
    return nuevo_arbol;
}
void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * nuevo_nodo = createTreeNode(key, value);
    if(tree->root == NULL)
    {
        tree->root = nuevo_nodo;
        tree->current = nuevo_nodo;
        return;
    }
    
    TreeNode * current = tree->root;

    while(1)
        {
            if(is_equal(tree, key, current->pair->key))
            {
                return;
            }
            if(current->left == NULL || current->right == NULL)
            {
                break;
            }
            if(tree->lower_than(current->pair->key, key))
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
    if(current->left == NULL)
    {
        current->left = nuevo_nodo;
    }
    else
    {
        current->right = nuevo_nodo;
    }
    nuevo_nodo->parent = current;
    tree->current = nuevo_nodo;
}

TreeNode * minimum(TreeNode * x){

    while(x->left != NULL)
        {
            x = x->left;
        }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode * temp = tree->root;
    if(node->left == NULL && node->right == NULL)
    {
        if(node -> parent == NULL)
        {
            tree->root = NULL;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = NULL;
        }
        else
        {
            node->parent->right = NULL;
        }
        return;
    }

    else if(node->left == NULL || node->right == NULL)
    {
        TreeNode * hijo;
        if(temp->left != NULL)
        {
            hijo = temp->left;
        }
        else
        {
            hijo = temp->right;
        }

        if(temp != tree->root)
        {
            if(temp->parent->left == temp)
            {
                temp->parent->left = hijo;
            }
            else
            {
                temp->parent->right = hijo;
            }
        }
        else
        {
            tree->root = hijo;
        }
    }
    free(temp);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * current = tree->root;
    
    while(current != NULL)
        {
            if(is_equal(tree,current->pair->key,key))
            {
                tree->current = current;
                return current->pair;
            }
            else if(tree->lower_than(key, current->pair->key))
            {
                current = current->left;
            }
            else
            {
                current = current->right;
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
