/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:56:48 by nsierra-          #+#    #+#             */
/*   Updated: 2021/12/11 00:08:07 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hotrace.h"
#include <stdio.h> // REMOVE ME
#include <stdlib.h>

/*
TODO: Adapter GNL pour garder la length des valeurs et opti l'appel final à read
*/
int	main(void)
{
	char	*line;
	t_state	state;

	state = LOAD_KEY;
	while (42)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		printf("%s", line);
	}
}
