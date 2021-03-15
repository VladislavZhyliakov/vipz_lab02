#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>

int counter = 0;
int i = 0;
struct sesiya* start = NULL;
struct sesiya* p ;
struct sesiya* pArr[10] = { 0 };

typedef struct sesiya
{
	char surname[50];
	char name[50];
	struct date
	{
		int date;
		int month;
		int year;
	}DATE;

	struct grades
	{
		int g1, g2, g3, g4, g5;
	}GRADES;

	struct sesiya* next;
};


//--------------------------------------------------------------------------------
void read() // функція зчитує файл зі списком студентів, додає у масив студентів у яких немає оцінки 5, виводить список у вигляді таблиці.
{

	FILE* fp = fopen("C:\\Users\\Владислав\\Desktop\\labs\\LAB8\\sesiya_sorted2.bin", "rb");

	struct sesiya* p = (struct sesiya*)malloc(sizeof(struct sesiya));
	struct sesiya* temp2 = NULL;

	printf("        ----------------------------------------------------------------\n");

	while (1)
	{
		if (start == NULL)
		{
			start = p;
			fread(&p->surname, sizeof(struct sesiya), 1, fp);
		}
		else
		{
			struct sesiya* pp = (struct sesiya*)malloc(sizeof(struct sesiya));
			p->next = pp;
			temp2 = p;
			p = pp;
			p->next = NULL;
			fread(&p->surname, sizeof(struct sesiya), 1, fp);
		}
		++counter;
		if (feof(fp))
		{
			free(p);
			p = temp2;
			counter--;
			break;
		}

		printf("\t| %10s | %10s | %2i | %2i | %4i | %i | %i | %i | %i | %i |\n", p->surname, (p->name), (p->DATE.date),								
																				(p->DATE.month), (p->DATE.year), (p->GRADES.g1),					
																				(p->GRADES.g2), (p->GRADES.g3), (p->GRADES.g4), (p->GRADES.g5));    
		printf("        ----------------------------------------------------------------\n");

		if ((p->GRADES.g1) != 5 &&							//	
			(p->GRADES.g2) != 5 && (p->GRADES.g3) != 5 &&   //перевіряємо оцінки студентів
			(p->GRADES.g4) != 5 && (p->GRADES.g5) != 5)     // 
		{
			pArr[i] = p;
			++i;
		}
	}

	p->next = NULL;
	p = start;

}
//--------------------------------------------------------------------------------
void add()// фунція додає нового студента у список.
{
	struct sesiya* temp1 = (struct sesiya*)malloc(sizeof(struct sesiya));
	printf("Enter new student:\n");
	scanf("%s %s %i %i %i %i %i %i %i %i", &(temp1->surname), &(temp1->name), &(temp1->DATE.date), 
											&(temp1->DATE.month), &(temp1->DATE.year), &(temp1->GRADES.g1), 
											&(temp1->GRADES.g2), &(temp1->GRADES.g3), &(temp1->GRADES.g4), &(temp1->GRADES.g5));

	//char symb;
	//printf("Enter where you want to input new student: b - beginning, e - end, m - middle :\n");
	//scanf("%c", &symb);
	//scanf("%c", &symb);
	/*if (symb == 'b')
	{*/
		start = temp1;
		temp1->next = p;
		p = temp1;
	//}
	/*else if (symb == 'e')
	{
		for (int i = 0; i <= counter; i++)
		{
			p = p->next;
			if (p->next == NULL)
			{
				p->next = temp1;
				p = p->next;
				p->next = NULL;
				break;
			}
		}
		p->next = NULL;
		p = start;
	}
	else if (symb == 'm')
	{
		for (int i = 0; i < (counter / 2); i++)
		{
			p = p->next;
		}
		struct sesiya* temp3 = (struct sesiya*)malloc(sizeof(struct sesiya));
		temp3 = p->next;
		p->next = temp1;
		p = p->next;
		p->next = temp3;


		p = start;
	}
	else
	{
		while (1)
		{
			printf("\nWrong input! Enter again:\n");

			scanf("%c", &symb);
			if ((symb == 'b') || (symb == 'e') || (symb == 'm'))
			{
				break;
			}
		}
	}*/


}
//--------------------------------------------------------------------------------
void sortedByGrades()// функція виводить список студентів у яких немає оцінки 5
{

	struct sesiya* temp = (struct sesiya*)malloc(sizeof(struct sesiya));

	while (p->next != NULL)
	{
		for (int j = 0; j < i; j++)
		{

			if (p == pArr[j])
			{
				temp = p;
				p = p->next;
				start = p;
				free(temp);
			}

			if (p->next == pArr[j])
			{
				temp = pArr[j];
				p->next = temp->next;
				free(temp);
			}
		}

		p = p->next;
	}

	p->next = NULL;
	p = start;

	printf("\n\n");
	printf("\n\n");


	printf("        ----------------------------------------------------------------\n");

	while (1)
	{
		printf("\t| %10s | %10s | %2i | %2i | %4i | %i | %i | %i | %i | %i |\n", p->surname, (p->name), (p->DATE.date),
																				(p->DATE.month), (p->DATE.year), (p->GRADES.g1),
																				(p->GRADES.g2), (p->GRADES.g3), (p->GRADES.g4), (p->GRADES.g5));
		printf("        ----------------------------------------------------------------\n");
		p = p->next;
		if (p->next == NULL)
		{
			printf("\t| %10s | %10s | %2i | %2i | %4i | %i | %i | %i | %i | %i |\n", p->surname, (p->name), (p->DATE.date), 
																					(p->DATE.month), (p->DATE.year), (p->GRADES.g1), 
																					(p->GRADES.g2), (p->GRADES.g3), (p->GRADES.g4), (p->GRADES.g5));
			printf("        ----------------------------------------------------------------\n");
			break;
		}
	}
	p->next = NULL;
	p = start;

	struct sesiya* freememory;
	struct sesiya* p_run;
	p_run = start;
	while (p_run != NULL)
	{
		freememory = p_run;
		p_run = p_run->next;
		free(freememory);
	}
}

int main()
{
	read();
	
	add();
	
	sortedByGrades();
	getchar();
	return 0;

}
