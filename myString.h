// 스트링 관련 함수 구현 헤더

#include <iostream>

using namespace std;

//////// 출력 위한 디파인 //////////////////////////////////////////////////////

#define PrintTop cout<<"  Welcome to JSW market\t\t\t\t\t\t("<<_usr<<"-th user)"<<endl<<"-----------------------------------------------------------------------------"<<endl;
#define PrintLine cout<<"-----------------------------------------------------------------------------"<<endl;

//////////////////////////////////////////////////////////////////////////////

//////// string 관련 함수 //////////////////////////////////////////////////////

// 입력받은 문자열 배열을 형식에 맞게 파싱하는 함수
void productInfo(char tmp[],char _name[], int &_price, int &_stock, char _cat[],char _loc[]);
void salesInfo(char tmp[],char _name[],int &_num,char _dc[]);

// 문자열 배열을 다른배열에 복사하는 함수
void myStrcpy(char result[], char source[]);
void myStrcpy(char result[], int source);

// 문자열을 정수형으로 변환하는 함수
int cToi(char ch[]);

// 두 문자열이 같은지 비교하는 함수
bool myStrcmp(char ch1[], char ch2[]);
bool myStrcmp(char ch1[], int n);

// strtok 구현
char *myStrtok(char token[],char del,char result[]);

//////////////////////////////////////////////////////////////////////////////
