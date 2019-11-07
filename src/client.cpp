//
// Created by Rodrigo Franzoi Scroferneker on 04/11/19.
//

#include "../include/client.h"


double var_valsend = 0;

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

  std::thread t1(log_speed);

  char c[PKT_SIZE];
  //string c = "hello";

  for (int i = 0; i < 30000; i++) {
    int valsend = send(sock , c ,PKT_SIZE , 0 );
    if (valsend > 0) var_valsend += valsend;

  }
  return 0;
}

void log_speed(){
  while (1) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    double value = var_valsend/1024/1024;
    cout << value << " MB/s" << endl;
    var_valsend = 0;

  }
}