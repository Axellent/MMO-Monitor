#include <curses.h>
#include "menu.h"

int main(){
	initscr();
	mainMenu();
	endwin();
}
