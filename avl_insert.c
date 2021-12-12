/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:35:26 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:03:33 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stddef.h>

static void	avl_linsert(void *key, void *data, t_avl *tree, t_avl_node **node)
{
	(*node)->left = avl_insert(key, data, tree, (*node)->left);
	if (avl_height((*node)->left) - avl_height((*node)->right) == 2)
	{
		if (tree->cmp(key, (*node)->left->key) < 0)
			*node = single_rotate_with_left(*node);
		else
			*node = double_rotate_with_left(*node);
	}
}

static void	avl_rinsert(void *key, void *data, t_avl *tree, t_avl_node **node)
{
	(*node)->right = avl_insert(key, data, tree, (*node)->right);
	if (avl_height((*node)->right) - avl_height((*node)->left) == 2)
	{
		if (tree->cmp(key, (*node)->right->key) > 0)
			*node = single_rotate_with_right(*node);
		else
			*node = double_rotate_with_right(*node);
	}
}

t_avl_node	*avl_insert(void *key, void *data, t_avl *tree, t_avl_node *node)
{
	int	cmp;

	if (node == NULL)
	{
		node = avl_new_node(key, data);
		if (node == NULL)
			return (NULL);
	}
	else
	{
		cmp = tree->cmp(key, node->key);
		if (cmp < 0)
			avl_linsert(key, data, tree, &node);
		else if (cmp > 0)
			avl_rinsert(key, data, tree, &node);
	}
	node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
	return (node);
}
