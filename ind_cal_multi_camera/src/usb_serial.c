#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>

//#include <ind_cal_multi_camera/laser_com.h>
#include <stdint.h>

#define LASER_FULL_POWER (0x0fff)
#define LASER_HALF_POWER (0x0fff/2)
#define DRUM_REV_PER_SECOND 12.5
#define DRUM_FACETS 12
#define OUTPUTS_PER_FACET 128

typedef struct laser_command{
  uint8_t phase_delay; // angle, phase_delay*PI/128 = angle in radians
  uint16_t laser_power[ 128 ]; // valid range is [ 0 , 0x0fff] or 12 bits, ox0fff is full power
} LASER_COMMAND;

main(){
	
  int pid, serial_fd; //process ID info for forking and file descriptor for serial stream -go
  struct termios laser_control_config; //sets up termios configuration structure for the laser_control serial port -go
  char c; //char for printing from serial port -go
  char input[10];
	
  const char *device = "/dev/ttyUSB0"; //sets where the serial port is plugged in -go
  serial_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY); //opens serial port in device slot -go
  if(serial_fd == -1) {
    fprintf(stdout, "failed to open port\n");
  }
	
  tcgetattr(serial_fd, &laser_control_config);
	
  cfsetispeed(&laser_control_config, B115200); //set baud input to 115200
  cfsetospeed(&laser_control_config, B115200); //set baud output to 115200
	
	
  laser_control_config.c_iflag = 0;
  laser_control_config.c_iflag &= (IXON | IXOFF |INLCR);
	
  laser_control_config.c_oflag = 0;

  laser_control_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	
  laser_control_config.c_cflag = 0;
  laser_control_config.c_cflag &= (CLOCAL | CREAD | CS8); //enable receiver and set to local mode
	
  laser_control_config.c_cc[VMIN]  = 1;
  laser_control_config.c_cc[VTIME] = 0;
	
  tcsetattr(serial_fd, TCSAFLUSH, &laser_control_config);
	
  pid = fork(); //splits process for recieving and sending -go
	
  if(pid == 0){ //child process continually receives 
    fprintf(stdout, "Receiving Process Started\n");
    while(1){
      if (read(serial_fd, &c, 1)>0){ //if there's something from the serial port, print it
        fprintf(stdout, "%c", c);
      }
    }
  }
  else{ //parent process sends data tout serial port
    fprintf(stdout, "Sending Process Started\n"); 
    LASER_COMMAND lc;
    lc.phase_delay = 25.0 * 3.1415/OUTPUTS_PER_FACET; // 25 degree phase delay
    double delta_t = DRUM_REV_PER_SECOND * DRUM_FACETS * OUTPUTS_PER_FACET;
    double time_per_sample = 1/delta_t;
    double omega = 10.0; // radians per second
    int message_len = sizeof(LASER_COMMAND);
    while(1){
      int i;
      for(i=0;i<OUTPUTS_PER_FACET;i++){
        double time = i*time_per_sample;
        double sot = sin(omega*time);
        double magnitude = LASER_HALF_POWER*(1+ sot);
        lc.laser_power[i] = (uint16_t) magnitude;
      }
      send(serial_fd, (char *) &lc, message_len, 0);
    }
  }

	
  close(serial_fd); //close serial stream -go
	
  fprintf(stdout, "complete"); //-debug -go

  return 0;
}
