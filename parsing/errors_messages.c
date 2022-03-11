/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:55 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/11 18:48:36 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**error_message(char ***line_split, int i)
{
	printf("minishell: syntax error near unexpected token \'%s\'\n",
		(*line_split)[i]);
	ft_free_array(*line_split);
	return (NULL);
}

char	**error_quotes(char ***line_split)
{
	printf("minishell: syntax error - unclosed quote\n");
	ft_free_array(*line_split);
	return (NULL);
}
