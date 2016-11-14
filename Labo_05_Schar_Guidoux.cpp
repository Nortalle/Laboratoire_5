/*
 -----------------------------------------------------------------------------------
 Laboratoire : 05
 Fichier     : Labo_05_Schar_Guidoux.cpp
 Auteur(s)   : Vincent Guidoux et Joel Schär
 Date        : 15.11.2016

 But         : affiche pour une année choisie par l’utilisateur 
               l’utilisateur le calendrier complet.

 Remarque(s) : -

 Compilateur : MinGW-g++ 5.3.0
 -----------------------------------------------------------------------------------
 */

#include <cmath>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <iostream>

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

enum class Mois {
   JANVIER   = 1,
   FEVRIER   = 2,
   MARS      = 3,
   AVRIL     = 4,
   MAI       = 5,
   JUIN      = 6,
   JUILLET   = 7,
   AOUT      = 8,
   SEPTEMBRE = 9,
   OCTOBRE   = 10,
   NOVEMBRE  = 11,
   DECEMBRE  = 12
};

using namespace std;

/**
 * fonction qui retourne si l'année en paramètre est bissextile
 * 
 * @param L'année dont nous voulons savoir la bissextilité
 * @return Si l'année est bissextile ou non
 */
bool estBissextile(const int annee);

/**
 * fonction qui affiche une grille avec une date pour chaque jour de la semaine,
 * en allant de 1 à nbJourMois
 * 
 * @param
 * jourDebut : valeur du jour de la semaine auquel il faut commencer à numéroter 
 *             (ex. mardi --> 2)
 * @param
 * nbJourMois : nombre de jours que comporte le mois (ex.janvier --> 31) 
 * 
 * @return la valeur du dernier jour de la semaine du mois affiché (ex. jeudi 31 --> return(4)
 */
int dateJour(const int jourDebut, const int nbJoursMois);

/**
 * fonction qui renvoie le nombre que contient le mois donné par rapport 
 * à l'année donnée
 * 
 * @param
 * mois : valeur du mois auquel nous voulons le nombre de jour
 * @param
 * annee : année dans laquelle le mois se trouve
 * 
 * @return le nombre de jours que contient le mois
 */
int nbreJour(const int mois, const int annee);

/* 
 * fonction qui retourne le jour de la semaine auquel correspont le premier jour de
 * l'année donnée en paramètre en utilisant l'Algorithme de Mike Keith 
 * 
 * (https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e )
 * 
 * @param
 * annee : année dont laquelle nous voulons savoir le premier jour.
 * 
 * @return la valeur du jour de la semaine (ex. mardi --> 2).
 */
int premierJour(const int annee);

/**
 * Fonction qui renvoit le string du mois en paramètre
 * 
 * @param le mois dont nous voulons le string
 * 
 * @return le string du mois en paramètre (NULL en cas de problème)
 */
string afficherMois(const int mois);

/**
 * Fonction qui demande à l'utilisateur s'il veut recommencer ou non
 *
 * @return
 * true : si l'utilisateur veut recommencer
 * @return
 * false : si l'utilisateur ne veut pas recommencer
 */
bool veutRecommencer();

/*
 * fonction qui met fin au programme en demande à l'utilisateur de presser "ENTER
 */
void fin();

int saisieAnnee(const int ANNEE_MIN, const int ANNEE_MAX);

int main() {

   const int ANNEE_MIN = 1900;
   const int ANNEE_MAX = 2100;

   int annee;
   int jourDebut;

   do {
      annee = saisieAnnee(ANNEE_MIN, ANNEE_MAX);
      
      jourDebut = premierJour(annee);
      
      for (int mois = int(Mois::JANVIER); mois <= int(Mois::DECEMBRE); mois++) {

         cout << endl;

         cout << " " << afficherMois(mois) << " " << annee;

         cout << endl;

         //+1 car dateJour retourne la valeur du jour où elle s'est arrêtée
         jourDebut = dateJour(jourDebut, nbreJour(mois, annee)) + 1;
      }

   } while (veutRecommencer());

   fin();

   return EXIT_SUCCESS;
}

bool estBissextile(const int annee) {

   return ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0);
}//fin, fonction estBissextile

int saisieAnnee(const int ANNEE_MIN, const int ANNEE_MAX){
   
   int annee;
   bool saisieOk;
   
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
   
      return annee;
} //fin, fonction saisieAnnee


int dateJour(const int jourDebut, const int nbJoursMois) {

   const char LUNDI    = 'L';
   const char MARDI    = 'M';
   const char MERCREDI = 'M';
   const char JEUDI    = 'J';
   const char VENDREDI = 'V';
   const char SAMEDI   = 'S';
   const char DIMANCHE = 'D';

   //taille d'une case dans le tableau du calendrier
   const int TAILLE_CASE = 3;

   //stoque la valeur du dernier jour de la semaine avec une date
   int jourFin;


   //affiche les entÃªtes du tableau (jours de la seamine)
   cout << setw(TAILLE_CASE) << LUNDI
        << setw(TAILLE_CASE) << MARDI
        << setw(TAILLE_CASE) << MERCREDI
        << setw(TAILLE_CASE) << JEUDI
        << setw(TAILLE_CASE) << VENDREDI
        << setw(TAILLE_CASE) << SAMEDI
        << setw(TAILLE_CASE) << DIMANCHE
        << endl;

   //ajouter les espaces en fonction de la valeur de jourDebut qui indique à quelle jour
   //de la semaine il faut commence à numéroter
   for(int jCase = 1; jCase < jourDebut; jCase++){
      
      cout << setw(TAILLE_CASE) << "";
   }//fin for

   //parcourt toutes les cases de la grille, passe à la ligne quand jCase % 7
   for(int jCase = jourDebut, jour = 1; jour <= nbJoursMois; jCase++) {

         //afficher le numéro du jour et l'incérmenter
         cout << setw(TAILLE_CASE) << jour++;

         //passe à la ligne quand le nombre de cases arrive à 7 (dimanche)
         if (!(jourFin = jCase % 7)) {
            
            cout << endl;
         }//fin if
   }//fin for

   cout << endl;

   //retourne la valeur du jour de la semaine où le mois s'arrète
   return (jourFin);
   
}//fin, fonction dateJour

int nbreJour(const int mois, const int annee) {

   switch (mois) {

      case int(Mois::MAI):
      case int(Mois::MARS):
      case int(Mois::AOUT):
      case int(Mois::JANVIER):
      case int(Mois::JUILLET):
      case int(Mois::OCTOBRE):
      case int(Mois::DECEMBRE):  return 31;

      case int(Mois::JUIN):
      case int(Mois::AVRIL):
      case int(Mois::NOVEMBRE):
      case int(Mois::SEPTEMBRE): return 30;

      case int(Mois::FEVRIER):   return estBissextile(annee) ? 29: 28;

      default:                   return -1;
   }
} //fin fonction nbreJour

int premierJour(const int annee){
   
   int jour = 1;                    // Premier
   int mois = 1;                    // Janvier
   int nbreMois = 12;
   int c = 1;                       // la formule originale est "(14 - mois)/12", 
                                    // nous n'uiliserons cette fonction que pour avoir 
                                    // le premier jour de janvier, donc c = 1.
   
   int a = annee - c;
   int m = mois + (nbreMois*c) - 2;
   int j = (jour + a + a/4 - a/100 + a/400 + (31*m)/nbreMois) % 7;
   
   return j;
}// fin, fonction premierJour

string afficherMois(const int mois) {

   switch (mois) {
      case int(Mois::JANVIER):   return "Janvier";
      case int(Mois::FEVRIER):   return "Fevrier";
      case int(Mois::MARS):      return "Mars";
      case int(Mois::AVRIL):     return "Avril";
      case int(Mois::MAI):       return "Mai";
      case int(Mois::JUIN):      return "Juin";
      case int(Mois::JUILLET):   return "Juillet";
      case int(Mois::AOUT):      return "Aout";
      case int(Mois::SEPTEMBRE): return "Septembre";
      case int(Mois::OCTOBRE):   return "Octobre";
      case int(Mois::NOVEMBRE):  return "Novembre";
      case int(Mois::DECEMBRE):  return "Decembre";
      default:                   return NULL;
   }//fin switch mois
   
}//fin fonction afficherMois

bool veutRecommencer() {

   char recommencer;

   const char OUI = 'O';
   const char NON = 'N';

   do {
      cout << endl;

      cout << "Voulez-vous recommencer ? [" << OUI << "|" << NON << "] : ";

      cin >> recommencer;

      VIDER_BUFFER;

   } while ((recommencer != OUI) && (recommencer != NON));

   return recommencer == OUI;
}//fin, fonction veutRecommencer

void fin() {

   cout << "presser ENTER pour quitter" << endl;
   cin.get();
}//fin, fonction fin