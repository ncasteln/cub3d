/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:22:29 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:22:29 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	int	shift;

	shift = 'a' - 'A';
	if ((c >= 'a') && (c <= 'z'))
	{
		c = c - shift;
	}
	return (c);
}