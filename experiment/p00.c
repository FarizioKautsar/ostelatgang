/*
// Sun Jun 21 14:27:37 WIB 2020
// Tue Jun  9 17:46:47 WIB 2020
 */

// adjust DELAY and akunGitHub
#define  DELAY 4
#define  akunGitHub "akunGH0"
#include "p00.h"

char*    progs[]={P01, P02};
myshare* mymap;
time_t standardTime; //variable time, global var
char tmpStr[256]={};  // a temporary string.
sem_t *mutex;
usrinfo akun1={akunGitHub, 0};
int entryIndex=0;
char *timeStandard=NULL;



int init(void) {
    int ssize=sizeof(myshare);
    int fd   =open(SHAREMEM, MYFLAGS, CHMOD);
    fchmod   (fd, CHMOD);
    ftruncate(fd, ssize);
    mymap=mmap(NULL, ssize, MYPROTECTION, MYVISIBILITY, fd, 0);
    close(fd);

    mymap->entry=MAXPROGS;
    mymap->state=OPEN;
    mutex=&(mymap->mutex);
    mymap->mutexctr=0;
    int mutexCtr = mymap->mutexctr;
    sem_init (mutex, 0, 1);
    standardTime=time(NULL);//set waktu sekarang
    sprintf(tmpStr, "%d", (int) standardTime);//translate to string
    timeStandard=tmpStr;
    for (int i = 0; i<2 ; i++){
        if (fork () == 0){
            execlp(*(progs+i),tmpStr, NULL);
        }
    }

    //  more INIT STUFFs...
    //  more INIT STUFFs...
    //  more INIT STUFFs...
    return BOSS;
}

void myprint(char* str1, char* str2) {
    printf("%s[%s]\n", str1, str2);
    // blah blah blah
    // blah blah blah
    // blah blah blah
}

int getEntry(void) {
    int entry;
    sem_wait(mutex);
    (mymap->mutexctr)+=1;
    int tempEntry = mymap->entry;
    if (tempEntry != 0){
        entry = MAXPROGS - (mymap->entry);//get index
        mymap->entry = tempEntry-1;//set remining entry

        mymap->progs[entry]=(usrinfo) {"", 1};//give dummy starter
        akun1.stamp=1;
        sem_post(mutex);
    } else {
        printf("Sorry, full load");
        exit(1);
    }
    return entry;
}

void display(int entry) {
    sem_wait(mutex);
    int tempIdentifier = MAXPROGS - (mymap->entry);//get last index
    // printf("last sisa entry %d", mymap->entry);
    (mymap->mutexctr)+=1;
    akun1.stamp=(akun1.stamp)+1;
    mymap->progs[entry].stamp=(akun1.stamp);
    int stamp=mymap->progs[entry].stamp;
    char* state = mymap->state==127? "CLOSED" : "OPEN";
    // printf("%d oajawa %s\n", (int)(time(NULL)-atoi(timeStandard)), timeStandard);
    printf("%s [progs[%2.2d] TIME[%2.2d] MUTEX[%2.2d] MMAP[%s] ", akunGitHub, entryIndex, ((int)(time(NULL)-atoi(timeStandard))), stamp, state);
    for (int i=0; i<tempIdentifier; i++){
        // char* gitHubUser = mymap->progs[i].akun;
        // if (gitHubUser==""){
        //     printf("[%s]", (mymap->progs[entry].akun));    
        // }
        printf("[%s]", (mymap->progs[i].akun));
    }
    printf("]\n");
    sem_post(mutex);
    // eg. akunGH2[progs[03] TIME[18] MUTEX[05] MMAP[OPEN] [akunGH1][akunGH3][akunGH0][akunGH2]]
}

void putInfo(char* akun, int entry) {
    sem_wait(mutex);
    (mymap->mutexctr)+=1;

    akun1.stamp=(akun1.stamp)+1;
    mymap->progs[entry].stamp=(akun1.stamp);
    mymap->progs[entry]=akun1;
    sem_post(mutex);
    // put "akunGitHub" into akun[] array (MMAP)
}

void checkOpen(void) {
    // exit if MMAP is closed.
    if (mymap->state==CLOSED){
        printf("CLOSED, BYE BYE ==== ====\n");
        exit(1);
    }
}

int main(void) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myprint(akunGitHub, tmpStr);
    int boss=init();
    sleep (DELAY);
    checkOpen();
    entryIndex = getEntry();
    display(entryIndex);
    putInfo(akun1.akun, entryIndex);
    sleep (DELAY);
    display(entryIndex);
    display(entryIndex);
    // blah... blah... blah...
    // blah... blah... blah...
    // blah... blah... blah...
    sleep (DELAY);
    mymap->state=CLOSED;
    myprint(akunGitHub, "BYEBYE =====  ===== =====");
    if (boss==BOSS){
        return 0;
    }
}

