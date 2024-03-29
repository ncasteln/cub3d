/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:49:42 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/23 07:58:05 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cub3d *data)
{
	data->assets = ft_calloc(1, sizeof(t_assets));
	if (!data->assets)
		err_free_exit("init_cub3d", data, 0, errno);
	data->assets->no = NULL;
	data->assets->ea = NULL;
	data->assets->so = NULL;
	data->assets->we = NULL;
	data->assets->d = NULL;
	data->assets->h = NULL;
	data->assets->f = 0;
	data->assets->c = 0;
	data->map = NULL;
	data->minimap = NULL;
	data->p = NULL;
	data->n_rows = 0;
	data->n_col = 0;
	data->line = NULL;
	data->fd = -1;
	data->sprite = NULL;
	data->n_d = 0;
	data->n_h = 0;
	data->minimap_pixel = 10;
}

/*
setting precise player coordinates
setting direction vector: in the beginning one of its components is 0
and the other one equals 1 or -1.
setting plane vector: at first we set it the same direction as the direction
vector but different magnitude and then rotate it right by 90 degrees
 */
void	init_move(t_player *p)
{
	p->pos.x = p->x;
	p->pos.y = p->y;
	if (p->dir == 'N' || p->dir == 'S')
		p->dirv.x = 0;
	else if (p->dir == 'W' || p->dir == 'E')
		p->dirv.y = 0;
	if (p->dir == 'N')
		p->dirv.y = -1;
	else if (p->dir == 'S')
		p->dirv.y = 1;
	else if (p->dir == 'W')
		p->dirv.x = -1;
	else if (p->dir == 'E')
		p->dirv.x = 1;
	p->plane.x = 0.66 * p->dirv.x;
	p->plane.y = 0.66 * p->dirv.y;
	rotate_vector(&p->plane, M_PI / 2);
}
