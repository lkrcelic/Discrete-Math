#include <bits/stdc++.h>
using namespace std;

// Global Variables
int a, b;

int tezinaBrida(int k, int l)
{
   return pow((a * k + b * l), 2) + 1;
}

struct Brid
{
   int tezina;
   std::pair<int, int> vrhovi;
   Brid(int tezina, pair<int, int> vrhovi) : tezina(tezina), vrhovi(vrhovi){};
};

Brid findMin(list<Brid> bridovi, int vrh, set<int> visited)
{
   int vrhA;
   int vrhB;
   Brid min = Brid(INT_MAX, make_pair(0, 0));

   for (auto it = bridovi.begin(); it != bridovi.end(); it++)
   {
      vrhA = it->vrhovi.first;
      vrhB = it->vrhovi.second;
      if ((vrh == vrhA && (visited.find(vrhB) == visited.end())) || (vrh == vrhB && (visited.find(vrhA) == visited.end())))
      {
         if (min.tezina > it->tezina)
            min = *it;
      }
   }
   return min;
}

int findTrenutniVrh(int first, int second, set<int> &visited)
{
   if (visited.find(first) == visited.end())
   {
      visited.insert(first);
      return first;
   }
   else
   {
      visited.insert(second);
      return second;
   }
}

int pohlepni(int n)
{
   // punjnje mape
   list<Brid> bridovi; // lista svih bridova
   set<int> visited;
   Brid min = Brid(INT_MAX, make_pair(0, 0));
   Brid pom = min;
   int sum = 0;
   int trenutniVrh;
   int prviVrh;

   // NAPUNI LISTU BRIDOVA
   for (int i = 1; i < n; i++)
   {
      for (int j = i + 1; j <= n; j++)
      {
         pom = Brid(tezinaBrida(i, j), make_pair(i, j));
         bridovi.push_back(pom);
         if (min.tezina > pom.tezina)
         {
            min = pom;
         }
      }
   }
   sum += min.tezina;
   visited.insert(min.vrhovi.first);
   visited.insert(min.vrhovi.second);

   /*
   //Ispisi visited
   for (auto it = visited.begin(); it != visited.end(); it++)
   {
      cout << *it << " ";
   }
   cout << endl;

   //Ispisi bridovi
   for (auto itr = bridovi.begin(); itr != bridovi.end(); ++itr)
   {
      cout << itr->tezina << "  (" << itr->vrhovi.first << ", " << itr->vrhovi.second << ")" << '\n';
   }
   cout << endl;
   */

   // pronađi smjer, treci vrh
   min = Brid(INT_MAX, make_pair(0, 0));
   for (auto it = visited.begin(); it != visited.end(); it++)
   {
      pom = findMin(bridovi, *it, visited);
      if (pom.tezina < min.tezina)
      {
         prviVrh = *visited.begin();
         min = pom;
      }
      else
         prviVrh = *it;
   }
   sum += min.tezina;
   trenutniVrh = findTrenutniVrh(min.vrhovi.first, min.vrhovi.second, visited);

   /*
   //Ispisi visited
   for (auto it = visited.begin(); it != visited.end(); it++)
   {
      cout << *it << " ";
   }
   cout << endl;
   */

   // pronadi smjer do kraja
   for (int i = 0; i < n - 3; i++)
   {
      min = findMin(bridovi, trenutniVrh, visited);
      trenutniVrh = findTrenutniVrh(min.vrhovi.first, min.vrhovi.second, visited);
      sum += min.tezina;
   }

   if (prviVrh > trenutniVrh)
      sum += tezinaBrida(trenutniVrh, prviVrh);
   else
      sum += tezinaBrida(prviVrh, trenutniVrh);

   return sum;
}

// ISCRPNI
void iscrpni(list<int> A, list<int> B, int n, int &rez)
{
   if (n == 2)
      return;

   // int m = 0;
   list<int> C;            // rezultat
   B.push_back(A.front()); // dodaj u B prvi iz A
   A.pop_front();          // makni prvog iz A

   for (int i = 0; i < n - 1; i++)
   {
      C.insert(C.end(), B.begin(), B.end());
      int back = A.back();
      A.pop_back();
      A.push_front(back);
      C.insert(C.end(), A.begin(), A.end());

      if (n == 3)
      {
         int pom = 0;
         auto it2 = C.begin();
         auto it1 = it2++;
         for (; it2 != C.end(); it1++, it2++)
         {
            if (*it1 < *it2)
            {
               pom += tezinaBrida(*it1, *it2);
               // cout << "(" << *it1 << ", " << *it2 << ") " << TMP << "   ";
            }
            else
            {
               pom += tezinaBrida(*it2, *it1);
               // cout << "(" << *it2 << ", " << *it1 << ") " << TMP << "   ";
            }
         }
         pom += tezinaBrida(C.front(), C.back());
         /* DETALNJI ISPIS
         cout << "(" << C.front() << ", " << C.back() << ") " << TMP << "   ";
         cout << endl;
         cout << "Duljina puta: " << pom << endl
              << endl;
         */
         if (pom < rez)
            rez = pom;
         // m++;
      }

      C.clear();
      iscrpni(A, B, n - 1, rez);
   }
}

// (𝑎𝑘 + 𝑏𝑙)^2 + 1 težina brida izmedu vrhpva k i l
// uvijek imamo potpuni graf
// U potpunom težinskom grafu nadi hamiltonovski ciklus minimalne duljine
// ima (n-1)!/2 hamiltonovskh ciklusa
int main(void)
{
   int n, rez = INT_MAX, pohle;

   cout << "Unesite redom, odvojene razmakom, parametre n, a i b: ";
   cin >> n >> a >> b;

   list<int> A;
   list<int> B;
   for (int i = 1; i <= n; i++)
   {
      A.push_back(i);
   }

   iscrpni(A, B, n, rez);
   pohle = pohlepni(n);

   cout << "Iscrpni algoritam nalazi ciklus duljine " << rez << endl;
   cout << "Pohlepni algoritam nalazi ciklus duljine " << pohle << endl;
   if (rez == pohle)
      cout << "Pohlepni algoritam na ovom grafu  daje optimalno rjesenje !" << endl;
   else
      cout << "Pohlepni algoritam na ovom grafu ne daje optimalno rjesenje !" << endl;
   cout << endl;
   for (int i = 1; i <= n; i++)
   {
      cout << "{";
      for (int j = 1; j <= n; j++)
      {
         if (i < j)
            cout << tezinaBrida(i, j) << " ";
         else if (i > j)
            cout << tezinaBrida(j, i) << " ";
         else
            cout << -1 << " ";
      }
      cout << "}" << endl;
   }

   return 0;
}
