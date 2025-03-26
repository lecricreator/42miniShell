/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:09:07 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:42:48 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define PLH_LIST "csxXidup%"
# define FORMAT_LIST "-0123456789#. +"

# include <stdarg.h>
# include <limits.h>
# include "libft.h"

typedef struct s_flags
{
	int	align;
	int	zero_pad;
	int	force_sign;
	int	space_sign;
	int	hex_prefix;
	int	precision;
	int	width;
	int	fd;
}	t_flags;

void	ft_flags(t_flags *flags, const char *str, int *index);
void	flag_init(t_flags *flags, int fd);
char	*ft_printf_itoa(int n, t_flags *flags);
int		ft_printchar(int fd, char c);
int		ft_putstr(int fd, char *str);
int		ft_printchar_flag(const char c, t_flags flags);
int		ft_printstr(char *str, t_flags flags);
int		padding(t_flags *flags, int input_len);
int		padding_nbr(t_flags *flags, int input_len);
int		ft_printhex(unsigned int n, const char format, t_flags flags);
int		ft_printnbr(int n, t_flags flags);
int		ft_printptr(unsigned long long ptr, t_flags flags);
int		ft_printunsigned(unsigned int n, t_flags flags);
int		ft_printf_fd(int fd, const char *str, ...);

#endif
