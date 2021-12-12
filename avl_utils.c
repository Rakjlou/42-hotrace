/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:30:57 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:37:00 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	avl_height(t_avl_node *node)
{
	if (node == NULL)
		return (-1);
	else
		return (node->height);
}

int	max(int l, int r)
{
	if (l > r)
		return (l);
	return (r);
}

t_avl_node	*avl_new_node(void *key, void *data)
{
	t_avl_node	*node;

	node = malloc(sizeof(t_avl_node));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->data = data;
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_avl	*new_avl(int (*cmp)(void *, void *),
	void (*free_key)(void *),
	void (*free_data)(void *))
{
	t_avl	*tree;

	tree = malloc(sizeof(t_avl));
	if (tree == NULL)
		return (NULL);
	tree->root = NULL;
	tree->cmp = cmp;
	tree->free_key = free_key;
	tree->free_data = free_data;
	return (tree);
}
