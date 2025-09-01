/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:37:59 by mstawski          #+#    #+#             */
/*   Updated: 2025/07/24 16:53:36 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	elements;

	elements = 0;
	while (*s)
	{
		if (*s != c)
		{
			elements++;
			while (*(s + 1) && *s != c)
				s++;
		}
		s++;
	}
	return (elements);
}

static int	search_end_index(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int	array_creation(char **words, char const *s, char c, int words_num)
{
	int	start_index;
	int	end_index;
	int	i;

	start_index = 0;
	i = 0;
	while (i < words_num)
	{
		while (s[start_index] == c)
			start_index++;
		end_index = search_end_index(s + start_index, c);
		words[i] = ft_substr(s, start_index, end_index);
		if (!words[i])
		{
			while (i-- > 0)
				free(words[i]);
			free(words);
			return (0);
		}
		start_index += end_index;
		i++;
	}
	words[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		words_num;

	if (!s)
		return (NULL);
	words_num = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (words_num + 1));
	if (!words)
		return (NULL);
	if (array_creation(words, s, c, words_num) == 0)
		return (NULL);
	return (words);
}

/*int	main(void)
{
	char	**array;
	char const *s;
	char c;

	s = "LUBU, DUBU, KOCHAC, FUBU";
	c = ' ';
	array = ft_split(s ,c);
	printf("%s\n", array[3]);
}*/
