#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <thread>

#define IP_ADDR "127.0.0.1"

using namespace std;

void log_speed();