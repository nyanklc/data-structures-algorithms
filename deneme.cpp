#include <iostream>

using namespace std;

class Node
{
public:
    long long int data;
    Node *next;
    Node(long long int dat, Node *nxt=NULL);
};
Node::Node(long long int dat, Node *nxt)
{
    data=dat;
    next=nxt;
}
Node *GetNode(long long int val)
{
    Node *temp;
    temp = new Node(val);
    return temp;
}

class LList
{
public:
    Node *head;
    Node *last;
    LList();
    void AddElement(long long int val);
    void DeleteElement(long long int val);
    void SearchElement(long long int val);
};
LList::LList()
{
    head=NULL;
    last=NULL;
}
void LList::AddElement(long long int val)
{
    if(head==NULL)
    {
        head=GetNode(val);
        last=head;
        return;
    }
    Node *temp=head;
    while(true)
    {
        if(temp->next==NULL)
        {
            temp->next=GetNode(val);
            last=temp->next;
            return;
        }
        else if(temp->data==-1)
        {
            temp->data=val;
            return;
        }
        else if(temp->data==val)
            return;

        temp=temp->next;
    }
}
void LList::DeleteElement(long long int val)
{
    Node *temp=head;
    while(true)
    {
        if(temp->data==val)
        {
            temp->data=-1;
            return;
        }
        else
        {
            if(temp->next==NULL)
            {
                cout<<"value not found in the table."<<endl;
                return;
            }
            temp=temp->next;
        }
    }
}
void LList::SearchElement(long long int val)
{
    Node *temp=head;
    while(true)
    {
        if(temp->data==val)
        {
            cout<<"value "<<temp->data<<" is found."<<endl;
            return;
        }
        else
        {
            if(temp->next==NULL)
            {
                cout<<"value not found in the table."<<endl;
                return;
            }
            temp=temp->next;
        }
    }
}

class HashTable
{
public:
    LList *head;
    string type;
    int N;
    HashTable(LList *hd=NULL, string typ="folding", int n=0);
    void SearchTC(long long int val);
    void AddTC(long long int val); //use this to add TC no.
    void DeleteTC(long long int val); //and this to delete.

    //below functions return the hash value.
    long long int Folding(long long int val);
    long long int MiddleSquaring(long long int val);
    long long int Truncation(long long int val);

};
HashTable::HashTable(LList *hd, string typ, int n)
{
    head=hd;
    type=typ;
    N=n;
}
void HashTable::SearchTC(long long int val)
{
    //checking if input is valid
    long long int temp=val;
    int digCount=0;
    while(temp>0)
    {
        temp=temp/10;
        digCount++;
    }
    if(digCount!=11)
    {
        cout<<"TC no should be 11 digits long and positive."<<endl;
        return;
    }

    if(type=="folding")
        (head+Folding(val))->SearchElement(val);
    else if(type=="middle squaring")
        (head+MiddleSquaring(val))->SearchElement(val);
    else if(type=="truncation")
        (head+Truncation(val))->SearchElement(val);
    return;
}
void HashTable::AddTC(long long int val)
{
    cout<<"askfljhskfnşkf"<<endl;
    //checking if input is valid
    long long int temp=val;
    int digCount=0;
    while(temp>0)
    {
        temp=temp/10;
        digCount++;
    }
    if(digCount!=11)
    {
        cout<<"TC no should be 11 digits long and positive."<<endl;
        return;
    }

    //adding the TC no
    if(type=="folding")
        (head+Folding(val))->AddElement(val);
    else if(type=="middle squaring")
        (head+MiddleSquaring(val))->AddElement(val);
    else if(type=="truncation")
        (head+Truncation(val))->AddElement(val);
    return;
}
void HashTable::DeleteTC(long long int val)
{
    //checking if input is valid
    long long int temp=val;
    int digCount=0;
    while(temp>0)
    {
        temp=temp/10;
        digCount++;
    }
    if(digCount!=11)
    {
        cout<<"TC no should be 11 digits long and positive."<<endl;
        return;
    }

    if(type=="folding")
        (head+Folding(val))->DeleteElement(val);
    else if(type=="middle squaring")
        (head+MiddleSquaring(val))->DeleteElement(val);
    else if(type=="truncation")
        (head+Truncation(val))->DeleteElement(val);
    return;
}
long long int HashTable::Folding(long long int val)
{
    long long int val1=val-(val/100)*100;
    val=val/100;
    long long int val2=val-(val/1000)*1000;
    val=val/1000;
    long long int val3=val-(val/1000)*1000;
    val=val/1000;
    long long int val4=val;
    long long int total=val1+val2+val3+val4;
    return total%N;
}
long long int HashTable::MiddleSquaring(long long int val)
{
    long long int val1=val-(val/10000000)*10000000;
    long long int val2=val1/10000;
    return (val2*val2)%N;
}
long long int HashTable::Truncation(long long int val)
{
    return (val-(val/100)*100)%N;
}

HashTable *InitializeHashTable(int len, string type)
{
    LList LLL[len];

    HashTable *temp;
    temp=new HashTable(LLL, type, len);
    return temp;
}

void PrintHashTable(HashTable *h)
{
    cout<<"ROWS REPRESENT EACH BUCKET"<<endl;
    Node *dumdum;
    for(int i=0;i<h->N;i++)
    {
        dumdum=((h->head)+i)->head;
        while(dumdum!=NULL)
        {
            cout<<dumdum->data<<"\t";
            dumdum=dumdum->next;
        }
        cout<<endl;
    }
}


int main()
{
    HashTable *hst;
    while(true)
    {
        cout<<"1. Initialize Hash Table"<<endl;
        cout<<"2. Load T.C. ID Numbers from file"<<endl;
        cout<<"3. Add new T.C. ID Number"<<endl;
        cout<<"4. Delete a T.C. ID Number"<<endl;
        cout<<"5. Search for a T.C. ID Number"<<endl;
        cout<<"6. Print out Hash Table"<<endl;

        int choice;
        cin>>choice;

        if(choice==1){
            cout<<"Size of Hash Table: ";
            int sizeh=0;
            while(!(sizeh>0))
                cin>>sizeh;
            cout<<endl;
            cout<<"Type of Hash Table (folding, middle squaring, truncation):";
            string typ="eheheh";
            while(!(typ=="folding" || typ=="middle squaring" || typ=="truncation"))
                cin>>typ;
            cout<<endl;
            hst=InitializeHashTable(sizeh,typ);
        }
        else if(choice==2){

        }
        else if(choice==3){
            cout<<"T.C. ID to be added: ";
            long long int tmp;
            cin>>tmp;
            cout<<endl;
            hst->AddTC(tmp);
        }
        else if(choice==4){
            cout<<"T.C. to be deleted: ";
            long long int tmp;
            cin>>tmp;
            cout<<endl;
            hst->DeleteTC(tmp);
        }
        else if(choice==5){
            cout<<"T.C. to be searched for: ";
            long long int tmp;
            cin>>tmp;
            cout<<endl;
            hst->SearchTC(tmp);
        }
        else if(choice==6){
            PrintHashTable(hst);
        }
        else{
            cout<<"invalid input"<<endl;
        }
    }

    return 0;
}
