/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 01:20:17 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

static unsigned int	haschich(char *key)
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

static t_state	store_keyval(t_hashmap (*map)[HASHMAP_SIZE],
	char *key, char *val, unsigned int val_len)
{
	unsigned int		hash;
	t_keyval			*kv;

	hash = haschich(key);
	kv = &(*map)[hash].kv;
	if (kv->key != NULL)
		puts("COLLISION");
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

	hash = haschich(key);
	kv = &(*map)[hash].kv;
	// strcmp pour verif key
	write(STDOUT_FILENO, kv->val, kv->val_len);
}

/*
TODO: Adapter GNL pour garder la length des valeurs et opti l'appel final à read
*/
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
