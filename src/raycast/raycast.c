/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 00:48:22 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**********************
Coordinates explanation
**********************
We have several spaces and each space has several coordinate systems
	1. Map space - this is a space where our player walks
it has two coordinate systems:
	1.1 Integer coordinates
first system is integer and based on squares
for example we have a map 10x10 squares
A square can be occupied or not occupied by the wall
It's easy to say where is the wall on the map using integer coordinates
for example we can put a column at (6, 7)
	1.2 Float point coordinates
A player doesn't occupy the whole square and he can move inside it
so it makes sense using float point coordinates to show his precise position
if a player has integer coordinates (1,1) and he moves inside the square (1,1)
his float coordinates can be (1.24, 1.76) for example
	2. Screen space - this is what out player sees and therefore
	what our game screen shows. It also has two types of coordinates:
	2.1 Integer (pixel) coordinates
first system is integer pixel system
if for example our game window is 640x480 pixels
a pixel is going to have integer coordinates like (120,65)
	2.2 Float point coordinates
float point coordinates are used to make vector manipulations easier
we use it only for x-dimension here
the left side of the window has x = -1, middle x = 0 right side - x = 1
I call them normalized coordinates because it's similar
to normalization process in math.
 */

/*
	calculates the distances to the first x/y interesction - that is
	the length of the ray from its start (player position)
	till the first intersection with x/y integer coordinate net
	rc->ray_len.x  - distance to to the first x intersection
	rc->ray_len.y  - distance to to the first y intersection
	(they are stored as one vector but it's not an actual vector in space)

	|         |/
	|        /| - intersection with x
	|       / |
	|      /  |
	|     /   |
	|----/----|----- intersection with y
	|   /     |
	|  /      |
	ray start
	calculation based on triangle proportion
 */
static void	first_intersec(t_raycast *rc, t_player *p)
{
	if (rc->raydir.x < 0)
		rc->ray_len.x = (p->pos.x - rc->ray.x) * rc->ray_delta.x;
	else
		rc->ray_len.x = (rc->ray.x + 1.0 - p->pos.x) * rc->ray_delta.x;
	if (rc->raydir.y < 0)
		rc->ray_len.y = (p->pos.y - rc->ray.y) * rc->ray_delta.y;
	else
		rc->ray_len.y = (rc->ray.y + 1.0 - p->pos.y) * rc->ray_delta.y;
}

/*
	Calculates the following ray parameters:
	|     | / (ray)
	|     |/
	|     /
	|----/|----- y
	|   / |
	|  /  |
	|-/---|----- y+1
	|/    |
	x     x+1

	@param cam_x - Camera space FP(float point) coordinate (cam_x). The screen
	drawing will be between -1 (left) to +1 (right).
	@param raydir - Initial ray direction vector (raydir_x, raydir_y)
	@param ray_delta - Ray length between two adjacent integer x/y. fabs() get
	the absolute value of a number.
	@param p->x and ->y - Map space integer coordinates
 */
static void	ray_init(int pixel_x, t_raycast *rc, t_player *p)
{
	double	cam_x;

	cam_x = 2 * pixel_x / ((double) WIN_W) - 1;
	rc->raydir.x = p->dirv.x + p->plane.x * cam_x;
	rc->raydir.y = p->dirv.y + p->plane.y * cam_x;
	rc->ray_delta.x = fabs(1 / rc->raydir.x);
	rc->ray_delta.y = fabs(1 / rc->raydir.y);
	p->x = (int) p->pos.x;
	p->y = (int) p->pos.y;
	rc->ray.x = p->x;
	rc->ray.y = p->y;
	first_intersec(rc, p);
}

/*
	Propagates the ray until it hits a wall and returns. The position in which
	the wall is hit, is calculated in the next step in get_hit_pos() using the
	rc->wall_dir set in this function.
*/
static void	find_hit(t_raycast *rc, t_cub3d *data)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->ray_len.x < rc->ray_len.y)
		{
			rc->ray_len.x += rc->ray_delta.x;
			rc->ray.x += sign(rc->raydir.x);
			rc->wall_dir = WEST_EAST;
		}
		else
		{
			rc->ray_len.y += rc->ray_delta.y;
			rc->ray.y += sign(rc->raydir.y);
			rc->wall_dir = NORTH_SOUTH;
		}
		if (read_map(data, rc->ray.y, rc->ray.x) == '1')
			rc->hit = 1;
	}
}

/*
	calculates where the wall was hit
	distance to the wall and
	the wall horizontal coordinate (wall_x)
	which is x (on the map) for North/South facing walls and
	y for West/East facing walls
	then we make wall_x relative to the start
	of the correspondent wall square/tile

	floor() rounds a number down to the nearest integer.
*/
static void	get_hit_pos(t_cub3d *data, t_raycast *rc)
{
	if (rc->wall_dir == WEST_EAST)
	{
		rc->wall_dist = rc->ray_len.x - rc->ray_delta.x;
		rc->wall_x = data->p->pos.y + rc->wall_dist * rc->raydir.y;
	}
	else
	{
		rc->wall_dist = rc->ray_len.y - rc->ray_delta.y;
		rc->wall_x = data->p->pos.x + rc->wall_dist * rc->raydir.x;
	}
	rc->wall_x -= floor(rc->wall_x);
}

/*


	For each x of the game screen (horizontal pixel) we take a ray that should
	be projected onto the screen. For that point we find where the ray hits the
	wall and calculate the distance to this wall and its height on the screen
	this allows us to draw the wall.

	About textures: after selecting a texure we calculate the coordinates in
	the texture corresponding to the wall coordinate (as if we stretch or
	shrink the texture to fit the wall tile) for the walls facing east and
	north we mirror the texture.
 */
void	raycasting(t_cub3d *data)
{
	int				pixel_x;
	mlx_texture_t	*tex;
	int				tex_ind;
	t_raycast		rc;

	pixel_x = 0;
	while (pixel_x < WIN_W)
	{
		ray_init(pixel_x, &rc, data->p);
		find_hit(&rc, data);
		get_hit_pos(data, &rc);
		data->dist_arr[pixel_x] = rc.wall_dist;
		data->dir_arr[pixel_x] = rc.wall_dir;
		tex_ind = select_texture(&rc);
		tex = data->tex[tex_ind];
		rc.tex_x = (int)(rc.wall_x * (double)tex->width);
		if ((rc.wall_dir == WEST_EAST && rc.raydir.x < 0)
			|| (rc.wall_dir == NORTH_SOUTH && rc.raydir.y > 0))
			rc.tex_x = tex->width - rc.tex_x - 1;
		set_draw_wall(&rc);
		putline(data, pixel_x, tex, &rc);
		pixel_x++;
	}
}
