/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:55 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/13 18:31:27 by tanya            ###   ########.fr       */
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

int	free_if_error(char **line_split, t_cmd_data *comand)
{
	int	i;

	perror("minishell");
	i = 0;
	while (comand[i].cmd_arg != NULL)
	{
		ft_free_array(comand[i].cmd_arg);
		i++;
	}
	free(comand);
	return (0);
}
