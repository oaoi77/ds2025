#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "172.23.147.113" 
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

void send_file(FILE *fp, int client_socket){
    int n;
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
        if(send(client_socket, buffer, sizeof(buffer), 0) == -1){
            perror("[-] Sending file failed");
            exit(EXIT_FAILURE);
        }
        bzero(buffer, BUFFER_SIZE);
    }
}

int main(){
    int client_socket;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "send.txt";

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

    //connect to server
    if(connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("[-] Connect error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("[+] Connect successfully\n");

    //read the file then send file data to server
    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("[-] Reading file failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    //send file data and close socket
    send_file(fp, client_socket);
    printf("[+] File data sent sucessfully\n");
    close(client_socket);
}
