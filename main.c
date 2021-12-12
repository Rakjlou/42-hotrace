/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 02:41:17 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

static inline int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == 0)
			return (0);
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int	ft_strcmp_void(void *v1, void *v2)
{
	return (ft_strcmp((const char *)v1, (const char *)v2));
}

static inline t_state	free_line_set_print_state(char *line)
{
	free(line);
	return (PRINT);
}

static t_state	store_keyval(t_avl *tree,
	char *key, char *val, unsigned int val_len)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (value == NULL)
		return (LOAD_KEY);
	value->val = val;
	value->len = val_len;
	tree->root = avl_insert(key, value, tree, tree->root);
	return (LOAD_KEY);
}

static void	print_val(t_avl *tree, char *key, unsigned int len)
{
	t_avl_node	*node;
	t_value		*val;

	node = avl_find(key, tree, tree->root);
	if (node == NULL)
	{
		write(STDOUT_FILENO, key, len - 1);
		write(STDOUT_FILENO, ": Not found.\n", 13);
	}
	else
	{
		val = (t_value *)node->data;
		write(STDOUT_FILENO, val->val, val->len);
	}
}

static void	avl_init(t_avl *tree,
	int (*cmp)(void *, void *),
	void (*free_key)(void *),
	void (*free_data)(void *))
{
	tree->root = NULL;
	tree->cmp = cmp;
	tree->free_key = free_key;
	tree->free_data = free_data;
}


void	free_avl_data(void *data)
{
	t_value	*value;

	value = (t_value *)data;
	free(value->val);
	free(data);
}

int	main(void)
{
	t_state				state;
	t_avl				tree;
	char				*key;
	char				*line;
	unsigned int		line_len;

	(state = LOAD_KEY, avl_init(&tree, ft_strcmp_void, free, free_avl_data));
	while (42)
	{
		line = get_next_line(STDIN_FILENO, &line_len);
		if (line == NULL)
			break ;
		else if (line_len == 1 && line[0] == '\n')
			state = free_line_set_print_state(line);
		else if (state == LOAD_KEY)
		{
			key = line;
			state = LOAD_VALUE;
		}
		else if (state == LOAD_VALUE)
			state = store_keyval(&tree, key, line, line_len);
		else if (state == PRINT)
			(print_val(&tree, line, line_len), free(line));
	}
	avl_dispose(&tree, tree.root);
}
