/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:53:00 by zanikin           #+#    #+#             */
/*   Updated: 2024/02/16 16:27:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

// no format tests

static int	n_string_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	n_empty_string_test(int (*print_func)(const char *, ...), int output, char *out_buff);
//static int	n_null_string_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// c tests

static int	c_test(int (*print_func)(const char *, ...), int, char *);
static int	c_null_test(int (*print_func)(const char *, ...), int, char *);
static int	c_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_sharp_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_zero_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_plus_zero_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_plus_one_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	c_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// s tests

static int	s_test(int (*print_func)(const char *, ...), int, char *);
static int	s_null_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_null_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_plus_sharp_space_0_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_plus_sharp_space_0_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_null_plus_sharp_space_0_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_empty_plus_sharp_space_0_width_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	s_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// p tests

static int	p_test(int (*print_func)(const char *, ...), int, char *);
static int	p_null_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_long_min_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_long_max_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_ulong_max_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_zero_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// i tests

static int	i_test(int (*print_func)(const char *, ...), int, char *);
static int	i_sign_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	i_sign_width_plus_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	i_space_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	i_zero_space_left_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	i_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// d tests

static int	d_test(int (*print_func)(const char *, ...), int, char *);
static int	d_0_width_neg_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	d_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// u tests

static int	u_test(int (*print_func)(const char *, ...), int, char *);
static int	u_plus_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// x tests

static int	x_test(int (*print_func)(const char *, ...), int, char *);
static int	x_zero_sharp_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	x_sharp_plus_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// X tests

static int	X_test(int (*print_func)(const char *, ...), int, char *);
static int	X_sharp_left_zero_space_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// Percent tests

static int	percent_test(int (*print_func)(const char *, ...), int, char *);
static int	percent_left_plus_zero_space_sharp_width_precision_test(int (*print_func)(const char *, ...), int output, char * out_buff);
static int	p_zero_zero_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff);
static int	p_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff);

// Mix tests
static int	mix_0_test(int (*print_func)(const char *, ...), int output, char * out_buff);

// Undefined behaviour tests

//static int	ub_test(int (*print_func)(const char *, ...), int output, char * out_buff);

static void	message_test(char *out_buff, const char *test_name, const char *format);

int	main()
{
	char	original[500];
	char	user[500];
	char	test_output[500];
	int	out_pipe[2];
  	int	saved_stdout;
	int		(*tests[])(int (*)(const char *, ...), int, char *) = {
		// no format

		&n_string_test,
		&n_empty_string_test,
//		&n_null_string_test,

		// c tests

		&c_test,
		&c_null_test,
		&c_width_test,
		&c_left_width_test,
		&c_sharp_width_precision_test,
		&c_zero_width_precision_test,
		&c_plus_zero_width_test,
		&c_plus_one_width_test,
		&c_mix_test,

		// s tests

		&s_test,
		&s_null_test,
		&s_null_width_precision_test,
		&s_plus_sharp_space_0_width_test,
		&s_plus_sharp_space_0_left_width_test,
		&s_null_plus_sharp_space_0_left_width_test,
		&s_empty_plus_sharp_space_0_width_test,
		&s_mix_test,

		// p test

		&p_test,
		&p_null_test,
		&p_long_min_test,
		&p_long_max_test,
		&p_ulong_max_test,
		&p_zero_zero_precision_test,
		&p_zero_precision_test,
		&p_mix_test,

		// i tests

		&i_test,
		&i_sign_precision_test,
		&i_sign_width_plus_precision_test,
		&i_space_width_precision_test,
		&i_zero_space_left_width_precision_test,
		&i_mix_test,

		// d tests

		&d_test,
		&d_0_width_neg_test,
		&d_mix_test,

		// u tests

		&u_test,
		&u_plus_test,

		// x tests

		&x_test,
		&x_zero_sharp_test,
		&x_sharp_plus_width_precision_test,

		// X tests

		&X_test,
		&X_sharp_left_zero_space_width_precision_test,

		// % tests

		&percent_test,
		&percent_left_plus_zero_space_sharp_width_precision_test,

		&mix_0_test,

		// undefined behaviour tests

		//&ub_test
	};
	saved_stdout = dup(STDOUT_FILENO);
	pipe(out_pipe);
	int	error = 0;
	for (unsigned long i = 0; !error && i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		dup2(out_pipe[1], STDOUT_FILENO);
		test_output[0] = 0;
		int	orig_count = tests[i](printf, 1, test_output);
		fflush(stdout);
		int	user_count = tests[i](ft_printf, 0, test_output);
		fflush(stdout);
		read(out_pipe[0], original, orig_count);
		read(out_pipe[0], user, user_count);
		if (orig_count == user_count)
		{
			if (memcmp(original, user, orig_count))
				error = 2;
		}
		else
			error = 1;
		dup2(saved_stdout, STDOUT_FILENO);
		if (error)
		{
			printf("%s\n", test_output);
			if (error == 1)
				printf("Printed characters counts are not the same: original - %i, user - %i\n", orig_count, user_count);
			printf("original: %.*s\nuser: %.*s\n", orig_count, original, user_count, user);
		}
	}
	if (!error)
		printf("Tests has been passed\n");
	return error;
}

// no format tests

static int	n_string_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiux X";
	if (output)
		message_test(out_buff, "string", format);
	return print_func(format);
}

static int	n_empty_string_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "";
	if (output)
		message_test(out_buff, "empty string", format);
	return print_func(format);
}

//static int	n_null_string_test(int (*print_func)(const char *, ...), int output, char *out_buff)
//{
//	const char *format = NULL;
//	if (output)
//		message_test(out_buff, "null string", format);
//	return print_func(format);
//}

// c tests

static int	c_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%ccspdiuxX";
	if (output)
		message_test(out_buff, "c", format);
	return print_func(format, 'a');
}

static int	c_null_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%ccspdiuxX";
	if (output)
		message_test(out_buff, "c null", format);
	return print_func(format, 0);
}

static int	c_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%3ccspdiuxX";
	if (output)
		message_test(out_buff, "c width", format);
	return print_func(format, 'a');
}

static int	c_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%-3ccspdiuxX";
	if (output)
		message_test(out_buff, "c - width", format);
	return print_func(format, 'a');
}

static int	c_sharp_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%#5.3ccspdiuxX";
	if (output)
		message_test(out_buff, "c sharp width precision", format);
	return print_func(format, 'a');
}

static int	c_zero_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%05.3ccspdiuxX";
	if (output)
		message_test(out_buff, "c 0 width precision", format);
	return print_func(format, 'a');
}

static int	c_plus_zero_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+0.3ccspdiuxX";
	if (output)
		message_test(out_buff, "c 0 width precision", format);
	return print_func(format, 'a');
}

static int	c_plus_one_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+1.3ccspdiuxX";
	if (output)
		message_test(out_buff, "c 0 width precision", format);
	return print_func(format, 'a');
}

static int	c_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "xc%+1.3ccspdiuxX|c% 0.0c|c%+ 0.0c";
	if (output)
		message_test(out_buff, "c mix", format);
	return print_func(format, 'a', 0, '1');
}

// s tests

static int	s_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%scspdiuxX";
	if (output)
		message_test(out_buff, "s", format);
	return print_func(format, "Hello, baby");
}

static int	s_null_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%scspdiuxX";
	if (output)
		message_test(out_buff, "s null", format);
	return print_func(format, NULL);
}

static int	s_null_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%10.2scspdiuxX";
	if (output)
		message_test(out_buff, "s null width precision", format);
	return print_func(format, NULL);
}

static int	s_plus_sharp_space_0_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+# 010scspdiuxX";
	if (output)
		message_test(out_buff, "s + # space 0 width precision", format);
	return print_func(format, "test");
}

static int	s_plus_sharp_space_0_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+# 0-10scspdiuxX";
	if (output)
		message_test(out_buff, "s + # space 0 width precision", format);
	return print_func(format, "test");
}

static int	s_null_plus_sharp_space_0_left_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+# 0-10scspdiuxX";
	if (output)
		message_test(out_buff, "s null + # space 0 - width precision", format);
	return print_func(format, NULL);
}

static int	s_empty_plus_sharp_space_0_width_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%+# 0-10scspdiuxX";
	if (output)
		message_test(out_buff, "s empty + # space 0 width precision", format);
	return print_func(format, "");
}

static int	s_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cs%+# 0-10sspdiu\nxX|%s|%0s|%0.s|%00.3s|%00.0001s|%-000.3s|% .25s";
	if (output)
		message_test(out_buff, "s mix", format);
	return print_func(format, "", NULL, NULL, "fs", "fs", 0, "test", "test");
}

// p tests

static int	p_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%pcspdiuxX";
	int			i = 534;
	if (output)
		message_test(out_buff, "p", format);
	return print_func(format, &i);
}

static int	p_null_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%pcspdiuxX";
	if (output)
		message_test(out_buff, "p null", format);
	return print_func(format, NULL);
}

static int	p_long_min_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%pcspdiuxX";
	if (output)
		message_test(out_buff, "p long min", format);
	return print_func(format, LONG_MIN);
}

static int	p_long_max_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%pcspdiuxX";
	if (output)
		message_test(out_buff, "p long max", format);
	return print_func(format, LONG_MAX);
}

static int	p_ulong_max_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%pcspdiuxX";
	if (output)
		message_test(out_buff, "p unsigned long max", format);
	return print_func(format, ULONG_MAX);
}

static int	p_zero_zero_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX% 5.00pcspdiuxX";
	if (output)
		message_test(out_buff, "p zero precision", format);
	return print_func(format, 0);
}

static int	p_zero_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX% 5.00pcspdiuxX";
	if (output)
		message_test(out_buff, "p zero precision", format);
	return print_func(format, 1);
}

static int	p_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "scp% 000.000p| +523%-#pp|%00.p|sdfbvs%%%-+1.1p";
	if (output)
		message_test(out_buff, "p mix", format);
	return print_func(format, 1, 2345, 0, 1000000);
}

// i tests

static int	i_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%icspdiuxX";
	int			i = 534;
	if (output)
		message_test(out_buff, "i", format);
	return print_func(format, i);
}

static int	i_sign_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%.5icspdiuxX";
	if (output)
		message_test(out_buff, "i signed precision", format);
	return print_func(format, -1);
}

static int	i_sign_width_plus_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%+7.5icspdiuxX";
	if (output)
		message_test(out_buff, "i + width precision", format);
	return print_func(format, 461);
}

static int	i_space_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX% 7.5icspdiuxX";
	if (output)
		message_test(out_buff, "i space width precision", format);
	return print_func(format, 461);
}

static int	i_zero_space_left_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX% 0-7.5icspdiuxX";
	if (output)
		message_test(out_buff, "i", format);
	return print_func(format, 461);
}

static int	i_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuii%0+04.12iispdiuxX|di% +00.000i|% +i|%- #+1.5i|534% #1.5i5345|53%+010.8";
	if (output)
		message_test(out_buff, "i mix", format);
	return print_func(format, INT_MIN, 0, 1, 15, -1, -23);
}

// d tests

static int	d_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%dcspdiuxX";
	int			i = 534;
	if (output)
		message_test(out_buff, "d", format);
	return print_func(format, i);
}

static int	d_0_width_neg_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%04dcspdiuxX";
	int			i = -15;
	if (output)
		message_test(out_buff, "d 0 width", format);
	return print_func(format, i);
}

static int	d_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%0+04.12dcspdiuxX|di% +00.000d|% +d|%- #+1.5d|534% #1.5d5345|53%+010.8d";
	if (output)
		message_test(out_buff, "d mix", format);
	return print_func(format, INT_MIN, 0, 1, 15, -1, -23);
}

// u tests

static int	u_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%ucspdiuxX";
	int			i = -1;
	if (output)
		message_test(out_buff, "u", format);
	return print_func(format, i);
}

static int	u_plus_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%+ucspdiuxX";
	int			i = -1;
	if (output)
		message_test(out_buff, "u", format);
	return print_func(format, i);
}

static int	u_mix_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%+ucspdiuxX";
	int			i = -1;
	if (output)
		message_test(out_buff, "u", format);
	return print_func(format, i);
}

// x tests

static int	x_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%xcspdiuxX";
	int			i = -1;
	if (output)
		message_test(out_buff, "x", format);
	return print_func(format, i);
}

static int	x_zero_sharp_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%#xcspdiuxX";
	if (output)
		message_test(out_buff, "x sharp", format);
	return print_func(format, 0);
}

static int	x_sharp_plus_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char *format = "cspdiuxX%#+7.3xcspdiuxX";
	if (output)
		message_test(out_buff, "x sharp", format);
	return print_func(format, 23);
}

// X tests

static int	X_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%XcspdiuxX";
	int			i = -1;
	if (output)
		message_test(out_buff, "X", format);
	return print_func(format, i);
}

static int	X_sharp_left_zero_space_width_precision_test(int (*print_func)(const char *, ...), int output, char *out_buff)
{
	const char	*format = "cspdiuxX%#-0 10.5XcspdiuxX";
	int			i = 346;
	if (output)
		message_test(out_buff, "X - 0 space width precision", format);
	return print_func(format, i);
}

// Percent tests

static int	percent_test(int (*print_func)(const char *, ...), int output, char * out_buff)
{
	const char *format = "cspdiuxX%%cspdiuxX";
	if (output)
		message_test(out_buff, "%", format);
	return print_func(format);
}

static int	percent_left_plus_zero_space_sharp_width_precision_test(int (*print_func)(const char *, ...), int output, char * out_buff)
{
	const char *format = "cspdiuxX%-+0 #10.5%cspdiuxX";
	if (output)
		message_test(out_buff, "% - + 0 space # width precision", format);
	return print_func(format);
}

// Mix tests

static int	mix_0_test(int (*print_func)(const char *, ...), int output, char * out_buff)
{
	const int i;
	const char *format = "cspdiuxX%-+0 #10.5%|%0 .i|%-.05d|% #+010.s|% .p|%-+30.20p|% .c|% 10.00x|%+-0.10X|% 5.00p|%+5.0d|% 5.X|%+5.0x|% 10.23xcspdiuxX";
	if (output)
		message_test(out_buff, "mix", format);
	return print_func(format, 0, -23, "test", &i, &i, 'a', 100, 100, NULL, 0, 0, 0, -5);
}

// Undefined behaviour tests

//static int	ub_test(int (*print_func)(const char *, ...), int output, char * out_buff)
//{
//	const char *format = "fdsfsdf%+-0 #1234.0001w1%s";
//	if (output)
//		message_test(out_buff, "undefined behaviour", format);
//	return print_func(format, "sus");
//}

static void	message_test(char *out_buff, const char *test_name, const char *format)
{
	sprintf(out_buff, "%s test: %s", test_name, format);
}
