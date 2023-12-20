/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:22:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/20 08:53:50 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_err_msg(int err_n)
{
	if (err_n == CE_ARGC)
		return ("invalid argc\n");
	return ("unknow error\n");
}

void	error(char *s, int err_n)
{
	char	*err_msg;

	err_msg = get_err_msg(err_n);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(err_msg, 2);
	exit(err_n);
}
