#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error( char *m )
{
	perror( m );
	exit( 0 );
}

int main( int argc, char *argv[] )
{
	int sockfd, newsockfd, port, clilen, n, num, num_mult;
	char buffer[256], message[256];
	struct sockaddr_in serv_addr, cli_addr;
	char *client_ip;
	if ( argc < 2 )
		error( "ERROR, no port provided\n" );
	port = atoi( argv[1] );
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if (sockfd < 0 )
		error( "ERROR opening socket" );
	//bzero( ( char * ) &serv_addr, sizeof( serv_addr ) );
	//memset() is preferred over bzero()
	memset( (char * ) &serv_addr, 0, sizeof( serv_addr ) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( port ); // host to network
	if ( bind( sockfd, ( struct sockaddr * ) &serv_addr, sizeof( serv_addr ) ) < 0 )
		error( "ERROR binding to socket" );
	listen(sockfd, 2 );
	printf( "Waiting for client connections on port %d\n", port );
	clilen = sizeof( cli_addr );
	newsockfd = accept( sockfd, (struct sockaddr * ) &cli_addr, &clilen );
	if ( newsockfd < 0 )
		error( "ERROR on accept" );
	client_ip = inet_ntoa(cli_addr.sin_addr);
	printf( "Client IP Address: %s\n", client_ip );
	n = read( newsockfd, buffer, 255 );
	if ( n < 0 )
		error( "ERROR reading from socket" );
	num = atoi( buffer );
	printf("Number received from Client: %d \n", num );
	num_mult = num * 5;
	printf("%d multiplied by 5: %d\n", num, num_mult );
	snprintf(buffer, 256, "%d", num_mult);
	n = write( newsockfd, buffer, strlen(buffer) );
	if ( n < 0 )
		error( "ERROR writing back to socket" );
	return 0;
}
