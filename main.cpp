//Aaron Dawson, cs 163, prog 4
//the goal of this program is to create a binary search
//tree and impliment functions to add a node, remove a
//node, edit a nodes description, get a node's data, get
//all keywords within a range, and display all keywords.

#include "tree.h"
#include "instructions.h"
using namespace std;

int main()
{
	char command[KEYWORD];
	char answer[KEYWORD];
	char answer2[KEYWORD];	
	char description[KEYWORD];
	int int_answer;
	int length = 0;

	tree my_tree;
	study_item to_fill;

	print_instructions();
	cout << "\nprog4 $";
	
	while(strcmp(command, "exit") != 0){
		cin.get(command, KEYWORD, '\n');
		cin.ignore(KEYWORD, '\n');

		if(strcmp(command, "add") == 0){
			if(!my_tree.add())
				cout << "could not add that item to the tree\n";
		}
	
		else if(strcmp(command, "remove") == 0){
			cout << "which item you like to remove?\n";
			cin.get(answer, KEYWORD, '\n');
			cin.ignore(100, '\n');
			length = strlen(answer);
			char sized[length+1];
			strcpy(sized, answer);

			if(!my_tree.remove(sized))
				cout << "no match found, nothing removed\n";
		}
	
		else if(strcmp(command, "edit") == 0){	
			cout << "what would you like to edit(keyword)? ";
			cin.get(answer, KEYWORD, '\n');
			cin.ignore(100,'\n');
			cout << "what would you like the new description to be? ";
			cin.get(description, KEYWORD, '\n');
			cin.ignore(100,'\n');

			if(!my_tree.edit(answer, description))
				cout << "no match found, could not edit\n";
		}

		else if(strcmp(command, "get") == 0){
			cout << "what item would you like more information on?";
			cin.get(answer, KEYWORD, '\n');
			cin.ignore(100, '\n');

			if(!my_tree.get(answer, to_fill))
				cout << "no match found\n";
			else{	
				cout << to_fill.keyword << endl 
					<< to_fill.description << endl 
					<< to_fill.chapter << endl 
					<< to_fill.page << endl;
				if(!to_fill.study_more)
					cout << "no more study needed\n";
				else
					cout << "more study needed";
			}
		}
		
		else if(strcmp(command, "display_range") == 0){	
			cout << "what is the smallest keyword in your range?";
			cin.get(answer, KEYWORD, '\n');
			cin.ignore(100, '\n');

			cout << "what is the largest keyword in your range?";
			cin.get(answer2, KEYWORD, '\n');
			cin.ignore(100, '\n');
	
			cout << "here are all the keywords within that range:\n";
			my_tree.display_range(answer, answer2);
		}
	
		else if(strcmp(command, "display_all") == 0){
			if(!my_tree.display_all())
				cout << "there was nothing in the tree\n";
		}

		else if(strcmp(command, "clear") == 0)
			clear();

		else if(strcmp(command, "help") == 0)
			print_instructions();

		else if(strcmp(command, "exit") == 0)
			return 0;
				
		else
			cout << "command '" << command << "' not found\n";
		
		cout << "\nprog4 $";
	}
	return 0;
}
