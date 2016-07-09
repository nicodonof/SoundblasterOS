#ifndef __SOUNDBLASTEROS__SYSCALL__
#define __SOUNDBLASTEROS__SYSCALL__

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void readSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void writeSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void clearSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void pianoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void boolkeySC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void getTimerSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void playTimeSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void stopsoundSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void playSoundOnlySC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void changeOctaveSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void clearBufferSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void createProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void playSoundNoVideoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void endProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void listProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void nextProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void randomSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void openMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void getMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void closeMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void sendMsgToQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void receiveMsgFromQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void drawLineSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void playSoundNoVideoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void printCharInPosSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void drawRecSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void drawTriangSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
#endif

