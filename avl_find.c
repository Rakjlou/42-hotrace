/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:37:43 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 05:47:29 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stddef.h>

t_avl_node	*avl_find(void *key, t_avl *tree, t_avl_node *node)
{
	int	cmp;

	if (node != NULL)
	{
		while (42)
		{
			if (node == NULL)
				return (NULL);
			cmp = tree->cmp(key, node->key);
			if (cmp < 0)
				node = node->left;
			else if (cmp > 0)
				node = node->right;
			else
				return (node);
		}
	}
	return (NULL);
}

t_avl_node	*avl_find_min(t_avl_node *node)
{
	if (node != NULL)
	{
		while (node->left != NULL)
			node = node->left;
	}
	return (node);
}

t_avl_node	*avl_find_max(t_avl_node *node)
{
	if (node != NULL)
	{
		while (node->right != NULL)
			node = node->right;
	}
	return (node);
}
