#include <fstream>
using namespace std;
ifstream cin("defrag.in");
ofstream cout("defrag.out");
///Disk fiind declarat global are toate valorile 0.
int disk[101][361]; ///disk[pista][sector].
//Un cluster este o pozitie a unui punct A(x,y) de pe disk.
int cerinta , pista , sector;
int cluster, x , y;

//Functia "mutari" returneaza minimul de mutari pt defragmentare.
//Ideea pentru minimul de mutari este explicata in main.
int mutari(int i)
{
    int nr1 = disk[i][sector];
    int sol = 0;
    ///Caz particular -  pista este libera.
    if(nr1 == 0)
        return 0; //Nu incheie programul ci returneaza valoarea 0.
    ///Sa luam fiecare interval [p,j] care contine nr1 pozitii.
    int j , p , interval;
    for(j = nr1;j<=sector;j++)
    {
        p = j - nr1;
        interval = disk[i][j] - disk[i][p];
        //cout<<interval<<' ';
        if(interval > sol)
            sol = interval;
    }
    //cout<<'\n';
    /**Codul este bun , exemplul da cum trebuie dar daca trimitem
    ce am facut pana acum, primim 40 de puncte. DE CE??  */

    /**O pista este circulara. Sa luam un exemplu pe o pista:
     pista{1,1,0,0,1,1} . nr1 = 4.
     poz   1 2 3 4 5 6
               p     j (interval final)
     Observati ca daca pista este circulara asta inseamna ca
     inceputul (poz: 1) si sfarsitul(poz: 6) sunt una langa alta.
     Cand noi cautam pe intervale de cate 4 numere, nu trecem
     si prin intervalul compus din pozitiile {5,6,1,2}
     care contine de fapt numarul maxim cautat (4). Adica nu este nevoie de mutari
     Pentru a repara aceasta neatentie putem :
     - dupa cum a sugerat Vlad  sa dublam efectiv vectorul si sa parcurgem de doua ori.
     - dupa cum am sugerat eu , sa facem un artificiu de calcul pentru a parcurge doar
     intervalele neverificate. In continuare voi explica ideea mea.
    */

    /** Sa luam exemplul de mai devreme doar ca dublat:
        pista{1,1,0,0,1,1,1,1,0, 0, 1, 1} . nr1 = 4 + 4.
        poz   1 2 3 4 5 6 7 8 9 10 11 12
                  p     j                 prima pereche (p,j)este ultimul interval din primul exemplu
                              p        j  a doua este ultimul interval din exemplul dublat.
                        p     j           a treia este de fapt ultimul interval care ne intereseaza.

        dupa ce (j > sector) putem calcula suma partiala din pozitia j in urmatorul mod :
        s = disk[i][sector]+disk[i][j-sector].
        Putem astfel sa parcurgem restul intervalelor pana cand p = sector;
    */
    for(p = sector - nr1 + 1, j = sector+1; p <= sector; p++ ,j++)
    {
        interval = disk[i][sector] + disk[i][j-sector] - disk[i][p];
        if(interval > sol)
            sol = interval;
    }
    return nr1 - sol;
}



//Functie ce afiseaza diskul.(Pentru intelegere)
void afisareDisk()
{       cout<<'\n';
     for(int i = 1;i<=pista;i++){
        for(int j = 1;j<=sector;j++)
            cout<<disk[i][j]<<' ';
        cout<<'\n';}
}
int main()
{
    cin >> cerinta >> pista >> sector;
    cin >> cluster;
    for(int i = 1; i <= cluster;i++)
    {
        cin >> x >> y;
        disk[x][y] = 1;
    }
    //afisareDisk();

    ///Facem suma partiala pe fiecare pista in parte.
    for(int i = 1;i<=pista;i++)
        for(int j = 1;j<=sector;j++)
            disk[i][j]+=disk[i][j-1];

    //afisareDisk();

    if(cerinta == 1)
    {
        /**Suma partiala fiind facuta, elementul disk[i][sector]
        contine cate clustere sunt ocupate pe pista i.
        Numaram cate dintre acestea sunt 0 (libere) pt prima cerinta.*/
        int sol = 0;
        for(int i = 1; i <= pista; i++)
            if(disk[i][sector] == 0)
                sol++;
        cout << sol;
        return 0;
        //"return 0;" incheie programul.
    }
    if(cerinta == 2)
    {
        /** Fie - nr1 numarul de clustere de pe o pista.
                - sol numarul maxim de clustere dintr-un interval de nr1 numere
            Numarul minim de mutari: nr1 - sol.

            Putem calcula cate clustere sunt intr-un interval [i,j]
            in O(1)datorita sumelor partiale.
            Nr clustere de pe linia i din intervalul [p,j] =
            disk[i][j] - disk[i][j-p].  */
        ///Afisam numarul minim de mutari de pe fiecare pista.
        for(int i = 1; i <= pista; i++)
            cout<<mutari(i)<<' ';
    }
    return 0;
}
