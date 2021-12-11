/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:59:10 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 07:10:11 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define HASHMAP_SIZE 399989

typedef enum e_state
{
	END,
	LOAD_KEY,
	LOAD_VALUE,
	PRINT
}	t_state;

typedef struct s_keyval
{
	char			*key;
	char			*val;
	unsigned int	val_len;
}	t_keyval;

typedef struct s_collision
{
	t_keyval			kv;
	struct s_collision	*next;
}	t_collision;

typedef struct s_hashmap
{
	t_keyval		kv;
	t_collision		*collision;
}	t_hashmap;

t_state	store_keyval(t_hashmap map[HASHMAP_SIZE],
			char *key, char *val, unsigned int val_len);
void	print_val(t_hashmap map[HASHMAP_SIZE], char *key);

#endif
