/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:02:26 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 15:05:14 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Extrait un mot de l'entrée input et le classe en fonction de son rôle dans la commande.

1. Parcourt les caractères jusqu'à ce qu'un caractère spécial soit rencontré (SPACE, |, " ", etc.).
2. L'ajoute comme COMMAND si le mot est le premier dans la ligne (is_first_word).
3. L'ajoute comme ARGUMENT s'il n'est pas le premier mot et qu'il commence par un tirer (-).
4. L'ajoute comme STRING s'il n'est pas le premier mot et qu'il ne commence pas par un tirer (-).
5. Met à jour l'index i et prépare l'ajout du token à la liste.
6. (?) Passe les WHITESPACE.
*/

void	token_is_command(char *input, int *i, t_token_list *tokens,
		int *is_first_word)
{
	char	temp[256];
	int		j;

	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\n' && input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		temp[j] = input[*i];
		(*i)++;
		j++;
	}
	temp[j] = '\0';
	if (j > 0)
	{
		if (*is_first_word)
		{
			add_token(tokens, temp, COMMAND);
			*is_first_word = 0;
		}
		else if (temp[0] == '-')
			add_token(tokens, temp, ARGUMENT);
		else
			add_token(tokens, temp, STRING);
		//skip_spaces(input, i);
	}
}

/*
__Fonctionnement :__

Extrait une variable d'environnement à partir de l'entrée input lorsqu'un $ est rencontré.

1. Ignore le $ initial et vérifie si le caractère suivant est ?.
2. Ajoute un token EXIT_STATUS si c'est le cas.
3. Récupère le nom de la variable (composé de caractères alphanumériques ou _ sinon.
4. L'ajoute à la liste des tokens en tant que ENV_VAR.
5. Met à jour l'index i pour continuer l'analyse.
*/

void	assign_env_var(char *input, int *i, t_token_list *tokens)
{
	char	var_name[256];
	int		j;

	j = 0;
	(*i)++;
	if (input[*i] == '?')
	{
		add_token(tokens, "?", EXIT_STATUS);
		(*i)++;
		return ;
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		var_name[j++] = input[*i];
		(*i)++;
	}
	var_name[j] = '\0';
	if (j > 0)
		add_token(tokens, var_name, ENV_VAR);
}
