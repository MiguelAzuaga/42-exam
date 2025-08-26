#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
	int (*cmpf)(void *, void *))
{
	void	*res;

	if (!root)
		return (NULL);
	res = btree_search_item(root->left, data_ref, cmpf);
	if (res)
		return (res);
	if (cmpf(data_ref, root->item) == 0)
		return (root->item);
	return (btree_search_item(root->right, data_ref, cmpf));
}
