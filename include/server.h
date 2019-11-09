#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>

#define PKT_SIZE 8196

void read_data();
void log_speed();