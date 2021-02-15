#include <iostream>
#include <unistd.h>
#include "UDPThread.h"

using namespace std;

int main() {

	UDP_Thread abc;

	if ( abc.StartInternalThread()){
		cout << "Start UDP port listening..." << endl;
	}

	while (1){
		sleep(1);
		if(abc.shared_udp_received_string == "reload\n"){
			abc.shared_udp_received_string = "";
			cout << "Reload needed !\n";
		}
	}
	return 0;
}
