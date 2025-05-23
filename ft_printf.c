/*
Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Your function must not leak.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Warning: Your function must not have any leaks, this will be checked during moulinette
*/

#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count = 0;
	int	i = 0;

	if (!str)
		str = "(nil)"; //
	while (str[i])
		count += ft_putchar(str[i++]);
	return (count);
}

int	ft_putnbr(int n)
{
	int		count = 0;
	long	nb = n;

	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_putnbr(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_puthex(unsigned int n)
{
	int		count = 0;
	char	*base = "0123456789abcdef"; //

	if (n >= 16)
		count += ft_puthex(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_printf(const char *format, ...) //
{
	va_list	args;
	int		count = 0;
	int		i = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				count += ft_putstr(va_arg(args, char *)); //
			else if (format[i] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (format[i] == 'x')
				count += ft_puthex(va_arg(args, unsigned int));
		}
		else
			count += ft_putchar(format[i]);
		i++; //
	}
	va_end(args);
	return (count);
}

#include <stdio.h>

int	main(void)
{
	int real;
	int custom;

	// Test 1: String
	real = printf("1. Hello %s!\n", "Bana");
	custom = ft_printf("1. Hello %s!\n", "Bana");
	printf("→ printf: %d, ft_printf: %d\n\n", real, custom);

	// Test 2: Decimal
	real = printf("2. Value: %d\n", -1234);
	custom = ft_printf("2. Value: %d\n", -1234);
	printf("→ printf: %d, ft_printf: %d\n\n", real, custom);

	// Test 3: Hexadecimal
	real = printf("3. Hex: %x\n", 255);
	custom = ft_printf("3. Hex: %x\n", 255);
	printf("→ printf: %d, ft_printf: %d\n\n", real, custom);

	// Test 4: NULL string test (with %p in printf)
	real = printf("4. Null test: %p\n", (void *)NULL);
	custom = ft_printf("4. Null test: %s\n", NULL);
	printf("→ printf: %d, ft_printf: %d\n\n", real, custom);

	// Test 5: Mixed
	real = printf("5. Hi %s, dec: %d, hex: %x!\n", "Bana", 42, 42);
	custom = ft_printf("5. Hi %s, dec: %d, hex: %x!\n", "Bana", 42, 42);
	printf("→ printf: %d, ft_printf: %d\n\n", real, custom);

	return (0);
}
