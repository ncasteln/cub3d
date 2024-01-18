/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:51:33 by nico              #+#    #+#             */
/*   Updated: 2024/01/18 12:39:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ') // || c == '\n'
		return (1);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	if (BONUS && c == 'D')
		return (1);
	return (0);
}

int	is_blank_string(char *s) // check if needed
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	// ft_printf("s[i] = {%c}\n", s[i]);
	if (s[i] == '\n')
		return (1);
	return (0);
}

int	is_valid_map_line(char *s)
{
	size_t	i;

	i = 0;
	if (is_blank_string(s))
	{
		// ft_printf("!!! BLANK !!!\n");
		return (1);
	}
	while (s[i]) // bonus only
	{
 		if (!is_valid_map_char(s[i]))
		{
			// ft_printf("!!! INVALID FOUND !!!\n");
			// ft_printf("{%c}\n", s[i]);
			return (0);
		}
		i++;
	}
	// while (s[i] && is_valid_map_char(s[i])) // mandatory
	// 	i++;
	// if (i == ft_strlen(s) - 1) // because of the new line ???? wtf means ???
	// 	return (1);
	return (1);
}

/*
	str to uint32_t needed for mlx library. The function assumes that the
	conversion is doing in base 16.
*/
uint32_t	str_to_ul(char *s)
{
	uint32_t	hex;
	int			i;
	int			current_digit;

	hex = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			current_digit = s[i] - '0';
		else
			current_digit = s[i] - 'A' + 10;
		hex = hex * 16 + current_digit;
		i++;
	}
	return (hex);
}
