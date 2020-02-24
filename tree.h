//Aaron Dawson, cs 163, prog 4
//this program uses concepts that we have leared to create
//a binary search tree that can add, remove, edit, display 
//range, and display all.

#ifndef fstream
#include <fstream>
#endif

#ifndef cstring
#include <cstring>
#endif

#ifndef iostream
#include <iostream>
#endif

const int KEYWORD = 100;

//the stucture for holding my data
struct study_item
{
	char * keyword;
	char * description;
	int chapter;
	int page;
	bool study_more;
};


//node structure used by the tree class
struct node
{
	study_item  data;
	node * left;
	node * right;
};


//my tree class structure
class tree
{
	public:
		tree();
		~tree();
		int add();// adds an entry into the tree
		int remove(char * keyword);//removes an entire entry of the keyword being looked up
		int edit(char * keyword, char * description);//edits the description of a matching keyword.
		int get(char * keyword, study_item & to_fill); //fills the container with the information for a found keyword.
		int display_range(char * min, char * max); //displays all keywords within a range specified
		int display_all(); //displays all keywords in sorted order


		//the capital 'R' in front stands for recursive
	private:
		node * root; //private data member that holds the root of the tree.
		int add_node(node * & root, node * to_add);	//adds the node given in the second argument to the tree
		int Rdisplay_all(node * root); //displays all keywords.
		int delete_tree(node * & root);	//deletes the whole tree, deallocates everything.  used by the deconstructore
		int Rremove(node * &root, node * &prev, char * keyword); //removes a node from tree as specified by the keyword given
		int Redit(node * root, char * keyword, char * description); //edits the description of the node specified by the keyword
		int Rget(node * root, char * keyword, study_item & to_fill); //fills the second argument with the data found at the node that matches the keyword
		int Rdisplay_range(node * root , char * min, char * max); //displays all keyword within the range given by max and min values
		void delete_node(node * root); // to get rid of one node, deallocating what needs to be.
};

int fill_node(node * & to_fill); //fills a node container with all the stuff a node contains. gets it from the user.
