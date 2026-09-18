#include <stdio.h>
#include <syslog.h>



int main(int argc, char *argv[]) {
	openlog(NULL, 0, LOG_USER);
	if(argc != 3){
		syslog(LOG_ERR,"Expected 3 Arguments - Received: %d", argc);
		closelog();
		return 1; ;
	}

	FILE *file = fopen(argv[1], "w");
	if(file != NULL){
		fputs(argv[2], file);
		fclose(file);
		syslog(LOG_INFO,"Write excecuted successfully");
	}else{
		syslog(LOG_ERR,"File Write Error");
		return 1;
	}

	closelog();
	return 0;
}


