#ifndef __SOUNDBLASTEROS__SHELL__
#define __SOUNDBLASTEROS__SHELL__

char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);

void parser(char * s, int size);
void beep();
void clear();
int strcmp(const char * str1, const char * str2);
int strlen(const char * s);
void str0(char * s);
void piano();

int keyToNotefreq(char key);
int isValidNote(char key);
void playSong();

void shell();
void printOsName();
void help();
void sleep(int time);
int getSeconds();

#endif
