/*
// Sun Jun 21 14:27:37 WIB 2020
// Tue Jun  9 17:46:47 WIB 2020
 */

// adjust DELAY and akunGitHub
#define  DELAY 8
#define  akunGitHub "WillySand"
#include "p00.h"
char*    progs[]={P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11};
myshare* mymap;
time_t seconds;
int init(void) {
    int ssize=sizeof(myshare);
    int fd   =open(SHAREMEM, MYFLAGS, CHMOD);
	seconds = time(NULL);

    fchmod   (fd, CHMOD);
    ftruncate(fd, ssize);
    mymap=mmap(NULL, ssize, MYPROTECTION, MYVISIBILITY, fd, 0);
    close(fd);
    //  more INIT STUFFs...
    //  more INIT STUFFs...
    //  more INIT STUFFs...
    return BOSS;
}

char tmpStr[256]={};  // a temporary string.
void myprint(char* str1, char* str2) {
    printf("%s[%s]\n", str1, str2);
    // blah blah blah
    // blah blah blah
    // blah blah blah
}
int getDuration(void){
	time_t secondsNow;
	secondsNow = time(NULL);
	return (int)(secondsNow-seconds);
}
int getEntry(void) {
    int entry;
    // get an entry number
    return entry;
}

void display(int entry) {
    // display an entry of MMAP. Eg.
    // akunGH2[progs[03] TIME[18] MUTEX[05] MMAP[OPEN] [akunGH1][akunGH3][akunGH0][akunGH2]]
	printf("%s[progs[%d] TIME[%d] MUTEX[%d] MMAP[%s] [%s][%s][%s][%s]]\n",akunGitHub, 999 ,getDuration(),999, "CLOPEN","AAA","BBB","CCC","DDD");
}

void putInfo(char* akun, int entry) {
    // put "akunGitHub" into akun[] array (MMAP)
}

void checkOpen(void) {
    // exit if MMAP is closed.
}

int main(void) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myprint(akunGitHub, tmpStr);
    int boss=init();
    checkOpen();
    sleep (DELAY);
	display(0);
    // blah... blah... blah...
    // blah... blah... blah...
    // blah... blah... blah...
    myprint(akunGitHub, "BYEBYE =====  ===== =====");
}

