//ncTest.c
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t fromBash(char* bashStr, int y, int x, bool chk4play){
	
	FILE *fp;

	char path[1035];
	/* Open the command for reading. */
	fp = popen(bashStr, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		if(chk4play == true){
			if(strcmp(path,"   playing")<=0){
				mvprintw(y,x,"%||");
			}
			else{
				mvprintw(y,x,"%>");
			}
		}
		else {
			mvprintw(y,x,path);
		}
//		mvprintw(3,0,"%d",strcmp(path, "   playing"));
		y++;
	}
	pclose(fp);
	size_t len = strlen(path);
	return len;
}




int main(int argc, char *argv[]) {
	
	
	initscr(); // Initialize the window
	noecho(); // Don't echo any keypresses
	curs_set(FALSE); // Don't display a cursor
	
	time_t timer;
    char buffer[26];
    char batstr[100];
	struct tm* tm_info;
	while(1){

		clear();
		time(&timer);
		tm_info = localtime(&timer);
		
	    size_t trackLen = fromBash("~/./gitstuff/SpotifyControl/SpotifyControl info | grep 'Track' | cut -f2 -d':'", 0, 18,false);
		int totTrackLen = (int)trackLen + 17;
		int totTrackLenAndBy = totTrackLen + 1;
	    size_t artLen = fromBash("~/./gitstuff/SpotifyControl/SpotifyControl info | grep 'Artist' | cut -f2 -d':'", 0, totTrackLenAndBy,false);
	    size_t playLen = fromBash("~/./gitstuff/SpotifyControl/SpotifyControl info | grep 'Player' | cut -f2 -d':'", 0, 18,true);
		int allLenMusic = totTrackLenAndBy + (int)artLen;	
	    size_t batLen = fromBash("pmset -g batt | egrep '([0-9]+\%).*' -o --colour=auto | cut -f1 -d';'", 0, allLenMusic +2,false);
		strftime(buffer, 26, "%d-%m-%Y %H:%M", tm_info);
		puts(buffer);
		mvprintw(0,0,buffer);
		mvprintw(0,allLenMusic + 5,"%%");
		mvprintw(0,totTrackLen," by ");
		mvprintw(0,allLenMusic,"|");
		refresh();
		sleep(1);

	}
	endwin();
}
