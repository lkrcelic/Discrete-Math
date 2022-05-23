#include <bits/stdc++.h>
using namespace std;

struct Vertex
{
   int brojVrha;
   vector<int> susjedi;
   // vector<int> zabranjeneBoje;
};

bool nadiElement(vector<int> &v, int element)
{
   for (int i : v)
   {
      if (i == element)
         return true;
   }
   return false;
}

void printVector(vector<int> &v)
{
   for (int i : v)
      cout << i << ' ';
   cout << endl;
}
int getMax(vector<int> &v)
{
   int max = 0;
   for (int i : v)
   {
      if (max < i)
         max = i;
   }
   return max;
}

bool provjeriBoju(vector<int> &bojeVrhova, Vertex &vrh, int boja)
{
   for (int i : vrh.susjedi)
   {
      if (bojeVrhova.at(i - 1) == boja)
         return false;
      else if (bojeVrhova.at(i - 1) == 0) // možemo ovo jer se susjedi dodaju po redu
         break;
   }
   return true;
}

// vrhovi i bojeVrhova krecu od broja 1 sa indexa 0 u polju
void prodiKrozBoje(vector<Vertex> &vrhoviGrafa, vector<int> &bojeVrhova, int &kromatskiBroj, int brojVrha, int brojBoja)
{
   if (vrhoviGrafa.size() < brojVrha)
      return;
   else
   {
      if (brojBoja >= kromatskiBroj - 1) // ne treba nam vise boja od kromatskog broja
         brojBoja = kromatskiBroj - 1;   // odmah ispituj za jednu boju manje
      for (int i = 0; i < brojBoja; i++)
      {
         if (provjeriBoju(bojeVrhova, vrhoviGrafa.at(brojVrha - 1), i + 1))
         {
            bojeVrhova.at(brojVrha - 1) = i + 1; // oboji vrh
            if (brojVrha == vrhoviGrafa.size())  ////////////////////////// cim nade za zadnji ajmo ca
               break;
            prodiKrozBoje(vrhoviGrafa, bojeVrhova, kromatskiBroj, brojVrha + 1, brojBoja + 1);
         }
      }
      if (vrhoviGrafa.size() == brojVrha && bojeVrhova.at(brojVrha - 1) != 0)
      {
         int pom = getMax(bojeVrhova);
         if (pom < kromatskiBroj)
         {
            kromatskiBroj = pom;
            printVector(bojeVrhova);
         }
      }

      bojeVrhova.at(brojVrha - 1) = 0; // izbrisi boju vrha
   }
   return;
}

int main(void)
{
   int brojVrhova, brojElemenata, kromatskiBroj;
   int maxSusjed = 0;          // najveci br. susjeda
   vector<Vertex> vrhoviGrafa; // vrhovi grafa, 1 2 3 ...

   ifstream MyFile("graf.txt");

   MyFile >> brojVrhova;
   vector<int> bojeVrhova(brojVrhova); // polje koje sadrzi boje vrhova,svi su nula na početku
   MyFile >> brojElemenata;            // br. elem. u skupu S
   vector<int> skup(brojElemenata);
   int pomVar;
   for (int i = 0; i < brojElemenata; i++)
      MyFile >> skup.at(i);
   MyFile.close();

   // DEFINIRAJ POLJE VRHOVA
   for (int i = 1; i <= brojVrhova; i++) // ide od jedan da razlika valja
   {
      Vertex v;
      v.brojVrha = i;                       /////////////////////////////////////////////////////////
      for (int j = 1; j <= brojVrhova; j++) // vrhovi idu 1 2 3 ...
      {
         int razlika = abs(i - j);
         if (nadiElement(skup, razlika))
            v.susjedi.push_back(j);
      }
      if (maxSusjed < v.susjedi.size())
         maxSusjed = v.susjedi.size();

      vrhoviGrafa.push_back(v);
   }
   kromatskiBroj = maxSusjed + 1;

   // ISPIS

   for (int i = 0; i < brojVrhova; i++)
   {
      cout << "Vrh: " << i + 1 << "  Susjedi: ";
      printVector(vrhoviGrafa[i].susjedi);
   }

   // POZIVANJE FUNKCIJE
   prodiKrozBoje(vrhoviGrafa, bojeVrhova, kromatskiBroj, 1, 1);

   cout << "Kromatski broj: " << kromatskiBroj << endl;
   return 0;
}

/*
n = | 20 | 18 | 16 | 12 | 10 | 8 |
    S = | 1 4 2 5 7 8 10 11 12 | 1 3 8 10 11 12 15 | 1 2 3 4 5 10 11 | 1 2 4 8 | 1 2 3 4 5 8 9 | 1 2 3 |
   krom = | 6 | 5 | 6 | 3 | 6 | 4 |
*/