//
// Created by Rodrigo Franzoi Scroferneker on 04/11/19.
//

#include "../include/server.h"

using namespace std;

double tmp = 0;
double var_valread = 0;

int new_socket, valread;

ofstream outfile;

int main(int argc, char const *argv[]) {

    int port;
    if (argc < 1) {
        cout << "Insufficient arguments." << endl;
        return -1;
    }

    port = atoi(argv[1]);

    std::thread t1(log_speed);

    string filepath = "../log/4000.csv";
    outfile.open(filepath);

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::thread t2(read_data);

    system("pause");

    close(new_socket);
    outfile.close();

    return 0;
}

void read_data() {
    char buffer[PKT_SIZE] = {0};
    while(1) {
        valread = read(new_socket ,buffer, PKT_SIZE);
        if (valread > 0 ) var_valread += valread;
    }
}

void log_speed(){
    int count = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
	    double v = var_valread;
        double value = (v-tmp)/1000/1000*8;
	    tmp = v;
	    outfile << value << "," << count++;
        cout << value << " Mbit/s" << endl;
    }
}

