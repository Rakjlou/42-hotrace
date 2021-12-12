/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 07:05:38 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:38:35 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
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

t_state	store_collision_keyval(t_avl *tree,
	char *key, char *val, unsigned int val_len)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (value == NULL)
		return (LOAD_KEY);
	value->val = val;
	value->len = val_len;
	avl_insert(key, value, tree, tree->root);
	return (LOAD_KEY);
}

void	free_hashmap(t_hashmap map[HASHMAP_SIZE])
{
	unsigned int	i;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		if (map[i].collision != NULL)
		{
			avl_dispose(map[i].collision, map[i].collision->root);
			free(map[i].collision);
		}
		if (map[i].kv.key != NULL)
		{
			free(map[i].kv.key);
			free(map[i].kv.val);
		}
		++i;
	}
}

t_state	free_line_set_print_state(char *line)
{
	free(line);
	return (PRINT);
}
