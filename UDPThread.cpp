#include "UDPThread.h"
#include "strings.h"
#include "string.h"
#include <unistd.h>

UDP_Thread::UDP_Thread () {
	_thread = pthread_self(); // get pthread ID
	pthread_setschedprio(_thread, SCHED_FIFO); // setting priority
	// udp initialization
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(14654);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

}
UDP_Thread::~UDP_Thread() {

	pthread_join(_thread, NULL); 	// close the thread
	close(sockfd); 					// close UDP socket
}

double UDP_Thread::getTimeElapsed(struct timeval end, struct timeval start)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.00;
}

/** Returns true if the thread was successfully started, false if there was an error starting the thread */
bool UDP_Thread::StartInternalThread()
{
	return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}

/** Will not return until the internal thread has exited. */
void UDP_Thread::WaitForInternalThreadToExit()
{
	(void) pthread_join(_thread, NULL);
}

void UDP_Thread::InternalThreadEntry(){

	gettimeofday(&tvalInit, NULL);

	for (;;)
	{
		len = sizeof(cliaddr);
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);

		mesg[n] = 0;

		string received(mesg);

		shared_udp_received_string = received;
		cout << "Data received \"" << received <<"\""<< endl;
	}
};

void * UDP_Thread::InternalThreadEntryFunc(void * This) {
	((UDP_Thread *)This)->InternalThreadEntry(); return NULL;
}