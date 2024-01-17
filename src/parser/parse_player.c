/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:51:01 by nico              #+#    #+#             */
/*   Updated: 2024/01/17 17:13:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_direction(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

static void	store_p_data(t_cub3d *data, int i, int j)
{
	data->p = ft_calloc(1, sizeof(t_player *));
	if (!data->p)
		err_free_exit("parse_player", data, errno);
	data->p->dir = data->map[i][j];
	data->p->x = j;
	data->p->y = i;
}

void	parse_player(t_cub3d *data)
{
	int			i;
	int			j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_valid_direction(data->map[i][j]))
			{
				if (data->p)
					err_free_exit("parse_player", data, E_DUP_PLAYER);
				store_p_data(data, i, j);
			}
			j++;
		}
		i++;
	}
	if (!data->p)
		err_free_exit("parse_player", data, E_NO_PLAYER);
}
