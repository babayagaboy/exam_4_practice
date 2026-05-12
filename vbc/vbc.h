#ifndef VBC_H
# define VBC_H

# include "unistd.h"
# include "stdio.h"
# include "ctype.h"

void	unexpected(char c);
int	ft_product();
int	ft_sum();
int	ft_factor();
int	check_input(char *str);

#endif