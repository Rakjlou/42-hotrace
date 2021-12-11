/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 07:07:24 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

static inline void	free_hashmap(t_hashmap map[HASHMAP_SIZE])
{
	unsigned int	i;
	t_collision		*prev;
	t_collision		*collision;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		if (map[i].collision != NULL)
		{
			collision = map[i].collision;
			while (collision)
			{
				prev = collision;
				collision = collision->next;
				(free(prev->kv.key), free(prev->kv.val), free(prev));
			}
		}
		if (map[i].kv.key != NULL)
			(free(map[i].kv.key), free(map[i].kv.val));
		++i;
	}
}

static inline t_state	free_line_set_print_state(char *line)
{
	free(line);
	return (PRINT);
}

int	main(void)
{
	char				*key;
	char				*line;
	unsigned int		line_len;
	t_state				state;
	static t_hashmap	map[HASHMAP_SIZE] = {0};

	state = LOAD_KEY;
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
	free_hashmap(map);
}
