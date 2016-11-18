//ncTest.c
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	
	int x=0, y=0;
	int max_y = 0, max_x = 0;
	int next_x = 0;
	int direction = 1;
	
	initscr(); // Initialize the window
	noecho(); // Don't echo any keypresses
	curs_set(FALSE); // Don't display a cursor
	
	while(1) {
		getmaxyx(stdscr, max_y, max_x);
		clear();
		mvprintw(0, x, "o");
		refresh();

		usleep(30000);
		next_x = x + direction;

		if(next_x >=max_x || next_x < 0){
			direction = direction * -1;
		}
		else {
			x+=direction;
		}
	}
	endwin();
}
