#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
struct tm *local;
time_t t;
t= time(NULL);
local=localtime(&t);
printf("%d/%d/%d hora: %d:%d\n",local->tm_mday,local->tm_mon+1,local->tm_year+1900,local->tm_hour,local->tm_min);

return 0;
}