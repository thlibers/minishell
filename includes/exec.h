/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:30:30 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/06 16:32:17 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define HEREDOC_F "/tmp/pipex_heredoc.tmp"

typedef struct s_command
{
	char		*command;
	char		**arguments;
	int			arg_count;
	int			cmd_count;
}				t_command;

typedef struct s_exec
{
	pid_t		*pid;
	t_command	*com_args;
	// char		***cmd_args;	// delete
	char		**argv;			// delete
	int			argc;			// delete
	char		**env;
	char		*limiter;
	int 		(*pipe_fd)[2];
	int			infile_fd;
	int			outfile_fd;
	int			index;
	int			heredoc; // ?
}				t_exec;

#endif