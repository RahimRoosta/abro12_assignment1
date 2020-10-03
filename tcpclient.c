#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


void main(int argc, char *argv[]){
	int clientSocket, n, m, portno, serverip, c;
	struct sockaddr_in serverAddr;
	char buffer [32];
	char newbuffer[256];
	char buffer2[256];
	char str1[] = "TEXT TCP 1.0\n\n";
	char str2[] = "OK\n";
	int result, result1;
	char delim[] = " ";
	char *str3[3];
	int i = 0;
	int operation;
	int num1, num2, cal2;
	float num3, num4, cal1;
	char fadd[] = "fadd";
	char fdiv[] = "fdiv";
	char fmul[] = "fmul";
	char fsub[] = "fsub";
	char add[] = "add";
	char div[] = "div";
	char mul[] = "mul";
	char sub[] = "sub";
	int flag = 0;
	int length;
	
	int number_to_send = 2;
	int convered_number = htonl(number_to_send);
	

	if (argc < 1)
	{
		printf("Please enter all arguments\n");
		exit(0);
	}

//Split input arg (IP:PORT)
	
	char *ipv4, *port;
	char* input = ":";
	ipv4 = strtok(argv[1], input);
	port = strtok(NULL, ":");
	
	portno = atoi(port);
	printf("Ipv4: --%s--\n", ipv4);
	printf("Port: --%d--\n", portno);

//Creating socket	
	clientSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(clientSocket<0)
	{
		printf("Client Socket Created Failed\n");
		exit(0);
	}	
	printf("Client Socket Created Successfully\n");	
	memset(&serverAddr, '\0', sizeof (serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(portno);
	serverAddr.sin_addr.s_addr=inet_addr(ipv4);
//Connect to the socket
	c=connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (c<0)
	{
		printf("Connection Error, server not responding!\n");
		exit(0);
	}
	printf("Connect to the Server\n");
	
	
	
	
	bzero(buffer,256);
	m=recv(clientSocket, buffer, 256, 0);
	printf("Version receaved from Server: %s\n", buffer);
	result = strcmp(str1, buffer);	
	printf("result: %d\n", result);
	if (result == 0)
	{
		//bzero(buffer,256);
		n = send(clientSocket, str2,strlen(str2),0);
		
		
		bzero(buffer,256);
		m=recv(clientSocket, buffer, sizeof(buffer), 0);
		printf("Assignment from Server:-%s-\n", buffer);
		
		
				//check the floating or integer
		char *ptr1 = strstr(buffer, ".");
		if( ptr1 != NULL)
		{
			//printf("Floating\n");
			//split the string(received data) to array
			char *ptr = strtok(buffer, delim);
			while (ptr != NULL)
			{
				str3[i++] = ptr;
				ptr = strtok(NULL, delim);
				//printf("%s\n", str3[i++]);
			
			}
			//for (i=0; i<3; ++i)
			//{			
				//printf("%s\n", str3[i]);
			//}
			
			//check the opearion type
			if (strcmp(str3[0], fadd)==0)
				{
					num3 = atof (str3[1]);
					num4 = atof (str3[2]);
					cal1 = num3 + num4;
					//printf("Client Calculation: %f\n", cal1);
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					snprintf(buffer,sizeof(buffer), "%f\n", cal1);	//int to buffer
					//fgets(buffer, 256, stdin);
					printf("Answer sent to Server: -%s-\n", buffer);
					n=write(clientSocket, buffer, strlen(buffer));
					//printf("Buffer2222: ...%s...\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer Confirmed by Server: %s\n", buffer);
					}
			if (strcmp(str3[0], fdiv)==0)
				{
					num3 = atof (str3[1]);
					num4 = atof (str3[2]);
					cal1 = num3 / num4;
					//printf("In the loop FADD: %f\n", cal1);
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					snprintf(buffer,sizeof(buffer), "%f\n", cal1);	//int to buffer
					//fgets(buffer, 256, stdin);
					//printf("Buffer: ---%s---\n", buffer);
					n=write(clientSocket, buffer, strlen(buffer));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmed by Server: %s\n", buffer);
					}
			if (strcmp(str3[0], fmul)==0)
				{
					num3 = atof (str3[1]);
					num4 = atof (str3[2]);
					cal1 = num3 * num4;
					//printf("In the loop FADD: %f\n", cal1);
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					snprintf(buffer,sizeof(buffer), "%f\n", cal1);	//int to buffer
					//fgets(buffer, 256, stdin);
					//printf("Buffer: ---%s---\n", buffer);
					n=write(clientSocket, buffer, strlen(buffer));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmation from Server: %s\n", buffer);
					}	
				if (strcmp(str3[0], fsub)==0)
					{
						num3 = atof (str3[1]);
						num4 = atof (str3[2]);
						cal1 = num3 * num4;
						//printf("In the loop FADD: %f\n", cal1);
						bzero(buffer,256);
						//bzero(buffer2,256);
						//printf("\nEnter answer: ");
						snprintf(buffer,sizeof(buffer), "%f\n", cal1);	//int to buffer
						//fgets(buffer, 256, stdin);
						//printf("Buffer: ---%s---\n", buffer);
						n=write(clientSocket, buffer, strlen(buffer));
						printf("Answer sent to Server: %s\n", buffer);
						
						bzero(buffer,256);
						m=recv(clientSocket,buffer,256,0);
						printf("Answer confirmation from Server:: %s\n", buffer);
						}						
		}
		else
		{
			
			//split the string(received data) to array
			char *ptr = strtok(buffer, delim);
			while (ptr != NULL)
			{
				str3[i++] = ptr;
				ptr = strtok(NULL, delim);
				//printf("%s\n", str3[i++]);
			
			}
			//for (i=0; i<3; ++i)
			//{			
				//printf("%s\n", str3[i]);
			//}
			
			//check the opearion type
			if (strcmp(str3[0], add)==0)
				{
					num1 = atoi (str3[1]);
					num2 = atoi (str3[2]);
				
					cal2 = num1 + num2;
					
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					sprintf(buffer, "%d\n", cal2);	//int to buffer
					//fgets(buffer, 256, stdin);
					
					n=write(clientSocket, buffer, sizeof(int));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmation from Server: %s\n", buffer);
					
					
				}
				
			if (strcmp(str3[0], div)==0)
				{
					num1 = atoi (str3[1]);
					num2 = atoi (str3[2]);
				
					cal2 = num1 / num2;
					
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					sprintf(buffer, "%d\n", cal2);	//int to buffer
					//fgets(buffer, 256, stdin);
					
					n=write(clientSocket, buffer, sizeof(int));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmation from Server: %s\n", buffer);
					
					
				}
		
			if (strcmp(str3[0], mul)==0)
				{
					num1 = atoi (str3[1]);
					num2 = atoi (str3[2]);
				
					cal2 = num1 * num2;
					
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					sprintf(buffer, "%d\n", cal2);	//int to buffer
					//fgets(buffer, 256, stdin);
					
					n=write(clientSocket, buffer, sizeof(int));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmation from Server: %s\n", buffer);
					
					
				}
			if (strcmp(str3[0], sub)==0)
				{
					num1 = atoi (str3[1]);
					num2 = atoi (str3[2]);
				
					cal2 = num1 - num2;
					
					bzero(buffer,256);
					//bzero(buffer2,256);
					//printf("\nEnter answer: ");
					sprintf(buffer, "%d\n", cal2);	//int to buffer
					//fgets(buffer, 256, stdin);
					
					n=write(clientSocket, buffer, sizeof(int));
					printf("Answer sent to Server: %s\n", buffer);
					
					bzero(buffer,256);
					m=recv(clientSocket,buffer,256,0);
					printf("Answer confirmation from Server: %s\n", buffer);
					
					
				}
		
		
		}


	}
	else
	{
		printf("TCP version is not matching\n");
		exit(0);
	}
}

