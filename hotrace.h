/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:59:10 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 01:48:07 by nsierra-         ###   ########.fr       */
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


void		avl_dispose(t_avl *tree, t_avl_node *node);
t_avl_node	*avl_find(void *key, t_avl *tree, t_avl_node *node);
t_avl_node	*avl_find_min(t_avl_node *node);
t_avl_node	*avl_find_max(t_avl_node *node);
t_avl_node	*avl_insert(void *key, void *data, t_avl *tree, t_avl_node *node);
//void		avl_display(t_avl_node *node);

#endif
