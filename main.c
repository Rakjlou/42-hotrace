/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 00:40:44 by nsierra-         ###   ########.fr       */
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

static inline t_state	free_line_set_print_state(char *line)
{
	free(line);
	return (PRINT);
}

static t_state	store_keyval(t_tree *tree,
	char *key, char *val, unsigned int val_len)
{
}

static void	print_val(t_tree *tree, char *key)
{
}

int	main(void)
{
	t_state				state;
	t_tree				*tree;
	char				*key;
	char				*line;
	unsigned int		line_len;

	state = LOAD_KEY;
	tree = NULL;
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
			state = store_keyval(map, key, line, line_len);
		else if (state == PRINT)
			(print_val(map, line), free(line));
	}
}
