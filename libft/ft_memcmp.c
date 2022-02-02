/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 20:09:39 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 16:32:16 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *buf1, const void *buf2, int count)
{
	const unsigned char	*c_bif1 = (const unsigned char *)buf1;
	const unsigned char	*c_bif2 = (const unsigned char *)buf2;
	int					i;

	i = 0;
	if (!count)
		return (0);
	while (i < count && !(c_bif1[i] - c_bif2[i]))
		i++;
	if (i == count)
		i--;
	return (c_bif1[i] - c_bif2[i]);
}
