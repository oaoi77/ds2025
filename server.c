#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 
#define BUFFER_SIZE 1024

//Function to receive file from client 
//server receive the data from client and write to file
void recv_file(int client_socket){
    int n;
    FILE *fp;
    char *fn = "message.txt";
    char buffer[BUFFER_SIZE];

    fp = fopen(fn, "w");
    //loop until connection closed or error occur
    while (1) {
        //recv return the number of bytes read
        n = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (n<=0){
            break;
            return;
        }
        //print the data received to message.txt
        fprintf(fp, "%s", buffer);
        bzero(buffer, BUFFER_SIZE); //Clear all data in buffer
    }
    return;
}

int main(){
    int client_socket, server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    //create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1){
        perror("[-] Error in socket");
        exit(EXIT_FAILURE);        
    }
    printf("[+] Server socket created successfully\n");

    //set up the server and address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    //bind the socket to the address and port number
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("[-] Bind error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("[+] Binding successfully\n");

    //listen request from client (incomming connection), not ovet 10 times attempt
    if(listen(server_socket, 10) == -1){
        perror("[-] Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("[+] Listening...\n");

    //establish the connection between server and client
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if(client_socket == -1){
        perror("[-] Acception failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("[+] Accepting client connection\n");

    //receive file and close socket connection
    recv_file(client_socket);
    printf("[+] Received data from client\n");
    close(server_socket);
}


