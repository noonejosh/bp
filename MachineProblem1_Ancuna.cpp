
//Hanz Joshua V. Ancuna
//BSCS2B
//Machine Problem 1

//ADT List of players usig array of structures
#include <iostream> //Used for input and output.
#include <stdlib.h>
#include <fstream>  //This library is used for file handling.
#include <sstream>  //Used to manipulate strings as I/O streams.
#include <iomanip>  //Used in setting width of output to align them.
#define MAX 5   //MAX number is defined.
using namespace std;
typedef struct players {
   string name;
   int fga,fgm;
}REC;
//DATA STRUCTURE
typedef struct adtlist {
    REC bp[MAX];
    int last;
}LIST;
//Class definition
class MyList {
private:
    LIST L;
    bool isfull();
    bool isempty();
    int locate(string n);
    int locatePos(string n);
    double computeFGP(int a, int m);
public:
    void makenull();
    void insertSort(REC r);
    void del(string n);
    void display();
    void update(string n);//update the fga and/or fgm only given the name of the record
    void save();
    void retrieve();
};
int menu();
void MyList::insertSort(REC r){
int p,i;
if(isfull()){
    cout<<"List is full.\n";
    system("pause");
}
else {
    p = locatePos(r.name);
    for(i=L.last;i>=p;i--){
        L.bp[i+1]=L.bp[i];
    }
    L.bp[p] = r;
    L.last++;
}
}
int MyList::locatePos(string n){
int i;
for (i=0;i<=L.last;i++){
    if (n<L.bp[i].name)
        return i;
}
return i;//or return L.last+1;
}
void MyList::update(string n){
    int i, p;
    REC x;
    if(isempty()){
        cout << "The array is empty" << endl;
        system("pause");
    }
    else{
        p=locate(n);
        if(p<0){
            cout << "Player not found.\n";
        }
        else{
            for(i=p;i<L.last;i++){
                system("cls");
                cout << "name: " << L.bp[p].name << endl;
                cout << "fga: " << L.bp[p].fga << endl;
                cout << "fga: " << L.bp[p].fgm << endl;
                system("pause");
            }
            while(1){
                system("cls");
                int c;
                cout << "1. Update fga" << endl;
                cout << "2. Update fgm" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter the number of your choice: ";
                cin >> c;

                switch(c){
                case 1:
                    system("cls");
                    cout << "Update fga Mode\n";
                    cout << "Enter the new fga: ";
                    cin >> x.fga;
                    L.bp[p].fga = x.fga;
                    cout << "The fga is updated.\n";
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    cout << "Update fgm Mode\n";
                    cout << "Enter the new fgm: ";
                    cin >> x.fgm;
                    L.bp[p].fgm = x.fgm;
                    cout << "The fgm is updated.\n";
                    system("pause");
                    break;
                case 3:
                    return;
                default:
                    cout << "Invalid input.\n";
                    system("pause");
                }
            }
        }
    }
}
int MyList::locate(string n) {
    for (int i = 0; i <= L.last; i++) {
        if (n == L.bp[i].name)
            return i;
    }
    return -1;
}
void MyList::del(string n) {
    if (isempty()) {
        cout << "List is empty.\n";
        system("pause");
    }
    else {
        int p = locate(n);
        for (int i = p; i <= L.last; i++) {
            L.bp[i] = L.bp[i + 1];
        }
        L.last--;
        cout << "Item deleted" << endl;
    }
}
bool MyList::isfull(){
return (L.last==MAX-1);
}

bool MyList::isempty() {
    return(L.last == -1);
}

void MyList::display(){
double fgp;
string remarks;
int i;
system("cls");
cout << setw(24) << left << "Name" << setw(19) << left << "FGA" << setw(22) << left  << "FGM" << setw(18) << left  << "FGP(%)" << setw(14) << left  << "REMARKS" << endl;
for (i=0;i<=L.last;i++){
    fgp = computeFGP(L.bp[i].fga, L.bp[i].fgm);
    remarks = fgp>50? "HIGH" : "LOW";
    cout <<i+1<<".) "<<setw(20)<<left<<L.bp[i].name<<setw(20)<<left<<L.bp[i].fga<<setw(20)<<left<<L.bp[i].fgm<<setw(20)<<setprecision(2)<<fixed<<fgp<<setw(20)<<left<<remarks<<endl;
}
system("pause");
}
double MyList::computeFGP(int a, int m){
return (double)m/a*100.0;
}
void MyList::makenull(){
L.last=-1;
}
int main(){
MyList pl;
REC pd;
pl.makenull();//initialize the list
pl.retrieve();//retrieve the data from file and insertSort to the list
while(true){
    switch(menu()){
    case 1: system("cls");cout <<"Insert Mode\n";
            cout<<"Input Name: ";getline(cin>>ws, pd.name);
            cout<<"Input FGA: ";cin >> pd.fga;
            cout<<"Input FGM: ";cin >> pd.fgm;
            pl.insertSort(pd);break;
    case 2: system("cls");cout <<"Update Mode\n";
            cout<<"Input Name: ";getline(cin>>ws, pd.name);
            pl.update(pd.name);
            break;
    case 3: system("cls");cout <<"Delete Mode\n";
            cout<<"Input Name: ";getline(cin>>ws, pd.name);
            pl.del(pd.name); break;
    case 4: pl.display();break;
    case 5: pl.save();exit(0);
    default: cout<<"1 to 4 only.\n";system("pause");

    }

}
}
int menu(){
int op;
system("cls");
cout<<"MENU\n";
cout<<"1. Add a Record\n";
cout<<"2. Update a Record\n";
cout<<"3. Delete a Record\n";
cout<<"4. Display All Records\n";
cout<<"5. Exit\n";
cout<<endl<<"Select(1-5): ";
cin >>op;
return op;
}
void MyList::save() //This function is used to save the record into a text file.
{
    int i;

    ofstream fileptr("data2.txt"); //The file is opened.

    for(i = 0; i <= L.last; i++)  //Using a loop, the contents of the array of structures is written into a text file.
    {
        if(i == L.last)
        {
            fileptr << L.bp[i].name << endl << L.bp[i].fga  << " " << L.bp[i].fgm; //If it's the last index of the array there is no endl at the end to avoid unnecessary spaces at the end of the file.
        }
        else
        {
            fileptr << L.bp[i].name << endl << L.bp[i].fga  << " " << L.bp[i].fgm << endl;
        }
    }
    fileptr.close();   //After writing the data, the file is closed.
    system("cls");
    cout << "The records have been saved successfully!" << endl;
}

void MyList::retrieve() //This function is used to retrieve data from a text file.
{
    string firstn;  //This will be used to store the first name of a player.
    string lastn;   //This will be used to store the last name of a player(if there is any).
    ifstream fileptr("data2.txt"); //The file is opened.
    if(fileptr.is_open()) //The various operations will only run if the file is indeed open.
    {
        REC d;  //Using REC, a structure is declared.
        string line; //This will be used in handling the contents of t he file.
        int strline = 0; //This variable will be used to keep track of the current line number.
        while(getline(fileptr, line)) //The loop will run as long as there is a line to be read.
        {
            istringstream data(line); //istringstream is used to handle the strings/lines like an input stream.
            if((strline%2)==0) //If the current line number is 0 or an even number it means that the current line holds the name of the player.
            {
                data >> firstn;//If there are two strings in the current line, they will be stored to firstn and lastn accordingly.
                if(data>>lastn)   //check if there is a stored value in the lastn.
                {
                    d.name = firstn + " " + lastn; //if the condition evaluates to true, concatenate the firstn and lastn.
                }
                else
                {
                    d.name = firstn; //If lastn is empty, only the contents of firstn will be assigned to d.name.
                }
            }
            else //If the current line number is an odd number, it means that it is where the FGA and FGM are written.
            {
                data >> d.fga >> d.fgm; //The FGA and FGM are stored in the structure accordingly.
                insertSort(d);
            }
            strline++; //This value is incremented to determine the current line number.
        }
        cout << "File is read successfully." << endl; //A message is displayed after retrieving the contents of the file.
    }
    else
    {
        cout << "There is no existing record." << endl; //If there is no file, a message will appear.
    }
    fileptr.close(); //The file is closed.
    cout << endl;
    system("pause");
}
