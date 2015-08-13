#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include <joystick.h>
#include <pthread.h>


using namespace std;

#define error printf

extern int forward;
extern int rotate; 

int maestroGetPosition(int fd, unsigned char channel)
{
    unsigned char command[] = {0x90, channel};
    if(write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }
   
    unsigned char response[2];
    if(read(fd,response,2) != 2)
    {
        perror("error reading");
        return -1;
    }
    return response[0] + 256*response[1];
}
 
// Sets the target of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
// The units of 'target' are quarter-microseconds.
int maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
    unsigned char command[] = {0x84, channel, static_cast<unsigned char>(target & 0x7F), static_cast<unsigned char>(target >> 7 & 0x7F)};
    if (write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }
    return 0;
}


int main()
{


  const char * device = "/dev/ttyACM0";  // Linux
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
    perror(device);
    return 1;
  }

  struct termios options;
  tcgetattr(fd, &options);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  options.c_oflag &= ~(ONLCR | OCRNL);
  tcsetattr(fd, TCSANOW, &options);




   

    pthread_t pt;
    pthread_create(&pt,NULL,joystick_main,NULL);

    int x[2];

     while(1)
    {
        x[0] = ie.js1_ud;
        x[1] = ie.js1_lr;
        printf("%d %d\n",x[0],x[1]);

         int target1 = 6000 + 4*x[0]/66;
          int target2 = 6000 + 4*x[1]/66;

          int position = maestroGetPosition(fd, 0);
          printf("Current position is %d.\n", position);

          int position2 = maestroGetPosition(fd, 1);
          printf("Current position is %d.\n", position2);
          maestroSetTarget(fd, 0, target1);
          maestroSetTarget(fd, 1, target2);

          fflush(stdout);
          usleep(10000);
    }
    return 0;

}
