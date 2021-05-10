#include "framework/io_thread.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

IOThread::IOThread(const ThreadHub &hub): IThread(hub) {

}

IOThread::~IOThread() {


}


void IOThread::work() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		cout << "IO thread" << endl;
	}
}


void IOThread::onNotify(uint64_t msgType) {
	cout << "got notify in io iothread" << msgType << endl;
}


