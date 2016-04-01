#include <curses.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "schedule.h"
#include "tradingpost.h"
#include "grandexchange.h"

MENU_TYPE initMenu(const char **alts, int nAlts, int highlighted);
int menuControl(MENU_TYPE menu, char *headerText);
void printMenu(MENU_TYPE menu, char *headerText);
void printMainManual();

void mainMenu(){
	bool inMenu = true;
	int selected, nAlts = 5;
	const char *alts[nAlts];
	MENU_TYPE menu;

	alts[0] = "1. Download MMO data";
	alts[1] = "2. Schedule Download";
	alts[2] = "3. Manual";
	alts[3] = "4. About";
	alts[4] = "5. Exit";
	menu = initMenu(alts, nAlts, 0);
	
	while(inMenu){
		selected = menuControl(menu, "Welcome to the MMO-monitor (Beta)");
		if(selected == 1){
			downloadMenu();
		}
		else if(selected == 2){
			scheduleMenu();
		}
		else if(selected == 3){
			printMainManual();
		}
		else if(selected == 4){
		}
		else if(selected == 5){
			inMenu = false;
		}
	}
}

void downloadMenu(){
	bool inMenu = true;
	int selected, nAlts = 5;
	const char *alts[nAlts];
	MENU_TYPE menu;

	alts[0] = "1. Download Guild Wars 2 data";
	alts[1] = "2. Download Runescape data";
	alts[2] = "3. Custom download";
	alts[3] = "4. Downloading manual";
	alts[4] = "5. Back";
	menu = initMenu(alts, nAlts, 0);
	
	while(inMenu){
		selected = menuControl(menu, "Download Menu");
		if(selected == 1){
			getGW2ExchangeRates();
			getTopGW2CraftingMatPrices();
		}
		else if(selected == 2){
			getBondPrice();
			getTopRunescapeCraftingMatPrices();
			getHistoricalBondPrices();
			getHistoricalCraftingMatPrices();
		}
		else if(selected == 3){
			customDownload();
		}
		else if(selected == 4){
		}
		else if(selected == 5){
			inMenu = false;
		}
	}
}

void scheduleMenu(){
	bool inMenu = true;
	int selected, nAlts = 7;
	const char *alts[nAlts];
	MENU_TYPE menu;

	alts[0] = "1. Add schedule date";
	alts[1] = "2. Remove schedule date";
	alts[2] = "3. View schedule";
	alts[3] = "4. Schedule downloading of Guild Wars 2 data";
	alts[4] = "5. Schedule downloading of Runescape data";
	alts[5] = "6. Scheduling manual";
	alts[6] = "7. Back";
	menu = initMenu(alts, nAlts, 0);
	
	while(inMenu){
		selected = menuControl(menu, "Schedule Menu");

		if(selected == 1){
			addScheduleDate();
		}
		else if(selected == 2){
			rmDateMenu();
		}
		else if(selected == 3){
			clear();
			printSchedule();
			getch();
		}
		else if(selected == 4){
			clear();
			scheduleDownload("Guild Wars 2");
		}
		else if(selected == 5){
			clear();
			scheduleDownload("Runescape");
			getch();
		}
		else if(selected == 6){
		}
		else if(selected == 7){
			inMenu = false;
		}
	}
}

void rmDateMenu(){
	struct tm *schedule = getSchedule();
	int i, selected, nAlts = getnDates();
	const char *alts[nAlts+1];
	char buffers[10][100];
	MENU_TYPE menu;

	if(nAlts == 0){
		printw("There are no scheduled dates for downloading\n");
		getch();
		return;
	}

	for(i = 0; i < nAlts; i++){
		sprintf(buffers[i], "%d. %d-%d-%d %d:%d", i + 1, schedule[i].tm_year + 1900, schedule[i].tm_mon + 1, schedule[i].tm_mday,
				schedule[i].tm_hour, schedule[i].tm_min);
		alts[i] = buffers[i];
	}
	sprintf(buffers[nAlts], "%d. Back", i + 1);
	alts[nAlts] = buffers[nAlts];
	nAlts++;

	menu = initMenu(alts, nAlts, 0);

	selected = menuControl(menu, "Remove Date Menu");

	if(selected == nAlts){
		return;
	}
	else{
		rmScheduleDate(selected - 1);
		rmDateMenu();
	}
}

MENU_TYPE initMenu(const char **alts, int nAlts, int highlighted){
	MENU_TYPE menu;
	menu.alts = alts;
	menu.nAlts = nAlts;
	menu.highlighted = highlighted;

	return menu;
}

int menuControl(MENU_TYPE menu, char *headerText){
	bool selected = false;
	char selection;

	while(!selected){
		clear();
		printMenu(menu, headerText);
		selection = getch();
		
		switch(selection){
			case 'w': case 'W':
				if(menu.highlighted > 0){
					menu.highlighted--;
				}
				break;
			case 's': case 'S':
				if(menu.highlighted < menu.nAlts - 1){
					menu.highlighted++;
				}
				break;
			case '1':
				menu.highlighted = 0;
				break;
			case '2':
				menu.highlighted = 1;
				break;
			case '3':
				menu.highlighted = 2;
				break;
			case '4':
				menu.highlighted = 3;
				break;
			case '5':
				menu.highlighted = 4;
				break;
			case '6':
				menu.highlighted = 5;
				break;
			case '7':
				menu.highlighted = 6;
				break;
			case '8':
				menu.highlighted = 7;
				break;
			case '9':
				menu.highlighted = 8;
				break;
			case '\n':
				selected = true;
				break;
			default:
				break;
		}
	}
	clear();
	return menu.highlighted + 1;
}

bool dateMenuControl(MENU_TYPE menu, char *headerText){
	bool done = false;
	char selection;

	while(!done){
		clear();
		printMenu(menu, headerText);
		selection = getch();

		switch(selection){
			case 'w': case 'W':
				if(menu.highlighted > 0){
					menu.highlighted++;
				}
				break;
			case 's': case 'S':
				if(menu.highlighted < menu.nAlts - 1){
					menu.highlighted--;
				}
				break;
			case '\n':
				done = true;
				break;
		}
	}
	return done;
}

void printMenu(MENU_TYPE menu, char *headerText){
	int i;
	
	if(strlen(headerText) > 0){
		printw("%s\n", headerText);
		printw("=================================\n");
	}

	for(i = 0; i < menu.nAlts; i++){
		if(i == menu.highlighted){
			printw("> %s\n", menu.alts[i]);
		}
		else{
			printw("  %s\n", menu.alts[i]);
		}
	}
}

void printMainManual(){
	clear();
	printw("Welcome to the main manual page for MMO Monitor\n"
			"================================================\n"
			"The main goal of this application is to enable automatic downloading of MMO data, at any pre-defined time.\n\n"
			"Press any key to continue");
	getch();
}
