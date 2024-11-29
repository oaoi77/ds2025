#include <stdio.h>
#include <stdlib.h>
#include <unistd/h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" //localhost
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

void send_file(FILE *fp, int server_socket){
    int n;
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
        if(send(server_socket, buffer, sizeof(buffer), 0) == -1){
            perror("[-] Sending file failed")
            exit(EXIT_FAILURE);
        }
        bzero(buffer, BUFFER_SIZE);
    }
}

int main(){
    int client_socket;
    struct sockaddr_in server_addr;

    //create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        perror("[-] Socket error");
        exit(EXIT_FAILURE);
    }
    printf("[+] Create socket successfully\n");

    //set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

}
