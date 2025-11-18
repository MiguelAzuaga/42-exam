#include <stdio.h>
#include <string.h>
#include "ft_btree.h"

void free_tree(t_btree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

void	print_item(void *item)
{
	printf("%s ", (char *)item);
}

void	print_node(void *item, int lvl, int is_first)
{
	printf("Level %d: %s %s\n", lvl + 1, (char *)item, is_first ? "(first)" : "");
}

int ft_strcmp(void *a, void *b)
{
	return strcmp((const char *)a, (const char *)b);
}

int	main(void)
{
	int a = '2', b = '1', c = '6', d = '4', e = '5', f = '3';

	// ex00 Create nodes
	t_btree *root = btree_create_node(&a);
	root->left = btree_create_node(&b);
	root->right = btree_create_node(&c);
	root->left->left = btree_create_node(&d);
	root->left->right = btree_create_node(&e);
	root->right->left = btree_create_node(&f);

	// ex01 Preorder
	printf("Prefix	(Root, Left, Right): ");
	btree_apply_prefix(root, &print_item);
	printf("\n");

	// ex02 Inorder
	printf("Infix	(Left, Root, Right): ");
	btree_apply_infix(root, &print_item);
	printf("\n");

	// ex03 Postorder
	printf("Suffix	(Left, Right, Root): ");
	btree_apply_suffix(root, &print_item);
	printf("\n\n");

	free_tree(root);
	root = NULL;

	// ex04 Insert ordered
	btree_insert_data(&root, "elk", ft_strcmp);
	btree_insert_data(&root, "cat", ft_strcmp);
	btree_insert_data(&root, "dog", ft_strcmp);
	btree_insert_data(&root, "ant", ft_strcmp);
	btree_insert_data(&root, "fox", ft_strcmp);
	btree_insert_data(&root, "gnu", ft_strcmp);
	btree_insert_data(&root, "bee", ft_strcmp);
	printf("Infix traversal (should be sorted): ");
	btree_apply_infix(root, &print_item);
	printf("\n\n");

	// ex05 Binary search
	char *find = "cat";
	char *result = (char *)btree_search_item(root, find, ft_strcmp);
	result ? printf("Found: %s\n", result) : printf("Not found: %s\n", find);
	find = "ray";
	result = (char *)btree_search_item(root, find, ft_strcmp);
	result ? printf("Found: %s\n\n", result) : printf("Not found: %s\n\n", find);

	// ex06 Tree Depth
	printf("Depth: %d\n", btree_level_count(root));

	// ex07 Apply function conditional with level
	btree_apply_by_level(root, print_node);
	free_tree(root);
	return (0);
}
