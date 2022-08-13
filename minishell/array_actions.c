/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:44:55 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:45:03 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_str_arr(char **str)
{
	int	cnt_env;

	cnt_env = 0;
	while (str[cnt_env])
		cnt_env++;
	return (cnt_env);
}

void	free_arr(char **arr)
{
	char	**begin_arr;

	begin_arr = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(begin_arr);
}

int	add_elem_int(int el_add, int **arr, int *cnt)
{
	int		*new_arr;
	int		i;

	i = 0;
	if (el_add != -1)
	{
		new_arr = malloc(sizeof(int) * ((*cnt) + 1));
		if (!new_arr)
			return (ERROR);
		if (*cnt != 0)
		{
			while (i < *cnt)
			{
				new_arr[i] = (*arr)[i];
				i++;
			}
		}
		new_arr[i] = el_add;
		if ((*arr) != NULL)
			free(*arr);
		*arr = new_arr;
		(*cnt)++;
	}
	return (SUCCESS);
}

int	add_elem_arr(char *el_add, char ***arr)
{
	char	**new_arr;
	int		i;
	int		cnt_el_arr;

	cnt_el_arr = cnt_str_arr(*arr);
	i = 0;
	new_arr = malloc(sizeof(char *) * (cnt_el_arr + 2));
	if (!new_arr)
		return (ERROR);
	while (i < cnt_el_arr)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[cnt_el_arr] = ft_strdup(el_add);
	new_arr[cnt_el_arr + 1] = NULL;
	free(*arr);
	*arr = new_arr;
	return (SUCCESS);
}

int	del_elem_arr(char *el_del, int el_len, char ***arr, int i)
{
	char	**new_arr;
	int		k;
	int		cnt_el_arr;

	if (!get_env(el_del, *arr, 0))
		return (SUCCESS);
	cnt_el_arr = cnt_str_arr(*arr);
	k = 0;
	new_arr = malloc(sizeof(char *) * (cnt_el_arr));
	if (!new_arr)
		return (ERROR);
	while (i < cnt_el_arr)
	{
		if (ft_strcmp(el_del, (*arr)[i]) == 0 || (*((*arr)[i] + el_len) == '='
			&& ft_strncmp(el_del, (*arr)[i], el_len) == 0))
		{
			k++;
			free((*arr)[i]);
		}
		new_arr[i] = (*arr)[i + k];
		i++;
	}
	free(*arr);
	*arr = new_arr;
	return (SUCCESS);
}
