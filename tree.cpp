//Aaron Dawson, cs163, prog 4
//Tree class implimentation
//note: the tree classe's wrapper functions and their
//respective recusive calls are placed next to each other

#include "tree.h"

using namespace std;

// tree constructor 
tree::tree()
{

	char ch;
	int integer;
	char temp_array[100];
	int i = 0;
	int index;

	root = NULL;

	ifstream in_file;
	in_file.open("data.txt");
	if(in_file)
	{	
		do	
		{
			//make a new node to fill with data
			node * temp = new node;
			temp->left = NULL;
			temp->right = NULL;

			//fill with Keyword
			in_file.get(temp_array, KEYWORD, '\n');
			in_file.ignore(100, '\n');
			i = strlen(temp_array);
			temp->data.keyword = new char[i+1];
			strcpy(temp->data.keyword, temp_array);	

			//fill with description
			in_file.get(temp_array, KEYWORD, '\n');
			in_file.ignore(100, '\n');
			i = strlen(temp_array);
			temp->data.description = new char[i+1];
			strcpy(temp->data.description, temp_array);	

			//fill with chapter number
			in_file >> integer;
			in_file.ignore(100, '\n');
			temp->data.chapter = integer;

			//fill with page number
			in_file >> integer;
			in_file.ignore(100, '\n');
			temp->data.page = integer;

			//boolean for if more study is needed
			in_file.get(ch);
			if(ch == 'y')
				temp->data.study_more = true; else
				temp->data.study_more = false;

			if(!root)
				root = temp;
			else
				add_node(root, temp);
			
			in_file.get(ch);
		}while(!in_file.eof());
	}

	in_file.close();
	in_file.clear();
}


//deconstructor
tree::~tree()
{
	delete_tree(root);
	root = NULL;
}


//wrapper function for adding a node
int tree::add()
{
	node * temp = new node;
	fill_node(temp);
	add_node(root, temp);
	return 1;
}

//recursive call for adding a node
int tree::add_node(node * & root, node * to_add)
{
	if(!root)
	{
		root = to_add;
		root->left=NULL;
		root->right=NULL;
		return 1;
	}
	if(strcmp(root->data.keyword, to_add->data.keyword) > 0)
		return add_node(root->left, to_add);
	else
		return add_node(root->right, to_add);
}


//wrapper function for removing a node
int tree::remove(char * keyword)
{
	if(!Rremove(root, root, keyword))
		return 0;
	return 1;
}

//recursive call for removing a node
int tree::Rremove(node * &current_root, node * &prev, char * keyword)
{
	if(!current_root)
		return 0;	
	//check if the keyword is smaller
	if(strcmp(current_root->data.keyword, keyword) > 0)
		return	Rremove(current_root->left, current_root, keyword);
	//check if th keyword is larger
	if(strcmp(current_root->data.keyword, keyword) < 0)
		return	Rremove(current_root->right, current_root, keyword);	

	//to get past this point, there would have to be a match
	//***********************************************************
	
		node * left = current_root->left;
		node * right = current_root->right;
		node * to_delete = current_root;

		//no children
		if(!left && !right){
			if(current_root == prev)
				current_root = NULL;
			else{
				if(prev->right == to_delete)
					prev->right = NULL;
				if(prev->left == to_delete)
					prev->left = NULL;
			}
			delete_node(to_delete);
			return 1;
		}

		//left child is the only child
		else if(!right){
			if(current_root == prev)
				current_root = to_delete->left;
			else{
				if(prev->right == to_delete)
					prev->right = left;
				if(prev->left == to_delete)
					prev->left = left;
			}
			delete_node(to_delete);
			return 1;
		}

		//right child is the only child
		else if(!left){
			if(current_root == prev)
				current_root = to_delete->right;
			else{
				if(prev->right == to_delete)
					prev->right = right;
				if(prev->left == to_delete)
					prev->left = right;
			}
			delete_node(to_delete);
			return 1;
		}

		//the last thing it could be is both children
		//in which case, an in order successor needs to be found to replace to deleted node
		else{	
			node * temp_to_delete = current_root;	//hold onto the current root
			node * in_order = current_root;		//for holding the in order successor
			node * hold_right = current_root->right;//hold onto the right subtree of node to be deleted
			node * hold_left = current_root->left; 	//hold onto the left subtree of node to be deleted

			//find in order successor
			in_order = in_order->right;//first go ONE right
			node * last = in_order;
			while(in_order->left){ //then go as far left as possible
				last = in_order;
				in_order = in_order->left;
			}
			last->left = NULL;

			in_order->left = hold_left;//connects up the left subtree
			current_root = in_order;// make the in order successor the new current root

			//then go as far right as possible and connect up the node to be deleted's right subtree
			//to the in order successor's rightmost node's right pointer
			node * largest_val = in_order; //the largest value in the in_orders' right subtree
			while(largest_val->right){
				largest_val = largest_val->right;
			}
			largest_val->right = hold_right;

			temp_to_delete->right = NULL;
			temp_to_delete->left = NULL;
			delete_node(temp_to_delete);//lastly delete the previous current root
			return 1;
		}
}


//release all memory of the node given
void tree::delete_node(node * root)
{
	delete [] root->data.keyword;
	delete [] root->data.description;
	delete root;
}


//wrapper function to edit the decription of a node
int tree::edit(char * keyword, char * description)
{
	if(!Redit(root,keyword,description))
		return 0;
	return 1;
}


//recursive call to edit the decription of a node
int tree::Redit(node * root, char * keyword, char * description)
{
	if(!root)
		return 0;

	//match found
	if(strcmp(root->data.keyword, keyword) == 0)
	{
		delete [] root->data.description;
		int length = strlen(description);
		root->data.description = new char[length + 1];
		strcpy(root->data.description, description);
		return 1;	
	}

	//find match
	if(strcmp(root->data.keyword, keyword) > 0)
		return Redit(root->left, keyword, description);
	if(strcmp(root->data.keyword, keyword) < 0)
		return Redit(root->right, keyword, description);
	
	return 0;
}


//wrapper function for getting data back about a matching node
int tree::get(char * keyword, study_item & to_fill)
{
	if(!Rget(root,keyword,to_fill))
		return 0;	
	return 1;
}


//recursive function that fills "to_fill" with data once a keyword match is found
int tree::Rget(node * root, char * keyword, study_item & to_fill)
{
	if(!root)
		return 0;

	if(strcmp(root->data.keyword, keyword) == 0)
	{
		int length = strlen(keyword);
		to_fill.keyword = new char[length + 1];
		strcpy(to_fill.keyword, keyword);

		length = strlen(root->data.description);
		to_fill.description = new char [length + 1];
		strcpy(to_fill.description, root->data.description);

		to_fill.chapter = root->data.chapter;
		to_fill.page = root->data.page;
		to_fill.study_more = root->data.study_more;
		
		return 1;
	}	

	
	if(strcmp(root->data.keyword, keyword) > 0)
		return Rget(root->left, keyword, to_fill);
	if(strcmp(root->data.keyword, keyword) < 0)
		return Rget(root->right, keyword, to_fill);

	return 0;
}


//wrapper function for displaying all keywords within a range (in order)
int tree::display_range(char * min, char * max)
{
	if(!Rdisplay_range(root, min, max))
		return 0;
	return 1;
}


//recursive call for displaying all keywords within a range (in order)
int tree::Rdisplay_range(node * root, char * min, char * max)
{
	if(!root)
		return 0;
	else
	{
		Rdisplay_range(root->left, min, max);
		if(strcmp(root->data.keyword, min) >= 0 && strcmp(root->data.keyword, max) <= 0)
			cout << root->data.keyword << endl;	//only display the keyword if its between the min and max
		Rdisplay_range(root->right, min, max);
	}
	return 1;
}


//wrapper function for displaying all keywords (in order)
int tree::display_all()
{
	if(!Rdisplay_all(root))
		return 0;
	return 1;
}


//recursive call that displays all keywords (in order)
int tree::Rdisplay_all(node * root)
{
	if(!root)
		return 0;
	else
	{
		Rdisplay_all(root->left);
		cout << root->data.keyword << endl;
		Rdisplay_all(root->right);
	}
	return 1;
}


//this function is used by the deconstructor to deallocate the tree
int tree::delete_tree(node * & root)
{
	if(!root)
		return 0;

	//take care of your children before yourself
	delete_tree(root->left);
	root->left = NULL;
	delete_tree(root->right);
	root->right = NULL;

	//then take care of yourself
	delete_node(root);
	
	return 0;
}


//this function fills a node pointer with all the data needed in a node pointer
//this function is not a part of the tree class, and has no idea how the tree 
//class will store or use any data like this to uphold data abstraction.
int fill_node(node * & to_fill)
{
	char temp_array[KEYWORD];
	int int_array[KEYWORD];
	int length = 0;
	int i = 0;
	char yn = 'y';

	//fill in the data for keyword
	cout << "what keyword would you like to use for your study item? \n";
	cin.get(temp_array, KEYWORD, '\n');
	cin.ignore(KEYWORD, '\n');
	length = strlen(temp_array);	
	to_fill->data.keyword = new char[length + 1];
	strcpy(to_fill->data.keyword, temp_array);
	//head->data.keyword[length] = '\0';

	//fill in the data for descriptiond
	cout << "what is the description? \n";
	cin.get(temp_array, KEYWORD, '\n');
	cin.ignore(KEYWORD, '\n');
	length = strlen(temp_array);	
	to_fill->data.description = new char[length + 1];
	strcpy(to_fill->data.description, temp_array);
	//head->data.description[length] = '\0';

	//fill in the data for the chapter
	cout << "what chapter is it in?\n";
	cin >> to_fill->data.chapter;  //todo: add type checking
	cin.ignore(KEYWORD, '\n');

	//fill in the data for the pages
	cout << "what page is it on?\n";
	cin >> to_fill->data.page;		//todo: add type checking
	cin.ignore(KEYWORD, '\n');

	//fill in the data for studying more
	cout << "do you need to study more on this topic?\n";
	cin >> yn;
	cin.ignore(KEYWORD, '\n');

	if(yn == 'y' || yn == 'Y')
		to_fill->data.study_more = true;
	else
		to_fill->data.study_more = false;
	return 1;
}
