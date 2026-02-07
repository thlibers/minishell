
#include "includes/minishell.h"

bool	is_command(t_tok *tok)
{
	if (!tok->prev && tok->prev->type != T_WORD)
		return (true);
	return (false);
}

bool	is_argument(t_tok *tok)
{
	if (tok->prev->type == T_WORD)
		return (true);
	return (false);
}

bool	is_file(t_tok *tok)
{
	if (tok->prev->type != T_WORD || tok->prev->type != T_FILE)
		return (true);
	return (false);
}
