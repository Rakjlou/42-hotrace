/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:59:10 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 00:39:54 by nsierra-         ###   ########.fr       */
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

#endif
