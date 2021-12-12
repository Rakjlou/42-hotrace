#include <stdio.h>
#include <stdlib.h>
#include "hotrace.h"

void	avl_dispose(t_avl *tree, t_avl_node *node)
{
	if (node != NULL)
	{
		avl_dispose(tree, node->left);
		avl_dispose(tree, node->right);
		tree->free_key(node->key);
		tree->free_data(node->data);
		free(node);
	}
}

t_avl_node	*avl_find(void *key, t_avl *tree, t_avl_node *node)
{
	int	cmp;

	if (node == NULL)
		return NULL;
	cmp = tree->cmp(key, node->key);
	if (cmp < 0)
		return avl_find(key, tree, node->left);
	else if (cmp > 0)
		return avl_find(key, tree, node->right);
	else
		return node;
}

t_avl_node	*avl_find_min(t_avl_node *node)
{
	if (node == NULL)
		return NULL;
	else if (node->left == NULL)
		return node;
	else
		return avl_find_min(node->left);
}

// Why is this iterative vs find_min ? Rewrite all in iterative or recursive ?
t_avl_node	*avl_find_max(t_avl_node *node)
{
	if (node != NULL)
	{
		while(node->right != NULL)
			node = node->right;
	}
	return node;
}

static int	avl_height(t_avl_node *node)
{
	if (node == NULL)
		return -1;
	else
		return node->height;
}

static int max(int l, int r)
{
	if (l > r)
		return (l);
	return (r);
}

static t_avl_node	*single_rotate_with_left(t_avl_node *k2)
{
	t_avl_node	*k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(avl_height(k2->left), avl_height(k2->right)) + 1;
	k1->height = max(avl_height(k1->left), k2->height) + 1;
	return k1;
}

static t_avl_node	*single_rotate_with_right(t_avl_node *k1)
{
	t_avl_node	*k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(avl_height(k1->left), avl_height(k1->right)) + 1;
	k2->height = max(avl_height(k2->right), k1->height) + 1;
	return k2;
}

static t_avl_node	*double_rotate_with_left(t_avl_node *k3)
{
	k3->left = single_rotate_with_right(k3->left);
	return single_rotate_with_left(k3);
}

static t_avl_node	*double_rotate_with_right(t_avl_node *k1)
{
	k1->right = single_rotate_with_left(k1->right);
	return single_rotate_with_right(k1);
}

t_avl_node	*avl_insert(void *key, void *data, t_avl *tree, t_avl_node *node)
{
	int	cmp;

	if (node == NULL)
	{
		node = malloc(sizeof(t_avl_node));
		if (node == NULL)
			return (NULL);
		else
		{
			node->key = key;
			node->data = data;
			node->height = 0;
			node->left = NULL;
			node->right = NULL;
		}
	}
	else
	{
		cmp = tree->cmp(key, node->key);
		if (cmp < 0)
		{
			node->left = avl_insert(key, data, tree, node->left);
			if (avl_height(node->left) - avl_height(node->right) == 2)
			{
				if (tree->cmp(key, node->left->key) < 0)
					node = single_rotate_with_left(node);
				else
					node = double_rotate_with_left(node);
			}
		}
		else if (cmp > 0)
		{
			node->right = avl_insert(key, data, tree, node->right);
			if (avl_height(node->right) - avl_height(node->left) == 2)
			{
				if (tree->cmp(key, node->right->key) > 0)
					node = single_rotate_with_right(node);
				else
					node = double_rotate_with_right(node);
			}
		}
	}
	node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
	return node;
}

/*void		avl_display(t_avl_node *node)
{
	if (node == NULL)
		return;
	printf("%d",node->data);

	if (node->left != NULL)
		printf("(L:%d)",node->left->data);
	if (node->right != NULL)
		printf("(R:%d)",node->right->data);
	printf("\n");

	display_avl(node->left);
	display_avl(node->right);
}*/
