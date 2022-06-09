#include "../includes/minishell.h"
int    terminal_settings(void)
{
    struct termios  term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return (1);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    signal(SIGQUIT, handler);
    signal(SIGINT, handler);
    return (0); 

}
int handle_signals(void)
{
    terminal_settings();
    return (0);
}

void    handler(int sig)
{
    if(sig == SIGINT)
    {
        ft_putstr_fd("\n", 2);
        rl_replace_line("", 1);
        rl_on_new_line();
    }
    rl_on_new_line();
    rl_redisplay();
}
<<<<<<< HEAD

void    free_env(t_list **env)
{
    t_list *tmp;
    t_list *next;

    tmp  = *env;
    while(tmp)
    {
        free(tmp->content);
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    env = NULL;
}

int ctrld(void)
{
    //free_env(env);
    rl_on_new_line();
    rl_redisplay();
    ft_putstr_fd("exit\n", 2);
    exit(1);
}
=======
// int ctrld(void)
// {
//     rl_on_new_line();
//     rl_redisplay();
//     //ft_putstr_fd("quit\n", 2);
//     return (1);
// }
>>>>>>> 6f8da807c76e5850dafb8566bdb77e20ae64b92f
