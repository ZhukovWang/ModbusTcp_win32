#pragma once

#include <stdio.h>  
#include <windows.h> 
#include <string>
#pragma comment(lib, "ws2_32.lib")

class M_Client
{
public:
	//Constructor  
	M_Client(const char* Addr, int Port, int Id);
	//连接  
	int Connect();
	//发送TCP包  
	int SendMsg(const char* msg, int len);
	//接收TCP包
	int M_Client::RecvMsg();
	//关闭  
	void Close();
	//发送modbus包  
	void Modbus_sender_single(int Ref, int addr, int value);

private:
	SOCKET m_sock;
	int port;
	const char* address;
	int id;
};

