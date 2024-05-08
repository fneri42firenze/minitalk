/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fneri <fneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:17:46 by fneri             #+#    #+#             */
/*   Updated: 2024/04/08 17:32:00 by fneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *value)
{
	t_list	*new;

	new = NULL;
	new = malloc(sizeof(t_list));
	if (new)
	{
		new->value = value;
		new->next = NULL;
	}
	return (new);
}
/*int main()
{
	t_list *new;
	char *str = "Hello";
	new = ft_lstnew(str);
	printf("%s\n",(char *) new->value);
	return (0);
}*/
