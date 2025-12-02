#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void	ft_putstr(const char *str, int *count)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str++, 1);
		(*count)++;
	}
}

// static void ft_putint(int n, int *count)
// {
//     char c;

//     if (n == -2147483648)
//     {
//         ft_putstr("-2147483648", count);
//         return;
//     }
//     if (n < 0)
//     {
//         write(1, "-", 1);
//         (*count)++;
//         n = -n;
//     }
//     if (n > 9)
//         ft_putint(n / 10, count);
//     c = (n % 10) + '0';
//     write(1, &c, 1);
//     (*count)++;
// }

void	ft_putint(int n, int *count)
{
	char *dec = "0123456789";

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
		n = -n;
	}
	if (n > 9)
		ft_putint(n / 10, count);
	write(1, &dec[n % 10], 1);
	(*count)++;
}

void	ft_puthex(unsigned int n, int *count)
{
	char *hex = "0123456789abcdef";

	if (n > 15)
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			if (*str == 's')
				ft_putstr(va_arg(ap, char *), &count);
			else if (*str == 'd')
				ft_putint(va_arg(ap, int), &count);
			else if (*str == 'x')
				ft_puthex(va_arg(ap, unsigned int), &count);
			else
			{
				write(1, str, 1);
				count++;
			}
		}
		else
		{
			write(1, str, 1);
			count++;
		}
		str++;
	}
	va_end(ap);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*name = "Ram";
// 	int		role = 255;
// 	int		marks = 80;

	
// 	ft_printf("Ft_printf:	%s with role %x got %d marks.\n", name, role, marks);
// 	printf("printf:		%s with role %x got %d marks.\n", name, role, marks);

// 	return (0);
// }
