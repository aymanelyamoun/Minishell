# Minishell
 *Tokenezation*
- [X] Read all ressources
- [X] Create prompt handeler 
- [X] handle signals
- [X] handle tokens
- [ ] handle syntax error
- [ ] send tokens to parsing (expander)


 *Parsing*
- [ ] Soon
void    check_newline(token_t *c)
{
    token_t *tmp = NULL;
    size_t index;

    tmp = c;
    index = 0;
    while(tmp)
    {
        while(tmp->next->type == SPACE)
             tmp = tmp->next;
        while(index < ft_strlen(tmp->data))
        {
            if(tmp->next == NULL)
            {
                if (tmp->data[index] == '>')
                {
                    if(tmp->data[index + 1] != '\0')
                        while(tmp->next->type == SPACE && tmp)
                             tmp = tmp->next;
                    printf("parse error near to newline hani\n");
                    break;
                }
                else if (tmp ->data[index] == '>' && (tmp->data[index + 1] == '>'))
                {
                   printf("parse error near to newline\n");
                    break;
                }
                else if (tmp->data[index] == '<' || (tmp->data[index + 1] == '<' && tmp->data[index + 1] != '>'))
                {
                    printf("parse error near to newline rf\n");
                    break ;
                }
            }
                // else if (tmp->data[index] == '|')
                // {
                //     printf("parse error in pipe\n");
                //     break;
                // }
            
            // else if (tmp->next != NULL)
            // {
            //     while(tmp->next->type == SPACE)
            //         tmp = tmp->next;
            //     if (tmp->data[index] ==  '>')
            //     {
            //         if(tmp->data[index + 1] == '<')
            //             printf("syntax error near to newline\n");
            //     }
                //     if(tmp->next->type == LESS || tmp->next->type == GREAT || tmp->next->type == DGREAT || tmp->next->type == DLESS)
                // printf("syntax error near to operator\n");
            
            
            index++;
        }
        index = 0;
        tmp = tmp->next;
    }

    void    check_newline(token_t *c)
{
    token_t *tmp = NULL;
    size_t index;

    tmp = c;
    index = 0;
    while(tmp)
    {
        while(tmp->next->type == SPACE)
             tmp = tmp->next;
        while(index < ft_strlen(tmp->data))
        {
            if(tmp->next == NULL)
            {
                if (tmp->data[index] == '>')
                {
                    if(tmp->data[index + 1] != '\0')
                        while(tmp->next->type == SPACE && tmp)
                             tmp = tmp->next;
                    printf("parse error near to newline hani\n");
                    break;
                }
                else if (tmp ->data[index] == '>' && (tmp->data[index + 1] == '>'))
                {
                   printf("parse error near to newline\n");
                    break;
                }
                else if (tmp->data[index] == '<' || (tmp->data[index + 1] == '<' && tmp->data[index + 1] != '>'))
                {
                    printf("parse error near to newline rf\n");
                    break ;
                }
            }
                // else if (tmp->data[index] == '|')
                // {
                //     printf("parse error in pipe\n");
                //     break;
                // }
            
            // else if (tmp->next != NULL)
            // {
            //     while(tmp->next->type == SPACE)
            //         tmp = tmp->next;
            //     if (tmp->data[index] ==  '>')
            //     {
            //         if(tmp->data[index + 1] == '<')
            //             printf("syntax error near to newline\n");
            //     }
                //     if(tmp->next->type == LESS || tmp->next->type == GREAT || tmp->next->type == DGREAT || tmp->next->type == DLESS)
                // printf("syntax error near to operator\n");
            
            
            index++;
        }
        index = 0;
        tmp = tmp->next;
    }

}