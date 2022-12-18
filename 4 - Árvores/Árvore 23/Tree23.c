#include <stdio.h>
#include <stdlib.h>
#include "Tree23.h"

Tree23 *Tree23_alloc(int (*compar)(void *, void *))
{
	Tree23 *t = NULL;

	if (compar)
	{
		t = (Tree23 *)malloc(sizeof(Tree23));
		t->valueLeft = NULL;
		t->valueMiddle = NULL;
		t->valueRight = NULL;

		t->left = NULL;
		t->middleLeft = NULL;
		t->middleRight = NULL;
		t->right = NULL;

		t->parent = NULL;
		t->compar = compar;
	}

	return t;
}

void Tree23_free(Tree23 *t)
{
}

int Tree23_nodeType(Tree23 *t)
{

	if (t)
	{
		if (t->valueLeft && t->valueMiddle && t->valueRight)
			return 4;

		if ((t->valueLeft && t->valueMiddle && !t->valueRight) ||
			(!t->valueLeft && t->valueMiddle && t->valueRight) ||
			(t->valueLeft && !t->valueMiddle && t->valueRight))
			return 3;

		if ((t->valueLeft && !t->valueMiddle && !t->valueRight) ||
			(!t->valueLeft && t->valueMiddle && !t->valueRight) ||
			(!t->valueLeft && !t->valueMiddle && t->valueRight))
			return 2;
	}

	return 0;
}

/**
 *                    (B)
 *   (A B C)   ->    /   \
 *  /  | |  \     (A)     (C)
 *               /   \   /   \
 */
Tree23 *Tree23_split4Root(Tree23 *t)
{
	Tree23 *tA = NULL;
	Tree23 *tB = NULL;
	Tree23 *tC = NULL;

	if (t)
	{
		tA = Tree23_alloc(t->compar);
		tB = Tree23_alloc(t->compar);
		tC = Tree23_alloc(t->compar);

		tA->valueMiddle = t->valueLeft;
		tB->valueMiddle = t->valueMiddle;
		tC->valueMiddle = t->valueRight;

		tA->middleLeft = t->left;
		tA->middleRight = t->middleLeft;

		tB->middleLeft = tA;
		tB->middleRight = tC;

		tC->middleLeft = t->middleRight;
		tC->middleRight = t->right;

		free(t);
	}

	return tB;
}

Tree23 *Tree23_split4Parent2(Tree23 *t)
{
	Tree23 *tA = NULL;
	Tree23 *tB = NULL;
	Tree23 *tC = NULL;
	Tree23 *tD = NULL;
	int (*compar)(void *, void *);

	if (t)
	{
		compar = t->compar;

		/** Left child
		 *          (D)          (B D)
		 *          / \         /  |  \
		 *   (A B C)     ->   (A) (C)
		 *  /  | |  \         / \ / \
		 */
		if (t->parent->middleLeft->valueMiddle)
			if (compar(t->parent->middleLeft->valueMiddle, t->valueMiddle) == 0)
			{
				tA = Tree23_alloc(t->compar);
				tC = Tree23_alloc(t->compar);

				tA->valueMiddle = t->valueLeft;
				tA->middleLeft = t->left;
				tA->middleRight = t->middleLeft;
				tA->parent = t->parent;

				tC->valueMiddle = t->valueRight;
				tC->middleLeft = t->middleRight;
				tC->middleRight = t->right;
				tC->parent = t->parent;

				t->parent->valueLeft = t->valueMiddle;
				t->parent->left = tA;
				t->parent->middleLeft = tC;

				free(t);
				return tA;
			}

		/** Right child
		 *  (A)                (A C)
		 *  / \                / | \
		 *     (B C D)  ->  (B) (D)
		 *     / | | \      / \ / \
		 */
		if (t->parent->middleRight->valueMiddle)
			if (compar(t->parent->middleRight->valueMiddle, t->valueMiddle) == 0)
			{
				tB = Tree23_alloc(t->compar);
				tD = Tree23_alloc(t->compar);

				tB->valueMiddle = t->valueLeft;
				tB->middleLeft = t->left;
				tB->middleRight = t->middleLeft;
				tB->parent = t->parent;

				tD->valueMiddle = t->valueRight;
				tD->middleLeft = t->middleRight;
				tD->middleRight = t->right;
				tD->parent = t->parent;

				t->parent->valueRight = t->valueMiddle;
				t->parent->middleRight = tB;
				t->parent->right = tD;

				free(t);
				return tD;
			}
	}

	return NULL;
}

Tree23 *Tree23_split4Parent3(Tree23 *t)
{
	Tree23 *tA = NULL;
	Tree23 *tB = NULL;
	Tree23 *tC = NULL;
	Tree23 *tD = NULL;
	int (*compar)(void *, void *);

	if (t)
	{
		compar = t->compar;

		/** Left child
		 *          (D E)             (B D E)
		 *          / | \             / | | \
		 *   (A B C)          ->   (A) (C)
		 *   / | | \               / \ / \
		 */
		if (t->parent->middleLeft)
			if (t->parent->middleLeft->valueMiddle)
				if (compar(t->parent->middleLeft->valueMiddle, t->valueMiddle) == 0)
				{
					tA = Tree23_alloc(t->compar);
					tC = Tree23_alloc(t->compar);

					tA->parent = t->parent;
					tA->valueMiddle = t->valueLeft;
					tA->middleLeft = t->left;
					tA->middleRight = t->middleLeft;

					tC->parent = t->parent;
					tC->valueMiddle = t->valueRight;
					tC->middleLeft = t->middleRight;
					tC->middleRight = t->right;

					t->parent->valueLeft = t->valueMiddle;
					t->parent->left = tA;
					t->parent->middleLeft = tC;

					free(t);
					return tA;
				}

		/** Middle child    (X Y -)
		 *                 /  | |
		 *
		 *    (A E)          (A C E)
		 *   /  |  \        /  | |  \
		 *   (B C D)   ->    (B) (D)
		 *   / | | \         / \ / \
		 */
		if (t->parent->valueLeft && t->parent->valueMiddle) // (X Y -)
			if (t->parent->middleLeft->valueMiddle)
				if (compar(t->parent->middleLeft->valueMiddle, t->valueMiddle) == 0)
				{
					tB = Tree23_alloc(t->compar);
					tD = Tree23_alloc(t->compar);

					tB->parent = t->parent;
					tB->valueMiddle = t->valueLeft;
					tB->middleLeft = t->left;
					tB->middleRight = t->middleLeft;

					tD->parent = t->parent;
					tD->valueMiddle = t->valueRight;
					tD->middleLeft = t->middleRight;
					tD->middleRight = t->right;

					t->parent->valueRight = t->parent->valueMiddle;
					t->parent->valueMiddle = t->valueMiddle;
					t->parent->middleLeft = tB;
					t->parent->middleRight = tD;

					free(t);
					return tD;
				}

		/** Middle child   (- X Y)
		 *                   | |  \
		 *
		 *    (A E)          (A C E)
		 *   /  |  \        /  | |  \
		 *   (B C D)   ->    (B) (D)
		 *   / | | \         / \ / \
		 */
		if (t->parent->valueMiddle && t->parent->valueRight) // (- X Y)
			if (compar(t->parent->middleRight->valueMiddle, t->valueMiddle) == 0)
			{
				tB = Tree23_alloc(t->compar);
				tD = Tree23_alloc(t->compar);

				tB->parent = t->parent;
				tB->valueMiddle = t->valueLeft;
				tB->middleLeft = t->left;
				tB->middleRight = t->middleLeft;

				tD->parent = t->parent;
				tD->valueMiddle = t->valueRight;
				tD->middleLeft = t->middleRight;
				tD->middleRight = t->right;

				t->parent->valueLeft = t->parent->valueMiddle;
				t->parent->valueMiddle = t->valueMiddle;
				t->parent->middleLeft = tB;
				t->parent->middleRight = tD;

				free(t);
				return tB;
			}
	}

	return NULL;
}

Tree23 *Tree23_split4(Tree23 *t)
{
	if (t)
	{
		if (Tree23_nodeType(t) == 4)
		{
			if (t->parent == NULL)
				return Tree23_split4Root(t);

			if (Tree23_nodeType(t->parent) == 3)
				return Tree23_split4Parent3(t);

			if (Tree23_nodeType(t->parent) == 2)
				return Tree23_split4Parent2(t);
		}
	}

	return NULL;
}

Tree23 *Tree23_search(Tree23 *t, void *value)
{
	int (*compar)(void *, void *);

	if (t && value)
	{

		compar = t->compar;

		if (t->valueMiddle == NULL)
		{
			t->valueMiddle = value;
			return t;
		}

		if (Tree23_nodeType(t) == 2)
		{

			if (compar(t->valueMiddle, value) < 0)
				return Tree23_search(t->middleRight, value);
			else
				return Tree23_search(t->middleLeft, value);
		}

		if (Tree23_nodeType(t) == 3)
		{
		}
	}

	return NULL;
}

void Tree23_insert(Tree23 *t, void *value)
{
}

void *Tree23_remove(Tree23 *t, void *value)
{
	return NULL;
}
