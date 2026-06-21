#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define BALL_SYMBOL "O"
#define BORDER  "#"
#define PADDLE "||"
#define SLEEP_TIME 20000


struct Paddle {
    int x, y, l, score, point;
};

struct Ball {
    int x, y, tx, ty;
};

int main(void){

    int quit = 0;
    int frame = 1;
    int max_x = 0;
    int max_y = 0;
    int miss = 0;
    int hit = 0;
    int best = 0;
    int streak = 0;

    struct Paddle p1, p2;
    struct Ball b;
    system("clear");

    srand(time(NULL));
    initscr();
   
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    nodelay(stdscr,1);
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    getmaxyx(stdscr, max_y, max_x);

    p1.l = 6;
    p1.x = max_x -3;
    p1.y = (max_y/2) - (p1.l/2);
    p1.score = 0;

    p2.l = 6;
    p2.x = 2;
    p2.y = (max_y/2) - (p2.l/2);
    p2.score = 0;

    b.x = max_x/33;
    b.y = max_y/23;
    b.tx = rand() & 1 ? -1 : 1;
    b.ty = rand() & 1 ? -1 : 1;


    while (!quit) {

        clear();

        getmaxyx(stdscr, max_y, max_x);
        mvprintw(0, max_x/2 - 30,"PLAYER 1: Hits:%d Points:%d      PLAYER 2: Hits:%d Points:%d", p1.score, p1.point, p2.score, p2.point);
        mvprintw(0, max_x/2 + 40,"Time: %d", frame / 50);
	
	attron(COLOR_PAIR(3));

        int i;
	
	int mid_x = max_x / 2;
	
	for (i = 1; i < max_y - 1; i++) {
    		mvprintw(i, mid_x, BORDER);
	}

	
        for (i = 0; i < max_x; i++) {
            mvprintw(1, i, BORDER);
            mvprintw(max_y - 1, i, BORDER);
        }

        //for (i = 1; i < max_y - 1; i++) {
          //  mvprintw(i, 0, BORDER);
      	   // mvprintw(i, max_x/2, BORDER);	
//	}
       
	attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(1));
        p1.x = max_x-3;
	

        for (i = 0; i < p1.l; i++) {
            mvprintw(p1.y + i, p1.x, PADDLE);
        }
	
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(1));
          p2.x = 2;


        for (i = 0; i < p2.l; i++) {
            mvprintw(p2.y + i, p2.x, PADDLE);
        }        


        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        
        mvprintw(b.y, b.x, BALL_SYMBOL);
        attroff(COLOR_PAIR(2));

        if ((b.x + b.tx) < 1 && b.x > 0)
            b.tx *= -1;

        if ((b.y + b.ty) < 2 || (b.y + b.ty) > max_y - 2)
            b.ty *= -1;

        if ((b.x + b.tx == p1.x) && (b.y + b.ty >= p1.y) && (b.y + b.ty <= (p1.y + p1.l))) {
            hit++;
            streak++;
	    p2.score++;	    
	     beep();

            if (streak > best){
                best = streak;
	        if (streak % 5 == 0) {
     			b.tx += b.tx > 0 ? 1 : -1;
	   		b.ty += b.ty > 0 ? 1 : -1;
		        mvprintw(max_y/2, max_x/2 - 10, "LEVEL UP! BALL SPEED INCREASED!");
        		refresh();
       			usleep(SLEEP_TIME * 10);
    		}
      	    }
            
	b.tx *= -1;
        }
   	
	if ((b.x + b.tx == p2.x) && (b.y + b.ty >= p2.y) && (b.y + b.ty <= (p2.y + p2.l))) {
 		hit++;
    		streak++;
	        p1.score++;	    
                   beep();

    		if (streak > best){
        		best = streak;
        	
			if (streak % 5 == 0) {
                		b.tx += b.tx > 0 ? 1 : -1;
                		b.ty += b.ty > 0 ? 1 : -1;
                		mvprintw(max_y/2, max_x/2 - 10, "LEVEL UP! BALL SPEED INCREASED!");
                		refresh();
                		usleep(SLEEP_TIME * 10);
        		}
    		}

    	b.tx *= -1;
	}

	
        if (b.x > max_x) {
            miss++;
	    p1.point++;	
            streak = 0;
            b.x = max_x / 33;
            b.y = max_y / 23;
            b.tx = rand() & 1 ? -1 : 1;
            b.ty = rand() & 1 ? -1 : 1;
       
            mvprintw(0, max_x/2 - 25,"PLAYER 1: Hits:%d Points:%d      PLAYER 2: Hits:%d Points:%d", p1.score, p1.point, p2.score, p2.point);
            mvprintw(max_y,max_x/2 - 10,"Time: %d", frame / 50);
            refresh();
	}
        
	if (b.x < 3) {
        	miss++;
	        p2.point++;	
    		streak = 0;
    		b.x = max_x / 33;
    		b.y = max_y / 23;
    		b.tx = rand() & 1 ? -1 : 1;
    		b.ty = rand() & 1 ? -1 : 1;
		
                mvprintw(0, max_x/2 - 25,"PLAYER 1: Hits:%d Points:%d      PLAYER 2: Hits:%d Points:%d", p1.score, p1.point, p2.score, p2.point);
                mvprintw(max_y, max_x/2 - 10,"Time: %d", frame / 50);
    		refresh();
	}
        
	if (frame % 4 == 0) {
            b.x += b.tx;
            b.y += b.ty;
        }
	
	int key = getch();
        switch (key) {

        case 'i':
	            if (p1.y - 1 > 1){
        	        p1.y -= 1;
	            }
           	break;

        case 'k':
            	if ((p1.y + p1.l) + 1 < max_y){
                	p1.y += 1;
		}
            	break;
 
	case 'w':
        	if (p2.y - 1 > 1){
            		p2.y -= 1;
        	}
        	break;

    	case 's':
        	if ((p2.y + p2.l) + 1 < max_y){
           		p2.y += 1;
        	}
        	break;     

        case 'Q':
        	quit = 1;
            	
		break;
        }

        frame++;
        
	usleep(SLEEP_TIME);

	}

    endwin();

    system("clear");

    return 0;

}


	






