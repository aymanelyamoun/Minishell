#include "../includes/minishell.h"

void	bubbleSort(t_list **head, int count)
{
	t_list	**h; 
	t_list	*p1;
	t_list	*p2;
	int		index1;
	int		index2;
	int		swapped;

	index1 = 0;
	while(index1 <= count)
	{
		h = head;
		swapped = 0;
		index2 = 0;
		while(index2 < count - index1 - 1)
		{
			p1 = *h;
			p2 = p1->next;
			if (((char *)p1->content)[0] > ((char *)p2->content)[0])
			{
				*h = swap(p1, p2);
				swapped = 1;
			}
			h = &(*h)->next;
			index2++;
		}
		if (swapped == 0)
			break;
		index1++;
	}
}

t_list	*swap(t_list *ptr1, t_list *ptr2)
{
	t_list	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

int	len_list(t_list **list)
{
	t_list	*tmp;
	int		index;

	index = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		index++;
	}
	return (index);
}

void	ft_sort(t_gen *gen)
{
	bubbleSort(&(gen)->env, len_list(&(gen)->env));
	print_export((gen)->env);
}

