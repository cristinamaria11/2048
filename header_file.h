void highlightchoice(WINDOW *menuwindow, int choice);
int printmenu();
void startgame(int status);
int youwon(int a[][4]);
int endofgame(int a[][4]);
int checkiffree(int poz,int a[][4]);
void addValue(int poz, int nr, int a[][4]);
void display(int a[][4], WINDOW *wnd);
void generateValue(int a[][4],WINDOW *wnd);
int randompoz(int MAX);
