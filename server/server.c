#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#define SERVER_PORT 8000

int main(){
	int serv_sock, cli_sock;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t cli_addr_len;
	char buf[1024];
	int read_len;
	char str[INET_ADDRSTRLEN];
	pid_t child_pid;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1){
		perror("Create socket error");
		exit(-1);
	}
	
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(SERVER_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		perror("Bind error");
		exit(-1);
	}

	listen(serv_sock, 128);// == -1){}{
	//	perror("listen error!");
	//	exit(-1);
	//
	
	while(1){
		cli_addr_len = sizeof(cli_addr);
		cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
		if(cli_sock == -1){
			perror("Accept error");
			exit(-1);
		}
		if((child_pid = fork()) == 0){
			close(serv_sock);
			memset(buf, 0, sizeof(buf));
			while((read_len = read(cli_sock, buf, sizeof(buf))) > 0){
				printf("Receiving message from %s at port %d\n",
					inet_ntop(AF_INET, &cli_addr.sin_addr, str, sizeof(str)),
					ntohs(cli_addr.sin_port)
				);
				write(cli_sock, buf, read_len);
				write(STDOUT_FILENO, buf, read_len);
			}
		}
		close(cli_sock);
	}

	close(serv_sock);
	return 0;
}
