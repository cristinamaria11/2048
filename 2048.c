#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#include "header_file.h"

int main()
{
	int option,status;

	/* It gets the option chosen from the main menu */
	option=printmenu();

	while (option != 3) {
		if(option == 1) {
			/*New game is chosen*/
			status = 0;
			startgame(status);
			status = 1;
		}
		if (option == 2)
			if(status == 1) 
			/* Resume was selected. */
			startgame(status); //daca a fost un joc in derulare se revine la acesta
		option = printmenu();
	}

	/* It gets here only if the chosen option is Quit. */
	return 0;
}
