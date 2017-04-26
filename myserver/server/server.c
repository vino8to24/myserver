#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#define SERVER_PORT 8000

int main(){
	int serv_sock, cli_sock;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t cli_addr_len;
	char buf[1024];
	int read_len;
	char str[INET_ADDRSTRLEN];

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1){
		perror("Create socket failed!");
		exit(-1);
	}
	
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(SERVER_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		perror("Bind failed!");
		exit(-1);
	}

	listen(serv_sock, 128);// == -1){}{
	//	perror("listen error!");
	//	exit(-1);
	//
	cli_addr_len = sizeof(cli_addr);
	cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
	if(cli_sock == -1){
		perror("accept error!");
		exit(-1);
	}
	while(1){
		read_len = read(cli_sock, buf, sizeof(buf));
		if(read_len == -1){
			perror("read error!");
			exit(-1);
		}
		if(read_len > 0){
			printf("Receiving message from %s at port %d\n",
				inet_ntop(AF_INET, &cli_addr.sin_addr, str, sizeof(str)),
				ntohs(cli_addr.sin_port)
			);
		}
		write(STDOUT_FILENO, buf, read_len);
	}

	close(serv_sock);
	close(cli_sock);
	return 0;
}
