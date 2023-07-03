//
// Created by Jannis Gehring on 31.01.2023.
//

#ifndef DATENVERWALTUNG_HEADERDATENGEHRING_H
#define DATENVERWALTUNG_HEADERDATENGEHRING_H

//------------------------------------
// INCLUDES
//------------------------------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

//------------------------------------
// DEFINES
//------------------------------------

#define MAXLEN 20
#define LANG 25
#define KURZ 5
#define LENKEY 13 //nicht die tatsächliche Keylänge, sondern die des Arrays

//------------------------------------
// STRUCTS
//------------------------------------

typedef struct m_buch{
    char autor[27];
    char titel[22];
    char inhalt[22];

    struct m_buch *davor;
    struct m_buch *danach;
}t_buch;

typedef struct{
    t_buch *momentan;
    t_buch *start;
    t_buch *letztes;

    struct{
        char autor[27];
        char titel[22];
        char inhalt[22];
    }buch;

}t_feld;

//------------------------------------
// FUNKTIONSMUSTER (Thematisch Gruppiert)
//------------------------------------

//Kategorielos
void up_menu();
void trim(char*string);
void eingabeZahl(int * eingabe);
char * strSearch(char * string, char * substring, bool caseSensitive);
void up_datum(char*datum);
void up_tauschenManuell(t_feld * f);
int oberMenue(t_feld * f);
void unterMenue(int kategorie, t_feld *f);

//Hinzufügen
void up_struct_liste(t_feld *f);
void up_liste_add   (t_feld *f);

//Eingabe
void up_handeingabe(t_feld *f);
void up_dateieinlesen(t_feld *f);

//Ausgabe
void up_dateiSchreiben(t_feld *f);
void up_ausgeben(t_feld *f);
void up_hex(t_feld *f);
void up_suchen(t_feld * f);

//Loeschen
void loeschenEinzeln(t_feld *f);
void loeschenMomentan(t_feld *f);
void loescheBereich(t_feld * f);
void loescheAlle(t_feld * f);
void loescheDoppelte(t_feld * f);

//Sortieren
void up_tauschenVorgang(t_feld * f, bool sorting);
void bubbleSort(t_feld * f);
char * compareWords(char * string1, char * string2, bool returnBigger, bool caseSensitive);

//Zufällige Datensätze
void randomInput(t_feld * f);
void randomString(char * stringDest);
void randomString2(char * stringDest);

//Amazon
void amazonManuell(t_feld * f);

//Verschluesselung
void schluesseln(char * message, char * key, bool verschluesseln);
void allesVerschluesseln(t_feld * f);
void allesEntschluesseln(t_feld * f);

#endif //DATENVERWALTUNG_HEADERDATENGEHRING_H