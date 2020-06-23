/*
// Sun Jun 21 14:27:37 WIB 2020
// Tue Jun  9 17:46:47 WIB 2020
 */

// adjust DELAY and akunGitHub
#define  DELAY 8
#define  akunGitHub "WillySand"
#include "p00.h"
#include <pthread.h>
#include <time.h> 
char*    progs[]={P01, P02, P03};
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
	//printf("Myshare.entry %d\n",mymap->entry);
	//printf("Myshare.state %d\n",mymap->state);
	//printf("Myshare.mutexctr %d\n",mymap->mutexctr);
	//printf("Myshare.usrinfo.akun %s\n",mymap->progs->akun);
	//printf("Myshare.usrinfo.stamp %d\n",mymap->progs->stamp);
	
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
    entry=getpid()-getppid();
	return entry;
}
const char* getState(){
	if (mymap->state==CLOSED){
		return "CLOSED";
	}else if (mymap->state==OPEN){
		return "OPEN";
	}
	return "NOT WORKING";
}
void display(int entry) {
    // display an entry of MMAP. Eg.
    // akunGH2[progs[03] TIME[18] MUTEX[05] MMAP[OPEN] [akunGH1][akunGH3][akunGH0][akunGH2]]
	printf("%s[progs[%d] TIME[%d] MUTEX[%d] MMAP[%s] [%s][%s][%s][%s]]\n",akunGitHub, getEntry() ,getDuration(),999, getState(),"AAA","BBB","CCC","DDD");
}

void putInfo(char* akun, int entry) {
   strcpy(mymap->progs[entry].akun,akun);
}

void checkOpen(void) {
    if (mymap == MAP_FAILED | mymap == NULL | mymap-> state == CLOSED) {
      exit(1);
    }
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
int main(void) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myprint(akunGitHub, tmpStr);
    int boss=init();
    checkOpen();
	pid_t ids[12];
	pid_t thisPid;
	/*sem_t *semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);

	if (semaphore == SEM_FAILED) {
		perror("sem_open(3) error");
		sem_unlink(SEM_NAME); 
		exit(EXIT_FAILURE);
	}*/
	char child[5]=P01;
	char num;
	for (int ii = 1; ii < 4; ii++) {
		if ((ids[ii] = fork()) < 0) {
			perror("fork(2) failed");
			exit(EXIT_FAILURE);
		} else if (ids[ii] == 0) {
			
			child[3]='0'+ii/10;
			
			child[4]='0'+ii%10;
			
			if (execl(child, child, NULL) < 0) {
				perror("execl(2) failed");
				exit(EXIT_FAILURE);
			}
		}else{
			
		}
   }
	//putInfo("TELATGANG",0);
	sleep (DELAY);
	display(0);
	//
	delay(3);
    myprint(akunGitHub, "BYEBYE =====  ===== =====");
	delay(3);
}

