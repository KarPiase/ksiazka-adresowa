#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

struct Uzytkownik
{
    int idUzytkownika=0;
    string nazwa="", haslo="";
};

vector<Uzytkownik> rejestracja(vector<Uzytkownik> users, int usersCount)
{
    int idUzytkownika;
    string nazwa, haslo;

    if (users.size()==0)
    {
        idUzytkownika =1;
    }
    else
    {
        idUzytkownika=users[users.size()-1].idUzytkownika+1;
    }

    cout<< "podaj nazwę uzytkownika"<<endl;
    cin.sync();
    cin>>nazwa;

    int i=0;
    while(i<usersCount)
    {
        if (users[i].nazwa == nazwa)
        {
            cout<<"taki uzytkownik istnieje"<<endl;
            cin>>nazwa;
            i=0;
        }
        else
            i++;
    }
    cout<<"Podaj hasło"<<endl;
    cin>>haslo;
    cout<< "konto zalozone"<<endl;

    fstream PlikZUzytkownikami;
    PlikZUzytkownikami.open("Uzytkownicy.txt", ios::out | ios::app);
    PlikZUzytkownikami<<idUzytkownika<<"|"<<nazwa<<"|"<<haslo<<endl;
    PlikZUzytkownikami.close();

    Uzytkownik obiekt;
    obiekt.idUzytkownika=idUzytkownika;
    obiekt.nazwa=nazwa;
    obiekt.haslo=haslo;
    users.push_back(obiekt);
    return users;

}

int logowanie(vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow)
{
    string nazwa,haslo;
    cout<<"Podaj login"<<endl;
    cin>>nazwa;

    int i=0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout<<"Podaj haslo, pozostało prób "<<3-proby<<endl;
                cin>>haslo;
                if (uzytkownicy[i].haslo==haslo)
                {
                    cout<<"Zalogowales sie"<<endl;
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<< "Podano 3 próby, poczekaj 3 sekundy przed kolejną próbą"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<< "Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(3000);
    return 0;
}

void zmianahasla(vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<<"Podaj nowe haslo: "<<endl;
    cin>>haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if(uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo=haslo;
            cout<<"Hasło zostało zmienione"<<endl;
            Sleep(1000);
        }
    }
}
Uzytkownik DodajUzytkownika(vector<Uzytkownik> uzytkownicy, string daneUzytkownika)
{
    Uzytkownik obiekt;
    string stringidUzytkownika="", nazwa="", haslo="";
    int idUzytkownika;
    int i=0;
    while (daneUzytkownika[i]!='|')
    {
        i++;
    }
    stringidUzytkownika=daneUzytkownika.substr(0,i);
    obiekt.idUzytkownika=atoi(stringidUzytkownika.c_str());
    daneUzytkownika.erase(0,i+1);
    i=0;
    while (daneUzytkownika[i]!='|')
    {
        i++;
    }
    obiekt.nazwa=daneUzytkownika.substr(0,i);
    daneUzytkownika.erase(0,i+1);
    i=0;
    while (daneUzytkownika[i]!='|')
    {
        i++;
    }
    obiekt.haslo=daneUzytkownika.substr(0,i);
    daneUzytkownika.erase(0,i+1);
    i=0;
    return obiekt;
}
vector<Uzytkownik> WczytajDaneUzytkownikowZPliku(vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow)
{
    fstream PlikZUzytkownikami;
    PlikZUzytkownikami.open("Uzytkownicy.txt", ios::in);
    if(PlikZUzytkownikami.good()==false) iloscUzytkownikow=0;
    string linia;
    while (getline(PlikZUzytkownikami, linia))
    {
        uzytkownicy.push_back(DodajUzytkownika(uzytkownicy, linia));
        iloscUzytkownikow++;
    }
    PlikZUzytkownikami.close();

    return uzytkownicy;
}
struct Znajomy
{
    int id=0, idZalogowanegoUzytkownika=0;
    string imie="", nazwisko="", telefon="", email="", adres="";
};

vector<Znajomy> ZapiszNowyAdres(vector<Znajomy> znajomi, int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    int id, i=0;
    string imie, nazwisko, telefon, adres, email, linia, ostatniaLinia, stringid;
    fstream PlikZAdresami;
    PlikZAdresami.open("adresy.txt", ios::in);
    if (PlikZAdresami.good())
    {
        while(getline (PlikZAdresami, linia))
            ostatniaLinia=linia;
        while (ostatniaLinia[i]!='|')
        {
            i++;
        }
        stringid=ostatniaLinia.substr(0,i);
        id=atoi(stringid.c_str())+1;
    }
    else
        id=1;
    PlikZAdresami.close();
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

    PlikZAdresami.open("adresy.txt", ios::out | ios::app);
    PlikZAdresami<<id<<"|"<<idZalogowanegoUzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<telefon<<"|"<<email<<"|"<<adres<<"|"<<endl;
    PlikZAdresami.close();

    Znajomy obiekt;
    obiekt.id=id;
    obiekt.idZalogowanegoUzytkownika=idZalogowanegoUzytkownika;
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
    string stringid="", stringidZalogowanegoUzytkownika="", imie="", nazwisko="", telefon="", email="", adres="";
    int id, idZalogowanegoUzytkownika;
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
    stringidZalogowanegoUzytkownika=adresZnajomego.substr(0,i);
    obiekt.idZalogowanegoUzytkownika=atoi(stringidZalogowanegoUzytkownika.c_str());
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
int WyswietlWszystkichZnajomych(vector<Znajomy> znajomi, int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    int i=0;

    while(i<iloscZnajomych)
    {
        if (idZalogowanegoUzytkownika==znajomi[i].idZalogowanegoUzytkownika)
        {
            cout<<znajomi[i].imie<<endl;
            cout<<znajomi[i].nazwisko<<endl;
            cout<<znajomi[i].telefon<<endl;
            cout<<znajomi[i].adres<<endl;
            cout<<znajomi[i].email<<endl;
        }
        i++;
    }
    return 0;
}

vector<Znajomy> WczytajDaneZPliku(vector<Znajomy> znajomi, int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    fstream PlikZAdresami;
    PlikZAdresami.open("adresy.txt", ios::in);
    if(PlikZAdresami.good()==false) iloscZnajomych=0;
    string linia, liniaRobocza, stringidZalogowanegoUzytkownika;

    while (getline(PlikZAdresami, linia))
    {
        liniaRobocza=linia;

        int i=0;
        while (liniaRobocza[i]!='|')
        {
            i++;
        }
        liniaRobocza.erase(0,i+1);
        i=0;
        while (linia[i]!='|')
        {
            i++;
        }
        stringidZalogowanegoUzytkownika=liniaRobocza.substr(0,i);
        if(idZalogowanegoUzytkownika==atoi(stringidZalogowanegoUzytkownika.c_str()))
        {
            znajomi.push_back(DodajAdres(znajomi, linia));
            iloscZnajomych++;
        }
    }
    PlikZAdresami.close();

    return znajomi;
}

void WyswietlZnajomychPoImieniu(vector<Znajomy> znajomi,int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    int i=0;
    string wyszukiwaneImie;
    cout<<"podaj wyszukiwane imie:"<<endl;
    cin.sync();
    getline (cin, wyszukiwaneImie);
    while(i<iloscZnajomych)
    {
        if (wyszukiwaneImie==znajomi[i].imie&&idZalogowanegoUzytkownika==znajomi[i].idZalogowanegoUzytkownika)
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

void WyswietlZnajomychPoNazwisku(vector<Znajomy> znajomi,int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    int i=0;
    string wyszukiwaneNazwisko;
    cout<<"podaj wyszukiwane nazwisko:"<<endl;
    cin>>wyszukiwaneNazwisko;
    while(i<iloscZnajomych)
    {
        if (wyszukiwaneNazwisko==znajomi[i].nazwisko&&idZalogowanegoUzytkownika==znajomi[i].idZalogowanegoUzytkownika)
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
void AktualizacjaPlikuZAdresami(vector<Znajomy> znajomi, int wyszukiwaneid, int idZalogowanegoUzytkownika)
{
    fstream PlikZAdresami;
    fstream TymczasowyPlikZAdresami;
    PlikZAdresami.open("adresy.txt", ios::in);
    TymczasowyPlikZAdresami.open("adresy_Tymczasowe.txt", ios::out);

    string linia, liniaRobocza, stringid, stringidUzytkownika;
    int j=0;
    while (getline(PlikZAdresami, linia))
    {
        liniaRobocza=linia;

        int i=0;
        while (liniaRobocza[i]!='|')
        {
            i++;
        }
        stringid=liniaRobocza.substr(0,i);
        liniaRobocza.erase(0,i+1);
        i=0;
        while (linia[i]!='|')
        {
            i++;
        }
        stringidUzytkownika=liniaRobocza.substr(0,i);
        if (idZalogowanegoUzytkownika==atoi(stringidUzytkownika.c_str())&&znajomi[j].id==atoi(stringid.c_str()))
        {
            TymczasowyPlikZAdresami<<znajomi[j].id<<"|"<<znajomi[j].idZalogowanegoUzytkownika<<"|"<<znajomi[j].imie<<"|"<<znajomi[j].nazwisko<<"|"<<znajomi[j].telefon<<"|"<<znajomi[j].email<<"|"<<znajomi[j].adres<<"|"<<endl;
            j++;
        }
        else if(idZalogowanegoUzytkownika!=atoi(stringidUzytkownika.c_str()))
            TymczasowyPlikZAdresami<<linia<<endl;
    }
    PlikZAdresami.close();
    remove( "adresy.txt" );
    TymczasowyPlikZAdresami.close();
    rename("adresy_Tymczasowe.txt", "adresy.txt");
}
vector<Znajomy> EdytujDaneZnajomego(vector <Znajomy> znajomi, int iloscZnajomych, int idZalogowanegoUzytkownika)
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
        }
        else i++;
    }
    AktualizacjaPlikuZAdresami(znajomi, wyszukiwaneid, idZalogowanegoUzytkownika);
    return znajomi;
}

vector<Znajomy> UsunZnajomego(vector <Znajomy> znajomi, int iloscZnajomych, int idZalogowanegoUzytkownika)
{
    int i=0, wyszukiwaneid;
    char wybor;
    cout<<"Podaj ID znajomego do usuniecia"<<endl;
    cin>>wyszukiwaneid;
    cout<<"Czy napewno chcesz usunac?"<<endl;
    cin>>wybor;
    if(wybor=='t')
    {
        while(i<znajomi.size())
        {
            if (wyszukiwaneid==znajomi[i].id&&idZalogowanegoUzytkownika==znajomi[i].idZalogowanegoUzytkownika)
            {
                znajomi.erase(znajomi.begin()+i);
            }
            i++;
        }
        AktualizacjaPlikuZAdresami(znajomi, wyszukiwaneid, idZalogowanegoUzytkownika);
    }
    return znajomi;
}

int main()
{
    int iloscZnajomych=0;
    int idZnajomego=0;
    vector<Znajomy> znajomi;
    int idZalogowanegoUzytkownika=0;
    int iloscUzytkownikow=0;
    vector<Uzytkownik> uzytkownicy;
    uzytkownicy=WczytajDaneUzytkownikowZPliku(uzytkownicy, iloscUzytkownikow);
    iloscUzytkownikow=uzytkownicy.size();
    char wybor;

    while(1)
    {
        if (idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout << "1. Rejestracja"<<endl;
            cout << "2. Logowanie"<< endl;
            cout << "3. Zakoñcz program" << endl;
            cin>>wybor;

            if (wybor =='1')
            {
                uzytkownicy= rejestracja(uzytkownicy,iloscUzytkownikow);
                iloscUzytkownikow=uzytkownicy.size();
            }
            else if(wybor=='2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                znajomi=WczytajDaneZPliku(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                iloscZnajomych=znajomi.size();
            }
            else if (wybor=='3')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<<znajomi.size()<<endl;
            cout << "1. Zapisz nowy adres"<<endl;
            cout << "2. Wyszukiwanie adresow po imieniu"<< endl;
            cout << "3. Wyszukiwanie adresow po nazwisku" << endl;
            cout << "4. Wyœwietl wszystkich znajomych"<<endl;
            cout << "5. Edytuj dane znajomego"<<endl;
            cout << "6. Usun znajomego"<<endl;
            cout << "7. Zmiana hasla"<<endl;
            cout << "8. Wylogowanie"<< endl;
            cin>>wybor;
            if(wybor=='1')
            {
                znajomi=ZapiszNowyAdres(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                iloscZnajomych=znajomi.size();
            }
            else if(wybor=='2')
            {
                WyswietlZnajomychPoImieniu(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                system("pause");
            }
            else if(wybor=='3')
            {
                WyswietlZnajomychPoNazwisku(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                system("pause");
            }
            else if(wybor=='4')
            {
                WyswietlWszystkichZnajomych(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                system("pause");
            }
            else if(wybor=='5')
            {
                znajomi=EdytujDaneZnajomego(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
            }
            else if(wybor=='6')
            {
                znajomi=UsunZnajomego(znajomi, iloscZnajomych, idZalogowanegoUzytkownika);
                iloscZnajomych=znajomi.size();
            }
            if (wybor =='7')
            {
                zmianahasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if(wybor=='8')
            {
                idZalogowanegoUzytkownika=0;
                znajomi.clear();
            }
        }
    }
    return 0;
}
