/* rotate.c : map a->b, b->c, .. z->a
 *   purpose: useful for showing tty modes
 */


#include <termios.h>
#include <signal.h>
#include   <stdio.h>
#include   <ctype.h>


struct termios orig_term, new_term; // original tty modes


void handle_signal(int signal) {

    reset_tty(); // reset the modes
    exit(2);

}

void reset_tty() {

    tcsetattr(0, TCSANOW, &orig_term); // restore original modes

}

int main()
{

    if (tcgetattr(0, &orig_term) != 0) { // gets original modes
        perror("tcgetattr");
        return 1;
    }

    new_term = orig_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // turn off canonical and echo
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &new_term) == -1) { // set new modes
        perror("tcsetattr");
        return 1;
    }

    signal(SIGINT, handle_signal); // resets tty modes

    int c;
 
    while ( ( c=getchar() ) != EOF ){
        
	if ( c == 'z' ){
  
            c = 'a';
       
	} else if (islower(c)){
           
		 c++;
       }
	
	 putchar(c);
  	
	
        if (c == 'Q') {
            reset_tty(); // reset modes
            return 0;
        }
    }

    reset_tty(); // reset tty modes
    return 0;

}
