/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 07:05:38 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 07:08:07 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stdlib.h>
#include <unistd.h>

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

static inline void	store_collision_keyval(t_collision **collision_list,
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

t_state	store_keyval(t_hashmap map[HASHMAP_SIZE],
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

void	print_val(t_hashmap map[HASHMAP_SIZE], char *key)
{
	unsigned int	hash;
	t_keyval		*kv;
	t_collision		*coll;

	hash = haschich(key);
	kv = &map[hash].kv;
	if (ft_strcmp(key, kv->key) == 0)
		write(STDOUT_FILENO, kv->val, kv->val_len);
	else
	{
		coll = map[hash].collision;
		while (coll && ft_strcmp(key, coll->kv.key) != 0)
			coll = coll->next;
		if (coll)
			write(STDOUT_FILENO, coll->kv.val, coll->kv.val_len);
	}
}
