/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_free_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:22:56 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/15 11:14:53 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_err_msg(int err_n)
{
	if (err_n == E_ARGC)
		return ("invalid argc");
	if (err_n == E_INV_EXT)
		return ("invalid file extension");
	if (err_n == E_PARSE_ASSETS)
		return ("invalid assets");
	if (err_n == E_DUP_ASSET)
		return ("duplicate asset");
	if (err_n == E_INV_ASSET)
		return ("invalid asset");
	if (err_n == E_MISS_ASSET)
		return ("missing asset");
	if (err_n == E_INV_CHAR)
		return ("invalid character");
	if (err_n == E_INV_FORMAT)
		return ("invalid format");
	if (err_n == E_NO_MAP)
		return ("no map provided");
	if (err_n == E_EMPTY_FILE)
		return ("empty file");
	if (err_n == E_DUP_PLAYER)
		return ("duplicate player");
	if (err_n == E_NO_PLAYER)
		return ("no player set");
	if (err_n == E_MAP_OPEN)
		return ("map is not enclosed");
	if (err_n == E_INV_DOOR)
		return ("door not between walls");
	if (err_n == E_MLX)
		return ("fail from MLX library");
	return ("unknow error");
}

static void	error(char *func_name, int err_n)
{
	char	*err_msg;

	if (err_n <= 106)
		err_msg = strerror(err_n);
	else
		err_msg = get_err_msg(err_n);
	ft_putendl_fd("Error", 2);
	if (func_name)
	{
		ft_putstr_fd(func_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg, 2);
}

void	err_free_exit(char *s, t_cub3d *data, int err_n)
{
	if (err_n)
		error(s, err_n);
	free_data(data);
	system("leaks cub3D");	// remove
	exit (err_n);
}
