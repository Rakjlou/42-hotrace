/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:39:03 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 05:40:08 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_avl_node	*double_rotate_with_left(t_avl_node *k3)
{
	k3->left = single_rotate_with_right(k3->left);
	return (single_rotate_with_left(k3));
}

t_avl_node	*double_rotate_with_right(t_avl_node *k1)
{
	k1->right = single_rotate_with_left(k1->right);
	return (single_rotate_with_right(k1));
}

t_avl_node	*single_rotate_with_left(t_avl_node *k2)
{
	t_avl_node	*k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(avl_height(k2->left), avl_height(k2->right)) + 1;
	k1->height = max(avl_height(k1->left), k2->height) + 1;
	return (k1);
}

t_avl_node	*single_rotate_with_right(t_avl_node *k1)
{
	t_avl_node	*k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(avl_height(k1->left), avl_height(k1->right)) + 1;
	k2->height = max(avl_height(k2->right), k1->height) + 1;
	return (k2);
}
