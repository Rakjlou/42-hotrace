/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:44:49 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

static void	free_avl_data(void *data)
{
	t_value	*value;

	value = (t_value *)data;
	free(value->val);
	free(data);
}

static inline unsigned int	haschich(char *key)
{
	unsigned int	hache;
	int				c;

	hache = 5381;
	while (42)
	{
		c = *key++;
		if (c == '\0')
			break ;
		hache = ((hache << 5) + hache) ^ c;
	}
	return (hache % HASHMAP_SIZE);
}

static t_state	store_keyval(t_hashmap map[HASHMAP_SIZE],
	char *key, char *val, unsigned int val_len)
{
	unsigned int		hash;
	t_keyval			*kv;

	hash = haschich(key);
	kv = &map[hash].kv;
	if (kv->key != NULL)
	{
		if (map[hash].collision == NULL)
			map[hash].collision = new_avl(ft_strcmp_void, free, free_avl_data);
		if (map[hash].collision == NULL)
			return (LOAD_KEY);
		return (store_collision_keyval(map[hash].collision, key, val, val_len));
	}
	else
	{
		kv->key = key;
		kv->val = val;
		kv->val_len = val_len;
	}
	return (LOAD_KEY);
}

static void	print_val(t_hashmap map[HASHMAP_SIZE], char *key, unsigned int len)
{
	unsigned int	hash;
	t_keyval		*kv;
	t_avl_node		*node;
	t_value			*value;

	hash = haschich(key);
	kv = &map[hash].kv;
	if (kv->key && ft_strcmp(key, kv->key) == 0)
		write(STDOUT_FILENO, kv->val, kv->val_len);
	else if (map[hash].collision)
	{
		node = avl_find(key, map[hash].collision, map[hash].collision->root);
		if (node)
		{
			value = (t_value *)node->data;
			write(STDOUT_FILENO, value->val, value->len);
		}
		else
			print_not_found(key, len);
	}
	else
		print_not_found(key, len);
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
			(print_val(map, line, line_len), free(line));
	}
	free_hashmap(map);
}
