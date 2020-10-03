#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MY_PORT		9999
#define MAX_BUF		1024

int main(int argc, char *argv[])
{   
    int sockfd;
    int portno;
	struct sockaddr_in self;
	char buffer[32];
	char str1[] = "TEXT TCP 1.0\n\n";
	char str[] = "OK\n";
	char str3[] = "Error\n";
	int m, n;
	int result, result2, result3, result4;
	char fadd[] = "fadd";
	char fdiv[] = "fdiv";
	char fmul[] = "fmul";
	char fsub[] = "fsub";
	char add[] = "add";
	char div[] = "div";
	char mul[] = "mul";
	char sub[] = "sub";
	int r1, r2, r3, r4, r5;
	char *arith[]={"add","div","mul","sub"};
	int ans1, ans2, ans3;
	float ans4;
	char *arith1[]={"fadd","fdiv","fmul","fsub"};
	float r6, r7, r8, r9;
	float f1 = 50.0;
	float ans5, ans6, ans7;
	
	time_t t;

//Split input-arg (IP:PORT)
	
	char *ipv4, *port;
	char* input = ":";
	ipv4 = strtok(argv[1], input);
	port = strtok(NULL, ":");
	
	portno = atoi(port);
	printf("IP: --%s--\n", ipv4);
	printf("PORT: --%d--\n", portno);
	
	

//Create streaming socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket");
		exit(errno);
	}

//Initialize address/port structure
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(portno);
	self.sin_addr.s_addr = inet_addr(ipv4);

//Assign a port number to the socket
    if (bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0)
	{
		perror("socket:bind()");
		exit(errno);
	}

//Make it a "listening socket". Limit to 20 connections
	if (listen(sockfd, 20) != 0)
	{
		perror("socket:listen()");
		exit(errno);
	}

//Server run continuously
	while (1)
	{	int clientfd;
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

//accept an incomming connection
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
		printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

//send TCP version to client		
		m=send(clientfd, str1, sizeof(str1), 0);
		
		bzero(buffer,256);
//get TCP confirmation from Client
		n=recv(clientfd, buffer, sizeof(buffer), 0);
		printf("Version cinfirmation from client: --%s--\n", buffer);
		//printf("str: --%s--\n", str);
//check OK answer from Client	
		result = strcmp( str, buffer);
		printf("result of OK: %d\n", result);
		
		
		if (result == 0)
			{
			
				
				//printf("Version matched\n");
			
				srand(time(0));
				//Select int or float 
				r1= rand() % 1;		//random seed
				//printf("Integer or Float?: %d\n", r1);
				
				if (r1 == 0)	
					{
						
						r2= rand() % 3;
							//printf("r2: %d\n", r2);
						//check Ineger or float in random
						if (r2 == 0)  //integer
							{
							//printf("Integer\n");
							r3= rand() % 100 + 1;
							//printf("r3:%d\n", r3);
							
								
							r4= rand() % 100 + 1;
							//printf("r4: %d\n", r4);
							
							r5= rand() % 3;
							//printf("r5: %d\n", r5);
							
							//result = strcmp(arith[r5], add);
							if (strcmp(arith[r5], add)== 0)
								{
								
								sprintf(buffer, "%s %d %d\n",add,r3, r4 );
								printf("Assignment sent to client: %s\n", buffer);
								m=send(clientfd, buffer, sizeof(buffer), 0);
								bzero(buffer, 256);
								n=recv(clientfd, buffer, sizeof(buffer), 0);
								printf("Calculation rec from Client: %s\n", buffer);
								//check the answer
								ans1 = r3+r4;
								//printf("answer1: --%d--\n", ans1);
								ans2 = atoi(buffer);
								//printf("answer2 from client: --%d--\n", ans2);
								ans3 = ans1-ans2;
								printf("Server calculation: --%d--\n", ans3);
								bzero(buffer, 256);
								if (ans3<0.0001)
								{
									m=send(clientfd, str, sizeof(str), 0);
									printf("msg send to client: %s\n", str);
									printf("---------------------------\n");
								}
								else
								{
									m=send(clientfd, str3, sizeof(str3), 0);
									printf("msg send to client: %s\n", str3);
									printf("---------------------------\n");
								}
							}
								if (strcmp(arith[r5], div)== 0)
								{
									//printf("DIV\n");
									sprintf(buffer, "%s %d %d\n",div,r3, r4 );
									printf("Assignment sent to Cleint: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("calculation rec from Client: %s\n", buffer);
									//check the answer
									ans1 = r3/r4;
									//printf("answer1: --%d--\n", ans1);
									ans2 = atoi(buffer);
									//printf("answer2 from client: --%d--\n", ans2);
									ans3 = ans1-ans2;
									printf("server calculation: --%d--\n", ans3);
									bzero(buffer, 256);
									if (ans3<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}
								}
								if (strcmp(arith[r5], mul)== 0)
								{
									//printf("MUL\n");
									sprintf(buffer, "%s %d %d\n",mul,r3, r4 );
									printf("Assignment sent to Cleint: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("Calculation rec from Client: %s\n", buffer);
									//check the answer
									ans1 = r3*r4;
									//printf("answer1: --%d--\n", ans1);
									ans2 = atoi(buffer);
									//printf("answer2 from client: --%d--\n", ans2);
									ans3 = ans1-ans2;
									printf("Server calculation: --%d--\n", ans3);
									bzero(buffer, 256);
									if (ans3<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}
								}
								if (strcmp(arith[r5], sub)== 0)
								{
									//printf("SUB\n");
									sprintf(buffer, "%s %d %d\n",sub,r3, r4 );
									printf("Assignment sent to Client: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("buffer rec from Client: %s\n", buffer);
									//check the answer
									ans1 = r3-r4;
									//printf("answer1: --%d--\n", ans1);
									ans2 = atoi(buffer);
									//printf("answer2 from client: --%d--\n", ans2);
									ans3 = ans1-ans2;
									printf("Server Calculation: --%d--\n", ans3);
									bzero(buffer, 256);
									if (ans3<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}
								}
							
							}	
						else
							{
								//printf("Float\n");
								//printf("\n");
								r6= (float)rand() /(float)(RAND_MAX) * f1;
								//printf("r6:%f\n", r6);
								
									
								r7= (float)rand() /(float)(RAND_MAX) * f1;
								//printf("r7: %f\n", r7);
								
								r5= rand() % 3;
								//printf("r5: %d\n", r5);
								//printf("random operation: %s\n", arith1[r5]);
								
								if (strcmp(arith1[r5], fadd)== 0)
								{
									//printf("FAD\n");
									sprintf(buffer, "%s %f %f\n",fadd,r6, r7 );
									printf("Assignment sent to Client: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									//printf("Answer rec from Client: %s\n", buffer);
									//check the answer
									ans5 = r6+r7;
									//printf("answer5: %f\n", ans5);
									ans6 = atof(buffer);
									printf("answer6 recv from client: --%f--\n", ans6);
									ans7 = ans5-ans6;
									printf("Server calculation: --%f--\n", ans7);
									bzero(buffer, 256);
									if (ans7<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}	
								}
								if (strcmp(arith1[r5], fdiv)== 0)
								{
									//printf("FDIVVVVV\n");
									sprintf(buffer, "%s %f %f\n",fdiv,r6, r7 );
									printf("Assignment sent to Client: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("calculation rec from Client: %s\n", buffer);
									//check the answer
									ans5 = r6/r7;
									//printf("answer5: %f\n", ans5);
									ans6 = atof(buffer);
									//printf("answer6 recv from client: --%f--\n", ans6);
									ans7 = ans5-ans6;
									printf("Server Calculation: --%f--\n", ans7);
									bzero(buffer, 256);
									if (ans7<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}	
									
								}
								if (strcmp(arith1[r5], fmul)== 0)
								{
									//printf("FMULLLLLL\n");
									sprintf(buffer, "%s %f %f\n",fmul,r6, r7 );
									printf("Assignment sent to Client: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("Calculation rec from Client: %s\n", buffer);
									//check the answer
									ans5 = r6*r7;
									//printf("answer5: %f\n", ans5);
									ans6 = atof(buffer);
									//printf("answer6 recv from client: --%f--\n", ans6);
									ans7 = ans5-ans6;
									printf("Server Calculation: --%f--\n", ans7);
									bzero(buffer, 256);
									if (ans7<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}	
									
								}
								if (strcmp(arith1[r5], fsub)== 0)
								{
									//printf("FSUB\n");
									sprintf(buffer, "%s %f %f\n",fsub,r6, r7 );
									printf("Assignment sent to Client: %s\n", buffer);
									m=send(clientfd, buffer, sizeof(buffer), 0);
									bzero(buffer, 256);
									n=recv(clientfd, buffer, sizeof(buffer), 0);
									printf("Calculation from Client: %s\n", buffer);
									//check the answer
									ans5 = r6-r7;
									//printf("answer5: %f\n", ans5);
									ans6 = atof(buffer);
									//printf("answer6 recv from client: --%f--\n", ans6);
									ans7 = ans5-ans6;
									printf("Server Calculation: --%f--\n", ans7);
									bzero(buffer, 256);
									if (ans7<0.0001)
									{
										m=send(clientfd, str, sizeof(str), 0);
										printf("msg send to client: %s\n", str);
										printf("---------------------------\n");
									}
									else
									{
										m=send(clientfd, str3, sizeof(str3), 0);
										printf("msg send to client: %s\n", str3);
										printf("---------------------------\n");
									}	
									
								}
								
								
							}			
							}
		
					
				
				
				
			}
			else
			{
				printf("version is not matching\n");
				m=send(clientfd, str3, sizeof(str3), 0);
				//exit(0);
			}
		/** Echo back the received data to the client */
		//send(clientfd, buffer, recv(clientfd, buffer, MAX_BUF, 0), 0);

		/** Close data connection */
		close(clientfd);
	}

	/** Clean up */
	close(sockfd);
	return 0;
}
