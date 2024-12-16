#include "minishell.h"


static t_grbdg **get_grbdg(void)
{
    static t_grbdg *grbdg = NULL; // Static variable within a function
    return &grbdg;               // Return its address
}

void add(void *ptr)
{
    t_grbdg **grbdg = get_grbdg();
    t_grbdg *current = *grbdg;

    while (current) 
    {
        if (current->ptr == ptr) 
            return;
        current = current->next;
    }

    t_grbdg *new_node = malloc(sizeof(t_grbdg));
    if (!new_node) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = *grbdg;
    *grbdg = new_node;
}

void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    add(ptr);
    return ptr;
}

void free_all(void)
{
    t_grbdg **grbdg = get_grbdg();
    t_grbdg *curr = *grbdg;
    t_grbdg *next;

    while (curr)
    {
        next = curr->next;

        if (curr->ptr)
            free(curr->ptr);
        free(curr);
        curr = next;
    }
    *grbdg = NULL;
}
