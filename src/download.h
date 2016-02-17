#ifndef DOWNLOAD_H_INCLUDED
#define DOWNLOAD_H_INCLUDED

void customDownload();
void getData(char *filenamePrefix, char *fileType, char *url);
void getDataCustom(char *filename, char *url);
void genFileName(char *prefix, char *type, char *output);

#endif
