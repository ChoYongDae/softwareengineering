#include <iostream>
#include <fstream>
#include "myString.h"		// ��Ʈ�� ���� ���

using namespace std;

//////// Ŭ���� ���� /////////////////////////////////////////////////////////

// ��ǰ ���
class Product
{
	// friend class�� ������ ���� �����ϰ� ��
	friend class List;
	friend class Title;
private:
	char Pname[40];		// ��ǰ �̸�
	int Pprice;			// ��ǰ �ܰ�
	int Pstock;			// ��ǰ ���
	int Pnum;			// ��ǰ �Ǹ� ����
	int U1num;			// Usr1 ���� ����
	int U2num;			// Usr2 ���� ����
	int U3num;			// Usr3 ���� ����
	bool U1Gpur;		// Usr1 �������� ����
	bool U2Gpur;		// Usr2 �������� ����
	bool U3Gpur;		// Usr3 �������� ����
	char PLoc[20];		// ��ǰ ����
	char PCat[20];		// ��ǰ ī�װ�
	Product *Clink;		// ��ǰ ī�װ��� ��ũ
	Product *Llink;		// ��ǰ ��ġ�� ��ũ
	Product *U1link;	// ����1 ��ũ
	Product *U2link;	// ����2 ��ũ
	Product *U3link;	// ����3 ��ũ
public:
	Product();			// ������
};

// product ������
Product::Product()
{
	// ��� ��ũ �η� �ʱ�ȭ
	Clink=NULL;Llink=NULL;U1link=NULL;U2link=NULL;U3link=NULL;
	// ��� int�� ������ 0���� �ʱ�ȭ
	Pnum=0;U1num=0;U2num=0;U3num=0;
	// ��� bool�� ������ false�� �ʱ�ȭ
	U1Gpur=false;U2Gpur=false;U3Gpur=false;
}

// ��ǰ���� ����Ʈ�� ���� Ÿ��Ʋ
class Title
{
	friend class List;
private:
	char Tname[20];		// Ÿ��Ʋ �̸�
	Title *Tlink;		// Ÿ��Ʋ ��ũ
	Product *Plink;		// ��ǰ ��ũ
public:
	Title() {Tlink=NULL;Plink=NULL;};	// ������
};

// �⺻ ����Ʈ
class List
{
private:
	Title *Lhead;	// ���� ���
	Title *Chead;	// ī�װ� ���
	Title *Uhead;	// ���� ���
public:
	List();			// ������
	~List();		// �Ҹ���
	void Insert(char _name[40],int _price,int _stock,char _cat[20],char _loc[20]);	// ����Ʈ�� ��ǰ �Է��ϴ� �Լ�
	void Update(int _usr,char _pername[40],int _pernum,int _gpur);					// ����Ʈ�� �Ǹ����� ������Ʈ�ϴ� �Լ�
	bool Pur(int _usr,char _pername[40],int _pernum,int _gpur);						// ���� �Լ�
	void AddUsrList(int _usr,Product *pro);											// ���� ����Ʈ�� ������ ��ǰ �߰��ϴ� �Լ�
	bool Ref(int _usr,char _refname[40]);											// ȯ�� �Լ�
	void DelUsrList(int _usr,Product *pro);											// ȯ���� ��ǰ ��������Ʈ���� �����ϴ� �Լ�
	void Print(int n);																// ����Ʈ ����ϴ� �Լ�(n=1:������ ���,n=2:ī�װ��� ���)
	void Print(ofstream &product);													// ����Ʈ�� ��ǰ ������ ���Ͽ� ����ϴ� �Լ�
	void PrintUsr(int _usr);														// ���� ���� ����Ʈ ��� �Լ�
	void PrintUsr(int _usr,ofstream &sales);										// ���� ���� ����Ʈ�� ���Ϸ� ����ϴ� �Լ�
	void FPrintSales(ofstream &sales);												// �Ǹ� ������ ���Ϸ� ����ϴ� �Լ�
};

// List ������
List::List()
{
	// ��� ��ũ �η� �ʱ�ȭ
	Lhead=NULL;Chead=NULL;;

	// ���� ����Ʈ �ʱ�ȭ
	Title *nTitle1=new Title;
	myStrcpy(nTitle1->Tname,1);
	Uhead=nTitle1;
	Title *nTitle2=new Title;
	myStrcpy(nTitle2->Tname,2);
	nTitle1->Tlink=nTitle2;
	Title *nTitle3=new Title;
	myStrcpy(nTitle3->Tname,3);
	nTitle2->Tlink=nTitle3;
}

// List �Ҹ���
List::~List()
{
	Title *Tpre, *Tcur;		// Ÿ��Ʋ Ž����
	Product *Ppre, *Pcur;	// ��ǰ Ž����

	// ������ ��ũ�� �������� ������
	if(Lhead!=NULL)	// ���� ����� ���� �ƴϸ�
	{
		Tcur=Lhead;	// Ÿ��Ʋ �ʱ� ����
		while(Tcur->Tlink!=NULL)			// Ÿ��Ʋ�� ���϶����� Ž��
		{
			Pcur=Tcur->Plink;			// ��ǰ Ž�� �ʱ� ����
			while(Pcur->Llink!=NULL)		// ��ǰ ������ Ž��
			{
				// ������ǰ���� �̵��� ���� ��ǰ ����
				Ppre=Pcur;
				Pcur=Pcur->Llink;
				delete Ppre;
			}
			delete Pcur;	// ������ ���� ��ǰ ����

			// ���� Ÿ��Ʋ�� �̵��� ���� Ÿ��Ʋ ����
			Tpre=Tcur;
			Tcur=Tcur->Tlink;
			delete Tpre;
		}
		delete Tcur;	// ������ Ÿ��Ʋ ����
	}
}

// ����Ʈ�� ��ǰ �Է��ϴ� �Լ�
void List::Insert(char _name[40],int _price,int _stock,char _cat[20],char _loc[20])
{
	// �� ��ǰ ���� �� ��ǰ ���� �Է�
	Product *nPro= new Product;
	myStrcpy(nPro->Pname,_name);
	myStrcpy(nPro->PCat,_cat);
	myStrcpy(nPro->PLoc,_loc);
	nPro->Pprice=_price;
	nPro->Pstock=_stock;

	// ���� ����Ʈ
	if(Lhead==NULL)	// ���� ����� ���̸�
	{
		// �� ���� �߰� �� �� ������ �� ��ǰ �߰�
		Title *nTitle=new Title;
		myStrcpy(nTitle->Tname,nPro->PLoc);
		Lhead=nTitle;
		nTitle->Plink=nPro;
	}
	else			// ���� ����� ���� �ƴϸ�
	{
		Title *Tcur;
		Product *Pcur;

		for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// Ÿ��Ʋ�� ��ũ�� ���϶�����
		{
			if(myStrcmp(Tcur->Tname,nPro->PLoc))		// ���� ������ �̸��� ����ǰ�� ���� �̸��� ���ٸ�
			{
				// ���� ������ �ǳ��� ��ǰ �߰�
				Pcur=Tcur->Plink;
				for(Pcur=Tcur->Plink;Pcur->Llink!=NULL;Pcur=Pcur->Llink);
				Pcur->Llink=nPro;
				break;
			}
			else
			{
				if(Tcur->Tlink==NULL)				// ������ ������ ���
				{
					// �� ���� �߰� �� �������� �� ��ǰ �߰�
					Title *nTitle=new Title;
					myStrcpy(nTitle->Tname,nPro->PLoc);
					Tcur->Tlink=nTitle;
					nTitle->Plink=nPro;
					break;
				}
			}
		}
	}

	// ī�װ� ����Ʈ
	if(Chead==NULL)	// ���� ����� ���̸�
	{
		// �� ī�װ� �߰� �� ��ī�װ��� �� ��ǰ �߰�
		Title *nTitle=new Title;
		myStrcpy(nTitle->Tname,nPro->PCat);
		Chead=nTitle;
		nTitle->Plink=nPro;
	}
	else			// ���� ����� ���� �ƴϸ�
	{
		Title *Tcur;
		Product *Pcur;

		for(Tcur=Chead;Tcur!=NULL;Tcur=Tcur->Tlink)	// ī�װ��� ��ũ�� ���϶�����
		{
			if(myStrcmp(Tcur->Tname,nPro->PCat))		// ���� ī�װ��� �̸��� ����ǰ�� ���� �̸��� ���ٸ�
			{
				// ���� ī�װ��� �ǳ��� ��ǰ �߰�
				Pcur=Tcur->Plink;
				for(Pcur=Tcur->Plink;Pcur->Clink!=NULL;Pcur=Pcur->Clink);
				Pcur->Clink=nPro;
				break;
			}
			else
			{
				if(Tcur->Tlink==NULL)				// ������ ī�װ��� ���
				{
					// �� ī�װ� �߰� �� ��ī�װ��� �� ��ǰ �߰�
					Title *nTitle=new Title;
					myStrcpy(nTitle->Tname,nPro->PCat);
					Tcur->Tlink=nTitle;
					nTitle->Plink=nPro;
					break;
				}
			}
		}
	}
}

// ����Ʈ�� �Ǹ����� ������Ʈ�ϴ� �Լ�
void List::Update(int _usr,char _pername[40],int _pernum,int _gpur)
{
	// ���� �������� ������Ʈ��
	if(Lhead!=NULL)	// ���� ����� ���� �ƴϸ�
	{
		// ���� �ʱ� ����
		Title *Tcur=Lhead;
		Product *Pcur;
		while(Tcur!=NULL)	// ������ ���� �ƴҶ�����
		{
			Pcur=Tcur->Plink;	// ��ǰ �ʱ� ����
			while(Pcur!=NULL)	// ��ǰ�� ���� �ƴҶ�����
			{
				if(myStrcmp(Pcur->Pname,_pername))	// ���� ��ǰ�� �̸��� ������Ʈ�� ��ǰ�� �̸��� ������
				{
					Pcur->Pnum+=_pernum;				// ���� ��ǰ�� �Ǹ� ������ ������Ʈ�� ������ ���Ѵ�
					switch(_usr)					// ������ ���� ���� ������Ʈ(���� ���Ű���, �������ſ���)
					{
					case 1:
						Pcur->U1num+=_pernum;
						if(_gpur) Pcur->U1Gpur=true;
						break;
					case 2: 
						Pcur->U2num+=_pernum;
						if(_gpur) Pcur->U2Gpur=true;
						break;
					case 3: 
						Pcur->U3num+=_pernum;
						if(_gpur) Pcur->U3Gpur=true;
						break;
					}
					AddUsrList(_usr,Pcur);	// ��������Ʈ�� �߰�
					return;
				}
				else
					Pcur=Pcur->Llink;	// ���� ��ǰ����
			}
			Tcur=Tcur->Tlink;			// ���� ��������
		}
	}
}

// ���� �Լ�
bool List::Pur(int _usr,char _pername[40],int _pernum,int _gpur)
{
	// ���� ��������
	if(Lhead!=NULL)		// ��������� ���� �ƴϸ�
	{
		// �ʱ� ����
		Title *Tcur=Lhead;
		Product *Pcur;
		while(Tcur!=NULL)		// ������
		{
			Pcur=Tcur->Plink;	// �ʱ� ����
			while(Pcur!=NULL)	// ��ǰ ������
			{
				if(myStrcmp(Pcur->Pname,_pername))	// ���� ��ǰ�� �̸��� ������ ��ǰ�� �̸��� ������
				{
					if(!(Pcur->Pstock<_pernum))		// ��� ���ż������� ������
					{
						Pcur->Pstock-=_pernum;		// ��� ����
						Pcur->Pnum+=_pernum;			// ���ż��� ����
						switch(_usr)				// ������ ���� ���� ������Ʈ(���� ���ż���, �������� ����)
						{
						case 1: 
							Pcur->U1num+=_pernum;
							if(_gpur) Pcur->U1Gpur=true;
							break;
						case 2: 
							Pcur->U2num+=_pernum;
							if(_gpur) Pcur->U2Gpur=true;
							break;
						case 3: 
							Pcur->U3num+=_pernum;
							if(_gpur) Pcur->U3Gpur=true;
							break;
						}
						AddUsrList(_usr,Pcur);	// ���� ����Ʈ�� �߰�
						return true;
					}
					else		// ��� �����ϸ� �޼��� ���
					{
						cout<<endl<<setw(50)<<right<<"=== ��� �����մϴ� ==="<<endl<<endl;
						return false;
					}
				}
				else
					Pcur=Pcur->Llink;		// ���� ��ǰ����
			}
			Tcur=Tcur->Tlink;				// ���� ��������
		}
	}

	// �˻� ���н� �޼��� ���
	cout<<endl<<setw(55)<<right<<"=== �ش� ��ǰ�� �����ϴ� ==="<<endl<<endl;
	return false;
}

// ���� ����Ʈ�� ���� ��ǰ �߰��ϴ� �Լ�
void List::AddUsrList(int _usr,Product *pro)
{
	Title *Tcur;
	Product *Pcur;

	for(Tcur=Uhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// Ÿ��Ʋ�� ��ũ�� ���϶�����
	{
		if(myStrcmp(Tcur->Tname,_usr))		// ���� Ÿ��Ʋ�� �̸��� ����ǰ�� ����� �̸��� ���ٸ�
		{
			// ���� Ÿ��Ʋ�� �ǳ��� ��ǰ �߰�
			Pcur=Tcur->Plink;
			switch(_usr)
			{
			case 1:
				if(Pcur==NULL)			// ��ǰ�� �������
					Tcur->Plink=pro;		// �� ó������ �߰�
				else
				{
					for(;Pcur->U1link!=NULL;Pcur=Pcur->U1link)	// �ǵڱ���
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					Pcur->U1link=pro;
				}
				break;
			case 2:
				if(Pcur==NULL)
					Tcur->Plink=pro;
				else
				{
					for(;Pcur->U2link!=NULL;Pcur=Pcur->U2link)
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					Pcur->U2link=pro;
				}
				break;
			case 3:
				if(Pcur==NULL)
					Tcur->Plink=pro;
				else
				{
					for(;Pcur->U3link!=NULL;Pcur=Pcur->U3link)
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// �̹� ����Ʈ�� ��ǰ�� ������ Ż��
							return;
					Pcur->U3link=pro;
				}
				break;
			}
			break;		// ��ǰ �߰��� Ż��
		}
	}

}

// ȯ�� �Լ�
bool List::Ref(int _usr,char _refname[40])
{
	Title *Tcur;
	Product *Pcur;

	// ���� ��������
	if(Lhead!=NULL)
	{
		Tcur=Lhead;	// �ʱ� ����
		while(Tcur!=NULL)	// ���� ������
		{
			Pcur=Tcur->Plink;	// ��ǰ �ʱ� ����
			while(Pcur!=NULL)	// ��ǰ ������
			{
				if(myStrcmp(Pcur->Pname,_refname))	// ȯ���� ��ǰ�̸��� ���� ��ǰ�̸��� ������
				{
					switch(_usr)					// ����ڿ� ���� ó��
					{
					case 1:
						Pcur->Pstock+=Pcur->U1num;	// ��� ȯ�� ���� ����
						Pcur->Pnum-=Pcur->U1num;		// ��ǰ �Ǹż��� ����
						Pcur->U1num=0;				// ���� ���ż��� ����
						break;
					case 2: 
						Pcur->Pstock+=Pcur->U2num;
						Pcur->Pnum-=Pcur->U2num;
						Pcur->U2num=0;
						break;
					case 3: 
						Pcur->Pstock+=Pcur->U3num;
						Pcur->Pnum-=Pcur->U3num;
						Pcur->U3num=0;
						break;
					}
					DelUsrList(_usr,Pcur);		// ��������Ʈ���� ��ǰ ����

					return true;
				}
				else
					Pcur=Pcur->Llink;		// ���� ��ǰ����
			}
			Tcur=Tcur->Tlink;				// ���� ��������
		}
	}

	return false;
}

// ���� ���� ����Ʈ���� ��ǰ �����ϴ� �Լ�
void List::DelUsrList(int _usr,Product *pro)
{
	// �ʱ� ����
	Title *Tcur=Uhead;
	Product *Ppre=NULL,*Pcur;

	while(Tcur!=NULL)	// ���� ������
	{
		if(myStrcmp(Tcur->Tname,_usr))	// ���� ������ �Է¹��� ������ ������ Ż��
			break;
		Tcur=Tcur->Tlink;				// ���� ������
	}

	// ������ ���� ó�� (������ ���� ��ũ ���)
	switch(_usr)
	{
	case 1:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// ���� ��ũ ������
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))				// ������ ��ǰ�̸��� ���� ��ǰ�̸��� ������
			{
				if(Ppre==NULL)								// ���� ��ǰ�� ������
				{
					Tcur->Plink=Pcur->U1link;				// ���� Ÿ��Ʋ�� ��ǰ ��ũ�� ������ǰ����
					Pcur->U1link=NULL;						// ���� ��ǰ�� ��ũ �η� �ʱ�ȭ
				}
				else
				{
					Ppre->U1link=Pcur->U1link;				// ���� ��ǰ�� ���� ��ũ�� ������ǰ����
					Pcur->U1link=NULL;						// ���� ��ǰ�� ���� ��ũ �η� �ʱ�ȭ
				}
				break;	// Ż��
			}
			Ppre=Pcur;	// ���� ��ǰ ����
		}
		break;
	case 2:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))
			{
				if(Ppre==NULL)
				{
					Tcur->Plink=Pcur->U2link;
					Pcur->U2link=NULL;
				}
				else
				{
					Ppre->U2link=Pcur->U2link;
					Pcur->U2link=NULL;
				}
				break;
			}
			Ppre=Pcur;
		}
		break;
	case 3:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))
			{
				if(Ppre==NULL)
				{
					Tcur->Plink=Pcur->U3link;
					Pcur->U3link=NULL;
				}
				else
				{
					Ppre->U3link=Pcur->U3link;
					Pcur->U3link=NULL;
				}
				break;
			}
			Ppre=Pcur;
		}
		break;
	}

}

// ��ǰ ����Ʈ ����ϴ� �Լ�
void List::Print(int n)
{
	// n=1 �̸� ������ ��ǰ ���
	// n=2 �̸� ī�װ��� ��ǰ ���

	Title *Tcur;
	Product *Pcur;

	switch(n)
	{
	case 1: // ������ ��ǰ ���
		for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)
		{
			cout<<"\t�� "<<Tcur->Tname<<endl;
			cout<<"\t   "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(3)<<" "<<"�� ��"<<endl;
			for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)
				cout<<"\t   "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(10)<<right<<Pcur->Pstock<<endl;
			cout<<endl;
		}
		break;
	case 2: // ī�װ��� ��ǰ ���
		for(Tcur=Chead;Tcur!=NULL;Tcur=Tcur->Tlink)
		{
			cout<<"\t�� "<<Tcur->Tname<<endl;
			cout<<"\t   "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(3)<<" "<<"�� ��"<<endl;
			for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Clink)
				cout<<"\t   "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(10)<<right<<Pcur->Pstock<<endl;
			cout<<endl;
		}
		break;
	}

}

// ���Ͽ� ��ǰ ���� ����ϴ� �Լ�
void List::Print(ofstream &product)
{
	Title *Tcur;
	Product *Pcur;

	// ���� �������� ���
	for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// ���� ������
	{
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)	// ��ǰ ������ ��ǰ�̸�, ����, ���, ī�װ�, ���� ���Ϸ� ���
			product<<setw(30)<<left<<Pcur->Pname<<setw(10)<<left<<Pcur->Pprice<<setw(10)<<left<<Pcur->Pstock<<setw(10)<<left<<Pcur->PCat<<setw(10)<<Pcur->PLoc<<"\n";
	}
}

// ���� ���� ����Ʈ ����ϴ� �Լ�
void List::PrintUsr(int _usr)
{
	// �ʱ� ����
	Title *Tcur=Uhead;
	Product *Pcur;

	while(Tcur!=NULL)	// ���� ������
	{
		if(myStrcmp(Tcur->Tname,_usr))	// ���� ������ �Է¹��� ������ ������ Ż��
			break;
		Tcur=Tcur->Tlink;				// ���� ������
	}

	// �������� ó��
	switch(_usr)
	{
	case 1:
		cout<<endl<<"      �� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// ���� ��ũ ������
		{
			if(!(Pcur->U1Gpur&&Pcur->Pnum<10))				// �Ϲݱ����̰ų� �������Ű� ������ ��ǰ�� ���
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				if(Pcur->U1Gpur&&Pcur->Pnum>9)	// �������Ű� ������ ��ǰ ���
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U1num*0.9<<endl;
				else							// �Ϲݱ��� ���
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<endl;
			}
		}

		cout<<endl<<"      �� �������� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// ������ũ ������
		{
			if(Pcur->U1Gpur&&Pcur->Pnum<10)		// �������Ű� �������� ��ǰ ���
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<endl;
			}
		}
		cout<<endl;
		break;
	case 2:
		cout<<endl<<"      �� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(!(Pcur->U2Gpur&&Pcur->Pnum<10))
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				if(Pcur->U2Gpur&&Pcur->Pnum>9)
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U2num*0.9<<endl;
				else
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<endl;
			}
		}

		cout<<endl<<"      �� �������� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(Pcur->U2Gpur&&Pcur->Pnum<10)
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<endl;
			}
		}
		cout<<endl;
		break;
	case 3:
		cout<<endl<<"      �� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(!(Pcur->U3Gpur&&Pcur->Pnum<10))
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				if(Pcur->U3Gpur&&Pcur->Pnum>9)
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U3num*0.9<<endl;
				else
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<endl;
			}
		}

		cout<<endl<<"      �� �������� ���� ��ǰ ����Ʈ"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(Pcur->U3Gpur&&Pcur->Pnum<10)
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<endl;
			}
		}
		cout<<endl;
		break;
	}
}

// ���� ���� ����Ʈ�� ���Ϸ� ����ϴ� �Լ�
void List::PrintUsr(int _usr,ofstream &sales)
{
	// �ʱ� ����
	Title *Tcur=Uhead;
	Product *Pcur;

	while(Tcur!=NULL)	// ���� ������
	{
		if(myStrcmp(Tcur->Tname,_usr))	// ���� ������ �Է¹��� ������ ������ Ż��
			break;
		Tcur=Tcur->Tlink;				// ���� ������
	}

	// ������ ���� ���
	switch(_usr)
	{
	case 1:
		sales<<"\n"<<"      �� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// ���� ��ũ ������
		{
			if(!(Pcur->U1Gpur&&Pcur->Pnum<10))				// �Ϲݱ����̰ų� �������Ű� ������ ��ǰ�� ���
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				if(Pcur->U1Gpur&&Pcur->Pnum>9)	// �������Ű� ������ ��ǰ ���
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U1num*0.9<<"\n";
				else							// �Ϲݱ��� ���
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<"\n";
			}
		}

		sales<<"\n"<<"      �� �������� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// ������ũ ������
		{
			if(Pcur->U1Gpur&&Pcur->Pnum<10)					// �������Ű� �������� ��ǰ ���
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<"\n";
			}
		}
		sales<<"\n";
		break;
	case 2:
		sales<<"\n"<<"      �� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(!(Pcur->U2Gpur&&Pcur->Pnum<10))
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				if(Pcur->U2Gpur&&Pcur->Pnum>9)
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U2num*0.9<<"\n";
				else
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<"\n";
			}
		}

		sales<<"\n"<<"      �� �������� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(Pcur->U2Gpur&&Pcur->Pnum<10)
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<"\n";
			}
		}
		sales<<"\n";
		break;
	case 3:
		sales<<"\n"<<"      �� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(!(Pcur->U3Gpur&&Pcur->Pnum<10))
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				if(Pcur->U3Gpur&&Pcur->Pnum>9)
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U3num*0.9<<"\n";
				else
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<"\n";
			}
		}

		sales<<"\n"<<"      �� �������� ���� ��ǰ ����Ʈ"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(Pcur->U3Gpur&&Pcur->Pnum<10)
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<"\n";
			}
		}
		sales<<"\n";
		break;
	}
}

// ���Ͽ� �Ǹ� ���� ����ϴ� �Լ�
void List::FPrintSales(ofstream &sales)
{
	// �ʱ� ����
	Title *Tcur=Uhead;
	Product *Pcur;
	int TOTAL=0;	// �� �Ǹűݾ�

	sales<<" �� �Ǹ� ���\n";
	sales<<"-----------------------------------------------------------------------------\n";
	// �ǸŸ�� ���� �������� ���
	sales<<"      "<<setw(11)<<" "<<"ǰ    ��"<<setw(11)<<" "<<setw(2)<<" "<<"��  ��"<<setw(2)<<" "<<setw(2)<<" "<<"����"<<setw(2)<<" "<<"��  ��"<<setw(4)<<" "<<"��  ��\n";
	for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// ���� ������
	{
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)	// ��ǰ ������
		{
			if(Pcur->Pnum>0)		// ��ǰ �Ǹ� ������ 0���� ũ�� ���
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->Pnum;
				if((Pcur->U1Gpur||Pcur->U2Gpur||Pcur->U3Gpur)&&Pcur->Pnum>9)			// �������� ��ǰ�̸鼭 ���� ������ 10�̻��̸�
				{
					// 10%DC
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->Pnum*0.9<<"\n";
					TOTAL+=Pcur->Pprice*Pcur->Pnum*0.9;
				}
				else
				{
					sales<<"     -     "<<setw(7)<<right<<Pcur->Pprice*Pcur->Pnum<<"\n";
					TOTAL+=Pcur->Pprice*Pcur->Pnum;
				}
			}
		}
	}
	sales<<"-----------------------------------------------------------------------------\n";
	sales<<"  >> ���� �Ѿ�\t"<<TOTAL<<"\n\n\n";

	sales<<" �� �� ���"<<"\n";

	// ���� ����Ʈ ���Ϸ� ���
	for(int i=1;i<4;i++)
	{
		sales<<"  >> "<<i<<"-th user"<<"\n";
		PrintUsr(i,sales);
	}
}


//////////////////////////////////////////////////////////////////////////////////