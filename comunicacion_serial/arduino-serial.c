#include <stdio.h>    // Standard input/output definitions 
#include <stdlib.h> 
#include <string.h>   // String function definitions 
#include <unistd.h>   // for usleep()
#include <getopt.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include "arduino-serial-lib.h"

void usage(void)
{
    printf("Usage: arduino-serial -b <bps> -p <serialport> [OPTIONS]\n"
    "\n"
    "Options:\n"
    "  -h, --ayuda        Ayuda\n"
    "  -e, --write	  Encender led, ejemplo: e13 (enciende led 13)\n"
    "  -a, --write        Apagar led, ejemplo: a13 (apaga led 13)\n"
    "  -a, --read         Leer el estado de los pines\n"
    "  -s, --salir        Salir del programa\n"
    "\n");
}


void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) 
{
    const int buf_max = 256;

    int fd = -1;
    char serialport[buf_max];
    int baudrate = 9600;  // default
    char quiet=0;
    char eolchar = '\n';
    int timeout = 5000;
    char buf[buf_max];

    int rc;
	int opt;

    if (argc==1) {
        usage();
    }

	const char* port =     "/dev/ttyACM0";
	fd = serialport_init(port, baudrate);
	if( fd==-1 ) error("couldn't open port ");
	if(!quiet) printf("opened port %s\n",serialport);
	serialport_flush(fd);

	int salir = 0;
	
	char cmd[100];

    while( salir != 1){
	printf("Ingrese el comando: ");
	scanf("%s", cmd);
	opt = cmd[0];
	
        if (opt==-1) break;
        switch (opt) {
        case '0': break;
        case 'h':
            usage();
            break;	
        case 'e': // encender
        case 'a': // apagar
	    if( fd == -1 ) 
		error("serial port not opened");
            sprintf(buf, (opt=='S' ? "%s\n" : "%s"), optarg);
		strcpy(buf,cmd);	
            if( !quiet ) 
		printf("send string:%s\n", buf);

            rc = serialport_write(fd, buf);
            if(rc==-1) 
		error("error writing");
            break;
	case 'r': //leer estado de los pines
            if( fd == -1 ) 
		error("serial port not opened");

            memset(buf,0,buf_max);  // 

            serialport_read_until(fd, buf, eolchar, buf_max, timeout);
            if( !quiet ) printf("read string:");
            printf("%s\n", buf);
            break;
        case 's': //salir
            salir = 1;
            printf("Saliendo del programa....\n\n");
            break;
        }
    }
    exit(EXIT_SUCCESS);    
} // end main
    
