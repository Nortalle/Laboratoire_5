/*
 -----------------------------------------------------------------------------------
 Laboratoire : 05
 Fichier     : Labo_05_Schar_Guidoux.cpp
 Auteur(s)   : Vincent Guidoux
 Date        : 15.11.2016

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 5.3.0
 -----------------------------------------------------------------------------------
 */

#include <cmath>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <iostream>

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;

bool estBissextile(int annee) {

   return ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0);
}

int nbreJour(int mois, int annee) {

   switch (mois) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12: return 31;

      case 4:
      case 6:
      case 9:
      case 11: return 30;

      case 2: return estBissextile(annee) ? 29: 28;
   }
}

bool veutRecommencer() {

   char recommencer;

   const char OUI = 'O';
   const char NON = 'N';

   do {
      cout << "Voulez-vous recommencer ? [" << OUI << "|" << NON << "] : ";

      cin >> recommencer;

      VIDER_BUFFER;

   } while ((recommencer != OUI) && (recommencer != NON));

   return recommencer == OUI;
}

void fin() {
   cout << "presser ENTER pour quitter" << endl;
   cin.get();
}

int main() {

   const int ANNEE_MIN = 1900;
   const int ANNEE_MAX = 2100;

   int annee;
   bool saisieOk;

   do {
      // Saisie de l'année
      //-----------------------------------------------------------------------------
      do {
         cout << endl << "Quelle annee ? [" << ANNEE_MIN
                 << "-" << ANNEE_MAX
                 << "] : ";

         if (!(saisieOk = (cin >> annee && ANNEE_MIN <= annee && annee <= ANNEE_MAX))) {
            cout << "Mauvaise valeur" << endl;
            cin.clear(); //Répare le buffer
         }
         VIDER_BUFFER;

      } while (!saisieOk);

   } while (veutRecommencer());

   fin();

   return EXIT_SUCCESS;
}

