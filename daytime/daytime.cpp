#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define port 13
#define address "172.16.41.130"
#define bufSize 512 
int main (int argc, char **argv)
{
    sockaddr_in *cAddr = new (sockaddr_in);
    cAddr->sin_family = AF_INET; 
   	cAddr->sin_port = 0; 
    cAddr->sin_addr.s_addr = 0;
    sockaddr_in * sAddr = new (sockaddr_in);
    sAddr->sin_family = AF_INET; 
    sAddr->sin_port = htons(port); 
    sAddr->sin_addr.s_addr = inet_addr(address);
  	char *buf = new char[bufSize];
  	string str ("Сколько времени?\n");
  	int msgLen = str.length();
  	size_t length = str.copy(buf,msgLen);
    int Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket == -1) {
         exit(1);
    }
    int rc = bind(Socket, (const sockaddr *) cAddr, sizeof (sockaddr_in));
    if (rc == -1) {
        exit(1);
    }
    rc = connect(Socket, (const sockaddr*) sAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(Socket);
        exit(1);
    }
    rc = send(Socket, buf,msgLen,0);
    if (rc == -1) {
        close(Socket);
        exit(1);
    }
    cout << "Было отправлено: " << buf << endl;
    rc = recv(Socket, buf, bufSize,0);
    if ( rc == -1) {
        close(Socket);
        exit(1);
    }
    buf[rc]='\0';
    cout << "Было получено: " << buf << endl;
    close(Socket);
    delete cAddr;
    delete sAddr;
    delete[] buf;
    return 0;
}
