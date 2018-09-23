/*************************************************************************
    > File Name: file_client.cpp
    > Author: yy
    > Mail: yy@ityy520.com 
    > Created Time: Sat 22 Sep 2018 03:10:35 PM CST
 ************************************************************************/
#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<string>
#include<cstring>
#include<unistd.h>
#pragma pack(1)
struct file_info
{
	char name[51];
	unsigned int size;
};
#pragma pack()


int main(int argc,char** argv)
{
	if(argc!=3)
	{
		std::cout<<"参数错误!\n";
		exit(1);
	}
	int sock;
	sock = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in youraddr;
	youraddr.sin_family = AF_INET;
	youraddr.sin_addr.s_addr = inet_addr(argv[1]);
	youraddr.sin_port = htons(atoi(argv[2]));


	if(connect(sock,(struct sockaddr*)&youraddr,sizeof(youraddr)))
	{
		perror("connect error");
		exit(1);
	}
	file_info info;
	char* buff = new char[1024];

	int ret,cnt=0;
	float t = 0;
	ret = recv(sock,&info,sizeof(info),0);
	if(ret == 55)
	{
		std::ofstream file_out(info.name,std::ofstream::out);
		while(ret>0)
		{
		//	pthread_t tid;
		//	pthread_create(&tid,NULL,fun,)
			
			system("clear");
			ret = recv(sock,buff,1024,0);
			file_out.write(buff,ret);
			cnt+=ret;
			t = float(cnt)/float(info.size)*100;
	
			printf("正在传输>>>>>>>>>>>>>>>>>>>>>>>%.0f%c\n",t,'%');
		}
		file_out.close();
	}
	else
	{
		std::cout<<"文件信息接收失败!\n";
		exit(1);
	}
	close(sock);

	return 0;
}
