/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:59:10 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:45:10 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define HASHMAP_SIZE 999983

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

typedef struct s_hashmap
{
	t_keyval		kv;
	t_avl			*collision;
}	t_hashmap;

t_state	free_line_set_print_state(char *line);
void	free_hashmap(t_hashmap map[HASHMAP_SIZE]);
t_state	store_collision_keyval(t_avl *tree,
	char *key, char *val, unsigned int val_len);

t_avl		*new_avl(int (*cmp)(void *, void *), void (*free_key)(void *),
		void (*free_data)(void *));
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

void		print_not_found(char *key, unsigned int len);
int			ft_strcmp_void(void *v1, void *v2);
int			ft_strcmp(const char *s1, const char *s2);


#endif
