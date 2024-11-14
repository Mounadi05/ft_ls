#include "includes/ft_ls.h"

t_file *ft_reverse(t_file *head)
{
    t_file *prev = NULL;
    t_file *current = head;
    t_file *next = NULL;
    
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;  // Return new head of reversed list
}

int	get_terminal_width(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col == 0)
		return (80);
	else
		return (w.ws_col);
}