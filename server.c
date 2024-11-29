#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080 
#define BUFFER_SIZE 1024

//Function to receive file from client 
//server receive the data from client and write to file
void recv_File(){
    int n;
    FILE *fp;
    char *fn = "message.txt";
    char buffer[size];

    fp = fopen(fn, "w");
    //loop until connection closed or error occur
    while (1) {
        //recv return the number of bytes read
        n = recv(sockfd, buffer, BUFFER_SIZE, 0)
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
    printf("[+] Binding successfully\n")
    

}


