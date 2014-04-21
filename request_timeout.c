/**
 * gcc -Wall -g -o request_timeout request_timeout.c
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//char req_header[] = "GET / HTTP/1.1\r\nUser-Agent: curl/7.19.7\r\nHost: 127.0.0.1\ r\nAccept: */*\r\n\r\n";
char req_header[] = "GET / HTTP/1.1\r\nUser-Agent: curl/7.19.7\r\n";

int main(int argc, char *const *argv)
{
      int sockfd;
      struct sockaddr_in server_addr;

      if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
             fprintf (stderr, "Socket error,%s\r\n", strerror (errno));
             return -1;
      }
    
      bzero (&server_addr, sizeof (server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons (80);
    
      if(!inet_aton("192.168.1.1", &server_addr.sin_addr)) {
             fprintf (stderr, "Bad address:%s\r\n", strerror (errno));
             close (sockfd);
             return -1;
      }
    
      if (connect (sockfd, (struct sockaddr *) (&server_addr),
             sizeof (struct sockaddr)) == -1) {
             fprintf (stderr, "Connect Error:%s\r\n", strerror (errno));
             close (sockfd);
             return -1;
      }
    
      write (sockfd, req_header, strlen(req_header));
    
      close (sockfd);
      return 0;
}
