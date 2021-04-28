/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:52:37 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/14 18:52:40 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mix_n_match_flags(const char *str, int i, va_list args, t_flags *s_fl)
{
	if (str[i] == '*') //when is not specified
	{
		s_fl->star = 1;
		set_star(s_fl, args);
	}
	if (str[i] == '-') //puts spaces at the left of the argument
		{
			s_fl->minus = 1;
			s_fl->zero = 0;
		}
	if (str[i] == '.') //quantos caracteres quer imprimir exemplo:".5"
		i = set_prec(str, i, args, s_fl);
	return (i);
}

int		mix_n_match_output(t_flags s_fl, va_list args)
{
	int counter;

	counter = 0;
	if (s_fl.letter == 'c') //char
		counter += conv_char(va_arg(args, int), s_fl);
	else if (s_fl.letter == 's') //string
		counter += conv_str(va_arg(args, char*), s_fl);
	else if (s_fl.letter == '%') //prints '%'
		counter += conv_char('%', s_fl);
	else if (s_fl.letter == 'd' || s_fl.letter == 'i') //signed intenger
		counter += conv_int(va_arg(args, int), s_fl);
	else if (s_fl.letter == 'u') //unsigned int
		counter += unsig_conv(va_arg(args, unsigned), s_fl);
	else if (s_fl.letter == 'p') //pointer
		counter += pointer_conv(va_arg(args, unsigned long long), s_fl);
	else if (s_fl.letter == 'x') //hexadecimal representation
		counter += hexa_conv(va_arg(args, unsigned int), 0, s_fl);
	else if (s_fl.letter == 'X')
		counter += hexa_conv(va_arg(args, unsigned int), 1, s_fl);
	else if (s_fl.letter == 'n') //nothing
		return (counter);
	return (counter);
}

int	verify(const char *str, int i, va_list args, t_flags *s_fl)
{
	while (str[i] != '\0')
	{
		if (!ck_char(str[i]) && !ck_flags(str[i]) && !ck_num(str[i]))
			break ;
		if (ck_flags(str[i]))
			i = mix_n_match_flags(str, i, args, s_fl);
		if (str[i] == '0' && s_fl->minus == 0 && s_fl->width == 0) //put zeros instead of spaces
			s_fl->zero = 1;
		if (ck_num(str[i]))
			{
				set_width(str[i], s_fl);
			}
		if (ck_char(str[i]))
		{
			set_letter(str[i], s_fl);
			break ;
		}
		i++;
	}
	return (i);
}

int		init(const char *str, va_list args)
{
	int i;
	int counter;
	t_flags s_fl;

	i = 0;
	counter = 0;
	while (str[i] != '\0') //prints until the end of the string or until a "%"
	{
		s_fl = flags_init();
		if (!str[i])
			break ;
		else if (str[i] == '%' && str[i + 1] != '\0')
		{
			i = verify(str, i + 1, args, &s_fl); //verify what comes after the "%" and processes how to deal with it
			if (s_fl.letter == 0)
			{
				return (counter);
			}
			counter += mix_n_match_output(s_fl, args);
		}
		else if (str[i] != '%')
			counter += ft_putchar(str[i]);
		i++;
	}
	return (counter);
}

int		ft_printf(const char *str, ...)
{
	va_list args;
	int counter;

	counter = 0;
	va_start(args, str);
	counter += init(str, args);
	va_end(args);
	return (counter);
}

// int	main(void)
// {
// 	// int i;
// 	// int j;

// 	printf("\n--------INICIO-------\n");

// 	ft_printf(".%0-*x. .%0*x.\n", 21, 1021, 21, -1011);
// 	printf(".%0-*x. .%0*x.\n", 21, 1021, 21, -1011);
// 	printf("\n---------------------\n");

// 	ft_printf(".%03x.\n", 0);
// 	printf(".%03x.\n", 0);
// 	// printf("\n---------------------\n");

// 	// ft_printf("m = .%0*.0x. .%0*.10x.\n", -21, 1234567, 21, -1);
// 	// printf("p = .%0*.0x. .%0*.10x.\n", -21, 1234567, 21, -1);
// 	// printf("\n---------------------\n");

// 	// ft_printf("m = .%-0*.2x. .%-0*.2x.\n", -21, 343647, 21, 343647 + 1);
// 	// printf("p = .%-0*.2x. .%-0*.2x.\n", -21, 343647, 21, 343647 + 1);
// 	// printf("\n---------------------\n");

// 	// ft_printf("m = .%9.0x.\n", 12345);
// 	// printf("p = .%9.0x.\n", 12345);
// 	// printf("\n---------------------\n");

// 	// ft_printf("m = .%9.1x.\n", 12345);
// 	// printf("p = .%9.1x.\n", 12345);
// }