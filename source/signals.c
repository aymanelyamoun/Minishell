#include "../includes/minishell.h"
int    terminal_settings(void)
{
    struct termios  term;

    if (tcgetattr(0, &term) == -1) //it gets the attributes from the trmios struct
        return (1);
    term.c_lflag &= ~(ECHOCTL); //it blocks the ECHOCTL flag
    tcsetattr(0, TCSANOW, &term); // it sets back the attributes / TCSANOW The change should take place immediately.
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
        gen.exit_status = 1;
        ft_putstr_fd("\n", 2); //print a new line
        rl_replace_line("", 1); //
        rl_on_new_line();
    }
    rl_on_new_line();
    rl_redisplay();
}

int ctrld(void)
{
    rl_on_new_line(); //move to empty line
    rl_redisplay(); //change what is displayed on the screen to reftlect teh cut=rrent content
    ft_putstr_fd("exit\n", 2);
    exit(0);
}