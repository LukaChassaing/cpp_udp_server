#ifndef UDPTHREAD_H_
#define UDPTHREAD_H_

#define UDP_FILE_LOG_FLAG 1

#include <iostream> 		// cout
#include <sstream>  		// parsing
#include <sys/socket.h>	// for UDP
#include <netinet/in.h>	// for UDP
#include <stdio.h>			// for File output
#include <sys/time.h>		// Time measurement

using namespace std;

class UDP_Thread {

private:

	pthread_t _thread;		// thread
	int sockfd,n;			// UDP
	struct sockaddr_in servaddr,cliaddr; 	// UDP
	socklen_t len;			// UDP
	char mesg[1000];		// UDP

	struct timeval tvalNow, tvalInit;	// for time stamp
	double getTimeElapsed(struct timeval end, struct timeval start); // For time stamp


protected:
	void InternalThreadEntry();

public:
	string shared_udp_received_string;
	bool StartInternalThread();
	void WaitForInternalThreadToExit();
	static void * InternalThreadEntryFunc(void * This);
	UDP_Thread();
	~UDP_Thread();
};

#endif /* UDPTHREAD_H_ */
