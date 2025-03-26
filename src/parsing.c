#include "minishell.h"

void    get_env(t_list **env_list, char **env)
{
    char    *tmp_content;
    int     i;

    i = 0;
    tmp_content = NULL;
    while (env[i])
    {
        tmp_content = ft_strdup(env[i]);
        if (!tmp_content)
            return ;
        ft_lstadd_back(env_list, ft_lstnew(tmp_content));
        i++;
    }
}
/*
void    parsing(t_data *data)
{

}
*/
