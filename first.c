#include <stdio.h>
#include <stdlib.h>
struct book 
{
	int bookId;
	char bookName[100];
	char isbnNo[50];
};
void addBooks()
{
	struct book bookObj;
	int input_bookId;
	printf("Please enter the book id\n");
	scanf("%d",&input_bookId);
	bookObj.bookId=input_bookId;
	printf("Please enter the book name \n");
	scanf("%s",&bookObj.bookName);
	printf("Please enter the book isbnNo\n");
	scanf("%s",&bookObj.isbnNo);
	FILE *f=fopen("Book_Data.txt","a");
	if(f==NULL)
	{
		printf("The entered book does not exist\n");
		return;
	}
	
	else 
	{
		fprintf(f,"%d %s %s\n",bookObj.bookId,bookObj.bookName,bookObj.isbnNo);
		printf("saving in file done\n");
		fclose(f);
	}
}

void displayallBooks()
{
	FILE *fp=fopen("Book_Data.txt","r");
	
	if(fp==NULL)
	printf("The file does not exist \n");
	
	struct book bookstruct;
	char datatobeRead[1000];
	while(fscanf(fp,"%d %s %s",&bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo)!=EOF)
	{
		printf("%d %s %s \n",bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo);
	}
	fclose(fp);
}  
void deletethisBook(int id)
{
	
	FILE *filePointer=fopen("Book_Data.txt","r");
	FILE *filePointerTemp=fopen("Book_Temp.txt","a");
	if(filePointer==NULL)
	printf("The book does not exist \n");
	
	struct book bookstruct;
	int found=0;
	
	while(fscanf(filePointer,"%d %s %s",&bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo)!=EOF)
	{
		if(bookstruct.bookId!=id)
		{
			found=1;
	     	fprintf(filePointerTemp,"%d %s %s\n",bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo);
		}
	}
	fclose(filePointer);
	fclose(filePointerTemp);
	if(found==0)
	printf("The given id does not exists please enter a valid id\n");
	int rem=remove("Book_Data.txt");
	int ren=rename("Book_Temp.txt","Book_Data.txt");	
}
void updatebookId(int id)
{
	struct book bookstruct;
	FILE* filepointer=fopen("Book_Data.txt","r");
	FILE* fileTempPointer=fopen("Book_Temp_Data.txt","a");
	
	if(filepointer==NULL)
	{
		printf("The file does not exist please check the file\n");
		return;
	}
	int found=0;
	while(fscanf(filepointer,"%d %s %s",&bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo)!=EOF)
	{
			if(bookstruct.bookId==id)
			{
				found=1;
				printf("Please enter the new details\n");
				printf("Please enter the new name\n");
				scanf("%s",&bookstruct.bookName);
				
				printf("Please enter the new isbn number\n");
				scanf("%s",&bookstruct.isbnNo);
			}
			fprintf(fileTempPointer,"%d %s %s\n",bookstruct.bookId,bookstruct.bookName,bookstruct.isbnNo);
	}
	fclose(filepointer);
	fclose(fileTempPointer);
	if(found==0)
	printf("The ID searched is not present in the file\n");
	
	remove("Book_Data.txt");
	rename("Book_Temp_Data.txt","Book_Data.txt");				
}
int main()
{
	printf("Welcome to the Book Management System\n");
	struct book structArray[10];
	while(1) 
	{
		int choice;
		printf("Enter the choice of functionality\n");
		scanf("%d",&choice);
		if(choice==5)
			break;

		int bookCount=0;
		switch(choice) 
		{
			case 1:
				printf("You can add the Book that you want \n");
				addBooks();
				break;

			case 2:
				printf("You can delete the Book you want\n");
				int delete_bookId;
				printf("Please enter the ID you want to delete\n");
				scanf("%d",&delete_bookId);
				deletethisBook(delete_bookId);
				break;


			case 3:
				printf("You can update the Book details that you want\n");
				printf("Please enter the book Id you want to update\n");
				int update_bookId;
				scanf("%d",&update_bookId);
				updatebookId(update_bookId);
				break;

			
			case 4:
				printf("Listing all the Book details for you \n");
				displayallBooks();
				break;

		}
	}
}