//
// Created by Rodrigo Franzoi Scroferneker on 04/11/19.
//

#include "../include/client.h"


double tmp = 0;
double var_valsend = 0;

int sock, valread;

ofstream outfile;

int main(int argc, char const *argv[]) {

  int port;
  if (argc < 1) {
    cout << "Insufficient arguments." << endl;
    return -1;
  }

  port = atoi(argv[1]);

  std::thread t1(log_speed);

  string c_port(argv[1]);
  string filepath = "../log/" + c_port + ".csv";
  outfile.open(filepath);

  struct sockaddr_in serv_addr;

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

  std::thread t2(send_data);

  cout << "Press ENTER to stop." << endl;
  getchar();

  close(sock);
  outfile.close();

  return 0;
}


void send_data() {
  char c[PKT_SIZE];
  while(1) {
    valread = send(sock , c ,PKT_SIZE , 0 );
    if (valread > 0 ) var_valsend += valread;
  }
}

void log_speed(){
  int count = 0;
  while (1) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    double v = var_valsend;
    double value = (v-tmp)/1000/1000*8;
    tmp = v;
    std::time_t t = std::time(0);
    cout << value << "Mbit/s" << endl;
    outfile << value << "," << count++ << "," << t << endl;
  }
}

