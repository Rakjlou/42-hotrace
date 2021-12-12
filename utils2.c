/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 06:43:41 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/12 06:44:23 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <unistd.h>

void	print_not_found(char *key, unsigned int len)
{
	write(STDOUT_FILENO, key, len - 1);
	write(STDOUT_FILENO, ": Not found.\n", 13);
}
