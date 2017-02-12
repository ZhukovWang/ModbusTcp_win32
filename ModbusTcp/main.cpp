#include "M_Client.h"  
#include<Windows.h>
#include<iostream>
#include <conio.h>

int main()
{
	std::cout << "读取%MW0的数据，按Esc键退出" << std::endl;
	int connect_error;
	M_Client client("192.168.1.223", 502, 1);
	printf("Waiting to connection\n");
	connect_error = client.Connect();
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
	bool end1 = true;
	while (end1)
	{
		if (connect_error == 0)
		{
			client.SendMsg((char*)buf, 12);
			client.RecvMsg();
			Sleep(4);
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				end1 = false;
			}
		}
	}
		

	
	system("pause");
	client.Close();
	return 0;
}
