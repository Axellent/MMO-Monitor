#include <curses.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "schedule.h"

void waitForDate(struct tm date);
void mallocDate();

static struct tm *schedule;
static int nDates = 0;

void addScheduleDate(){
	time_t currTime;

	mallocDate();
	time(&currTime);
	schedule[nDates] = *localtime(&currTime);

	clear();
	printw("Enter date to add to schedule.\nFormat : YYYY-MM-DD HH:MM : ");
	scanw("%d-%d-%d %d:%d", &schedule[nDates].tm_year, &schedule[nDates].tm_mon, &schedule[nDates].tm_mday, &schedule[nDates].tm_hour, &schedule[nDates].tm_min);

	schedule[nDates].tm_year -= 1900;
	schedule[nDates].tm_mon -= 1;
	schedule[nDates].tm_sec = 0;
	nDates++;

	printScheduleFrom(nDates - 1);
	getch();
}

void rmScheduleDate(int i){
	if(i < 0){
		return;
	}

	for(i; i < nDates - 1; i++){
		schedule[i] = schedule[i+1];
	}
	nDates--;
	printw("Date succesfully removed from schedule");
	getch();
}

void printSchedule(){
	int i;

	if(nDates == 0){
		printw("There are no scheduled dates for downloading\n");
	}

	for(i = 0; i < nDates; i++){
		printw("Data collection has been scheduled to run : %d. %d-%d-%d %d:%d\n", i + 1, schedule[i].tm_year + 1900, schedule[i].tm_mon + 1, schedule[i].tm_mday,
				schedule[i].tm_hour, schedule[i].tm_min);
	}
}

void printScheduleFrom(int i){
	if(nDates == 0){
		printw("There are no scheduled dates for downloading\n");
	}

	for(i; i < nDates; i++){
		printw("Data collection has been scheduled to run : %d. %d-%d-%d %d:%d\n", i + 1, schedule[i].tm_year + 1900, schedule[i].tm_mon + 1, schedule[i].tm_mday,
				schedule[i].tm_hour, schedule[i].tm_min);
	}
}

void scheduleDownload(char *game){
	int i = 0;

	if(nDates <= 0){
		printw("There are no scheduled dates for downloading\n");
		return;
	}

	for(i = 0; i < nDates; i++){
		printScheduleFrom(i);
		refresh();
		waitForDate(schedule[i]);
		printw("Running scheduled download NO%d...\n", i+1);

		if(strcmp(game, "Guild Wars 2") == 0){
			getGW2ExchangeRates();
			getTopGW2CraftingMatPrices();
		}
		else if(strcmp(game, "Runescape") == 0){
			getBondPrice();
			//getTopRunescapeCraftingMatPrices();
		}

		printw("Download complete\n");
	}
	nDates = 0;
	printw("\nData collection finished\n");
}

void waitForDate(struct tm date){
	time_t currTime;
	bool waiting = true;
	double secondsDiff;

	while(waiting){
		time(&currTime);
		secondsDiff = difftime(mktime(&date), currTime);

		if(secondsDiff <= 0){
			waiting = false;
		}
	}
}

void mallocDate(){
	struct tm *newSchedule;
	int i = 0;

	if(nDates <= 0){
		schedule = (struct tm*)malloc(1 * sizeof(struct tm));
		return;
	}
	newSchedule = (struct tm*)malloc(1 * (nDates + 1) * sizeof(struct tm));
	
	for(i = 0; i < nDates; i++){
		newSchedule[i] = schedule[i];
	}
	free(schedule);
	schedule = newSchedule;
}

struct tm *getSchedule(){
	return schedule;
}

int getnDates(){
	return nDates;
}
