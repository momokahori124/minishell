// #include <stdio.h>
#include <string.h> /* strcmp(  ), size_t で必要 */
#include "includes/minishell.h"
// pwd | aaa;bbb;

int main()
{
	int i = 1;
	printf("%d\n", ~i);
	bool s = 2;
	printf("%d\n", s);

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
