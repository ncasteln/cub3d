/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/16 00:58:57 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// this function clears the image - makes it black
void clearScreen(t_cub3d *data)
{
	int x;
	int y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			mlx_put_pixel(data->img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void vert_line(t_cub3d *data, int x, int draw_start, int draw_end)
{
	int y;

	y = 0;
	while (y >=0 && y < WIN_H)
	{
		if (y >= draw_start && y <= draw_end)
			mlx_put_pixel(data->img, x, y, data->rc->w_color);
		else if (y < draw_start)
			mlx_put_pixel(data->img, x, y, data->assets->c);
		else if (y > draw_end)
			mlx_put_pixel(data->img, x, y, data->assets->f);
		y++;
	}
}

uint32_t getpixcol(uint8_t *p)
{
	uint32_t b;
	uint32_t g;
	uint32_t r;
	uint32_t a;

	r = (uint32_t) *p;
	g = (uint32_t) *(p + 1);
	b = (uint32_t) *(p + 2);
	a = (uint32_t) *(p + 3);
	
	// printf("init%i \n", r);
	// printf("%i \n", g);
	// printf("%i \n", b);
	// printf("%i \n", a);

	//printf("col%x \n", getcol(r, g, b, a));
	return (getcol(r, g, b, a));
}

uint32_t getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	// r = r >> 24;
	// g = g << 8 >> 24;
	// b = b << 16 >> 24;

	// printf("after%i \n", r);
	// printf("%i \n", g);
	// printf("%i \n", b);
	// printf("%i \n", a);

	return ((r << 24) + (g << 16) + (b << 8) + a);
}

uint32_t dim(uint32_t color, uint32_t shift)
{
	uint32_t b;
	uint32_t g;
	uint32_t r;

	b = (color << 16 >> 24);
	g = (color << 8 >> 24);
	r = (color >> 24);
	if (b >= shift)
		b = b - shift;
	if (g >= shift)
		g = g - shift;
	if (r >= shift)
		r = r - shift;
	return ((r << 24) + (g << 16) + (b << 8) + 0xFF);
}

int sign(double x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	else
		return (0);
}

t_dvect *set_vectt(t_dvect *v, double x, double y)
{
	v->x = x;
	v->y = y;
	return (v);
}

//loads 4 texures from files
//change to add mlx files
void load_textures(t_cub3d *data)
{
	data->rc->tex[0] = mlx_load_png(data->assets->no);
	data->rc->tex[1] = mlx_load_png(data->assets->we);
	data->rc->tex[2] = mlx_load_png(data->assets->so);
	data->rc->tex[3] = mlx_load_png(data->assets->ea);
}

