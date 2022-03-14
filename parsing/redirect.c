/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:31:58 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/14 23:31:02 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isredirect(char ch1, char ch2)
{
	if (ch1 == '>' && ch2 == '>')
		return (3);
	else if (ch1 == '>')
		return (1);
	else if (ch1 == '<' && ch2 == '<')
		return (4);
	else if (ch1 == '<')
		return (2);
	return (0);
}

int	redirect(t_cmd_data *cmds, char *redirect, char *filename)
{
	int	type;
	int	fd;

	type = ft_isredirect(redirect[0], redirect[1]);
	if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == 2)
		fd = open(filename, O_RDONLY, 0644);
	if (type == 4)
		fd = here_doc(filename);
	if (fd == -1)
		return (1);
	if (type == 1 || type == 3)
		cmds->fd_in_out[1] = fd;
	else
		cmds->fd_in_out[0] = fd;
	return (0);
}
