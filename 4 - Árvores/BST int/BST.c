#include <stdio.h>
#include <stdlib.h>
#include "BST.h"


BST *BST_alloc()
{
    BST *bst = malloc(sizeof(BST));

    if (bst)
    {
        bst->value = 0;
        bst->left = NULL;
        bst->right = NULL;
    }

    return bst;
}

void BST_free(BST *bst)
{
    if (bst)
    {
        BST_free(bst->left);
        BST_free(bst->right);
        free(bst);
    }
}

void BST_insert(BST *bst, int value)
{
    BST *new = NULL;

    if (bst && value)
    {
        if (bst->value == 0)
            bst->value = value;
        else
        {
            if (bst->value < value)
            {
                if (bst->right == NULL)
                {
                    new = BST_alloc();
                    new->value = value;
                    bst->right = new;
                }
                else
                {
                    BST_insert(bst->right, value);
                }
            }
            else if (bst->value > value)
            {
                if (bst->left == NULL)
                {
                    new = BST_alloc();
                    new->value = value;
                    bst->left = new;
                }
                else
                {
                    BST_insert(bst->left, value);
                }
            }
        }
    }
}

BST *BST_search(BST *bst, int value)
{
    if (bst && value)
    {
        if (bst->value == value)
        {
            return bst;
        }
        else if (bst->value > value)
        {
            return BST_search(bst->left, value);
        }
        else if (bst->value < value)
        {
            return BST_search(bst->right, value);
        }
    }

    return NULL;
}

BST *BST_remove(BST *bst, int value)
{
    BST *aux = NULL, *n = NULL;

    if (bst && value)
    {
        if (bst->value == value)
        {
            if (bst->left && bst->right)
            {

                n = bst->left;
                while (n->right)
                {
                    aux = n;
                    n = n->right;
                }

                if (aux)
                {
                    aux->right = n->left;
                    n->left = bst->left;
                }

                n->right = bst->right;
                free(bst);
                return n;
            }
            else if (bst->left)
            {
                aux = bst->left;
                free(bst);
                return aux;
            }
            else if (bst->right)
            {
                aux = bst->right;
                free(bst);
                return aux;
            }
            else
            {
                free(bst);
                return NULL;
            }
        }
        else if (bst->value < value)
        {
            bst->right = BST_remove(bst->right, value);
        }
        else if (bst->value > value)
        {
            bst->left = BST_remove(bst->left, value);
        }
    }

    return bst;
}

void BST_print(BST *bst)
{
    if (bst)
    {
        printf("(%d ", bst->value);
        BST_print(bst->left);
        BST_print(bst->right);
        printf(") ");
    }
    else
        printf("~ ");
}

