#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main (int argc, char **argv)
{
	sockaddr_in * self_addr = new (sockaddr_in);
	self_addr->sin_family = AF_INET;
	self_addr->sin_port = 0;
	self_addr->sin_addr.s_addr = 0;
	sockaddr_in * srv_addr = new (sockaddr_in);
	srv_addr->sin_family = AF_INET;
	srv_addr->sin_port = htons(7);
	srv_addr->sin_addr.s_addr = inet_addr("172.16.40.1");
	char *buf = new char[1024];
	string str ("MITYA_CHEREP\n");
	int msg = str.length();
	size_t length = str.copy(buf,msg);
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
		cerr << "Ошибка сокета";
	}
	int rc = bind(s, (const sockaddr *) self_addr, sizeof ( sockaddr_in));
	if (rc == -1) {
		close(s);
		cerr <<"Ошибка привязки сокета";
	}
	rc = connect(s, ( const sockaddr*) srv_addr, sizeof(sockaddr_in));
	if ( rc == -1) {
		close(s);
		cerr <<"Ошибка подключения к удаленному серверу";
	}
	rc = send(s, buf,msg,0);
	if ( rc == -1) {
		close(s);
		cerr <<"Ошибка при отправке сообщения";
	}
	cout << "Мы отправили: " << buf << endl;
	rc = recv(s, buf, 1024,0);
	if ( rc == -1) {
		close(s);
		cerr <<"Ошибка при получении ответа";
	}
	buf[rc]='\0';
	cout << "Мы получили: " << buf << endl;
	close(s);
	delete self_addr;
	delete srv_addr;
	delete[] buf;
	return 0;
}
