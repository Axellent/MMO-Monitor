#include <time.h>
#include <stdio.h>
#include <string.h>
#include "download.h"

void customDownload(){
	char filename[100], url[1000];

	clear();
	printw("Enter custom download parameters.\nSyntax: filename url: ");
	scanw("%100s %100s", filename, url);
	printw("%s %s", filename, url);
	getch();

	getDataCustom(filename, url);
}

void getData(char *filenamePrefix, char *fileType, char *url){
	char filename[100], command[1100];
	FILE *stream;

	genFileName(filenamePrefix, fileType, filename);
	sprintf(command, "wget -O %s %s", filename, url);

	stream = popen(command, "w");
	pclose(stream);
}

void getDataCustom(char *filename, char *url){
	char command[1100];
	FILE *stream;

	sprintf(command, "wget -O %s %s", filename, url);

	stream = popen(command, "w");
	pclose(stream);
}

void genFileName(char *prefix, char *type, char *output){
	time_t rawtime;
	struct tm * timeinfo;
	char hour[2], min[2];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if(timeinfo->tm_hour < 10){
		sprintf(hour, "0%d", timeinfo->tm_hour);
	}
	else{
		sprintf(hour, "%d", timeinfo->tm_hour);
	}
	if(timeinfo->tm_min < 10){
		sprintf(min, "0%d", timeinfo->tm_min);
	}
	else{
		sprintf(min, "%d", timeinfo->tm_min);
	}
	sprintf(output, "%s_%d-%d-%d-%s-%s%s", prefix, timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, hour, min, type);
}
