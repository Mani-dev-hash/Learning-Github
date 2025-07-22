#Link List simple implementation

#include <iostream>
using namespace std;

struct node{
int data;
node *next;

node() {
next = NULL;}
};

class List{
node *head;
public:
List(){
head=NULL;}

void insert(int val)
{
  if(head == NULL){
head=new node;
head->data=val;
    head->next=NULL; 
    return;
  }
node *temp;
temp = head;
while(temp!=NULL)
{
temp=temp->next;
}
temp = new node;
temp->data = val;
temp->next = NULL;
return;
}
void display()
{
  if(head==NULL)
  {
    return;
  }
  node *temp; temp = head;
  while(temp!=NULL)
    {
      cout << temp->data;
      temp = temp->next;
    }
};

int main()
{
  List obj;
obj.insert(5);
obj.insert(6);
obj.insert(10);
obj.insert(12);

obj.display();
return 0;
}
