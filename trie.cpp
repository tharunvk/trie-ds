#include <bits/stdc++.h>
using namespace std;

struct Trie{
    bool isLeafNode;
    unordered_map<char,Trie*> Triemap;
};

Trie * getNode(){
    Trie *newNode= new Trie;
    newNode->isLeafNode=false;
    return newNode;
}

Trie * insert(Trie *head, string s){
    if(head==nullptr)
        head=getNode();
    Trie *curr=head;
    for(int i=0;i<s.size();i++){
        if(curr->Triemap.find(s[i])==curr->Triemap.end()){
            curr->Triemap[s[i]]=getNode();
        }
        curr=curr->Triemap[s[i]];
    }
    curr->isLeafNode=true;
    return head;
}

void search(Trie *head, string s){
    if(head==nullptr){
        cout<<"Trie is empty. String not found\n\n";
        return;
    }

    Trie *curr=head;
    for(int i=0;i<s.size();i++){
        if(curr->Triemap.find(s[i])==curr->Triemap.end()){
            cout<<"String not found.Exiting search.....\n\n";
            return;
        }
        curr=curr->Triemap[s[i]];
    }
    if(curr->isLeafNode==true)
        cout<<"Voila!! String found.Exiting search....\n\n";
    else
        cout<<"String not found.Exiting search.....\n\n";
    
}

void display(Trie *head,char *displayString,int idx){
    if(head==nullptr){
        cout<<"Trie is empty. Better insert some strings and check again\n\n";
        return;
    }
    
    Trie *curr=head;
    if(curr->isLeafNode){
        cout<<displayString<<endl;
        return;
    }
    for(auto i=curr->Triemap.begin();i!=curr->Triemap.end();i++){
        displayString[idx]=i->first;
        display(i->second,displayString,idx+1);
    }
    displayString[idx]='\0';
}

void deleteNode(Trie *head,string s,int idx){
    if(head->isLeafNode==true){
        return;
    }
    Trie *curr=head;
    if(curr->Triemap.find(s[idx])==curr->Triemap.end()){
        cout<<"String not present can't delete\n";
        return;
    }
    deleteNode(curr->Triemap[s[idx]],s,idx+1);
    
    if(curr->Triemap[s[idx]]->isLeafNode==true){
        delete curr->Triemap[s[idx]];
        curr->Triemap.erase(s[idx]);
    }
    
    if(curr->Triemap.size()==0)
        curr->isLeafNode=true;
    if(idx==0)
        head->isLeafNode=false;
    
}

void autofeature(Trie *head,char *str,int idx){
    if(head==nullptr){
        cout<<"Trie is empty. String not found\n\n";
        return;
    }
    Trie *curr=head;
    for(int i=0;str[i]!='\0';i++){
        if(curr->Triemap.find(str[i])==curr->Triemap.end()){
            cout<<"String not found.Exiting search.....\n\n";
            return;
        }
        curr=curr->Triemap[str[i]];
    }
    if(curr->isLeafNode==true)
        cout<<"Voila!! String found.Exiting search....\n\n";

    cout<<"Generating strings starting with "<<str<<" ......"<<endl;
    display(curr,str,idx);
}

int main()
{
    Trie * head=nullptr;
    string s;
    int idx=0;
    char displayString[20]="",temp[10]="";
    while(1){
        cout<<"Choose any option\n";
        cout<<"-----------------\n";
        cout<<"1.Insert\n2.Search\n3.Display\n4.Auto recommendation\n5.Delete\nTap any other key to exit.......\n\n";
        int choice;
        cin>>choice;
        
        switch(choice){
            case 1:
                cout<<"Enter the string to insert into Trie : ";
                cin>>s;
                head=insert(head,s);
                break;
            case 2: 
                cout<<"Enter the string to search in Trie : ";
                cin>>s;
                search(head,s);
                break;
            case 3:
                cout<<"All the strings stored in Trie are :\n";
                cout<<"------------------------------------\n";
                display(head,displayString,idx);
                break;
            case 4:
                cout<<"Enter a partial string for auto recommendation : ";
                cin>>temp;
                autofeature(head,temp,strlen(temp));
                break;
            case 5:
                cout<<"Enter string you wanna delete: ";
                cin>>s;
                deleteNode(head,s,0);
                break;
            default:
                cout<<"There are only 5 options you moron.\n";
                exit(0);
                
        }
    }

    return 0;
}
