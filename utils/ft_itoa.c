/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:27:09 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 20:32:14 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nlen(long n)
{
	int	c;

	c = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static char	*getnum(char *arr, unsigned long n, int numsize, int neg)
{
	long	res;
	int		div;
	int		i;

	res = 0;
	i = 0;
	div = 1;
	if (neg)
		arr[i++] = '-';
	while (numsize > 1)
	{
		div *= 10;
		numsize--;
	}
	while (div)
	{
		res = n / div;
		n = n - res * div;
		div /= 10;
		arr[i++] = res + '0';
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	int				nl;
	char			*arr;
	int				neg;
	unsigned int	nbr;

	neg = 0;
	if (n < 0)
	{
		nbr = n * -1;
		nl = nlen(nbr);
		arr = (char *)ft_malloc(nl * sizeof(char) + 2);
		neg++;
	}
	else
	{
		nbr = n;
		nl = nlen(nbr);
		arr = (char *)ft_malloc(nl * sizeof(char) + 1);
	}
	if (!arr)
		return (NULL);
	arr = getnum(arr, nbr, nl, neg);
	return (arr);
}
