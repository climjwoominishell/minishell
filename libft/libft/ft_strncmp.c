/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:50:40 by jwoo              #+#    #+#             */
/*   Updated: 2021/06/18 14:55:55 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	len;
	
	if (n == 0)
		return (0);
	len = 0;
	while (len + 1 < n && s1[len] && s2[len])
	{
		if (s1[len] == s2[len])
			len++;
		else
			break ;
	}
	return (s1[len] - s2[len]);
}
