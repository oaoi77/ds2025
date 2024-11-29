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



