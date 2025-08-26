#include <stdio.h>
#include <string.h>
#include "ft_btree.h"

void	print_item(void *item)
{
	printf("%s ", (char *)item);
}

int ft_strcmp(void *a, void *b)
{
	return strcmp((const char *)a, (const char *)b);
}

int	main(void)
{
	int a = '2', b = '1', c = '6', d = '4', e = '5', f = '3';

	// Create nodes
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
	printf("\n");

	// Reset tree (leaks)
	root = NULL;

	btree_insert_data(&root, "dog", ft_strcmp);
	btree_insert_data(&root, "cat", ft_strcmp);
	btree_insert_data(&root, "elk", ft_strcmp);
	btree_insert_data(&root, "ant", ft_strcmp);
	btree_insert_data(&root, "bee", ft_strcmp);

	printf("Infix traversal (should be sorted): ");
	btree_apply_infix(root, &print_item);
	printf("\n");
	return (0);
}