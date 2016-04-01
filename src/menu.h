#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct{
	const char **alts;
	int nAlts;
	int highlighted;
}MENU_TYPE;

void mainMenu();
void downloadMenu();
void scheduleMenu();
void rmDateMenu();

#endif
