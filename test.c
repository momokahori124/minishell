// #include <stdio.h>
#include <string.h> /* strcmp(  ), size_t で必要 */
#include "includes/minishell.h"
// pwd | aaa;bbb;

static int	count_quotation(char *tmp, char quo)
{
	static char	*str;
	int			cnt;

	cnt = 0;
	if (str == NULL)
	{
		tmp++;
		while (*tmp && *tmp != '\n')
		{
			if (*tmp == quo)
				cnt++;
			tmp++;
		}
		printf("[%d]\n", cnt);
		if ((cnt & 1) == 1)
			return (true);
		else
		{
			str = tmp;
			return (false);
		}
	}
	else
	{
		str++;
		while (*str && *str != '\n')
		{
			if (*str == quo)
				cnt++;
		}
		if (*str == '\n')
		{
			if ((cnt & 1) == 1)
				return (true);
			else
			{
				return (false);
			}
		}
	}

	exit(puts("ここ"));
}

void	rm_chr_in_str(char **str, char chr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != chr)
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
}

static bool	press_eof_while_looking(char match, char **inputs, t_minishell_info *info)
{
	ptr_free((void **)inputs);
	if (write(1, "minishell: unexpected EOF while looking for matching `", 54) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, &match, 1) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "`\nminishell: syntax error: unexpected end of file\n", 50)
				< 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (false);
}

static bool	do_when_input_char_equal_newline(int *first_quo_cnt, int *other_quo_cnt, \
		char **inputs, char first_appear)
{
	if ((*first_quo_cnt & 1) == 1)
	{
		if ((*other_quo_cnt & 1) == 0)
		{
			*first_quo_cnt = 0;
			*other_quo_cnt = 0;
			return (true);
		}
	}
	else
	{
		rm_chr_in_str(inputs, first_appear);
		*first_quo_cnt = 0;
		*other_quo_cnt = 0;
	}
	write(1, "> ", 2);
	return (false);
}

static char	*prepare_in_advance(int *num1, int *num2, t_minishell_info *info)
{
	char	*res;

	if (write(1, "> ", 2) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!(res = ft_strdup("\n")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	*num1 = 0;
	*num2 = 0;
	return (res);
}

static bool	check_buf_and_return_value(ssize_t rc, char buf, int count[2], char first_appear)
{
	char	other_quo;

	if (first_appear == '\'')
		other_quo = '\"';
	else if (first_appear == '\"')
		other_quo = '\'';
	if (rc == 0 && buf == '\0')
		return (true);
	else if (rc != 0 && buf == first_appear)
		count[0]++;
	else if (rc != 0 && buf == other_quo)
		count[1]++;
	return (false);
}


bool wait_quotation(char first_appear, char **command, t_minishell_info *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	int			count[2];

	inputs = prepare_in_advance(&count[0], &count[1], info);
	while ((rc = read(0, &buf, 1)) >= 0)
	{
		if (write(0, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&inputs);
			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		if (check_buf_and_return_value(rc, buf, count, first_appear) == true)
				return (press_eof_while_looking(first_appear, &inputs, info));
		if (buf == '\n')
			if (do_when_input_char_equal_newline(&count[0], &count[1],
						&inputs, first_appear) == true)
				break;
		if (!(inputs = re_strjoinch(&inputs, buf)))
			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	*command = re_strjoin(command, inputs);
	ptr_free((void **)&inputs);
	return (true);
}
// __attribute__((destructor))
// void end()
// {
// 	system("leaks a.out");
// }

bool	spaces_or_not_in_array(char **arr, int *element_num)
{
	int		i;
	bool	flag;

	i = -1;
	*element_num = 0;
	flag = false;
	while (arr[++i])
	{
		if (arr[i][0] == ' ')
		{
			if (skip_space(arr[i])[0] == '\0')
				flag = true;
		}
		else
			(*element_num)++;
	}
	return (flag);
}

char	**create_no_spaces_array(char **new, char **old)
{
	int		i;
	int		new_index;

	i = -1;
	new_index = 0;
	while (old[++i])
	{
		printf("old : [%s]\n", old[i]);
		if (old[i][0] == ' ')
		{
			if (skip_space(old[i])[0] == '\0')
				ptr_free((void **)&old[i]);
		}
		else
		{
			puts("+");
		// printf("old : [%s]\n", old[i]);
			new[new_index++] = old[i];
		}
	}
	new[new_index] = NULL;
	return (new);
}


char	**rm_space_in_array(char **arr, t_minishell_info *info)
{
	int		i;
	int		element_num;
	char	**res;

	if (spaces_or_not_in_array(arr, &element_num) == false)
		return (arr);
	printf("%d\n", element_num);
	if (!(res = malloc(sizeof(char *) * (element_num + 1))))
	{
		ptr_2d_free((void ***)&arr, i);
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	res = create_no_spaces_array(res, arr);
	ptr_2d_free((void ***)&arr, 0);
	return (res);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks a.out");
// }

int main()
{
	t_minishell_info *info;
	// char **res = ft_split("aaa|   |    |bbb|   |ccc", '|');
	char **res = split_by_chrs_contain_delimiters("pd |     ", "><;|");
	int i = 0;
	// while (res[i])
	// {
	// 	printf("res1 = %s\n", res[i]);
	// 	i++;
	// }

	char **resa = rm_space_in_array(res, info);
	i = 0;
	while (resa[i])
	{
		printf("res2 = %s\n", resa[i]);
		free(resa[i]);
		i++;
	}
	free(resa);

}

// #define NUM_DATA 7
// const char *base[NUM_DATA] = {"cd", "echo", "env", "exit",
// 							  "export", "pwd", "unset"};

// /* バイナリサーチを行う */
// int BSearch(const char *key, const char *base[], int bottom, int top);

// int BSearch(const char *key, const char *base[], int bottom, int top)
// {
// 	int middle;
// 	int temp;

// 	if (bottom == top)
// 		return (-1);
// 	middle = (top + bottom) / 2;
// 	if ((temp = strcmp(key, base[middle])) == 0)
// 		return (middle);
// 	else if (temp > 0)
// 		if (top == middle + 1)
// 			BSearch(key, base, middle, top + 1);
// 		else
// 			BSearch(key, base, middle + 1, top);
// 	else
// 		BSearch(key, base, bottom, middle);
// 	return (-1);
// }

// int main(void)
// {
// 	int i;
// 	int temp;
// 	const char *key = "pwd"; /* 検索対象の文字列 */
// 	int top = NUM_DATA - 1;
// 	int bottom = 0;

// 	printf("キーワード：%s\n", key);
// 	printf("検索対象のデータ：%s\n", key);
// 	for (i = 0; i < NUM_DATA; i++)
// 		printf("\t%s\n", base[i]);

// 	if ((temp = BSearch(key, base, bottom, top)) != -1)
// 		printf("\n見つかりました: %s は %d 番目の要素です。\n",
// 			   base[temp], temp + 1);
// 	else
// 		printf("\n見つかりません。\n");
// // }

// #include <stdio.h>

#define ARRAY_SIZE 8
const char *a[ARRAY_SIZE] = {"cd", "echo", "env", "exit",
							  "export", "pwd", "unset", "zzz"};

// int	str_bsearch(char *key, const char *base[], int right)
// {
// 	int	left;
// 	int	mid;
// 	int	tmp;

// 	left = 0;
// 	if (left == right)
// 		return (-1);
// 	while (left <= right)
// 	{
// 		mid = (left + right) / 2;
// 		if ((tmp = strcmp(key, base[mid])) == 0)
// 			return (mid);
// 		else if (tmp > 0)
// 			left = mid + 1;
// 		else
// 			right = mid - 1;
// 	}
// 	return (-2);
// }

// int main(void)
// {
// 	// int a[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7}; /* sorted array */
// 	int left = 0;							   /* start key of index */
// 	int right = ARRAY_SIZE;					   /* end key of index */
// 	int mid;								   /* middle key of index */
// 	char *value;								   /* search value */
// 	int tmp;

// 	puts("Find value?");
// 	scanf("%s", value);

// 	// while (left <= right)
// 	// {
// 	// 	mid = (left + right) / 2; /* calc of middle key */
// 	// 	if ((tmp = strcmp(value, a[mid])) == 0)
// 	// 	{
// 	// 		puts("Found!\n");
// 	// 		printf("%d : %s\n", mid, a[mid]);
// 	// 		return 0;
// 	// 	}
// 	// 	else if (tmp > 0)
// 	// 	{
// 	// 		left = mid + 1; /* adjustment of left(start) key */
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		right = mid - 1; /* adjustment of right(end) key */
// 	// 	}
// 	// }
// 	// puts("Not Found.\n");
// 	int i = str_bsearch(value, a, ARRAY_SIZE);
// 	if (i == -2)
// 	{
// 		puts("Not Found.");
// 		return (1);
// 	}
// 	printf("%d : %s\n", i, a[i]);
// 	return 0;
// }

// int main()
// {
// 	int i = str_bsearch("cd", a, ARRAY_SIZE);
// }
