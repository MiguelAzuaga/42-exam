typedef struct s_btree
{
struct s_btree	*left;
struct s_btree	*right;
char			*item;
}	t_btree;

#include <stdio.h>
#include <stdlib.h>

int	ft_strcmp(char *a, char *b)
{
	int	i = 0;

	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

void	tree_insert(t_btree **root, char *item, int (*ft_strcmp)(char *, char *))
{
	if (!root)
		return ;
	if (*root == NULL)
	{
		*root = malloc(sizeof(t_btree));
		if (!root)
			return ;
		(*root)->item = item;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return ;
	}
	if (ft_strcmp(item, (*root)->item) < 0)
		tree_insert(&(*root)->left, item, ft_strcmp);
	else
		tree_insert(&(*root)->right, item, ft_strcmp);
}

void	insert_copy(t_btree **root, char *str, int len)
{
	char	*cpy;

	cpy = malloc(len + 1);
	if (!cpy)
		return ;
	for (int i = 0; i < len; i++)
		cpy[i] = str[i];
	cpy[len] = 0;
	tree_insert(root, cpy, ft_strcmp);
}

void	swap(char *a, char *b)
{
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void permute(char *str, int i, int len, t_btree **root)
{
	int	j;

	if (i == len)
	{
		insert_copy(root, str, len);
		return ;
	}
	else
	{
		j = i;
		while(j < len)
		{
			swap(&str[i], &str[j]);
			permute(str, i + 1, len, root);
			swap(&str[i], &str[j]);
			j++;
		}
	}
}

void	tree_print(t_btree *root)
{
	if (!root)
		return ;
	tree_print(root->left);
	puts(root->item);
	tree_print(root->right);
}

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1][0])
		return (0);
	int len = 0;
	t_btree *root = NULL;
	while (av[1][len])
		len++;
	permute(av[1], 0, len, &root);
	tree_print(root);
}
