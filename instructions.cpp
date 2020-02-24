#include "instructions.h"

using namespace std;

void print_instructions()
{
	cout << "availible commands:\n"<<
			"add\t\tremove\n"<<
			"edit\t\tget\n"<<
			"display_range\tdisplay_all\n"<<
			"clear\t\texit\n";
	return;
}

void clear()
{
	for(int i=0 ; i<100; i++)
		cout<<"\n";
	return;
}
