/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:30:23 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/18 22:58:11 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(char const *str, ...);
int	ft_putchar(int c);
int	ft_putnbr(int nb);
int	ft_putstr(char *str);
int	ft_unsnb(unsigned int nb);
int	ft_address(unsigned long nb);
int	ft_hexadec(unsigned long nb, char c);

#endif