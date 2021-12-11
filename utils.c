/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 07:05:38 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 07:18:37 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stdlib.h>
#include <unistd.h>

void	store_collision_keyval(t_collision **collision_list,
	t_collision *new_collision)
{
	if (collision_list == NULL)
		*collision_list = new_collision;
	else
	{
		new_collision->next = *collision_list;
		*collision_list = new_collision;
	}
}

void	free_hashmap(t_hashmap map[HASHMAP_SIZE])
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

t_state	free_line_set_print_state(char *line)
{
	free(line);
	return (PRINT);
}
