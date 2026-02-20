/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:18:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/06 16:21:11 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_infile(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error(filename);
	return (fd);
}

int	open_outfile(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(filename);
	return (fd);
}

// bool  is_command(t_tok *tok)
// {
// 	if (!tok->prev && tok->prev->type != T_WORD)
// 		return (true);
// 	return (false);
// }

// bool  is_argument(t_tok *tok)
// {
// 	if (tok->prev->type == T_WORD)
// 		return (true);
// 	return (false);
// }

// bool  is_file(t_tok *tok)
// {
// 	if (tok->prev->type != T_WORD || tok->prev->type != T_FILE)
// 		return (true);
// 	return (false);
// }

// static int init_count(t_exec *exec, t_tok *tok)
// {
// 	while (tok)
// 	{
// 		if (is_command(tok))
// 		{

// 		}
// 		else if()
// 		{

// 		}
// 		else if()
// 		{

// 		}
// 		tok = tok->next;
// 	}
// }

int	init_parsing(t_exec *exec, int argc, char **argv)
{
	// int i;
	exec->argc = argc;
	exec->argv = argv;
	exec->com_args->cmd_count = argc - 3;
	exec->env = convert_env(env);
	// i = 0;
	// while (argv[i])
	// {
	// 	if ((ft_strncmp(argv[i], "<<", ft_strlen(exec->argv[i]))) == 0)
	// 	{
	// 		exec->limiter = ft_strdup(argv[i + 1]);
	// 		exec->heredoc = 1;
	// 		exec->com_args->cmd_count -= 1;
	// 	}
	// 	else if ()
	// 	{
	// 		exec->infile_fd = open_infile(exec->argv[i]);
	// 		if (exec->infile_fd == 0)
	// 			return (0);
	// 	}
	// 	i++;
	// }
	// exec->outfile_fd = open_outfile(argv[argc - 1]);
	// if (exec->outfile_fd == 0)
	// 	return (0);
	return (1);
}

// recuperer le nb de com et le nb d'arg
