#include "ft_btree.h"

static void	apply_level(t_btree *root, int cur_lvl, int target_lvl,
	void (*applyf)(void *, int, int), int *is_first)
{
	if (!root)
		return ;
	if (cur_lvl == target_lvl)
	{
		applyf(root->item, cur_lvl, *is_first);
		*is_first = 0;
	}
	else
	{
		apply_level(root->left, cur_lvl + 1, target_lvl, applyf, is_first);
		apply_level(root->right, cur_lvl + 1, target_lvl, applyf, is_first);
	}
}

void	btree_apply_by_level(t_btree *root,
	void (*applyf)(void *item, int current_level, int is_first_elem))
{
	int	size;
	int	lvl;
	int	is_first;

	size = btree_level_count(root);
	lvl = 0;
	while (lvl < size)
	{
		is_first = 1;
		apply_level(root, 0, lvl, applyf, &is_first);
		lvl++;
	}
}
