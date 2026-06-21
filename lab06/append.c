#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

   
int main (int ac, char *av[]) {
	
	const char* filename = av[1];

	const char* line = av[2];

	int end  = 0;

	int fd = open(filename, O_WRONLY | O_APPEND);
  
	if (ac != 3) {
	
        	printf("Usage: %s <filename> <line>\n", av[0]);
        
		return -1;
    	}


	while (end  < 10 && lock_passwd(filename) != 0) {
	 	end ++;
		sleep(1);
	}


	if (end >= 10) {
	
       		perror("link");	
		return -1;
	}


	
	if (fd == -1) {
        
       		perror("open");
 
		return -1;
    	}


   
	if (write(fd, line, strlen(line)) == -1) {
        	
		perror("write");
		
		close(fd);
        	
		return -1;

	}


   
	if (close(fd) == -1) {
	
		perror("close");        
        	return -1;
    	}


    
	unlock_passwd(filename);


	return 0;
}

int lock_passwd(const char* filename) {

    
	int rv = 0; 
	
	if (link(filename, strcat(filename, ".LCK")) == -1)

        rv = (errno == EEXIST ? 1 : 2);

    	return rv;
}


int unlock_passwd(char* filename) {

	char f_lock[strlen(filename) + 5];
	
	if (unlink(f_lock) == -1) {

        	perror("Error unlocking file");

        	return -1;
    	}

    	return 0;

}


