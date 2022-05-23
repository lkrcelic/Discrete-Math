#include <bits/stdc++.h>
using namespace std;

double formula(double lambda_1, double lambda_2, double a_1, double a_0, int n)
{
   double rez, alfa_1, alfa_2, x_1, x_2;

   x_1 = (lambda_1 + sqrt(lambda_1 * lambda_1 + 4 * lambda_2)) / 2;
   x_2 = (lambda_1 - sqrt(lambda_1 * lambda_1 + 4 * lambda_2)) / 2;

   if (x_1 == x_2)
   {
      alfa_1 = a_0;
      alfa_2 = a_1 / x_1 - alfa_1;
      rez = alfa_1 * pow(x_1, n) + n * alfa_2 * pow(x_2, n);
   }
   else
   {
      alfa_1 = (a_1 - a_0 * x_2) / (x_1 - x_2);
      alfa_2 = a_0 - alfa_1;
      rez = alfa_1 * pow(x_1, n) + alfa_2 * pow(x_2, n);
   }
   return rez;
}

double rekurzija(double lambda_1, double lambda_2, double a_1, double a_0, int n)
{
   if (n == 2)
      return lambda_1 * a_1 + lambda_2 * a_0;
   else
   {
      double rez;
      rez = lambda_1 * a_1 + lambda_2 * a_0;
      return rekurzija(lambda_1, lambda_2, rez, a_1, n - 1);
   }
}

int main(void)
{
   double lambda_1, lambda_2, a_0, a_1, alfa_1, alfa_2, x_1, x_2;
   int n;
   double check1, check2, check3;

   cout << "Unesite prvi koeficijent λ_1 rekurzivne relacije: ";
   cin >> lambda_1;
   cout << "Unesite drugi koeficijent λ_2 rekurzivne relacije: ";
   cin >> lambda_2;
   cout << "Unesite vrijednost nultog clana niza a_0: ";
   cin >> a_0;
   cout << "Unesite vrijednost prvog clana niza a_1: ";
   cin >> a_1;
   cout << "Unesite redni broj n trazenog clana niza: ";
   cin >> n;

   // pomocu formule za opce rješenje homogene rekurzivne relacije

   cout << endl;
   cout << "Vrijednost n-tog clana niza pomocu formule: " << formula(lambda_1, lambda_2, a_1, a_0, n) << endl;
   check1 = rekurzija(lambda_1, lambda_2, a_1, a_0, n);
   cout
       << "Vrijednost n-tog clana niza iz rekurzije: " << rekurzija(lambda_1, lambda_2, a_1, a_0, n) << endl;

   cout << endl;
   check2 = formula(lambda_1, lambda_2, a_1, a_0, n + 2);
   cout
       << "Vrijednost (n+2) clana niza pomocu formule: " << formula(lambda_1, lambda_2, a_1, a_0, n + 2) << endl;
   if (check1 == check2)
      cout << "(n+2)-clan je jednak od n-tog clana" << endl;
   else if (check1 > check2)
      cout << "(n+2)-clan je manji od n-tog clana" << endl;
   else
      cout << "(n+2)-clan je veci od n-tog clana" << endl;

   return 0;
}