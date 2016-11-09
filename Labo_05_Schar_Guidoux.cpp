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

/*
 * 
 */
int main() {

   const char OUI = 'O';
   
   const char CUNNI = 'C';
   const char NON = 'N';

   const int ANNEE_MIN = 1900;
   const int ANNEE_MAX = 2100;

   char recommencer;
   bool saisieOk;
   int annee;


   do {
      // Saisie de l'année
      //-----------------------------------------------------------------------------
      do {
         cout << endl << "Quelle annee ? [" << ANNEE_MIN
                 << "-" << ANNEE_MAX
                 << "] : ";

         if (!(saisieOk = (cin >> annee
                 && ANNEE_MIN <= annee
                 && annee <= ANNEE_MAX))) {
            cout << "Mauvaise valeur" << endl;
            cin.clear(); //Répare le buffer
         }
         VIDER_BUFFER;

      } while (!saisieOk);


      do {
         cout << "Voulez-vous recommencer ? [" << OUI << "|" << NON << "] : ";

         cin >> recommencer;

         VIDER_BUFFER;

      } while ((recommencer != OUI) && (recommencer != NON));

   } while (recommencer == OUI);



   return EXIT_SUCCESS;
}

