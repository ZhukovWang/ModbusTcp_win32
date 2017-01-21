#include "M_Client.h"  

using namespace std;

int main()
{
	int connect_error;
	M_Client client("192.168.1.223", 502, 1);  
	printf("Waiting to connection\n");
	connect_error = client.Connect();
	if (connect_error==0)
	{
		//client.Modbus_sender_single(0, 145, 24323);// 将145号寄存器写为24323（十进制）  
		unsigned char buf[12];
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 6;
		buf[6] = 1;//从机ID  
		buf[7] = 3;//命令代码  
		buf[8] = 0;
		buf[9] = 0;
		buf[10] = 0;
		buf[11] = 2;
		client.SendMsg((char*)buf, 12);
		client.RecvMsg();
		client.Close();
	}
	else
	{
		;
	}
	system("pause");
	return 0;
}