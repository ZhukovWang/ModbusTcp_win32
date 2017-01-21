#include "M_Client.h"

#include <errno.h>  
#include <iostream>

M_Client::M_Client(const char* Addr, int Port, int Id)
{
	address = Addr;
	port = Port;
	id = Id;
}

int M_Client::Connect()
{
	int rlt = 0;

	

	//用于记录错误信息并输出  
	int iErrMsg;

	//启动WinSock  
	WSAData wsaData;
	iErrMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (iErrMsg != NO_ERROR)
		//有错误  
	{
		printf("failed with wsaStartup error : %d\n", iErrMsg);

		rlt = 1;
		return rlt;
	}

	//创建Socket  
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)
		//创建Socket失败  
	{
		printf("socket failed with error : %d\n", WSAGetLastError());

		rlt = 2;
		return rlt;
	}

	//建立bind
	const char* pcaddress = "192.168.1.120";
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(0);
	sockAddr.sin_addr.s_addr = inet_addr(pcaddress); // 为待绑定的ip地址   
	auto binderr = bind(m_sock, (sockaddr*)&sockAddr, sizeof(sockaddr));
	if (binderr != 0)
	{
		printf("bind is err = %d", binderr);

	}


	//目标服务器数据  
	sockaddr_in sockaddrServer;
	sockaddrServer.sin_family = AF_INET;
	sockaddrServer.sin_port = htons(port);
	sockaddrServer.sin_addr.s_addr = inet_addr(address);

	//连接,sock与目标服务器连接  
	iErrMsg = connect(m_sock, (sockaddr*)&sockaddrServer, sizeof(sockaddrServer));


	if (iErrMsg < 0)
	{
		printf("connect failed with error : %d\n", iErrMsg);
		printf("Error: %d\n", errno);
		rlt = 3;
		return rlt;
	}

	return rlt;
}




int M_Client::SendMsg(const char* msg, int len)
{
	int rlt = 0;

	int iErrMsg = 0;

	//发送消息，指定sock发送消息  
	iErrMsg = send(m_sock, msg, len, 0);
	if (iErrMsg < 0)
		//发送失败  
	{
		printf("send msg failed with error : %d\n", iErrMsg);

		rlt = 1;
		return rlt;
	}

	return rlt;
}

int M_Client::RecvMsg()
{
	char revData[255];
	int rlt = 0;

	rlt = recv(m_sock, revData, 255, 0);
	
	if (rlt > 0)
	{

//		revData[rlt] = 0x00;
//		printf("%x",revData);
		printf("Receive data = \n");
		for (int i = 0; i <= 13; i++)
		{
			printf("%02X ",revData[i]);
		}
		
	}
	return rlt;
	
}

void M_Client::Close()
{
	closesocket(m_sock);
}

void M_Client::Modbus_sender_single(int Ref, int addr, int value)  //写一个寄存器，使用功能码16，修改后就可以写多个  
{
	unsigned char Temp_buf[20];
	Temp_buf[0] = Ref;
	Temp_buf[1] = 0;
	Temp_buf[2] = 0;
	Temp_buf[3] = 0;
	Temp_buf[4] = 0;//从ID开始到最后的字节数  
	Temp_buf[5] = 9;
	Temp_buf[6] = id;//从机ID  
	Temp_buf[7] = 16;//命令代码  
	Temp_buf[8] = (addr - 1) / 256;//addr head //开始的地址  
	Temp_buf[9] = (addr - 1) % 256;
	Temp_buf[10] = 0;//number of addr   //地址的长度  
	Temp_buf[11] = 1;
	Temp_buf[12] = 2;//# of Bytes for values    //一共多少byte的值  
	Temp_buf[13] = value / 256;//values           //具体的值，这里我只改一个寄存器，就写一个值  
	Temp_buf[14] = value % 256;
	SendMsg((char*)Temp_buf, 15);   //将报文发出，15为报文长度，这里是固定的  
}
