/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:01:41 by gricquie          #+#    #+#             */
/*   Updated: 2016/11/27 13:01:43 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(s) && s[i] != c)
	{
		i++;
	}
	if (s[i] == '\0' && c != '\0')
		return (NULL);
	return ((char *)(s + i));
}
