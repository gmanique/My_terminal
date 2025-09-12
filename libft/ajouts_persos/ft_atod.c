/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:13:49 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/11 02:26:03 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ajouts.h"

static int	is_valid_number(const char *str)
{
	int	has_digits;
	int	has_dot;

	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	has_digits = 0;
	has_dot = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			has_digits = 1;
		else if ((*str == '.' || *str == ',') && !has_dot)
			has_dot = 1;
		else
			return (0);
		str++;
	}
	return (has_digits);
}

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**str == '.' || **str == ',')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction = fraction * 10.0 + (**str - '0');
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

double	ft_atod(const char *str)
{
	double	result;
	int		sign;

	if (!str || !is_valid_number(str))
		return (0);
	sign = 1;
	str = skip_whitespace_and_sign(str, &sign);
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	return (sign * result);
}
