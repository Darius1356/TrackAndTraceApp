#include <stdio.h>
#include <stdlib.h>

struct person *ptr= NULL, *temp=NULL, *temp_p=NULL, *head=NULL;
struct treenode *rootptr=NULL;

struct treenode 
{ char name[50];
  int location [10];
  struct treenode* Lptr;
  struct treenode* Rptr;
};

struct person
{ char name[50];
  int location [10];
  struct person *next;  
};

//string copy function
char my_strcpy (char str2[50], char str1[50])
{
  int i;
  for (i = 0; str1[i] != '\0'; i++)
    {
      str2[i] = str1[i];
    }
  str2[i] = '\0'; 
  return *str2;
}

//string compare function
int my_strcmp(char string1[50], char string2[50])
{
  int i;
  int difference;
  for (i=0; string1[i] == string2[i]; i++)
    if (string1[i]  == '\0' && string2[i] == '\0')
      return 0;
  difference = string1[i] - string2[i];
  return difference;
}

//adding new user function
int add_to_linkedlist (int x,char string[50])
{ int n;
  if (x == 0)  //case for first record insertion//
  { //memory allocated
    ptr = (struct person*) malloc(sizeof(struct person));
//data copied/initialised into record
    my_strcpy(ptr->name,string);
    for (n=0; n<10; n++)
    {  ptr->location[n] = 0;
    }
//pointers set up for linked list
    ptr->next=0;
    head = ptr;
  }
  else
  { //case for subsequent record insertions
    //temporary pointers set up
    temp = head;  
    temp_p = head;
//memory allocated & data inserted/initialised 
    ptr = (struct person*) malloc(sizeof(struct person));
    my_strcpy(ptr->name,string);
    for (n=0; n<10; n++)
      {  ptr->location[n] =  0;
      }
//pointer traverses list until correct position is found
    while (temp !=0 && my_strcmp(string,temp->name) > 0)
    {
      temp_p = temp;
      temp=temp->next;
    }
//new record is inserted into linked list
    ptr->next = temp; 
    if (temp == head) //in the case of insertion at the head
    {  head = ptr;
    }
    else  
    { //in the case of middle or end insertions
      temp_p->next = ptr;
    }
  }
return 0;
}

//deleting user function 
int delete_from_linkedlist (char string[50])
{  //temporary pointers set up for traversing list to find user to delete      
  temp_p = head;
  temp = head->next; 
//case for deleteing head of list
  if (my_strcmp(string, temp_p->name) == 0)
  { head = temp;
    free(temp_p);
  }  
  else
  { //pointers traverse list to find user to delete 
    for (temp=head; temp!=NULL; temp=temp->next)
    {  if (my_strcmp(string, temp->name) == 0)
        { //linking previous and next records of the user to be deleted
          temp_p->next = temp->next;
          free(temp); //deleteing user record
        }  
       else
          temp_p=temp;
    }
  }      
return 0;
}

//new site visit function
int new_site_visit(char string[50])
{  int n, locationID, found=0;
// pointer traverses the linked list until name is found 
   for (temp = head; temp != NULL; temp = temp->next)
    {  if (my_strcmp(string, temp->name) == 0)
        { found = 1;
          printf("Please type the ID of the location visited by %s\n",temp->name);
          scanf("%d", &locationID);
// the next empty slot is found in the location array to insert the new site visit    
          n=0;
          while (n<10 && temp->location[n] !=0)
            { n++;
            }    
          if (temp->location[n] == 0)
              temp->location[n] = locationID;
        } 
    }
    if (!found)
      {  printf("No such user on system\n");
      }
  return 0;
}

//checking site function
int site_check(int site)
{   int n;
    printf("The people at this venue who have been in contact are:\n\n");
//traversing all linked user records 
    for (temp = head; temp != NULL; temp = temp->next)
//traversing all location records within each user record to find the site wanted
      {  n=0;
         while (n>=0 && n<10)
          { if (temp->location[n] == site)
            {  printf("%s\n\n", temp->name);
            }
            n++;
          }
      }
  return 0;
  }

//writing to file
int save_to_file()
{ FILE *fp;
  fp = fopen ("library","wb"); //opening file to write structs to 
  if (fp != NULL) //check to make sure file is found 
    for (temp = head; temp != NULL; temp = temp-> next)
      fwrite(temp,sizeof(struct person), 1, fp); //writing each record to file
    fclose(fp); //closing file before ending program
return 0;
}

//reading from file
int retrieve_data()
{ FILE *fp;
  int n, presult;
  
  fp = fopen ("library", "rb"); //opening file to read structs from
  if (fp != NULL) //check to make sure file is found & opened
    { temp= head;
      presult= fread(temp, sizeof(struct person), 1, fp);//one record at a time is read
      printf("%s  ", temp->name);//& printed
      for (n=0; (n<10 && temp->location[n]!=0); n++)
        {  printf(" Visited site: %d  ", temp->location[n]);
        } 
      printf("\n\n");
      while (presult != 0)
        for (temp = temp->next; temp !=NULL; temp= temp->next)
        { printf("%s  ", temp->name);
          for (n=0; (n<10 && temp->location[n] != 0); n++)
            {  printf(" Visited site: %d  ", temp->location[n]);
            }
          printf("\n\n");
          presult = fread(temp, sizeof(struct person), 1, fp);
        }
        fclose(fp);
    }  
      else printf ("Error reaading from file\n");
  return(0);
}

// insertion into a BST
struct treenode* Insert_bst(struct treenode *rootptr, char strng[50])
{ int n;
  if (rootptr == NULL)
  { rootptr=(struct treenode*)malloc(sizeof(struct treenode));
    rootptr->Lptr = NULL;
    rootptr->Rptr = NULL;
    my_strcpy(rootptr->name,strng);
    for (n=0; n<10; n++)
      {  rootptr->location[n] = 0;
      }
  }
  else if (my_strcmp(rootptr->name, strng) > 0)
    {  rootptr->Lptr = Insert_bst(rootptr->Lptr, strng);
    }
    else
      rootptr->Rptr = Insert_bst(rootptr->Rptr,strng);
  return rootptr;
}

//searching a BST
int search_bst(struct treenode* rootptr, char strng[50])
{
  if (rootptr == NULL)
    return 0;
  else  
    if (my_strcmp(rootptr->name, strng)==0)
      return 1;
    else 
      if (my_strcmp(rootptr->name, strng) > 0)
          return search_bst(rootptr->Lptr, strng);
      else 
          return search_bst(rootptr->Rptr, strng);
}

int main(void) 
{ FILE *fp;
  int choice, compare_locationID, x=0;
  char old_user[50], new_user[50];
  
  do{
    printf("Enter the associated number to make a choice:\n1) Introduce a new user\n2) Introduce a new site visit\n3) Remove user\n4) Check which users have been in a particular site\n5) Save to file\n6) Retrieve data from file\n7) Exit programme\n");
    scanf("%d", &choice);
    switch (choice) 
    {
      case 1:
      printf("Please type the name of the user\n");
      scanf("%s", new_user);
      add_to_linkedlist (x, new_user);
      x++;
      break;

      case 2:
      printf("Please type the name of the corresponding user\n");
      scanf("%s", old_user);
      new_site_visit(old_user);     
      break;

      case 3:
      if (head == NULL)
      {  printf("There are no users on the system\n");
      }
      else 
      { printf("Please type the name of the user to remove\n");
        scanf("%s", old_user);
        delete_from_linkedlist(old_user);
      }
      break;

      case 4:
      printf("Type the ID number of the location you would like to check\n");
      scanf("%d", &compare_locationID);
      site_check (compare_locationID);
      break;       

      case 5:
      save_to_file();        
      break;

      case 6:
      retrieve_data();
      break;

      case 7:
      break;
      
      default:
      break;
    }
    if (choice < 1 || choice > 7)
      printf("Incorrect input. Please enter a number between 1 and 7 to make a choice.");
    }
    while (choice != 7);
    return 0;
}