#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdarg.h>
using namespace std;

//Макро для ідентифікації значення, що не має ключа
#define UNFIND "No instance match"

struct Pair 
{
	//поле для ключа
	unsigned int key;
	//поле для значення
	char* value;
};

struct map
{
	//Елемент структури
	Pair El;
	//pointer на наступний
	map* next;
};

//pointer на початок структури
map *frst=NULL;
	
char* FindElement(unsigned int k)
{
	//створюємо вказівник на новий елемент
	map *temp;
	//ініціалізуємо його початком структури
	temp=frst;

	//поки наш елемент вказує на якусь область пам'яті
	while (temp!=NULL)
	{
		//Якщо ключ поточного елемента рівний переданому параметру
		if (temp->El.key==k)
			//повертаємо значення, що відповідає даному ключу
			return temp->El.value;
		else
		//інакше, в силу унікальності ключів структури, 
		//переміщуємо вказівник на наступний елемент
			temp=temp->next;
	}

	//якщо значення для такого ключа не знайдено
	return UNFIND;
}
void Insert2Map(unsigned int k, char* v)
{
	//Якщо такого ключа не знайдено
	if (FindElement(k)==UNFIND)
	{
		//створюємо pointer на новий елемент
		map *temp=new map;
		//він не має наступного
		temp->next=NULL;
		//Ініціалізуємо його вхідними параметрами
		temp->El.key=k;
		temp->El.value=v;

		//якщо початок порожній
		if (!frst)
			//присвоюємо відповідний елемент на початок
			frst=temp;
		else
		{
			//Проводимо вставку новоствореного вказівника

			//Якщо значення параметра k менше ніж значення ключа на початку карти
			if (k<frst->El.key)
			{
				//вставляємо його перед початком
				temp->next=frst;
				//встановлюємо початковим елементом новостворений
				frst=temp;
			}
			else
			{
				//в іншому випадку створюємо новий вказівник на структуру
				map *ptr=frst;
				//шукаємо два послідовні значення ключів, 
				//між якими можна розмістити передане значення для ключа
				while ( (ptr->next!=NULL)&&(k>ptr->El.key)&&(k>ptr->next->El.key) )
					ptr=ptr->next;
				//знайшовши таке значення вставляємо його у структуру
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
	//створюємо тимчасовий pointer на структуру 
	//для елемента, що має бути видалений
	map *temp=new map;

	//ініціалізуємо його початком структури
	temp=frst;

	//При видаленні першого елемента
	if (frst->El.key==k)
	{
		//pointer на перший елемент переносимо на наступний до нього
		frst=temp->next;
		//Занулюємо pointer елемента на ночатку
		temp->next=NULL;
		//і видаляємо його
		delete temp;
		cout <<"Element was deleted\n";
	}
	else
	{
		//рухаємося по структурі, поки не досягнуто її кінця
		while (temp->next!=NULL)
		{
			//Якщо знайдено елемент із ключем, що рівний параметру
			if (temp->next->El.key==k)
			{
				//створюємо додатковий pointer
				//що вказував би на знайдений елемент 
				map *temp2=temp->next;
				//pointer попереднього до знайденого встановлюємо на наступний за знайденим
				temp->next=temp2->next;
				//pointer знайденого елемента перестає вказувати на наступний
				temp2->next=NULL;
				//видаляємо знайдений елемент
				delete temp2;
				cout <<"Element was deleted\n";
				return;
			}

			//переміщаємо pointer поточного елемента на наступний за ним
			temp=temp->next;
		}
		cout <<"Element not found\n";
	}
	
}
void EraseElement(unsigned int k1, unsigned int k2)
{
	//створюємо тимчасовий pointer на структуру 
	//для елемента, що має бути видалений
	map *temp=new map;

	//ініціалізуємо його початком структури
	temp=frst;

	while ( (temp->El.key<k1)&&(temp->next!=NULL) )
		temp=temp->next;
		
	while ( (temp->El.key<k2)&&(temp->next!=NULL) )
	{
		//створюємо додатковий pointer
		//що вказував би на знайдений елемент 
		map *temp2=temp;
		//pointer попереднього до знайденого встановлюємо на наступний за знайденим
		temp=temp2->next;
		//pointer знайденого елемента перестає вказувати на наступний
		temp2->next=NULL;
		//видаляємо знайдений елемент
		delete temp2;
		cout <<"Element was deleted\n";
	}
}
void ClearMap()
{
	system("cls");
	//процюємо, поки існує початок структури
	while (frst)
	{
		//створюємо тимчасовий pointer на структуру 
		//що вказує на початок структури
		map *temp=frst;
		//переміщуємо початок на елемент. наступний до новоствореного
		frst=temp->next;
		//онулюємо вказівник на наступний до тимчасового елемента
		temp->next=NULL;
		//видаляємо створений pointer
		delete temp;
	}
	cout <<"Map is cleared\n";
}
int MapSize()
{
	//оголошуємо та ініціалізуємо лічильник
	int q=0;
	//Якщо стрктура не порожня - ненульовий pointer на початок
	if (frst!=NULL)			
	{
		//створюємо тимчасовий pointer на структуру 
		//що вказує на початок структури
		map *temp=frst;
		//поки pointer має наступний елемент
		while (temp!=NULL)
		{
			//переміщаємо pointer поточного елемента на наступний за ним
			temp=temp->next;
			//інкрементуємо лічильник
			q++;
		}
	}
	return q;
}
void PrintMapContent()
{
	system("cls");
	//Якщо стрктура не порожня - ненульовий pointer на початок
	if (frst!=NULL)
	{
		cout <<"\t\tMap content:\n";
		//створюємо тимчасовий pointer на структуру 
		//що вказує на початок структури
		map *temp=frst;

		cout <<"\n\tKey\t\tValue\n";
		//поки даний pointer має наступний елемент
		while(temp!=NULL)
		{			
			//Здійснюємо вивід пар ключ-значення
			cout <<setw(10)<<right<<temp->El.key<<"\t\t";
			cout <<setw(20)<<left<<temp->El.value<<endl;
			//переміщаємо pointer поточного елемента на наступний за ним	
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