// Listing 5.10 (socket-server.c) Local Namespace Socket Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Read text from the socket and print it out. Continue until the
   socket closes. Return nonzero if the client sent a "quit" message,
   zero otherwise. */
int server (int client_socket) {
	while (1) {
		int length;
		char* text;

		/* First, read the length of the text message from the socket.
		   If read returns zero, the client closed the connection. */
		if (read(client_socket, &length, sizeof(length)) == 0) {
			return 0;
		}

		/* Allocate a buffer to hold the text. */
		text = (char*)malloc(length);

		/* Read the text itself, and print it. */
		read(client_socket, text, length);

		printf("%s\n", text);

		/* If the client sent the message "quit", we're all done. */
		if (!strcmp(text, "quit")) {
			free(text);
			return 1;
		}

		/* Free the buffer. */
		free(text);
	}
}

int main(int argc, char* const argv[]) {
	const char* const socket_name = argv[1];
	int socket_fd;
	struct sockaddr_un name;

	socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_name);
	bind(socket_fd, (struct sockaddr *)&name, SUN_LEN(&name));

	listen(socket_fd, 1);

	struct sockaddr_un client_name;
	socklen_t client_name_len = SUN_LEN(&client_name);
	int client_socket_fd;

	client_socket_fd = accept(socket_fd,
		(struct sockaddr *)&client_name, &client_name_len);
		
	server(client_socket_fd);
	close(client_socket_fd);

	/* Remove the socket file. */
	close(socket_fd);
	unlink(socket_name);

	return 0;
}
