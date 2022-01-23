#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

struct Znajomy
{
    int id=0;
    string imie="", nazwisko="", telefon="", email="", adres="";
};

vector<Znajomy> ZapiszNowyAdres(vector<Znajomy> znajomi, int iloscZnajomych)
{
    int id;
    string imie, nazwisko, telefon, adres, email;
    if (znajomi.size()==0)
    {
        id=0;
    }
    else
    {
        id=znajomi[znajomi.size()-1].id+1;
    }
    cout<<"podaj imie nowego znajomego"<<endl;
    cin.sync();
    getline(cin, imie);
    cout<<"podaj nazwisko nowego znajomego"<<endl;
    getline(cin, nazwisko);
    cout<<"podaj telefon nowego znajomego"<<endl;
    getline(cin, telefon);
    cout<<"podaj email nowego znajomego"<<endl;
    getline(cin, email);
    cout<<"podaj adres nowego znajomego"<<endl;
    getline(cin, adres);

    fstream PlikZAdresami;
    PlikZAdresami.open("adresy.txt", ios::out | ios::app);
    PlikZAdresami<<id<<"|"<<imie<<"|"<<nazwisko<<"|"<<telefon<<"|"<<email<<"|"<<adres<<"|"<<endl;
    PlikZAdresami.close();

    Znajomy obiekt;
    obiekt.id=id;
    obiekt.imie=imie;
    obiekt.nazwisko=nazwisko;
    obiekt.telefon=telefon;
    obiekt.email=email;
    obiekt.adres=adres;
    znajomi.push_back(obiekt);
    return znajomi;
}

Znajomy DodajAdres(vector<Znajomy> znajomi, string adresZnajomego)
{
    Znajomy obiekt;
    string stringid="", imie="", nazwisko="", telefon="", email="", adres="";
    int id;
    int i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    stringid=adresZnajomego.substr(0,i);
    obiekt.id=atoi(stringid.c_str());
    adresZnajomego.erase(0,i+1);
    i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    obiekt.imie=adresZnajomego.substr(0,i);
    adresZnajomego.erase(0,i+1);
    i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    obiekt.nazwisko=adresZnajomego.substr(0,i);
    adresZnajomego.erase(0,i+1);
    i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    obiekt.telefon=adresZnajomego.substr(0,i);
    adresZnajomego.erase(0,i+1);
    i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    obiekt.email=adresZnajomego.substr(0,i);
    adresZnajomego.erase(0,i+1);
    i=0;
    while (adresZnajomego[i]!='|')
    {
        i++;
    }
    obiekt.adres=adresZnajomego.substr(0,i);
    return obiekt;
}
int WyswietlWszystkichZnajomych(vector<Znajomy> znajomi, int iloscZnajomych)

{
    int i=0;
    while(i<iloscZnajomych)
    {
        cout<<znajomi[i].imie<<endl;
        cout<<znajomi[i].nazwisko<<endl;
        cout<<znajomi[i].telefon<<endl;
        cout<<znajomi[i].adres<<endl;
        cout<<znajomi[i].email<<endl;
        i++;
    }
    return 0;
}

vector<Znajomy> WczytajDaneZPliku(vector<Znajomy> znajomi, int iloscZnajomych)
{
    fstream PlikZAdresami;
    PlikZAdresami.open("adresy.txt", ios::in);
    if(PlikZAdresami.good()==false) iloscZnajomych=0;
    string linia;
    while (getline(PlikZAdresami, linia))
    {
        znajomi.push_back(DodajAdres(znajomi, linia));
        iloscZnajomych++;
    }
    PlikZAdresami.close();

    return znajomi;
}

void WyswietlZnajomychPoImieniu(vector<Znajomy> znajomi,int iloscZnajomych)
{
    int i=0;
    string wyszukiwaneImie;
    cout<<"podaj wyszukiwane imie:"<<endl;
    cin.sync();
    getline (cin, wyszukiwaneImie);
    while(i<iloscZnajomych)
    {
        if (wyszukiwaneImie==znajomi[i].imie)
        {
            cout<<znajomi[i].imie<<endl;
            cout<<znajomi[i].nazwisko<<endl;
            cout<<znajomi[i].telefon<<endl;
            cout<<znajomi[i].adres<<endl;
            cout<<znajomi[i].email<<endl;
            i++;
        }
        else
            i++;
    }
}

void WyswietlZnajomychPoNazwisku(vector<Znajomy> znajomi,int iloscZnajomych)
{
    int i=0;
    string wyszukiwaneNazwisko;
    cout<<"podaj wyszukiwane nazwisko:"<<endl;
    cin>>wyszukiwaneNazwisko;
    while(i<iloscZnajomych)
    {
        if (wyszukiwaneNazwisko==znajomi[i].nazwisko)
        {
            cout<<znajomi[i].imie<<endl;
            cout<<znajomi[i].nazwisko<<endl;
            cout<<znajomi[i].telefon<<endl;
            cout<<znajomi[i].adres<<endl;
            cout<<znajomi[i].email<<endl;
            i++;
        }
        else
            i++;
    }
}
void EdytujDaneZnajomego(vector <Znajomy> znajomi, int iloscZnajomych)
{
    int i=0, wyszukiwaneid;
    char wybor;
    cout<<"podaj ID znajomego"<<endl;
    cin>>wyszukiwaneid;
    while(i<iloscZnajomych)
    {
        if (wyszukiwaneid==znajomi[i].id)
        {
            cout<<"wybierz daną do zmiany"<<endl;
            cout<<"1. "<<znajomi[i].imie<<endl;
            cout<<"2. "<<znajomi[i].nazwisko<<endl;
            cout<<"3. "<<znajomi[i].telefon<<endl;
            cout<<"4. "<<znajomi[i].adres<<endl;
            cout<<"5. "<<znajomi[i].email<<endl;
            cout<<"6. Powrót do menu"<<endl;
            cin>>wybor;
            if (wybor=='1')
            {
                cout<<"Podaj nowe imię"<<endl;
                cin>>znajomi[i].imie;
            }
            else if (wybor=='2')
            {
                cout<<"Podaj nowe nazwisko"<<endl;
                cin>>znajomi[i].nazwisko;
            }
            else if (wybor=='3')
            {
                cout<<"Podaj nowy numer telefonu"<<endl;
                cin>>znajomi[i].telefon;
            }
            else if (wybor=='4')
            {
                cout<<"Podaj nowy email"<<endl;
                cin>>znajomi[i].email;
            }
            else if (wybor=='5')
            {
                cout<<"Podaj nowy adres"<<endl;
                cin>>znajomi[i].adres;
            }
            else if (wybor=='6')
            {
                break;
            }
            fstream PlikZAdresami;
            PlikZAdresami.open("adresy.txt", ios::out);
            for (int i=0; i<znajomi.size(); i++)
            {
                string stringid;
                stringid=to_string(znajomi[i].id);
                PlikZAdresami<<stringid<<"|"<<znajomi[i].imie<<"|"<<znajomi[i].nazwisko<<"|"<<znajomi[i].telefon<<"|"<<znajomi[i].email<<"|"<<znajomi[i].adres<<"|"<<endl;
            }
            PlikZAdresami.close();
        }
        else i++;
    }
}

vector<Znajomy> UsunZnajomego(vector <Znajomy> znajomi, int iloscZnajomych)
{
    int i=0, wyszukiwaneid;
    char wybor;
    cout<<"Podaj ID znajomego do usuniecia"<<endl;
    cin>>wyszukiwaneid;
    cout<<"Czy napewno chcesz usunac?"<<endl;
    cin>>wybor;
    if(wybor=='t')
    {
        fstream PlikZAdresami;
        PlikZAdresami.open("adresy.txt", ios::out);
        while(i<znajomi.size())
        {
            if (wyszukiwaneid==znajomi[i].id)
            {
                znajomi.erase(znajomi.begin()+i);
            }
            i++;
        }
        i=0;
        while(i<znajomi.size())
        {
            string stringid;
            stringid=to_string(znajomi[i].id);
            PlikZAdresami<<stringid<<"|"<<znajomi[i].imie<<"|"<<znajomi[i].nazwisko<<"|"<<znajomi[i].telefon<<"|"<<znajomi[i].email<<"|"<<znajomi[i].adres<<"|"<<endl;
            i++;
        }
        PlikZAdresami.close();
    }
    return znajomi;
}

int main()
{
    int iloscZnajomych=0;
    int idZnajomego=0;
    vector<Znajomy> znajomi;
    znajomi=WczytajDaneZPliku(znajomi, iloscZnajomych);
    iloscZnajomych=znajomi.size();
    char wybor;

    while(1)
    {
        cout << "1. Zapisz nowy adres"<<endl;
        cout << "2. Wyszukiwanie adresow po imieniu"<< endl;
        cout << "3. Wyszukiwanie adresow po nazwisku" << endl;
        cout << "4. Wyœwietl wszystkich znajomych"<<endl;
        cout << "5. Edytuj dane znajomego"<<endl;
        cout << "6. Usun znajomego"<<endl;
        cout << "9. Zakoncz program"<<endl;
        cin>>wybor;
        if(wybor=='1')
        {
            znajomi=ZapiszNowyAdres(znajomi, iloscZnajomych);
            iloscZnajomych=znajomi.size();
        }
        else if(wybor=='2')
        {
            WyswietlZnajomychPoImieniu(znajomi, iloscZnajomych);
        }
        else if(wybor=='3')
        {
            WyswietlZnajomychPoNazwisku(znajomi, iloscZnajomych);
        }
        else if(wybor=='4')
        {
            WyswietlWszystkichZnajomych(znajomi, iloscZnajomych);
        }
        else if(wybor=='5')
        {
            EdytujDaneZnajomego(znajomi, iloscZnajomych);
        }
        else if(wybor=='6')
        {
            znajomi=UsunZnajomego(znajomi, iloscZnajomych);
            iloscZnajomych=znajomi.size();
        }
        else if(wybor=='9')
        {
            exit(0);
        }
    }
    return 0;
}
