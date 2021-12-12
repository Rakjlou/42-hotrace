/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 04:48:39 by nsierra-         ###   ########.fr       */
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
	t_collision			*new_collision;

	hash = haschich(key);
	kv = &map[hash].kv;
	if (kv->key != NULL)
	{
		new_collision = malloc(sizeof(t_collision));
		if (new_collision == NULL)
			return (LOAD_KEY);
		new_collision->kv.key = key;
		new_collision->kv.val = val;
		new_collision->kv.val_len = val_len;
		store_collision_keyval(&map[hash].collision, new_collision);
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
	t_collision		*coll;

	hash = haschich(key);
	kv = &map[hash].kv;
	if (kv->key && ft_strcmp(key, kv->key) == 0)
		write(STDOUT_FILENO, kv->val, kv->val_len);
	else
	{
		coll = map[hash].collision;
		while (coll && ft_strcmp(key, coll->kv.key) != 0)
			coll = coll->next;
		if (coll)
			write(STDOUT_FILENO, coll->kv.val, coll->kv.val_len);
		else
		{
			write(STDOUT_FILENO, key, len - 1);
			write(STDOUT_FILENO, ": Not found.\n", 13);
		}
	}
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
