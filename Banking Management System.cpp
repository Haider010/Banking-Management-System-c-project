#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class account{
    char account_number[10];
    float balance;
    char first_name[10];
    char last_name[10];
    public:

    void setdata();
    void showdata();
    void search_data();
    void del_data();
    void updat_data();
    void writ_recrd();
    void read_recrd();
};
void account ::setdata(){
    cout<<"Enter the account Number :";cin>>account_number;
    cout<<"Enter First Name : ";cin>>first_name;
    cout<<"Enter Last Name : ";cin>>last_name;
    cout<<"Enter balance : ";cin>>balance;
}
void account ::showdata(){
    cout<<endl;
    cout<<"**Account Details**"<<endl;
    cout<<endl;
    cout<<"=> Account Number is = "<<account_number<<endl;
    cout<<"=> First Name is = "<<first_name<<endl;
    cout<<"=> Last Name is = "<<last_name<<endl;
    cout<<"=> Balance in  account is = "<<balance<<endl;
    cout<<endl;
    cout<<"****THANKS FOR USING OUR SERVICE****"<<endl;
}
void account::search_data(){
    int n,num;
    ifstream inrec;
    inrec.open("record1.txt");
    if (!inrec){
        cout<<"*****ERROR****"<<endl;
        cout<<endl;
        cout<<"File not found"<<endl;
        return;
    }
    inrec.seekg(0,ios::end);
    num =inrec.tellg()/sizeof(*this);
    cout<<"There are "<<num<<" numbers of records"<<endl;
    cout<<endl;
    int a;
    if(num==0){
        cout<<"Press 0 to exit: ";cin>>a;
    }
    if(a==0){
        return;
    }
    cout<<"Enter record number to open :";cin>>n;
    inrec.seekg((n-1)*sizeof(*this));
    inrec.read(reinterpret_cast<char*>(this),sizeof(*this));
    showdata();
}
void account::del_data(){
    int n,num;
    ifstream dele;
    dele.open("record1.txt",ios::binary);
    if(!dele){
        cout<<"*****ERROR*****"<<endl;
        cout<<endl;
        cout<<"File not found"<<endl;
        return;
    }
    dele.seekg(0,ios::end);
    num = dele.tellg()/sizeof(*this);
    cout<<"There are "<<num<<" numbers of records"<<endl;
    cout<<endl;
    cout<<"Enter file number you want to delete :";cin>>n;
    fstream temp;
    temp.open("temp.txt",ios::out|ios::binary);
    dele.seekg(0);
    for (int i = 0; i < num; i++)
    {
        dele.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
        continue;
        temp.write(reinterpret_cast<char*>(this),sizeof(*this));
    }
    dele.close();
    temp.close();
    remove("record1.txt");
    rename("temp.txt","record1.txt");
}
void account::updat_data(){
    int n,num;
    fstream updat;
    updat.open("record1.txt",ios::in|ios::out);
    if(!updat){
        cout<<"*****ERROR*****"<<endl;
        cout<<endl;
        cout<<"File not found"<<endl;
        return;
    }
    updat.seekg(0,ios::end);
    num=updat.tellg()/sizeof(*this);
      if(num==1){
        cout<<"There are only 1 record"<<endl;
    }
    else cout<<"There are "<<num<<" numbers of records"<<endl;
    cout<<endl;
    cout<<"Enter record number to edit : ";cin>>n;
    updat.seekg((n-1)*sizeof(*this));
    updat.read(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"The record "<<n<<" has following data : "<<endl;
    showdata();
    updat.close();
    updat.open("record1.txt",ios::in|ios::out|ios::binary);
    updat.seekg((n-1)*sizeof(*this));
    cout<<"Enter data to modify : "<<endl;
    setdata();
    updat.write(reinterpret_cast<char*>(this),sizeof(*this));
    }

void account::writ_recrd(){
    ofstream writ;
    writ.open("record1.txt", ios::binary|ios::app);
    setdata();
    writ.write(reinterpret_cast<char*>(this),sizeof(*this));
    writ.close();
}
void account::read_recrd(){
    ifstream readi;
    readi.open("record1.txt",ios::binary);
    if(!readi){
        cout<<"*****ERROR*****"<<endl;
        cout<<endl;
        cout<<"File not found"<<endl;
        return;
    }
    while(!readi.eof()){
        if(readi.read(reinterpret_cast<char*>(this),sizeof(*this))){ 
            showdata();
        }
    }
    readi.close();
}
int main(){
    account b;
    int n;
    cout<<"******HAIDER ACCOUNT INFORMATION SYSTEM*****"<<endl;
    cout<<endl;
    cout<<"Select one option below :"<<endl;
    cout<<endl;
    cout<<"     1=> Add record to file"<<endl;
    cout<<"     2=> Show record from file"<<endl;
    cout<<"     3=> Search record from file"<<endl;
    cout<<"     4=> Update record"<<endl;
    cout<<"     5=> Delete record"<<endl;
    cout<<"     6=> Quit"<<endl;
    cout<<"Enter your choice : ";cin>>n;
    switch (n)
    {
        case 1:
        b.writ_recrd();
        break;
        case 2:
        b.read_recrd();
        break;
        case 3:
        b.search_data();
        break;
        case 4:
        b.updat_data();
        break;
        case 5:
        b.del_data();
        case 6:
        cout<<"***THANKS FOR USING OUR SERVICE***"<<endl;
        default:
        exit(0);
    }
    system("pause");
    return 0;
}