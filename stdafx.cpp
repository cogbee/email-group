/******************************
这个下标一定注意了。与我们平时想的不一样。

********************************/

// stdafx.cpp : 只包括标准包含文件的源文件
// sendemail.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息
#include "stdafx.h"//这个头文件必须在第一个位置
#include "CSpreadSheet.h"

struct info information[MAX];
CString header[MAX];
int RowNum,RowSize;
CString path;

void print(struct info information);
int getinformation()
{
	CSpreadSheet SS(path, "");

	CStringArray Rows, Column;
	RowNum = SS.GetTotalRows();
	if(RowNum > MAX)
	{
	printf("error,the number of people is bigger than defined.");
	exit(0);
	}
	int i,j,k;
	
	//CString strContents = "";
	//清空列表框
	//m_AccessList.ResetContent();
	//从第1行开始读取,i=1代表的是表头。从2开始是数据。
	for (i = 1; i <= SS.GetTotalRows(); i++)
	{
		// 读取一行
		SS.ReadRow(Rows, i);
		//int j = 0;
		RowSize = Rows.GetSize();
		
		//将头存放在header
		if(i == 1)
		{
			for (j = 1; j <= Rows.GetSize(); j++)
			{
				header[j] = Rows.GetAt(j-1);//这个必须从j-1开始。
				//strcpy(header[j],Rows.GetAt(j));
			}
		}
		else
		{
		//int j =0;
		//printf("%d\n",Rows.GetSize());
		/*
		for ( j = 1; j <= Rows.GetSize(); j++)
		{
			
			if(j == 1)
				strContents[i] = Rows.GetAt(j-1);
			else
				strContents[i] = strContents[i] +  "\n" + Rows.GetAt(j-1);
		}
		*/
			j = 1;//重新定j的值
			information[i].ID = Rows.GetAt(j-1);
			information[i].name = Rows.GetAt(j);
		    information[i].pro = Rows.GetAt(j+1);
			information[i].email = Rows.GetAt(j+2);
			//j = 3;
			k = 1;
			for(j = 5; j <= Rows.GetSize();j++)
			//while(j <= Rows.GetSize())
			{
				//j++;
				information[i].content[k++] = Rows.GetAt(j-1);
				//information[i-1].content[k++]= information[i-1].content + '\n';
			}
			CString buf;
			buf = informalize(information[i],header);
			printf("%s\n",buf);
			//print(information[i]);
		//printf("%s\n",strContents[i]);
		}//else
		//m_AccessList.AddString(strContents);
	}
	return 0;

}

CString informalize(struct info information,CString *header)
{
	int headc = 7;
	int j = 3;
	CString body = "";
	body = information.name + information.pro +" 您好！";
	body = body + "\n";
	body = body + information.content[j++] + "\n";
	headc++;
	//int headc = 5;
	//这要求之前的必须固定
	while(j <= RowSize-4)
		body = body + header[headc++] + " " + information.content[j++] + "\n";
	//printf("%s\n",body);
	return body;
}



void print(struct info information)
{
	//int i,j;
	//i = 2;
	int j = 1;
	int headc = 1;
	//while(i < RowNum)
	
		printf("---------------------------------\n");
		printf("%s:%s\n",header[headc++],information.ID);
		printf("%s:%s\n",header[headc++],information.name);
		printf("%s:%s\n",header[headc++],information.pro);
		printf("%s:%s\n",header[headc++],information.email);
		while(j < RowSize-3)
		printf("%s:%s\n",header[headc++],information.content[j++]);
		//i++;
}
/*
int main()
{
	getinformation();
	return 0;
}
*/
