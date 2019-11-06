//
// Created by Rodrigo Franzoi Scroferneker on 04/11/19.
//

#include "../include/client.h"


int main(int argc, char const *argv[]) {

  int port;
  if (argc < 1) {
    cout << "Insufficient arguments." << endl;
    return -1;
  }

  port = atoi(argv[1]);

  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  //char buffer[1024] = {0};

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      cout << "Socket creation error." << endl;
      return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if(inet_pton(AF_INET, IP_ADDR, &serv_addr.sin_addr)<=0) {
    cout << "Invalid address/ Address not supported " << endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    cout << "Connection Failed" << endl;
    return -1;
  }

  std:string c = "oi";
  while (1) {
    send(sock , c.c_str() , c.length() , 0 );
  }

  return 0;
}
