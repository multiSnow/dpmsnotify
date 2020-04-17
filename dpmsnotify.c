#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <xcb/dpms.h>

int is_running=0;
struct timespec delay;

void sighandler(int signum){
  is_running=0;
}

void printdpms(int level){
  switch(level){
  case XCB_DPMS_DPMS_MODE_ON:
    fprintf(stdout,"%d ON\n",level);
    break;
  case XCB_DPMS_DPMS_MODE_STANDBY:
    fprintf(stdout,"%d STANDBY\n",level);
    break;
  case XCB_DPMS_DPMS_MODE_SUSPEND:
    fprintf(stdout,"%d SUSPEND\n",level);
    break;
  case XCB_DPMS_DPMS_MODE_OFF:
    fprintf(stdout,"%d OFF\n",level);
    break;
  default:
    fprintf(stdout,"%d UNKNOWN\n",level);
    break;
  }
  fflush(stdout);
}

int check_xcb_connection(xcb_connection_t *conn){
  if(xcb_connection_has_error(conn)==0)return 0;
  xcb_disconnect(conn);
  return 1;
}

int get_dpms_level(xcb_connection_t *conn){
  xcb_dpms_info_cookie_t cookie=xcb_dpms_info_unchecked(conn);
  xcb_dpms_info_reply_t *reply=xcb_dpms_info_reply(conn,cookie,NULL);
  return reply->power_level;
}

int wait_for_dpms(xcb_connection_t *conn,int previous_level){
  int level=0;
  while(is_running){
    nanosleep(&delay,NULL);
    level=get_dpms_level(conn);
    if(level!=previous_level)return level;
  }
  return -1;
}

int main(int argc,char **argv){
  xcb_connection_t *c=xcb_connect(NULL,NULL);
  if(check_xcb_connection(c))
    return 1;

  signal(SIGINT,sighandler);
  signal(SIGTERM,sighandler);

  is_running=1;
  delay.tv_sec=0;
  delay.tv_nsec=200000000; // 200 ms

  int level=get_dpms_level(c);
  while(is_running&&level>-1){
    printdpms(level);
    level=wait_for_dpms(c,level);
  }

  xcb_disconnect(c);
  return 0;
}
