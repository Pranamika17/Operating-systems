#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5984
#define BUFF_SIZE 4096
/* References:https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html 
		https://linux.die.net/man/3/send  */
int main(int argc, const char *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFF_SIZE] = {0};
	char *hello = "Hello from server";

	/* [S1]
	 * socket() system call is used to create a new socket.It takes three parameters which are address domain,type of socket and protocol.
	The domain specifies the communication medium.PF_INET is the most frequently used domain for internet connections.For PF_INET the address is AF_INET where AF stands for address family.
	SOCK_STREAM is a sequenced, reliable, connection-based, two-way byte stream.
	If zero is specified for protocol,then OS will choose most appropriate protocol.
	server_fd is the socket file descriptor and if the socket() system call returns 0 ,then an error message is displayed .
	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* [S2]
	 * setsockopt function sets the socket options.It takes 5 parameters.
        syntax of the function is as follows:
		 int setsockopt(int socket,int level,int option_name,char *option_value, option length).
	The first argument is the socket file  descriptor,server_fd         
The option specified in the option_name is set by the function  at the protocol level specified.
         The socket option  is SO_REUSEADDR which specifies the rules for validating address supplied. 
	 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		       &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	/* [S3]
	 * address is a structure of type struct sockaddr_in.This structure has four fields.
	The first field should contain the code for the address family which is AF_INET.
	The second field contains the port number.The port number is typecasted using the htons function from host byte order to network byte order.
	The third field contains the IP address of the host.
	 */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	/* [S4]
	 *  The bind system call binds a socket to an address.It takes 3 arguments,the socket file descriptor 
         server_fd,the address to which it is bound and size of the address.
	The address is typecasted to a structure of type sockaddr.
	 If the function returns a  value less than 0 then it indicates failure,a message is displayed and exits.
	 */
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	/* [S5]
	 * The listen system call allows the process to listen on the socket for connections.
	The first parameter is the socket file descriptor.
	The second parameter is the size of the backlog queue.Backlog queue size indicates the number of connections that can be waiting when a process is working on a particular connection.If a value of -1 is obtained the program exits.
	 */
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* [S6]
	 * 
         The accept system call causes the process to block until a client connects to the server.
         It wakes up the process when the connection from the client is  established.
	It takes 3 arguments the file descriptor, the reference pointer to the address of the client and the size of the structure.
	The function returns a new file descriptor on which further communication is established.
         */

	
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
				 (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* [S7]
	 * printf() is used to display the statement.getchar() waits until there is any keyboard stroke detected.
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [S8]
	 * The read() function reads 1024 bytes of input into the buffer.
	new_socket file descriptor reads the message from the client and stores it in the buffer.
	This message is then printed.
	 */
	read( new_socket , buffer, 1024);
	printf("Message from a client: %s\n",buffer );

	/* [S9]
	 * The send() function sends data using the file descriptor .
	The second parameter points to the buffer containing the message.
	The third parameter is the size of the message in bytes.
	The fourth parameter specifies the type of message transmission.
	 */
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}
