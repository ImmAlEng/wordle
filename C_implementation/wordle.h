
#ifndef WORDLE_H
#define WORDLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "get_next_line.h"

#ifndef GREEN
#define GREEN "\033[32m"
#endif

#ifndef YELLOW
#define YELLOW "\033[33m"
#endif

#ifndef RED
#define RED "\033[31m"
#endif

#ifndef RESET
#define RESET "\033[0m"
#endif


typedef struct s_slist
{
	char			*str;
	struct s_slist	*next;

}					t_slist;

typedef struct s_data
{
	struct s_slist	*list;
    int32_t       size;
	int32_t       nb ;
	int32_t       guess;
	char			*sol;
	char			matrix[6][5];
	int				table[26];
}					t_data;

void ft_clean_exit(t_data *d, char *err, int error);

// list.c
t_slist				*ft_slstnew(char *str);
int					ft_slstadd_back(t_slist **lst, t_slist *new_l);
void				ft_print_slst(t_slist *lst);
void                ft_create_w_list(t_data *d);
t_slist	            *ft_listlast(t_slist *lst);

// string.c
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
int ft_strncmp(char *s1, char *s2, size_t n);

#endif