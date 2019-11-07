#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <thread>

#define PKT_SIZE 8196
#define IP_ADDR "192.168.0.102"

using namespace std;

void log_speed();
