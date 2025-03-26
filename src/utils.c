#include "minishell.h"

void    print_env(t_list *env_list)
{
    while (env_list)
    {
        printf("%s\n", (char *)env_list->content);
        env_list = env_list->next;
    }
}