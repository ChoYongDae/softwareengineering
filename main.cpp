#include <iostream>
#include <iomanip>
#include <fstream>
#include "myDataStructure.h"	// Ŭ���� ����
#include "myString.h"			// ��Ʈ�� ���� ��� ����

using namespace std;

//////// define, �۷ι� ���� /////////////////////////////////////////////////////

int _sel=0;	// ����� �޴� ����
int _usr=1;	// ���� ī��Ʈ
List LIST;	// ��ǰ ����Ʈ

// ������ ���Ͽ��� ��ǰ���� �Ľ��� ������ ������
char tmp[200];
char _name[40], _loc[20], _cat[20], _dc[7];
int _price, _stock, _num;

////////////////////////////////////////////////////////////////////////////////

//////// �޴� ���� �Լ� ///////////////////////////////////////////////////////

void MainMenu();		// ���� �޴�
void CatSearch();		// ī�װ� ��ǰ �˻�
void LocSearch();		// ���� ��ǰ �˻�
void PurList();			// ���� ����Ʈ
void NormPur();			// �Ϲݱ���
void GroupPur();		// ��������
void Refund();			// ȯ��

//////////////////////////////////////////////////////////////////////////////

void InitSales(ifstream &Isales,int _usr);	// �Ǹ� �������� �޾Ƽ� ������ �ʱ� �����ϴ� �Լ�

//////// ���� ���� ///////////////////////////////////////////////////////////

int main()
{
	// input file��
	ifstream Iproduct,Isales;
	Iproduct.open("product_list.dat");	// ��ǰ ���� ����
	Isales.open("sales_list.dat");		// �Ǹ� ���� ����

	// input ���� open ������ �޼��� ���
	if(Iproduct.fail()||Isales.fail())
	{
		cout<<"Data File Open Error!!"<<endl;
		return 0;
	}

	// ��ǰ �������� �о LIST �ʱ� ����
	while(!Iproduct.eof())
	{
		Iproduct.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		productInfo(tmp,_name,_price,_stock,_cat,_loc);
		LIST.Insert(_name,_price,_stock,_cat,_loc);
	}

	// ��ǰ �Ǹ� �������� �о LIST �ʱ� ����
	Isales.getline(tmp,200);
	if(myStrcmp(tmp," �� �Ǹ� ���"))	// ��ǰ �Ǹ��������Ͽ� �ƹ��͵� ������ ���� ����
	{
		// usr1-3 �Ǹ� ���� �Է�
		InitSales(Isales,1);
		InitSales(Isales,2);
		InitSales(Isales,3);
	}

	// input ���� ����
	Iproduct.close();
	Isales.close();

	// usr1-3���� �ݺ�
	while(_usr<4)
	{
		system("cls");	// ȭ�� �ʱ�ȭ
		
		// ���° �������� ���
		PrintLine;
		cout<<endl<<endl<<endl<<endl;
		cout<<setw(32)<<right<<_usr<<"-th user Login"<<endl;
		cout<<endl<<endl<<endl<<endl;
		PrintLine;
		
		system("pause");
		MainMenu();		// ���θ޴� ȣ��
		_usr++;			// ���θ޴� ���� �� usr ������Ŵ
	}

	system("cls");	// ȭ�� �ʱ�ȭ

	// output ���ϵ�
	ofstream Oproduct,Osales;
	Oproduct.open("product_list.dat");
	Osales.open("sales_list.dat");

	// LIST�� ������ output���Ͽ� ���
	LIST.Print(Oproduct);
	LIST.FPrintSales(Osales);

	// output ���� ����
	Oproduct.close();
	Osales.close();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////

//////// �޴� �Լ� ���� ///////////////////////////////////////////////////////

// ���� �޴�
void MainMenu()
{
	while(1)
	{
		_sel=0;
		system("cls");		// ȭ�� �ʱ�ȭ
		PrintTop;
		// �޴� ���
		cout<<"\t1. ī�װ� ��ǰ �˻�"<<endl;
		cout<<"\t2. ���� ��ǰ �˻�"<<endl;
		cout<<"\t3. ���� ����Ʈ"<<endl;
		cout<<"\t4. ����"<<endl;
		cout<<"\t>> ";
		// �Է� ���� �ʱ�ȭ
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// �Է¹��� �޴� ȣ��
		if(_sel==1)
			CatSearch();
		else if(_sel==2)
			LocSearch();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// ī�װ� ��ǰ �˻�
void CatSearch()
{
	while(1)
	{
		_sel=0;
		system("cls");		// ȭ�� �ʱ�ȭ
		PrintTop;
		cout<<" ī�װ� ��ǰ �˻� ���"<<endl<<endl;
		LIST.Print(2);	// ī�װ��� ��ǰ ���

		// �޴� ���
		PrintLine;
		cout<<setw(30)<<left<<"\t1. �Ϲ� ����"<<"2. ���� ����"<<endl<<setw(30)<<left<<"\t3. ���� ����Ʈ"<<"4. ���� �޴�"<<endl;
		cout<<"\t>> ";
		// �Է� ���� �ʱ�ȭ
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// �Է¹��� �޴� ȣ��
		if(_sel==1)
			NormPur();
		else if(_sel==2)
			GroupPur();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// ���� ��ǰ �˻�
void LocSearch()
{
	while(1)
	{
		_sel=0;
		system("cls");		// ȭ�� �ʱ�ȭ
		PrintTop;
		cout<<" ���� ��ǰ �˻� ���"<<endl<<endl;
		LIST.Print(1);	// ������ ��ǰ ���
		
		// �޴� ���
		PrintLine;
		cout<<setw(30)<<left<<"\t1. �Ϲ� ����"<<"2. ���� ����"<<endl<<setw(30)<<left<<"\t3. ���� ����Ʈ"<<"4. ���� �޴�"<<endl;
		cout<<"\t>> ";
		// �Է� ���� �ʱ�ȭ
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// �Է¹��� �޴� ȣ��
		if(_sel==1)
			NormPur();
		else if(_sel==2)
			GroupPur();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// ���� ����Ʈ
void PurList()
{
	while(1)
	{
		_sel=0;
		system("cls");		// ȭ�� �ʱ�ȭ
		PrintTop;
		LIST.PrintUsr(_usr);	// ���� ������ ���Ÿ���Ʈ ���

		PrintLine;
		cout<<setw(30)<<left<<"\t1. ȯ��"<<"2. ���� �޴�"<<endl;
		cout<<"\t>> ";
		// �Է� ���� �ʱ�ȭ
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		if(_sel==1)
			Refund();
		else if(_sel==2)
			break;
		else
			continue;
	}
}

// �Ϲݱ���
void NormPur()
{
	char PerName[40];
	int PerNum;

	// �Է¹��� �ʱ�ȭ
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// ������ ��ǰ�̸�, ���� �Է�
	cout<<endl<<"\t������ ��ǰ���� �Է����ֽʽÿ� : ";
	cin.getline(PerName,40);
	cout<<"\t������ ������ �Է����ֽʽÿ� : ";
	cin>>PerNum;

	// �Է¹��� ��ǰ�̸�, �������� Pur�Լ� ȣ��
	if(LIST.Pur(_usr,PerName,PerNum,0))		// Pur�Լ��� ������ �Ű������� �Ϲݱ���, �������Ÿ� �ǹ��� (0:�Ϲ�,1:����)
		cout<<endl<<endl<<"\t"<<PerName<<" "<<PerNum<<"�� ���� �Ϸ�Ǿ����ϴ�."<<endl<<endl;
	
	system("pause");	// ���� �Ϸ� Ȯ���� ���� �Ͻ� ����
}

// ��������
void GroupPur()
{
	char PerName[40];
	int PerNum;

	// �Է� ���� �ʱ�ȭ
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// ���������� ��ǰ��, ���� �Է�
	cout<<endl<<"\t���������� ��ǰ���� �Է����ֽʽÿ� : ";
	cin.getline(PerName,40);
	cout<<"\t���������� ������ �Է����ֽʽÿ� : ";
	cin>>PerNum;

	// �Է¹��� ��ǰ��, �������� ��������
	if(LIST.Pur(_usr,PerName,PerNum,1))	// Pur�Լ��� ������ �Ű������� �Ϲݱ���, �������Ÿ� �ǹ��� (0:�Ϲ�,1:����)
		cout<<endl<<endl<<"\t"<<PerName<<" "<<PerNum<<"�� ���� �Ϸ�Ǿ����ϴ�."<<endl<<endl;
	
	system("pause");	// ���ſϷ� Ȯ���� ���� �Ͻ� ����
}

// ȯ��
void Refund()
{
	char RefName[40];

	// �Է� ���� �ʱ�ȭ
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// ȯ���� ��ǰ�� �Է�
	cout<<endl<<"\tȯ���� ��ǰ���� �Է����ֽʽÿ� : ";
	cin.getline(RefName,40);
	
	// �Է¹��� ��ǰ������ ȯ��
	if(LIST.Ref(_usr,RefName))	// ȯ�� ������ �޼��� ���
		cout<<endl<<endl<<"\t"<<RefName<<" ȯ�� �Ϸ�Ǿ����ϴ�."<<endl<<endl;
	else						// ȯ�� ���н� �޼��� ���
		cout<<endl<<setw(55)<<right<<"=== �ش� ��ǰ�� �����ϴ� ==="<<endl<<endl;

	system("pause");		// ȯ�� �Ϸ� Ȯ���� ���� �Ͻ� ����
}

//////////////////////////////////////////////////////////////////////////////

// �ʱ� LIST �Ǹ� ���� ������Ʈ
void InitSales(ifstream &Isales,int _usr)
{
	// ����1�̸� ���� ���� ����
	if(_usr==1)
		Isales.getline(tmp,200);

	// ���° �������� Ȯ���ϱ� ���� ���� ����
	char bfr[15]="  >> 0-th user";
	bfr[5]=(char)(_usr+48);

	while(!myStrcmp(tmp,bfr))		// ���� �̸� Ȯ�εɶ����� ������ ����
		Isales.getline(tmp,200);

	// ���� �̸� Ȯ�� �� �����ٿ� �ٷ� ���� ���� �̸��� ������ Ż��
	Isales.getline(tmp,200);
	bfr[5]++;
	if(myStrcmp(tmp,bfr)||Isales.eof())
		return;

	// �Ϲݱ��� ������ ã������ Ž��
	while(!myStrcmp(tmp,"      �� ���� ��ǰ ����Ʈ"))
		Isales.getline(tmp,200);
	while(!myStrcmp(tmp,"                 ǰ    ��             ��  ��    ����  ��  ��    ��  ��"))
		Isales.getline(tmp,200);
	// ������ �Է¹޾� �Ľ� �� LIST�� �߰�
	while(1)
	{
		Isales.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		salesInfo(tmp,_name,_num,_dc);		// �Ľ� �Լ�
		if(_dc[0]!=' ')						// dc�� ù��° ���� �����̸�
			LIST.Update(_usr,_name,_num,0);	// �Ϲݱ��ŷ� ó��
		else								// ������ �ƴϸ�
			LIST.Update(_usr,_name,_num,1);	// �������ŷ� ó��
	}

	// �Ϲݱ��� ������ ã������ Ž��
	while(!myStrcmp(tmp,"      �� �������� ���� ��ǰ ����Ʈ"))
		Isales.getline(tmp,200);
	while(!myStrcmp(tmp,"                 ǰ    ��             ��  ��    ����  ��  ��    ��  ��"))
		Isales.getline(tmp,200);
	// ������ �Է¹޾� �Ľ� �� LIST�� �߰�
	while(1)
	{
		Isales.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		salesInfo(tmp,_name,_num,_dc);
		LIST.Update(_usr,_name,_num,1);	// �������ŷ� ó��
	}
}