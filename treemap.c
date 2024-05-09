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
    TreeNode *hijo = NULL;
    TreeNode * eliminar = node;
    TreeNode *padre = eliminar->parent;
    
    if(eliminar->left == NULL && eliminar->right == NULL)
    {
        if(padre->left == eliminar)
            padre->left = NULL;
        else
            padre->right = NULL;
    }
    else if(eliminar->left == NULL || eliminar->right == NULL)
    {
        if(eliminar->left == NULL)
            hijo = eliminar->right;
        else
            hijo = eliminar->left;

        if(padre->left == eliminar)
            padre->left = hijo;
        else
            padre->right = hijo;
        
        hijo->parent = padre;
    }
    else
    {
        TreeNode *aux = minimum(eliminar->right);
        removeNode(tree, aux);
        eliminar->pair = aux->pair;
    }
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
    TreeNode * min_node = minimum(tree->root);
    return min_node->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode * current = tree->current;
    if(current->right != NULL)
    {
        TreeNode * minimo = minimum(current->right);
        tree->current = minimo;
        return minimo->pair;
    }
    else
    {
        while(current->parent != NULL && current->parent->right == current)
            current = current->parent;

        if(current->parent != NULL)
        {
            tree->current = current->parent;
            return current->parent->pair;
        }
    }
    return NULL;
}
