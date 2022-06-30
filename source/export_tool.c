#include "../includes/minishell.h"

void	bubbleSort(t_list **head, int count)
{
	t_var	var;

	var.index1 = 0;
	while (var.index1 <= count)
	{
		var.h = head;
		var.swapped = 0;
		var.index2 = 0;
		while (var.index2 < count - var.index1 - 1)
		{
			var.p1 = *var.h;
			var.p2 = var.p1->next;
			if (((char *)var.p1->content)[0] > ((char *)var.p2->content)[0])
			{
				*var.h = swap(var.p1, var.p2);
				var.swapped = 1;
			}
			var.h = &(*var.h)->next;
			var.index2++;
		}
		if (var.swapped == 0)
			break ;
		var.index1++;
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
