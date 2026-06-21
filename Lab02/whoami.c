#include <stdio.h>
#include <stdlib.h>


int main(int ac, char *av[]){
	

	char *username = getenv("USER");

    	if (username == NULL) {
        
		printf("Error: Failed to get USER\n");
       	
	 	return -1;
    	}

    	printf("%s", username);

	return 0;
	

}
