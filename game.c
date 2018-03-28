#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#include "header_file.h"

/* Generates a random position havin max value MAX. */
int randompoz(int MAX)
{
	int random_number,a;

	srand(time(NULL));	
	random_number = rand() % MAX;
	a = random_number + 1;

	return a;
}

/* Moves all values up. */
void moveup(int *ok, int a[][4], WINDOW *w, int *score)
{
	int i, j, k=0;
	for(j = 0; j < 4; j++) {
		for(k = 0; k < 4; k++) {
			for(i = 3; i > 0; i--)
				if(a[i-1][j] == 0 && a[i][j] != 0) {
						*ok = 1;
						a[i-1][j] = a[i][j];
						a[i][j] = 0;
					}
		}
	}
	for(j = 0; j < 4; j++){
		i = 0;
		while(i < 3) {
			if(a[i][j] == a[i+1][j] && a[i][j] != 0) {
				/*The score is modified as two matching values are found .*/
				*ok = 1;
				a[i][j] = 2 * a[i+1][j];
				a[i+1][j] = 0;
				*score += a[i][j];
				i++;
			}
			i++;
		}
	}

	for(j = 0; j < 4; j++) {
		for(k = 0; k < 4; k++) {
			for(i = 3; i > 0; i--)
				if(a[i-1][j] == 0 && a[i][j] != 0) {
						a[i-1][j] = a[i][j];
						a[i][j] = 0;
					}
		}
	}
}

/* It moves all values down. */
void movedown(int *ok, int a[][4], WINDOW *w, int *score)
{
	int i,j,k=0;

	for(j = 0; j < 4; j++) {
		for(k = 0; k < 4; k++) {
			for(i = 0; i < 3; i++)
				if(a[i+1][j] == 0 && a[i][j] != 0) {
						*ok = 1;
						a[i+1][j] = a[i][j];
						a[i][j] = 0;
					}
		}
	}

	for(j = 0; j < 4; j++) {
		i = 3;
		while(i > 0) {
			if(a[i][j] == a[i-1][j] && a[i][j] != 0) {
				*ok = 1;
				a[i][j] = 2 * a[i-1][j];
				a[i-1][j] = 0;
				*score += a[i][j];
				i--;
			}
			i--;
		}
	}

	for(j = 0; j < 4; j++) {
		for(k = 0; k < 4; k++) {
			for(i = 0; i < 3; i++)
				if(a[i+1][j] == 0 && a[i][j] != 0) {
						a[i+1][j] = a[i][j];
						a[i][j] = 0;
					}
		}
	}
}

/*Moves all values to the right*/
void moveright(int *ok, int a[][4], WINDOW *w, int *score) {
	int i,j,k=0;

	for(i = 0; i < 4; i++) {
		for(k = 0; k < 4; k++) {
			for(j = 0; j < 3; j++)
				if(a[i][j+1] == 0 && a[i][j] != 0) {
						*ok = 1;
						a[i][j+1] = a[i][j];
						a[i][j] = 0;
					}
		}
	}

	for(i = 0; i < 4; i++) {
		j = 3;
		while(j > 0) {
			if(a[i][j] == a[i][j-1] && a[i][j] != 0) {
				*ok = 1;
				a[i][j] = 2 * a[i][j-1];
				a[i][j-1] = 0;
				*score += a[i][j];
				j--;
			}
			j--;
		}
	}

	for(i = 0; i < 4; i++) {
		for(k = 0; k < 4; k++) {
			for(j = 0; j < 3; j++)
				if(a[i][j+1] == 0 && a[i][j] != 0) {
						a[i][j+1] = a[i][j];
						a[i][j] = 0;
					}
		}
	}
}

/* Moves all values to the left. */
void moveleft(int *ok, int a[][4], WINDOW *w,int *score)
{
	int i,j,k=0;

	for(i = 0; i < 4; i++) {
		for(k = 0; k < 4; k++) {
			for(j = 3; j > 0; j--)
				if(a[i][j-1] == 0 && a[i][j] != 0) {
						*ok = 1;
						a[i][j-1] = a[i][j];
						a[i][j] = 0;
					}
		}
	}

	for(i = 0; i < 4; i++) {
		j = 0;
		while(j < 3) {
			if(a[i][j] == a[i][j+1] && a[i][j] != 0) {
				*ok = 1;
				a[i][j] = 2 * a[i][j+1];
				a[i][j+1] = 0;
				*score += a[i][j];
				j++;
			}
			j++;
		}
	}

	for(i = 0; i < 4; i++) {
		for(k = 0; k < 4; k++) {
			for(j = 3; j > 0; j--)
				if(a[i][j-1] == 0 && a[i][j] != 0) {
						a[i][j-1]=a[i][j];
						a[i][j]=0;
					}
		}
	}
}

/* Checks if the game is won*/
int youwon(int a[][4]) {
	int i,j;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(a[i][j] == 2048)
				return 1;
	return 0;
}

/* Checks if there are any possible moves*/
int endofgame(int a[][4]) {
	int i,j;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(a[i][j] == 0)
				return 1;
	return 0;
}

/* Checks is a position is available. */
int checkiffree(int poz,int a[][4]) {
	if(poz==1 && a[0][0]==0)
		return 1;
	if(poz==2 && a[0][1]==0)
		return 1;
	if(poz==3 && a[0][2]==0)
		return 1;
	if(poz==4 && a[0][3]==0)
		return 1;
	if(poz==5 && a[1][0]==0)
		return 1;
	if(poz==6 && a[1][1]==0)
		return 1;
	if(poz==7 && a[1][2]==0)
		return 1;
	if(poz==8 && a[1][3]==0)
		return 1;
	if(poz==9 && a[2][0]==0)
		return 1;
	if(poz==10 && a[2][1]==0)
		return 1;
	if(poz==11 && a[2][2]==0)
		return 1;
	if(poz==12 && a[2][3]==0)
		return 1;
	if(poz==13 && a[3][0]==0)
		return 1;
	if(poz==14 && a[3][1]==0)
		return 1;
	if(poz==15 && a[3][2]==0)
		return 1;
	if(poz==16 && a[3][3]==0)
		return 1;
	return 0;
}

/* Adds an element to the matrix. */
void addValue(int poz, int nr, int a[][4]) {
	if(poz == 1)
		a[0][0]=nr;
	if(poz == 2)
		a[0][1]=nr;
	if(poz==3)
		a[0][2]=nr;
	if(poz==4)
		a[0][3]=nr;
	if(poz==5)
		a[1][0]=nr;
	if(poz==6)
		a[1][1]=nr;
	if(poz==7)
		a[1][2]=nr;
	if(poz==8)
		a[1][3]=nr;
	if(poz==9)
		a[2][0]=nr;
	if(poz==10)
		a[2][1]=nr;
	if(poz==11)
		a[2][2]=nr;
	if(poz==12)
		a[2][3]=nr;
	if(poz==13)
		a[3][0]=nr;
	if(poz==14)
		a[3][1]=nr;
	if(poz==15)
		a[3][2]=nr;
	if(poz==16)
		a[3][3]=nr;
}

/* Display the matrix */
void display(int a[][4],WINDOW *wnd)
{
	int i,j,xi,yi,nrows,ncols;
	
	getmaxyx(wnd, nrows, ncols);
	
	yi=ncols/2-10;
	xi=nrows/2-3;
	
	init_pair(6,COLOR_BLACK,COLOR_RED);
	init_pair(7,COLOR_WHITE,COLOR_MAGENTA);
	init_pair(8,COLOR_WHITE,COLOR_BLUE);
	init_pair(9,COLOR_WHITE,COLOR_YELLOW);
	init_pair(10,COLOR_WHITE,COLOR_GREEN);
	init_pair(11,COLOR_WHITE,COLOR_CYAN);
	init_pair(12,COLOR_RED,COLOR_WHITE);
	init_pair(13,COLOR_WHITE,COLOR_BLUE);
	init_pair(14,COLOR_WHITE,COLOR_BLUE);
	init_pair(15,COLOR_WHITE,COLOR_BLUE);

	/* Display the values according to the corespondent colour. */	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			if(a[i][j] == 0)
				mvprintw(xi+i*2,yi+j*5,"    ");
			if(a[i][j] == 2) {
				attron(COLOR_PAIR(6) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5,"  %d ",a[i][j]);
				attroff(COLOR_PAIR(6) | A_BOLD);
			}
			if(a[i][j] == 4) {
				attron(COLOR_PAIR(7) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5,"  %d ",a[i][j]);
				attroff(COLOR_PAIR(7) | A_BOLD);
			}
			if(a[i][j] == 8) {
				attron(COLOR_PAIR(8) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5,"  %d ",a[i][j]);
				attroff(COLOR_PAIR(8) | A_BOLD);
			}
			if(a[i][j] == 16) {
				attron(COLOR_PAIR(9) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d ",a[i][j]);
				attroff(COLOR_PAIR(9) | A_BOLD);
			}
			if(a[i][j] == 32) {
				attron(COLOR_PAIR(10) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d ",a[i][j]);
				attroff(COLOR_PAIR(10) | A_BOLD);
			}
			if(a[i][j] == 64) {
				attron(COLOR_PAIR(11) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d ",a[i][j]);
				attroff(COLOR_PAIR(11) | A_BOLD);
			}
			if(a[i][j] == 128) {
				attron(COLOR_PAIR(12) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d",a[i][j]);
				attroff(COLOR_PAIR(12) | A_BOLD);
			}
			if(a[i][j] == 256) {
				attron(COLOR_PAIR(13) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d",a[i][j]);
				attroff(COLOR_PAIR(13) | A_BOLD);
			}
			if(a[i][j] == 512) {
				attron(COLOR_PAIR(14) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5," %d",a[i][j]);
				attroff(COLOR_PAIR(14) | A_BOLD);
			}
			if(a[i][j] == 1024) {
				attron(COLOR_PAIR(15) | A_BOLD);
				mvprintw(xi+i*2,yi+j*5,"%d",a[i][j]);
				attroff(COLOR_PAIR(15) | A_BOLD);
			}
		}
}

/* Generate a random value on the table. */
void generateValue(int a[][4],WINDOW *wnd)
{
	double a1;
	int poz1;
	srand(time(NULL));
	poz1=randompoz(16);

	while(checkiffree(poz1,a) == 0)
	{
		srand(time(NULL));
		poz1=randompoz(16);
	}

	a1=pow(2, rand() % 2 + 1);
	addValue(poz1,a1,a);
}


void startgame(int status)
{
	int static nrows, ncols,c,i,j,a[4][4],ok,score=0,highscore=0;
	time_t t;
	struct tm * tinfo;
	/* In initializes the window. */
	WINDOW *wnd=initscr();
	getmaxyx(wnd, nrows, ncols);

	/* It clears the screen. */
	clear();
	/* The input from stdin is not displayed. */
	noecho();
	/* No buffering while reading input. */
	cbreak();
	/* The cursor is hidden. */	
	curs_set(0);

	/* Initialize the matrix. */
	if (status == 0)
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				a[i][j] = 0;
	
    /* The table is created. */
	mvprintw(nrows/2-4, ncols/2-10, "---- ---- ---- ----");
	mvprintw(nrows/2-3, ncols/2-11, "|    |    |    |    |");
	mvprintw(nrows/2-2, ncols/2-10, "---- ---- ---- ----");
	mvprintw(nrows/2-1, ncols/2-11, "|    |    |    |    |");
	mvprintw(nrows/2, ncols/2-10, "---- ---- ---- ----");
	mvprintw(nrows/2+1, ncols/2-11, "|    |    |    |    |");
	mvprintw(nrows/2+2, ncols/2-10, "---- ---- ---- ----");
	mvprintw(nrows/2+3, ncols/2-11, "|    |    |    |    |");
	mvprintw(nrows/2+4, ncols/2-10, "---- ---- ---- ----");
	
    /* Generates the first 2 random values. */
	if (status == 0) {
		generateValue(a,wnd);
		generateValue(a,wnd);
		score = 0;
	}

    /* Display the options. */
	mvaddstr(0,0, "Press Q to return to menu.");
	display(a,wnd);

	keypad(wnd,TRUE);
	while (1) {
		/* Display date and time. */
		time(&t);
		tinfo = localtime(&t);
		mvprintw(1, 0, "Current date: %d.%d.%d",tinfo->tm_mday,tinfo->tm_mon+1,tinfo->tm_year+1900);
		mvprintw(2, 0, "Current time: %d:%d",tinfo->tm_hour,tinfo->tm_min);
		nodelay(wnd,100);
		/* Display the score and highschore. */
		mvprintw(3, 50, "Score: %d",score);
		if(score > highscore)
			highscore = score;
		mvprintw(4, 50, "Highscore: %d",highscore);
		c = wgetch(wnd);

		/* If q is pressed exit game. */
		if (tolower(c) == 'q')
			break;

		/* If the game ended, it returns to the main menu after 
			displaying a message. */
		if (endofgame(a) == 0) {
			mvprintw(4,ncols/2-4,"You lost!");
			sleep(5);
			status=0;
			break;
		}
		if (youwon(a) == 1) {
			mvprintw(4, ncols/2-4, "You won!");
			sleep(5);
			status = 0;
			break;
		}
		switch(c) {
			case KEY_UP : 
			{
				ok = 0;
				moveup(&ok,a,wnd,&score);
				/* If a move was made, another value is put on the table. */
				if (ok == 1)
					generateValue(a,wnd);
				break;
			}
			case KEY_DOWN:
			{
				ok = 0;
				movedown(&ok,a,wnd,&score);
				if (ok == 1)
					generateValue(a,wnd);
				break;
			}
			case KEY_RIGHT: {
				ok = 0;
				moveright(&ok,a,wnd,&score);
				if(ok == 1)
					generateValue(a,wnd);
				break;
			}
			case KEY_LEFT:
			{
				ok = 0;
				moveleft(&ok,a,wnd,&score);
				if(ok == 1)
					generateValue(a,wnd);
				break;
			}
			
		}

		/* The modified table game is displayed. */
		display(a,wnd);

		/* The window is refreshed. */
		wrefresh(wnd);
	}
	/* The ncurses window is closed. */	
	endwin();
}
