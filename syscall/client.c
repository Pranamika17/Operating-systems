#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 5984
#define BUFF_SIZE 4096
/* References:https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html 
                comments from server.c file  */
int main(int argc, const char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[BUFF_SIZE] = {0};

	/* [C1]
	 *     socket() system call is used to create a new socket.It takes three parameters which are address domain,type of socket and protocol.
        The domain specifies the communication medium.PF_INET is the most frequently used domain for internet connections.For PF_INET the address is AF_INET where AF stands for address family.
        SOCK_STREAM is a sequenced, reliable, connection-based, two-way byte stream.
        If zero is specified for protocol,then OS will choose most appropriate protocol.
        sock is the socket file descriptor and if the socket() system call returns -1  ,then an error message is displayed .	 */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	/* [C2]
	 * serv_addr is a structure of type struct sockaddr_in.This structure has four fields.
        The first field should contain the code for the address family which is AF_INET.
        The second field contains the port number.The port number is typecasted using the htons function from host byte order to network byte order.
        	 */
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	/* [C3]
	 * inet_pton converts IPv4 address from text to binary.It takes 3 parametrs address,source and destination.
	The source points to the IPv4 network address
        The function returns 1  on success otherwise returns -1 on an invalid address.
	 */
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	/* [C4]
	 * The connect function is called by the client to establish a connection to the server.
	 It takes three arguments, the socket file descriptor, the address of the host to which it wants to connect, and the size of this address. This function returns 0 on success.
	 */
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}


	/* [C5]
	 * printf() is used to display the statement.getchar() waits until there is any keyboard stroke detected.
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [C6]
	 * The send() function sends data using the file descriptor .
        The second parameter points to the buffer containing the message.
        The third parameter is the size of the message in bytes.
        The fourth parameter specifies the type of message transmission.
	 */
	send(sock , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");

	/* [C7]
	 * The read() function reads 1024 bytes of input into the buffer.
        new_socket file descriptor reads the message from the server  and stores it in the buffer.
        This message is then printed.
 */
	read( sock , buffer, 1024);
	printf("Message from a server: %s\n",buffer );
	return 0;
}
