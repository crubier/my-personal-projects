#include <asm/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <strings.h>

#ifndef CONNEXIONUDP_
#define CONNEXIONUDP_


int creerSocket() {
	int	socketRes = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketRes < 0) {
		std::cerr << "cannot create socket Reception";
		exit(1);
	}
	return socketRes;
}

struct sockaddr_in creerAdresse(const char *adresse, int port) {
	struct sockaddr_in adresseRes;
	adresseRes.sin_family = AF_INET;
	adresseRes.sin_addr.s_addr = inet_addr(adresse);
	adresseRes.sin_port = htons(port);
	return adresseRes;
}

int binderSocket(int socket, const struct sockaddr_in * adresse) {
	int i =bind(socket,(sockaddr*)adresse,sizeof(struct sockaddr_in));
		if ( i < 0) {
			std::cerr << "cannot bind emission socket";
			exit(1);
		}
		return i;
}






#endif /*CONNEXIONUDP_*/
