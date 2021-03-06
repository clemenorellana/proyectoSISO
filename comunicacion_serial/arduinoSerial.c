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
    "  -h, --help                 Ayuda\n"
    "  -e, --send=string	  Encender led ejemplo: e13 (enciende led 13)"
    "  -a, --send=string          Encender led ejemplo: a13 (apaga led 13)\n"
    "  -a, --send=string          Encender led ejemplo: a13 (apaga led 13)\n"
    "  -s, --receive              Salir del programa\n"
    "\n");
//    exit(EXIT_SUCCESS);
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
    int n;
    int rc;

    if (argc==1) {
        usage();
    }

    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        {"help",       no_argument,       0, 'h'},
        {"port",       required_argument, 0, 'p'},
        {"send",       required_argument, 0, 's'},
        {"receive",    no_argument,       0, 'r'},
        {"delay",      required_argument, 0, 'd'},
        {"exiy",       0,		  0, 'a'},
        {NULL,         0,                 0, 0}
    };

	const char* port =     "/dev/ttyACM0";
	fd = serialport_init(port, baudrate);
	if( fd==-1 ) error("couldn't open port %s", port);
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
	case 'r':
            if( fd == -1 ) 
		error("serial port not opened");

            memset(buf,0,buf_max);  // 

            //rc = serialport_write(fd, "r");
            //if(rc==-1) error("error writing");

            serialport_read_until(fd, buf, eolchar, buf_max, timeout);
            if( !quiet ) printf("read string:");
            printf("%s\n", buf);
            break;
  
        case 's': //salir
            salir = 1;
            printf("Saliendo del programa");
            break;
/*        case 'd':
            n = strtol(optarg,NULL,10);
            if( !quiet ) printf("sleep %d millisecs\n",n);
            usleep(n * 1000 ); // sleep milliseconds
            break;
        case 'h':
            usage();
            break;
        case 's':
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
        case 'r':
            if( fd == -1 ) error("serial port not opened");
            memset(buf,0,buf_max);  // 

            //rc = serialport_write(fd, "r");
            //if(rc==-1) error("error writing");

            serialport_read_until(fd, buf, eolchar, buf_max, timeout);
            if( !quiet ) printf("read string:");
            printf("%s\n", buf);
            break;*/
        }
    //}
}
    exit(EXIT_SUCCESS);    
} // end main
    
