#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define SERVER_PORT 8000
#define MAXLINE 1024
int main(int argc, char *argv[]){
	int cli_sock;
	struct sockaddr_in serv_addr;
	int read_len;
	char buf[1024];

	if(argc != 2){
		perror("Number of parameters error!");
		exit(-1);
	}

	cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_sock < 0){
		perror("socket error!");
		exit(-1);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	serv_addr.sin_port = htons(SERVER_PORT);

	if(connect(cli_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		perror("connection failed!");
		exit(-1);
	}

	// str = argv[1];
	char str[MAXLINE];
	while(fgets(str, MAXLINE, stdin) != NULL){
		write(cli_sock, str, strlen(str));

		if((read_len = read(cli_sock, buf, sizeof(buf))) > 0){
		//write(STDOUT_FILENO, buf, read_len);
			fputs(buf, stdout);
			memset(buf, 0, sizeof(buf));
		}else{
			perror("Read from server error.");
			exit(-1);
		}
	}
	close(cli_sock);

	return 0;
}
