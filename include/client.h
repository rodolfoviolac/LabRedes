#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>

#define IP_ADDR "192.168.0.102"

using namespace std;

void stoc(std::string str, char* c);
