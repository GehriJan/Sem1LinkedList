//
// Created by Jannis Gehring on 16.01.2023.
// Doppelt verkettete Liste

//------------------------------------
// INCLUDES
//------------------------------------

#include "HeaderDatenGehring.h"
#include "GehriJanHintergrundFunktionen.cpp"
#include "GehriJanSortierenRandomEncrypt.cpp"
#include "GehriJanEingabeLoeschenFunktionen.cpp"
#include "GehriJanAusgabeSuchen.cpp"

//------------------------------------
// MAIN
//------------------------------------

int main(void) {
    t_feld feld;
    t_feld *f = &feld;

    f->momentan = 0;
    f->start = 0;
    f->letztes = 0;

    srand(time(NULL));

    int eingabe;

    while(1){
        eingabe = oberMenue(f);
        if(eingabe==0) return(42);
        unterMenue(eingabe, f);
    }
}

int oberMenue(t_feld * f){

    char eingabe;
    char balken[LANG], balkenDuenn[LANG], balkenKurz[KURZ], balkenDuennKurz[KURZ];

    int i, j;

    for (i = 0; i < LANG; ++i) {
        balken[i] = 205;
        balkenDuenn[i] = 196;
    }
    for (j = 0; j < KURZ; ++j) {
        balkenKurz[j] = 205;
        balkenDuennKurz[j] = 196;
    }

    balken[LANG-1] = '\0';
    balkenDuenn[LANG-1] = '\0';
    balkenKurz[KURZ-1] = '\0';
    balkenDuennKurz[KURZ-1] = '\0';

    system("cls");
    //MENÜKOPF
    printf("\n\xC9%s%s\xCD%s%s\xCD%s%s\xBB", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
    printf("\n\xBA""                                HERZLICH WILLKOMMEN ZUR                               \xBA");
    printf("\n\xBA""          BUECHERDATENBANKVERWALTUNGSVERKETTUNGSLISTENPROGRAMMIMPLEMENTIERUNG         \xBA");
    printf("\n\xBA""                                  von Jannis Gehring                                  \xBA");
    printf("\n\xBA""                         .-~~~~~~~~~-._       _.-~~~~~~~~~-.                          \xBA");
    printf("\n\xBA""                     __.'              ~.   .~              `.__                      \xBA");
    printf("\n\xBA""                   .'//                  \\./                  \\\\`.                    \xBA");
    printf("\n\xBA""                 .'//                     |                     \\\\`.                  \xBA");
    printf("\n\xBA""               .'// .-~\"\"\"\"\"\"\"~~~~-._     |     _,-~~~~\"\"\"\"\"\"\"~-. \\\\`.                \xBA");
    printf("\n\xBA""             .'//.-\"                 `-.  |  .-'                 \"-.\\\\`.              \xBA");
    printf("\n\xBA""           .'//______.============-..   \\ | /   ..-============.______\\\\`.            \xBA");
    printf("\n\xBA""         .'______________________________\\|/______________________________`.          \xBA");
    printf("\n\xCC%s%s\xCD%s%s\xCD%s%s\xB9", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
    printf("\n\xBA""                                    >>BEDIENUNG<<                                     \xBA");
    printf("\n\xBA""      (Zahlen) Funktionen ausw\x84hlen              (Esc) Zur\x81""ck                         \xBA");
    printf("\n\xBA""      (i) Info                                   (e) Exit (Wenn in Hauptprogramm)     \xBA");
    printf("\n\xCC%s%s\xCD%s%s\xCD%s%s\xB9", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
    //FUNKTIONEN
    printf("\n\xBA""                               >>FUNKTIONSKATEGORIEN<<                                \xBA");
    printf("\n\xBA""%s%s\xC4%s%s\xC4%s%s\xBA", balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz);
    printf("\n\xBA""                                                                                      \xBA");
    printf("\n\xBA""                        (1) Eingabe             (2) Ausgabe                           \xBA");
    printf("\n\xBA""                                                                                      \xBA");
    printf("\n\xBA""                        (3) L\x94schen             (4) Sortieren                         \xBA");
    printf("\n\xBA""                                                                                      \xBA");
    printf("\n\xBA""                        (5) Suchen              (6) Suche auf Amazon                  \xBA");
    printf("\n\xBA""                                                                                      \xBA");
    printf("\n\xBA""                        (7) Verschl\x81sselung     (8) Manuell Tauschen                  \xBA");
    printf("\n\xBA""                                                                                      \xBA");
    printf("\n\xC8%s%s\xCD%s%s\xCD%s%s\xBC", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);

    do {
        eingabe=getch();
    }while(!(eingabe=='1' || eingabe=='2'|| eingabe=='3' || eingabe=='4' || eingabe=='5' || eingabe=='6'|| eingabe=='7' || eingabe=='8' || eingabe=='e' || eingabe=='i'));

    switch(eingabe){
        case('1'): return(1);
        case('2'): return(2);
        case('3'): return(3);
        case('4'): bubbleSort(f);   return (4);
        case('5'): up_suchen(f);    return(5);
        case('6'): amazonManuell(f); return(6);
        case('7'): return(7);
        case('8'): up_tauschenManuell(f); return(8);
        case('e'): return(0);
        case('i'): system("START InformationenJannisGehring.txt"); return(9);
    }
    return(4);
}

void unterMenue(int kategorie, t_feld *f) {

    char balken[LANG], balkenDuenn[LANG], balkenKurz[KURZ], balkenDuennKurz[KURZ];
    char eingabe;

    int i, j;

    for (i = 0; i < LANG; ++i) {
        balken[i] = 205;
        balkenDuenn[i] = 196;
    }
    for (j = 0; j < KURZ; ++j) {
        balkenKurz[j] = 205;
        balkenDuennKurz[j] = 196;
    }

    balken[LANG - 1] = '\0';
    balkenDuenn[LANG - 1] = '\0';
    balkenKurz[KURZ - 1] = '\0';
    balkenDuennKurz[KURZ - 1] = '\0';

    if (kategorie == 1) {
        system("cls");
        printf("\n\xC9%s%s\xCD%s%s\xCD%s%s\xBB", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
        printf("\n\xBA""                                >>EINGABE VON DATEN<<                                 \xBA");
        printf("\n\xCC%s%s\xC4%s%s\xC4%s%s\xB9", balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz);
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                      (1) Eingabe per Hand        (2) Eingabe aus Datei               \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                      (3) Random Eingabe          (Esc) Zur\x81""ck                        \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xC8%s%s\xCD%s%s\xCD%s%s\xBC", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);

        do {
            eingabe = getch();
        } while (!(eingabe == '1' || eingabe == '2' || eingabe == '3' || eingabe == '\x1B'));

        switch (eingabe) {
            case ('1'):
                up_handeingabe(f);
                break;
            case ('2'):
                up_dateieinlesen(f);
                break;
            case ('3'):
                randomInput(f);
                break;
            case ('\x1B'):
                return;
        }
    } else if(kategorie==2){
        system("cls");
        printf("\n\xC9%s%s\xCD%s%s\xCD%s%s\xBB", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
        printf("\n\xBA""                                >>AUSGABE VON DATEN<<                                 \xBA");
        printf("\n\xCC%s%s\xC4%s%s\xC4%s%s\xB9", balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz);
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                     (1) Ausgabe in Konsole       (2) Ausgabe in Datei                \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                     (3) Adressen einsehen        (Esc) Zur\x81""ck                        \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xC8%s%s\xCD%s%s\xCD%s%s\xBC", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);

        do {
            eingabe = getch();
        } while (!(eingabe == '1' || eingabe == '2' || eingabe == '3' || eingabe == '\x1B'));

        switch (eingabe) {
            case ('1'):
                up_ausgeben(f);
                break;
            case ('2'):
                up_dateiSchreiben(f);
                break;
            case ('3'):
                up_hex(f);
                break;
            case ('\x1B'):
                return;
        }
    } else if(kategorie==3){
        system("cls");
        printf("\n\xC9%s%s\xCD%s%s\xCD%s%s\xBB", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
        printf("\n\xBA""                                >>L\x99SCHEN VON DATEN<<                                 \xBA");
        printf("\n\xCC%s%s\xC4%s%s\xC4%s%s\xB9", balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz);
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                     (1) Einzelnes L\x94schen           (2) Mehrere L\x94schen              \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                     (3) Doppelte L\x94schen            (4) Alle L\x94schen                 \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                                                     (Esc) Zur\x81""ck                     \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xC8%s%s\xCD%s%s\xCD%s%s\xBC", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);

        do {
            eingabe = getch();
        } while (!(eingabe == '1' || eingabe == '2' || eingabe == '3' || eingabe == '4' ||eingabe == '\x1B'));

        switch (eingabe) {
            case ('1'):
                loeschenEinzeln(f);
                break;
            case ('2'):
                loescheBereich(f);
                break;
            case ('3'):
                loescheDoppelte(f);
                break;
            case ('4'):
                loescheAlle(f);
                break;
            case ('\x1B'):
                return;
        }
    } else if(kategorie==7){
        system("cls");
        printf("\n\xC9%s%s\xCD%s%s\xCD%s%s\xBB", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);
        printf("\n\xBA""                                >>VERSCHL\x81SSELUNG<<                                   \xBA");
        printf("\n\xCC%s%s\xC4%s%s\xC4%s%s\xB9", balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuenn, balkenDuennKurz);
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                     (1) Verschl\x81sseln           (2) Entschl\x81sseln                    \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xBA""                                                     (Esc) Zur\x81""ck                     \xBA");
        printf("\n\xBA""                                                                                      \xBA");
        printf("\n\xC8%s%s\xCD%s%s\xCD%s%s\xBC", balken, balkenKurz, balken, balkenKurz, balken, balkenKurz);

        do {
            eingabe = getch();
        } while (!(eingabe == '1' || eingabe == '2' ||eingabe == '\x1B'));

        switch (eingabe) {
            case ('1'):
                allesVerschluesseln(f);
                break;
            case ('2'):
                allesEntschluesseln(f);
                break;
            case ('\x1B'):
                return;
        }
    }
}