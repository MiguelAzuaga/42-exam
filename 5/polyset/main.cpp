// Assigment name: Polyset
// Expected File: searchable_array_bag.cpp, searchable_array_bag.hpp,
// searchable_tree_bag.cpp, searchable_tree_bag.hpp, set.cpp, set.hpp

// You will find in this directory some classes:
// - bag: an abstract class representing a bag
// - searchable_bag: an abstract class representing a bag with the ability to
// 	search in it.
// - array_bag: an implementation of a bag with an array an underlying data
// 	structure.
// - tree_bag: an implementation of a bag with a binary search tree as underlying
// 	data structure.

// If you don't know what is a set or a bag (shame!) you can read the attached
// file shame.en.txt

// First Part:
// Since a bag without a searching function isn't very useful, implement two
// classes searchable_array_bag and searchable_tree_bag, that will inherit from
// array_bag and tree_bag and implement the searchable bag abstract class.

// Second Part:
// Implement the class set that will wrap a searchable_bag and turn it into a set.
// You will find in this dir a main that must compile with your code.
// All classes should be under orthodox canonical form. Don't forget the const.

#include "searchable_bag.hpp"

#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc == 1)
		return 1;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;

	for (int i = 1; i < argc; i++) {
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();
	a->print();

	for (int i = 1; i < argc; i++) {
		std::cout << t->has(atoi(argv[i])) << std::endl;
		std::cout << a->has(atoi(argv[i])) << std::endl;
		std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
		std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	}

	t->clear();
	a->clear();

	const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
	tmp.print();
	tmp.has(1);

	set sa(*a);
	set st(*t);
	for (int i = 1; i < argc; i++) {
		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));

		sa.has(atoi(argv[i]));
		sa.print();
		sa.get_bag().print();
		st.print();
		sa.clear();
		int values[] = {1, 2, 3, 4};
		sa.insert(values, 4);
		std::cout << std::endl;
	}
	delete a;
	delete t;
	return 0;
}
