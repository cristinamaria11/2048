#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#include "header_file.h"

/* It highlights on the screen the chosen option. */
void highlightchoice(WINDOW *menuwindow, int choice)
{
	char *choices[] = {"New game", "Resume", "Quit"};
	int x, y, i;	
	int nrch = sizeof(choices) / sizeof(char *);
	x = 2;
	y = 2;
	curs_set(0);
	box(menuwindow, 0, 0);
	for(i = 0; i < nrch; ++i)
	{	if(choice == i + 1) 
		{	wattron(menuwindow, A_REVERSE); 
			start_color();
			init_pair(5,COLOR_BLACK,COLOR_RED);
			wattron(menuwindow,COLOR_PAIR(5));
			mvwprintw(menuwindow, y, x, "%s", choices[i]);
			wattroff(menuwindow, A_REVERSE);
			wattroff(menuwindow,COLOR_PAIR(5));
		}
		else
			mvwprintw(menuwindow, y, x, "%s", choices[i]);
		++y;
		refresh();
	}
	wrefresh(menuwindow);
}

/* It prints the menu and returns a value for each chosen option. */
int printmenu()
{
	
	char *choices[] = {"New game", "Resume", "Quit"};
	WINDOW *menuwindow,*wnd=initscr();
	int nrch = sizeof(choices) / sizeof(char *);
	int choice=1,c,ok=0,nrows,ncols;

	/* The screen is cleared. */
	clear();

	getmaxyx(wnd, nrows, ncols);
	/* The input from stdin is not displayed. */
	noecho();
	/* No buffering while reading input. */
	cbreak();
	/* The cursor is hidden. */
	curs_set(0);
	/* A new window is initialized. */
	menuwindow=newwin(7,20,(nrows-7)/2,(ncols-20)/2);
	keypad(menuwindow,TRUE);
	mvprintw(0,(ncols-6)/2,"--- ---");
	mvprintw(1,ncols/2-4,"|   |   |");
	mvprintw(2,(ncols-6)/2,"--- ---");
	mvprintw(3,ncols/2-4,"|   |   |");
	mvprintw(4,(ncols-6)/2,"--- ---");
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(3,COLOR_YELLOW,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(1,(ncols-4)/2,"2");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvprintw(3,(ncols+4)/2,"8");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	mvprintw(1,(ncols+4)/2,"0");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(4));
	mvprintw(3,(ncols-4)/2,"4");
	attroff(COLOR_PAIR(4));
	attron(COLOR_PAIR(1));

	/* The legend is displayed. */
	mvprintw(6, ncols/2-15, "Press ENTER to select a choice.");
	mvprintw(7, ncols/2-3, "UP/DOWN");
	attroff(COLOR_PAIR(1));
	refresh();

	/* It highlights the chosen option. */
	highlightchoice(menuwindow, choice);
	while(1){	
		c = wgetch(menuwindow);
		switch(c){	
			case KEY_UP:
				if(choice == 1)
					choice = nrch;
				else
					--choice;
				break;
			case KEY_DOWN:
				if(choice == nrch)
					choice = 1;
				else 
					++choice;
				break;
			case 10:
			{
				ok = choice;
				break; 
			}
		}
		if(ok != 0)
			break;
		highlightchoice(menuwindow, choice);
	}	
	clrtoeol();
	refresh();
	endwin();

	/* It returns a value for the chosen option. */
	if(choice==1)
		return 1;
	if(choice==2)
		return 2;
	if(choice==3)
		return 3;
	return 3;
}
