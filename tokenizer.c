/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/05 14:55:33 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__


Analyse la string passée en commande et la transforme en liste chaînée de tokens (t_token)


1. Ignore les espaces initiaux
2. Parcourt l'entrée caractère par caractère pour identifier et traiter les différents types de tokens :
      - variables : $
      - pipes : |
      - redirections : < ou >
      - contenu : " " ou ' '
3. Détecte les commandes et gère leur position dans la ligne de commande
4. Retourne la liste chaînée contenant les tokens extraits


*/

t_token	*tokenize_input(char *input)
{
	int		i;
	t_token_list *tokens;
	int		is_first_word;
	size_t	len;

	len = ft_strlen(input);
	i = 0;
	is_first_word = 1;
	tokens = malloc(sizeof(t_token_list));
	tokens->head = NULL;
	tokens->cur = NULL;
	skip_spaces(input, &i);
	while (i < (int)len)
	{
		assign_dollar(input[i], tokens);
		assign_pipe(input[i], tokens);
		assign_redirection(input, &i, tokens);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, tokens, input[i]);
		else
		{
			token_is_command(input, &i, tokens, &is_first_word);
			i++;
		}
	}
	return (tokens->head);
}
