#include <syslog.h>
#include <stdio.h>

//nomer 4
int
main (void)
{
	openlog("fs", 0, LOG_USER);
	
	syslog(LOG_INFO, "", "");
	
	syslog(LOG_WARNING, "", "");
	
}
