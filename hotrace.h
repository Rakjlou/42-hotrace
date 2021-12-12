/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:59:10 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 05:54:00 by nsierra-         ###   ########.fr       */
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

typedef struct s_value
{
	char			*val;
	unsigned int	len;
}	t_value;

typedef struct s_avl_node
{
	void				*key;
	void				*data;
	struct s_avl_node	*left;
	struct s_avl_node	*right;
	int					height;
}	t_avl_node;

typedef struct s_avl
{
	t_avl_node	*root;
	int			(*cmp)(void *, void *);
	void		(*free_key)(void *);
	void		(*free_data)(void *);
}	t_avl;

int			ft_strcmp_void(void *v1, void *v2);
t_state		free_line_set_print_state(char *line);

void		avl_dispose(t_avl *tree, t_avl_node *node);
t_avl_node	*avl_find(void *key, t_avl *tree, t_avl_node *node);
t_avl_node	*avl_find_min(t_avl_node *node);
t_avl_node	*avl_find_max(t_avl_node *node);
t_avl_node	*avl_insert(void *key, void *data, t_avl *tree, t_avl_node *node);
t_avl_node	*avl_new_node(void *key, void *data);
t_avl_node	*double_rotate_with_left(t_avl_node *k3);
t_avl_node	*double_rotate_with_right(t_avl_node *k1);
t_avl_node	*single_rotate_with_left(t_avl_node *k2);
t_avl_node	*single_rotate_with_right(t_avl_node *k1);
int			avl_height(t_avl_node *node);
int			max(int l, int r);

#endif
