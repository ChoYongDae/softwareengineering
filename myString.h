// ��Ʈ�� ���� �Լ� ���� ���

#include <iostream>

using namespace std;

//////// ��� ���� ������ //////////////////////////////////////////////////////

#define PrintTop cout<<"  Welcome to JSW market\t\t\t\t\t\t("<<_usr<<"-th user)"<<endl<<"-----------------------------------------------------------------------------"<<endl;
#define PrintLine cout<<"-----------------------------------------------------------------------------"<<endl;

//////////////////////////////////////////////////////////////////////////////

//////// string ���� �Լ� //////////////////////////////////////////////////////

// �Է¹��� ���ڿ� �迭�� ���Ŀ� �°� �Ľ��ϴ� �Լ�
void productInfo(char tmp[],char _name[], int &_price, int &_stock, char _cat[],char _loc[]);
void salesInfo(char tmp[],char _name[],int &_num,char _dc[]);

// ���ڿ� �迭�� �ٸ��迭�� �����ϴ� �Լ�
void myStrcpy(char result[], char source[]);
void myStrcpy(char result[], int source);

// ���ڿ��� ���������� ��ȯ�ϴ� �Լ�
int cToi(char ch[]);

// �� ���ڿ��� ������ ���ϴ� �Լ�
bool myStrcmp(char ch1[], char ch2[]);
bool myStrcmp(char ch1[], int n);

// strtok ����
char *myStrtok(char token[],char del,char result[]);

//////////////////////////////////////////////////////////////////////////////
