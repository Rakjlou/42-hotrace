/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 05:30:30 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

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

static void	store_collision_keyval(t_hashmap (*map)[HASHMAP_SIZE],
	char *key, char *val, unsigned int val_len)
{
	unsigned int	hash;
	t_collision		*new_collision;
	t_collision		**collision_list;

	hash = haschich(key);
	new_collision = malloc(sizeof(t_collision));
	if (new_collision == NULL)
		return ;
	new_collision->kv.key = key;
	new_collision->kv.val = val;
	new_collision->kv.val_len = val_len;
	collision_list = &(*map)[hash].collision;
	if (collision_list == NULL)
		*collision_list = new_collision;
	else
	{
		new_collision->next = *collision_list;
		*collision_list = new_collision;
	}
}

static t_state	store_keyval(t_hashmap (*map)[HASHMAP_SIZE],
	char *key, char *val, unsigned int val_len)
{
	unsigned int		hash;
	t_keyval			*kv;

	hash = haschich(key);
	kv = &(*map)[hash].kv;
	if (kv->key != NULL)
		store_collision_keyval(map, key, val, val_len);
	else
	{
		kv->key = key;
		kv->val = val;
		kv->val_len = val_len;
	}
	return (LOAD_KEY);
}

static void	print_val(t_hashmap (*map)[HASHMAP_SIZE], char *key)
{
	unsigned int	hash;
	t_keyval		*kv;
	t_collision		*coll;

	hash = haschich(key);
	kv = &(*map)[hash].kv;
	if (ft_strcmp(key, kv->key) == 0)
		write(STDOUT_FILENO, kv->val, kv->val_len);
	else
	{
		coll = (*map)[hash].collision;
		while (coll)
		{
			if (ft_strcmp(key, coll->kv.key) == 0)
			{
				write(STDOUT_FILENO, coll->kv.val, coll->kv.val_len);
				return ;
			}
			coll = coll->next;
		}
	}
}

int	main(void)
{
	char				*key;
	unsigned int		line_len;
	register char		*line;
	register t_state	state;
	static t_hashmap	map[HASHMAP_SIZE] = {0};

	state = LOAD_KEY;
	while (42)
	{
		line = get_next_line(STDIN_FILENO, &line_len);
		if (line == NULL)
			break ;
		if (line_len == 1 && line[0] == '\n')
			state = PRINT;
		else if (state == LOAD_KEY)
		{
			key = line;
			state = LOAD_VALUE;
		}
		else if (state == LOAD_VALUE)
			state = store_keyval(&map, key, line, line_len);
		else if (state == PRINT)
			print_val(&map, line);
	}
}
