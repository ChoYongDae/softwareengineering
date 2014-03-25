#include <iostream>
#include "myString.h"

using namespace std;


//////// string �Լ� ���� ////////////////////////////////////////////////////

// �Է¹��� ���ڿ� �迭�� ���Ŀ� �°� �Ľ��ϴ� �Լ� (��ǰ ����)
void productInfo(char tmp[],char _name[], int &_price, int &_stock, char _cat[],char _loc[])
{
	char bfr[50];	// �ӽ� ����

	// tmp���� �ش� ������ �Ľ��� ����
	myStrtok(tmp,' ',_name);
	myStrtok(tmp,' ',bfr);
	_price=cToi(bfr);
	myStrtok(tmp,' ',bfr);
	_stock=cToi(bfr);
	myStrtok(tmp,' ',_cat);
	myStrtok(tmp,' ',_loc);
}

// �Է¹��� ���ڿ� �迭�� ���Ŀ� �°� �Ľ��ϴ� �Լ� (�Ǹ� ����)
void salesInfo(char tmp[],char _name[],int &_num,char _dc[])
{
	char bfr[50];	// �ӽ� ����

	// tmp���� �ش� ������ �Ľ��� ����
	myStrtok(tmp,' ',_name);
	myStrtok(tmp,' ',bfr);
	myStrtok(tmp,' ',bfr);
	_num=cToi(bfr);
	myStrtok(tmp,' ',_dc);
}

// ���ڿ� �迭�� �ٸ��迭�� �����ϴ� �Լ�
void myStrcpy(char result[], char source[])
{
	int i;
	for(i=0;source[i]!=NULL;i++)	// source�� ������ result�� ����
		result[i]=source[i];
	result[i]=NULL;	// result �������� NULL ����
}

// ���ڸ� ���ڿ��� �����ϴ� �Լ�
void myStrcpy(char result[], int source)
{
	result[0]=source;
	result[1]=NULL;
}

// ���ڿ��� ���������� ��ȯ�ϴ� �Լ�
int cToi(char ch[])
{
	int result=0;

	for(int i=0;ch[i]!=NULL;i++)	// ch������
	{
		result*=10;			// �ڸ��� ����
		result+=ch[i]-48;	// �ƽ�Ű�ڵ� �̿��� ���� ����
	}

	return result;
}

// �� ���ڿ��� ������ ���ϴ� �Լ�
bool myStrcmp(char ch1[], char ch2[])
{
	int i;
	for(i=0;ch1[i]!=NULL;i++)	// ch1������
	{
		if(ch1[i]==ch2[i])	// ch1�� ch2�� ������ ���� ��
			continue;
		else				// �ٸ��� ���� ��ȯ
			return false;
	}
	if(ch2[i]==NULL)		// for�� ���� �� ch2 �������� �ΰ������� ����ȯ
		return true;
	else
		return false;
}

// �� ���ڿ��� ������ ���ϴ� �Լ� (���ڿ� ���� ��)
bool myStrcmp(char ch1[], int n)
{
	if((int)ch1[0]==n)
		return true;
	else
		return false;
}

// strtok ����
char *myStrtok(char token[],char del,char result[])
{
	int j=0;	// result �ε���
	for(int i=0;token[i]!=NULL;i++)		// token�� ������
	{
		if(token[i]==del)		// token[i]�� del�� ������ ���
			continue;
		else					// token[i]�� del�� �ٸ���
		{
			// token[i]�� del�� ���ų� ���� �ɶ����� token�� result�� ����
			while(!(token[i]==del||token[i]==NULL))
			{
				result[j]=token[i];
				token[i]=del;
				j++;i++;
			}
			result[j]=NULL;	// result �������� �� ����
			return result;
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////