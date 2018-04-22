#ifndef CONNEXIONUDP_
#define CONNEXIONUDP_

int creerSocket() ;

struct sockaddr_in creerAdresse(const char *, int ) ;

int binderSocket(int , const struct sockaddr_in *) ;

char* envoyerPaquet();





#endif /*CONNEXIONUDP_*/
