/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:59:41 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 13:40:07 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*new_content;

	if (!lst)
		return (NULL);
	new_content = f(lst->content);
	new = ft_lstnew(new_content);
	lst = lst->next;
	while (lst)
	{
		new_content = f(lst->content);
		ft_lstadd_back(&new, ft_lstnew(new_content));
		if (!new->content)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new);
}
