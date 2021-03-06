//query_app.c
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
 
#include "query_ioctl.h"
 
/*
void get_vars(int fd)
{
    query_arg_t q;
 
    if (ioctl(fd, QUERY_GET_VARIABLES, &q) == -1)
    {
        perror("query_apps ioctl get");
    }
    else
    {
        printf("Status : %d\n", q.pin2);
    }
}*/

void set_LedOn(int fd, int led)
{
    query_arg_t q;
 
    q.pin2 = led;
 	
    printf("Encendiendo led : %d\n", led);

	if (ioctl(fd, QUERY_SET_VARIABLES, &q, led) == -1)
	{
		perror("query_apps ioctl set");
	}

}
 
void set_LedOff(int fd, int led)
{
    query_arg_t q;
 
    q.pin2 = led;
 	
    printf("Apagando led : %d\n", led);

    if (ioctl(fd, QUERY_CLR_VARIABLES, &q) == -1)
    {
        perror("query_apps ioctl set");
    }
}

void get_LedsStatus(int fd)
{
    query_arg_t q;
 
    if (ioctl(fd, QUERY_GET_VARIABLES, &q) == -1)
    {
        perror("query_apps ioctl get");
    }
    else
    {
        printf("Led 2  : %d\n", q.pin2);
        printf("Led 3  : %d\n", q.pin3);
        printf("Led 13 : %d\n", q.pin13);
    }
}

int main(int argc, char *argv[])
{
    char *file_name = "/dev/query";
    int fd;
    int led=0;
    enum
    {
//        e_get,
	e_setLedOn,
	e_setLedOff,
	e_getLedsStatus
    } option;
 
    if (argc == 1)
    {
        option = e_getLedsStatus;
    }
    else if (argc == 2)
    {
        /*if (strcmp(argv[1], "-g") == 0)
        {
            option = e_get;
        }
	else */if (strcmp(argv[1], "-s") == 0)
        {
            option = e_getLedsStatus;
        }
        else
        {
            fprintf(stderr, "Usage: %s [-g | -e | -a]\n", argv[0]);
            return 1;
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-e") == 0)
        {
            option = e_setLedOn;
        }
	else if (strcmp(argv[1], "-a") == 0)
        {
            option = e_setLedOff;
        }
        else
        {
            fprintf(stderr, "Usage: %s [-g | -e | -a]\n", argv[0]);
            return 1;
        }

	if (strcmp(argv[2], "2") == 0){
		led = 2;
	}
	else if (strcmp(argv[2], "3") == 0){
		led = 3;
	}
	else if (strcmp(argv[2], "13") == 0){
		led = 13;
	}
    }
    else
    {
        fprintf(stderr, "Usage: %s [-g | -e | -a]\n", argv[0]);
        return 1;
    }
    fd = open(file_name, O_RDWR);
    if (fd == -1)
    {
        perror("query_apps open");
        return 2;
    }
 
    switch (option)
    {
        /*case e_get:
            get_vars(fd);
            break;*/
	case e_setLedOn:
            set_LedOn(fd,led);
            break;
	case e_setLedOff:
            set_LedOff(fd,led);
            break;
	case e_getLedsStatus:
            get_LedsStatus(fd);
            break;
        default:
            break;
    }
 
    close (fd);
 
    return 0;
}
