/* sigdemo1.c - shows how a signal handler works.
 *            - run this and press Ctrl-C a few times
 */

#include	<stdio.h>
#include	<signal.h>
#include 	<stdlib.h>


int max = 0;


int main(int argc, char *argv[])
{
	void	f(int);			/* declare the handler	*/
	int	i;

	if (argc != 2) {
     		printf("Usage: %s <max_count>\n", argv[0]);
        	return 1;
    	}

	signal( SIGINT, f );		/* install the handler	*/

	max = atoi(argv[1]);
	
	for(i=0; i<5; i++ ){		/* do something else	*/
		printf("hello\n");
		sleep(1);
	}
}

void f(int signum)			/* this function is called */
{
	int num = 0;
	int i;
	printf("OUCH!\n");

	for (i = 0; i < num; i++) {
       		printf("!");
    	}

	num++;

	printf("\n");
    	
   	
	if (num >= max) {
        	exit(0);
    	}
}
