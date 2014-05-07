/*******************************
author:jaffer
time:2013-03-07
version:1.0
question:每次发邮件都要重新连接。会很烦吧。可是我将连接和清理分开之后，为什么只能发5封邮件，然后就出错了？
没有相应的一些处理出错的措施，毕竟对邮件不是很了解。这儿暂且这样了。邮箱密码必须输入正确。
******************************/

#include "stdafx.h"
#include "email.h"
#include <windows.h>

using namespace std;
#pragma  comment(lib, "ws2_32.lib")
//定义我们的头文件里面的变量。如果定义在头文件会出错
CString yourEmail;
CString yourPasswd ;
CString suffixOfEmail;

struct Base64Date6
{
	unsigned int d4:6;
	unsigned int d3:6;
	unsigned int d2:6;
	unsigned int d1:6;
};
// 协议中加密部分使用的是base64方法
char ConvertToBase64  (char   c6);
void EncodeBase64     (char   *dbuf, char *buf128, int len);
int SendMail         (char   *email,char *body);
int  OpenSocket       (struct sockaddr *addr);


int sendtopeople       (struct info information,CString *header);
int connectToSmtp();
void clean();
int count = 0;
 int flag = 0;
//成功返回0,失败返回-1
int run()
{
	int i; 
	char notice[26];
	getinformation();
	
		for(i = 2;i < RowNum+1;i++)
		{
			if(!sendtopeople(information[i],header))
				count++;
		}
	//前4封信属于探测型的吧。邮件时探测的。
		sprintf(notice,"您总共发送了%d封邮件",count);
		MessageBox(NULL,notice,"提示",MB_OK);
		//return 0;
	
 	return 0;
}

int sendtopeople(struct info information,CString *header)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	/*
	//char EmailTo[]         = *emailaddr;
	char *from = strcat(( "From: \"jaffer\"<"),emailaddr);
	//printf("%s\n",from);
	char *from1 = strcat(from,(char *)(">\r\n"));
	char *to = strcat(("To: \"jaffer\"<"),emailaddr);
	char *to1 = strcat(to,(">\r\n"));
	char *sub = "Subject: Hello\r\n\r\n";
	char *content = "HEllO ,jaffer";
	char *first = strcat(from1,to1);
	char *second = strcat(first,sub);
	char *third = strcat(second,content);
	char *EmailContents   = third;
	*/
	//第一个char版本
	/*
	char EmailContents[1024] = {'\0'};
	//EmailContents = (char *)malloc(sizeof(char) * 1024);
	//EmailContents = "From: \"jaffer\"<";
	strcat(EmailContents,"From: \"jaffer\"<");
	strcat(EmailContents,information.email);
	strcat(EmailContents,"To: \"");
	strcat(EmailContents,information.name);
	strcat(EmailContents,"\"<");
	strcat(EmailContents,information.email);
	strcat(EmailContents,">\r\n");
	strcat(EmailContents, "Subject: Hello\r\n\r\n");
	strcat(EmailContents, information.content);
	strcat(EmailContents,information.name);
	*/
	//char EmailTo[]         = emailaddr;
	/*char EmailContents[]   = "From: \"lucy\"<hanyinlong@126.com>\r\n"
		"To: \"dasiy\"<hanyinlong@126.com>\r\n"
		"Subject: Hello\r\n\r\n"
		"Hello World, Hello Email!";
		*/


	CString EmailContents;
	EmailContents = "From: \"" +information.content[1] +"\"<";//来自哪个用户
	EmailContents = EmailContents + yourEmail + "\n";//这个应该是发送者的邮箱
	EmailContents = EmailContents + "To: \"";
	EmailContents = EmailContents + information.name;
	EmailContents = EmailContents + "\"<";
	EmailContents = EmailContents + information.email;
	EmailContents = EmailContents + ">\r\n";
	EmailContents = EmailContents + "Subject: " + information.content[2] + "\r\n\r\n";
	EmailContents = EmailContents + informalize(information,header);
	//EmailContents = EmailContents + information.name;
	SendMail((LPSTR)(LPCTSTR)information.email, (LPSTR)(LPCTSTR)EmailContents);
		//return -1;
	return 0;
}

char ConvertToBase64(char uc)
{
	if(uc < 26)
	{
		return 'A' + uc;
	}
	if(uc < 52)
	{
		return 'a' + (uc - 26);
	}
	if(uc < 62)
	{
		return '0' + (uc - 52);
	}
	if(uc == 62)
	{
		return '+';
	}
	return '/';
}

// base64的实现
void EncodeBase64(char *dbuf, char *buf128, int len)
{
	struct Base64Date6 *ddd      = NULL;
	int           i        = 0;
	char          buf[256] = {0};
	char          *tmp     = NULL;
	char          cc       = '\0';

	memset(buf, 0, 256);
	strcpy_s(buf, 256, buf128);
	for(i = 1; i <= len/3; i++)
	{
		tmp             = buf + (i-1)*3;
		cc              = tmp[2];
		tmp[2]          = tmp[0];
		tmp[0]          = cc;
		ddd             = (struct Base64Date6 *)tmp;
		dbuf[(i-1)*4+0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i-1)*4+1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i-1)*4+2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i-1)*4+3] = ConvertToBase64((unsigned int)ddd->d4);
	}
	if(len % 3 == 1)
	{
		tmp             = buf + (i-1)*3;
		cc              = tmp[2];
		tmp[2]          = tmp[0];
		tmp[0]          = cc;
		ddd             = (struct Base64Date6 *)tmp;
		dbuf[(i-1)*4+0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i-1)*4+1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i-1)*4+2] = '=';
		dbuf[(i-1)*4+3] = '=';
	}
	if(len%3 == 2)
	{
		tmp             = buf+(i-1)*3;
		cc              = tmp[2];
		tmp[2]          = tmp[0];
		tmp[0]          = cc;
		ddd             = (struct Base64Date6 *)tmp;
		dbuf[(i-1)*4+0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i-1)*4+1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i-1)*4+2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i-1)*4+3] = '=';
	}
	return;
}


// 发送邮件
int SendMail(char *email, char *body)
{
	 int     sockfd     = {0};
	char    buf[1500]  = {0};
	char    rbuf[1500] = {0};
	char    login[128] = {0};
	char    pass[128]  = {0};
	char    result[4] = {0};

	WSADATA WSAData;

	struct sockaddr_in their_addr = {0};
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	memset(&their_addr, 0, sizeof(their_addr));

	their_addr.sin_family = AF_INET;
	their_addr.sin_port   = htons(25);
	hostent* hptr;
	//直接用“=”是因为suffixOfEmail是CString类型。如果是char*就不可以直接“=”
	if( (suffixOfEmail == _T("hust.edu.cn")))
		hptr = gethostbyname("mail.hust.edu.cn");
	if((suffixOfEmail == _T("163.com")))
		hptr = gethostbyname("smtp.163.com");
    if((suffixOfEmail == _T("126.com")))
		hptr = gethostbyname("smtp.126.com");
	if((suffixOfEmail == _T("qq.com")))
		hptr = gethostbyname("smtp.qq.com");
	memcpy(&their_addr.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length); 
//	printf("IP of smpt.hust.com is : %d:%d:%d:%d\n", 
	//	their_addr.sin_addr.S_un.S_un_b.s_b1, 
//		their_addr.sin_addr.S_un.S_un_b.s_b2, 
//		their_addr.sin_addr.S_un.S_un_b.s_b3, 
//		their_addr.sin_addr.S_un.S_un_b.s_b4); 

	// 连接邮件服务器，如果连接后没有响应，则2 秒后重新连接
	sockfd = OpenSocket((struct sockaddr *)&their_addr);
	memset(rbuf, 0, 1500);
	while(recv(sockfd, rbuf, 1500, 0) == 0)
	{
		cout<<"reconnect..."<<endl;
		Sleep(2);
		sockfd = OpenSocket((struct sockaddr *)&their_addr);
		memset(rbuf, 0, 1500);
	}

	cout<<rbuf<<endl;

	// EHLO
	memset(buf, 0, 1500);
	sprintf_s(buf, 1500, "EHLO HYL-PC\r\n");
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"EHLO REceive: "<<rbuf<<endl;

	// AUTH LOGIN
	memset(buf, 0, 1500);
	sprintf_s(buf, 1500, "AUTH LOGIN\r\n");
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Auth Login Receive: "<<rbuf<<endl;

	// USER
	memset(buf, 0, 1500);
	sprintf_s(buf, 1500, (LPSTR)(LPCTSTR)yourEmail);//你的邮箱账号
	memset(login, 0, 128);
	EncodeBase64(login, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", login);
	send(sockfd, buf, strlen(buf), 0);
	cout<<"Base64 UserName: "<<buf<<endl;
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"User Login Receive: "<<rbuf<<endl;

	// PASSWORD
	sprintf_s(buf, 1500, (LPSTR)(LPCTSTR)yourPasswd);//你的邮箱密码
	memset(pass, 0, 128);
	EncodeBase64(pass, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", pass);
	send(sockfd, buf, strlen(buf), 0);
	cout<<"Base64 Password: "<<buf<<endl;

	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Send Password Receive: "<<rbuf<<endl;
	//这是一个判断，用户名或者密码是否错误,只判断一次
	/*
	if(flag == 0)
	{
	int k;
	memset(result,0,4);
	for(k = 0; k < 3; k++)
		result[k] = rbuf[k];
	result[k] = '\0';
	if(strcmp(result,"235") != 0)
	{
			MessageBox(NULL,"邮箱用户名或密码错误","提示",MB_OK);
			return -1;
	}
	flag = 1;
	}
	*/
	// MAIL FROM
	memset(buf, 0, 1500);
	sprintf_s(buf, 1500, "MAIL FROM: <%s>\r\n",(LPSTR)(LPCTSTR)yourEmail);
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"set Mail From Receive: "<<rbuf<<endl;

	// RCPT TO 第一个收件人
	sprintf_s(buf, 1500, "RCPT TO:<%s>\r\n", email);
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Tell Sendto Receive: "<<rbuf<<endl;

	// DATA 准备开始发送邮件内容
	sprintf_s(buf, 1500, "DATA\r\n");
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Send Mail Prepare Receive: "<<rbuf<<endl;

	// 发送邮件内容，\r\n.\r\n内容结束标记
	sprintf_s(buf, 1500, "%s\r\n.\r\n", body);
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Send Mail Receive: "<<rbuf<<endl;
	//t++;
	

	//return 0;

//清理工作
	// QUIT
	sprintf_s(buf, 1500, "QUIT\r\n");
	send(sockfd, buf, strlen(buf), 0);
	memset(rbuf, 0, 1500);
	recv(sockfd, rbuf, 1500, 0);
	cout<<"Quit Receive: "<<rbuf<<endl;

	closesocket(sockfd);
	WSACleanup();
	return 0;
}
// 打开TCP Socket连接
int OpenSocket(struct sockaddr *addr)
{
	int sockfd = 0;
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		cout<<"Open sockfd(TCP) error!"<<endl;
		exit(-1);
	}
	if(connect(sockfd, addr, sizeof(struct sockaddr)) < 0)
	{
		cout<<"Connect sockfd(TCP) error!"<<endl;
		exit(-1);
	}
	return sockfd;
} 
