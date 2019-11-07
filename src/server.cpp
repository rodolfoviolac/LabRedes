//
// Created by Rodrigo Franzoi Scroferneker on 04/11/19.
//

#include "../include/server.h"

using namespace std;

double var_valread = 0;

int main(int argc, char const *argv[]) {

    int port;
    if (argc < 1) {
        cout << "Insufficient arguments." << endl;
        return -1;
    }

    port = atoi(argv[1]);

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

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

    std::thread t1(log_speed);

    for (int i = 0; i < 30000; i++) {
        valread = read(new_socket ,buffer, PKT_SIZE);
        if (valread > 0 ) var_valread += valread;
    }

    return 0;
}

void log_speed(){
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        double value = var_valread/1024/1024;
        cout << value << " MB/s" << endl;
        var_valread = 0;

    }
}

