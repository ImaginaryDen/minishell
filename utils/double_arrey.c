/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_arrey.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:23:30 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 17:25:16 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_arr(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs + i && strs[i])
	{
		free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
	strs = NULL;
}

int	ft_add_words(char const *s, char **words)
{
	char	*start;
	char	*end;
	size_t	size;

	start = (char *)s;
	while (start && *start)
	{
		while (ft_isspace_s(*start))
			start++;
		end = start;
		while (*end && !ft_isspace_s(*end))
			end++;
		if (*start)
		{
			if (!end)
				size = ft_strlen(start) + 1;
			else
				size = end - start + 1;
			*words = malloc(sizeof(char) * size);
			exit_if_null(*words, "malloc");
			if (!*words)
				return (0);
			ft_strlcpy(*words, start, size);
			words++;
		}
		start = end;
	}
	return (1);
}

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
<<<<<<< Updated upstream
		free(array[i]);
=======
		if (array[i])
			free(array[i]);
>>>>>>> Stashed changes
		i++;
	}
	free(array);
}
