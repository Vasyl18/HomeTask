#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdarg.h>
using namespace std;

//����� ��� ������������� ��������, �� �� �� �����
#define UNFIND "No instance match"

struct Pair 
{
	//���� ��� �����
	unsigned int key;
	//���� ��� ��������
	char* value;
};

struct map
{
	//������� ���������
	Pair El;
	//pointer �� ���������
	map* next;
};

//pointer �� ������� ���������
map *frst=NULL;
	
char* FindElement(unsigned int k)
{
	//��������� �������� �� ����� �������
	map *temp;
	//���������� ���� �������� ���������
	temp=frst;

	//���� ��� ������� ����� �� ����� ������� ���'��
	while (temp!=NULL)
	{
		//���� ���� ��������� �������� ����� ���������� ���������
		if (temp->El.key==k)
			//��������� ��������, �� ������� ������ �����
			return temp->El.value;
		else
		//������, � ���� ���������� ������ ���������, 
		//��������� �������� �� ��������� �������
			temp=temp->next;
	}

	//���� �������� ��� ������ ����� �� ��������
	return UNFIND;
}
void Insert2Map(unsigned int k, char* v)
{
	//���� ������ ����� �� ��������
	if (FindElement(k)==UNFIND)
	{
		//��������� pointer �� ����� �������
		map *temp=new map;
		//�� �� �� ����������
		temp->next=NULL;
		//���������� ���� �������� �����������
		temp->El.key=k;
		temp->El.value=v;

		//���� ������� �������
		if (!frst)
			//���������� ��������� ������� �� �������
			frst=temp;
		else
		{
			//��������� ������� �������������� ���������

			//���� �������� ��������� k ����� �� �������� ����� �� ������� �����
			if (k<frst->El.key)
			{
				//���������� ���� ����� ��������
				temp->next=frst;
				//������������ ���������� ��������� �������������
				frst=temp;
			}
			else
			{
				//� ������ ������� ��������� ����� �������� �� ���������
				map *ptr=frst;
				//������ ��� �������� �������� ������, 
				//�� ����� ����� ��������� �������� �������� ��� �����
				while ( (ptr->next!=NULL)&&(k>ptr->El.key)&&(k>ptr->next->El.key) )
					ptr=ptr->next;
				//��������� ���� �������� ���������� ���� � ���������
				temp->next=ptr->next;
				ptr->next=temp;
			}
		}
		cout <<"Element successfully inserted\n";
	}		
	else
		cout <<"Such key already exists\n";
}
void Insert(unsigned int amount, ...)
{
	unsigned int i;
	va_list v1;
	va_start(v1, amount);
	for (i=0; i<amount; i++)
	{
		Pair p;
		p=va_arg(v1, Pair);
		Insert2Map(p.key, p.value);
	}
}
void EraseElement(unsigned int k=0)
{
	//��������� ���������� pointer �� ��������� 
	//��� ��������, �� �� ���� ���������
	map *temp=new map;

	//���������� ���� �������� ���������
	temp=frst;

	//��� �������� ������� ��������
	if (frst->El.key==k)
	{
		//pointer �� ������ ������� ���������� �� ��������� �� �����
		frst=temp->next;
		//��������� pointer �������� �� �������
		temp->next=NULL;
		//� ��������� ����
		delete temp;
		cout <<"Element was deleted\n";
	}
	else
	{
		//�������� �� ��������, ���� �� ��������� �� ����
		while (temp->next!=NULL)
		{
			//���� �������� ������� �� ������, �� ����� ���������
			if (temp->next->El.key==k)
			{
				//��������� ���������� pointer
				//�� �������� �� �� ��������� ������� 
				map *temp2=temp->next;
				//pointer ������������ �� ���������� ������������ �� ��������� �� ���������
				temp->next=temp2->next;
				//pointer ���������� �������� ������� ��������� �� ���������
				temp2->next=NULL;
				//��������� ��������� �������
				delete temp2;
				cout <<"Element was deleted\n";
				return;
			}

			//��������� pointer ��������� �������� �� ��������� �� ���
			temp=temp->next;
		}
		cout <<"Element not found\n";
	}
	
}
void EraseElement(unsigned int k1, unsigned int k2)
{
	//��������� ���������� pointer �� ��������� 
	//��� ��������, �� �� ���� ���������
	map *temp=new map;

	//���������� ���� �������� ���������
	temp=frst;

	while ( (temp->El.key<k1)&&(temp->next!=NULL) )
		temp=temp->next;
		
	while ( (temp->El.key<k2)&&(temp->next!=NULL) )
	{
		//��������� ���������� pointer
		//�� �������� �� �� ��������� ������� 
		map *temp2=temp;
		//pointer ������������ �� ���������� ������������ �� ��������� �� ���������
		temp=temp2->next;
		//pointer ���������� �������� ������� ��������� �� ���������
		temp2->next=NULL;
		//��������� ��������� �������
		delete temp2;
		cout <<"Element was deleted\n";
	}
}
void ClearMap()
{
	system("cls");
	//��������, ���� ���� ������� ���������
	while (frst)
	{
		//��������� ���������� pointer �� ��������� 
		//�� ����� �� ������� ���������
		map *temp=frst;
		//��������� ������� �� �������. ��������� �� ��������������
		frst=temp->next;
		//�������� �������� �� ��������� �� ����������� ��������
		temp->next=NULL;
		//��������� ��������� pointer
		delete temp;
	}
	cout <<"Map is cleared\n";
}
int MapSize()
{
	//��������� �� ���������� ��������
	int q=0;
	//���� �������� �� ������� - ���������� pointer �� �������
	if (frst!=NULL)			
	{
		//��������� ���������� pointer �� ��������� 
		//�� ����� �� ������� ���������
		map *temp=frst;
		//���� pointer �� ��������� �������
		while (temp!=NULL)
		{
			//��������� pointer ��������� �������� �� ��������� �� ���
			temp=temp->next;
			//������������ ��������
			q++;
		}
	}
	return q;
}
void PrintMapContent()
{
	system("cls");
	//���� �������� �� ������� - ���������� pointer �� �������
	if (frst!=NULL)
	{
		cout <<"\t\tMap content:\n";
		//��������� ���������� pointer �� ��������� 
		//�� ����� �� ������� ���������
		map *temp=frst;

		cout <<"\n\tKey\t\tValue\n";
		//���� ����� pointer �� ��������� �������
		while(temp!=NULL)
		{			
			//��������� ���� ��� ����-��������
			cout <<setw(10)<<right<<temp->El.key<<"\t\t";
			cout <<setw(20)<<left<<temp->El.value<<endl;
			//��������� pointer ��������� �������� �� ��������� �� ���	
			temp=temp->next;
		}
	}
	else
		cout <<"Map is empty\n";
}
void InsertProcedure()
{
	system("cls");
	int k;
	char* v=new char();
	cout <<"Input information about person for inserting to the map\nkey:  ";
	cin >>k;
	cout <<"value:  ";
	cin >>v;
	if (k<0)
		cout <<"Incorect key data!\n";
	else
		Insert2Map(k, v);

}
void DeleteProcedure()
{
	system("cls");
	if (!frst)
		cout <<"Sorry there is nothing to delete from the empty map\n";
	else
	{
		//	int k;
		//cout <<"Input key to delete element: ";
		//cin >>k;
		int k1, k2;
		cout <<"Input k1: ";
		cin >>k1;
		cout <<"Input k2: ";
		cin >>k2;

		/*if (k<0)
			cout <<"Incorect key data!\n";
		else
			EraseElement(k);*/
		if ( (k1<0)||(k2<0) )
			cout <<"Incorect key data!\n";
		else
			EraseElement(k1, k2);
	}
}
void FindProcedure()
{
	system("cls");
	int k;
	cout <<"Input key to find element: ";
	cin >>k;
	if (k<0)
		cout <<"Incorect key data!\n";
	else
	{
		char* (*f)(unsigned int);
		f=&FindElement;
		cout <<"Element: "<<f(k)<<endl;
	}
}

void Processing()
{
	while (1)
	{
		system("cls");
		cout <<"_________________________________\n";
		cout <<"|\t\tPress:\t\t|\n";
		cout <<"| 1 - to insert to the map\t|\n";
		cout <<"| 2 - to find element in map\t|\n";	
		cout <<"| 3 - to delete element\t\t|\n";
		cout <<"| 4 - to clear map content\t|\n";
		cout <<"| 5 - to print map content\t|\n";
		cout <<"| 6 - to close a program\t|\n";
		cout <<"|_______________________________|\n";
		switch( _getch() )
		{
		case '1':
			InsertProcedure();
			break;
		case '2':
			FindProcedure();
			break;
		case '3':
			DeleteProcedure();
			break;
		case '4':
			ClearMap();
			break;
		case '5':
			{
			PrintMapContent();
			cout <<"Size: "<<MapSize()<<endl;
			}
			break;
		case '6':
			return;
	/*	default:
			cout <<"Size: "<<MapSize()<<endl;*/
		};
		_getch();
	}
}

int main()
{
	Insert2Map(1, "Vasyl");
	Insert2Map(53, "Vita");
	Insert2Map(12, "Yuri");
	Insert2Map(7, "Yulia");
	Insert2Map(11, "Roman");
	Insert2Map(41, "Olia");

	Processing();

	return 0;
}