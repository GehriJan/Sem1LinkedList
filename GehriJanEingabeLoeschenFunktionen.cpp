//
// Created by Jannis Gehring on 12.02.2023.
//

#include "HeaderDatenGehring.h"

//------------------------------------
// FUNKTIONEN EINGABE
//------------------------------------

void up_handeingabe(t_feld *f){

    int j=0, k=0, l;
    bool eingabeRichtig;
    char repeat;
    do {
        printf("\nWichtig! Bitte bedenke, dass die Eingaben per Definition nicht l\x84nger als %d Zeichen sein k\x94nnen. Leere Eingaben werden ignoriert.\n", MAXLEN);

        do {
            printf("\nGib den Titel ein: ");
            fgets(f->buch.titel, 27, stdin);
            eingabeRichtig = eingabeText(f->buch.titel);
            fflush(stdin);
            if (strlen(f->buch.titel) > MAXLEN+1 || !eingabeRichtig) {
                printf("\nDie Eingabe ist entspricht nicht den Vorgaben."
                       "Bitte maximal %d Zeichen L\x84nge und nur Buchstaben des Standardalphabets.", MAXLEN);
            }
        } while (strlen(f->buch.titel) > MAXLEN+1 || !eingabeRichtig);   //Die Do-While Schleife erzielt jeweils, dass die Eingabe nicht zu lang ist
        trim(f->buch.titel);
        for (j = 0; j <= strlen(f->buch.titel); ++j) {
            if(*(f->buch.titel+j)=='\n') *(f->buch.titel+j)='\0';
        }

        do {
            printf("\nGib den Autor ein: ");
            fgets(f->buch.autor, 27, stdin);
            eingabeRichtig = eingabeText(f->buch.autor);
            fflush(stdin);
            if (strlen(f->buch.autor) > MAXLEN+1 || !eingabeRichtig) {
                printf("\nDie Eingabe entspricht nicht den Vorgaben."
                       "Bitte maximal %d Zeichen L\x84nge und nur Buchstaben des Standardalphabets.", MAXLEN);
            }
        } while (strlen(f->buch.autor) > MAXLEN+1 || !eingabeRichtig);
        trim(f->buch.autor);
        for (k = 0; k <= strlen(f->buch.autor); ++k) {
            if(*(f->buch.autor+k)=='\n') *(f->buch.autor+k)='\0';
        }

        do {
            printf("\nGib den Inhalt (beziehungsweise das Stichwort) ein: ");
            fgets(f->buch.inhalt, 27, stdin);
            eingabeRichtig = eingabeText(f->buch.inhalt);
            fflush(stdin);
            if (strlen(f->buch.inhalt) > MAXLEN+1 || !eingabeRichtig) {
                printf("\nDie Eingabe entspricht nicht den Vorgaben."
                       "Bitte maximal %d Zeichen L\x84nge und nur Buchstaben des Standardalphabets.", MAXLEN);
            }
        } while (strlen(f->buch.inhalt) > MAXLEN+1 || !eingabeRichtig);
        trim(f->buch.inhalt);
        for (l = 0; l <= strlen(f->buch.inhalt); ++l) {
            if(*(f->buch.inhalt+l)=='\n') *(f->buch.inhalt+l)='\0';
        }

        if(strlen(f->buch.titel) || strlen(f->buch.autor) || strlen(f->buch.inhalt)) {
            up_liste_add(f);
            printf("\nSoll ein weiterer Datensatz per Hand eingegeben werden? (j=Ja), (alles !=j bedeutet Nein)\n");
        } else {
            printf("\nSo kann man das System leider nicht austricksen. Es wurde kein Datensatz hinzugef\x81gt.");
            printf("\nSoll jetzt ein Datensatz per Hand eingegeben werden? (j=Ja), (alles !=j bedeutet Nein)\n");
        }
    }while(getch()=='j');
}
void up_dateieinlesen(t_feld *f){

    char text[111],htext[40], dateiName[200], eingabe;
    int i=0, j=0, k=0;
    FILE *einlesen;
    do {
        printf("\nVon welcher Datei soll eingelesen werden? (Escape f\x81hrt zum Men\x81)"
               "\n\t1. DatenSatzJannisGehring.txt"
               "\n\t2. AusgabeJannisGehring.txt"
               "\n\t3. Andere Datei\n");
        eingabe=getch();
        if(eingabe=='\x1B') return;
        if(!(eingabe=='1' || eingabe=='2'|| eingabe=='3'))printf("Deine Auswahl stimmte nicht. Bitte versuche erneut.");
    }while(!(eingabe=='1' || eingabe=='2'|| eingabe=='3'));

    dateiName[0] = '\0';
    if(eingabe=='1'){
        strcat(dateiName, "DatenSatzJannisGehring.txt");
    } else if(eingabe=='2') {
        strcat(dateiName, "AusgabeJannisGehring.txt");
    } else{
        printf("Bitte gib den Dateinamen (wenn sie sich im gleichen Ordner befindet)"
               "oder den absoluten Pfad ein.\n");
        fgets(dateiName, 199, stdin);
    }
    for (k = 0; k < 200; ++k) { //Hier wird der String zum Dateipfad bearbeitet
        if(dateiName[k]=='\n') dateiName[k]='\0';
    }
    einlesen = fopen(dateiName, "r");

    if(!einlesen){
        printf("\nDatei kann leider nicht geöffnet werden. Eventuell ist der Dateipfad zu lang, kurz oder falsch.\n");
        getch();
    } else {
        fgets(text,100, einlesen);
        while(!feof(einlesen)){
            //Notizen überspringen
            while(text[0]=='*'){ //hier werden die Notizen übersprungen
                fgets(text, 100, einlesen);
            }
            //hiermit wird der Tabellenkopf (das erste Mal) übersprungen
            if(!i) {
                fgets(text, 100, einlesen);
                fgets(text, 100, einlesen);
                fgets(text, 100, einlesen);
                i++;
            }
            //Schutz vor zu langen Zeilen
            for (j = 0; i==1 && j < 100; ++j) {
                if (text[j] == '\n') {
                    j = 100;
                    break;
                }
                if (j == 99) {
                    printf("\nEine Zeile der Datei ist zu lang.\nBitte \x81""berpr\x81""fe die Datei "
                           "und bedenke, dass die Maximall\x84nge der Elemente %d betr\x84gt.", MAXLEN);
                    getch();
                    return;
                }
            }
            //Zeile auslesen
            strncpy(htext, text+2, 20);
            trim(htext);
            strcpy(f->buch.titel, htext);

            strncpy(htext, text + 29, 20);
            trim(htext);
            strcpy(f->buch.autor, htext);

            strncpy(htext, text + 56, 20);
            trim(htext);
            strcpy(f->buch.inhalt, htext);

            fgets(text, 100, einlesen);
            up_liste_add(f);
        }
    }
    fclose(einlesen);
}

//------------------------------------
// FUNKTIONEN LOESCHEN
//------------------------------------

void loeschenEinzeln(t_feld *f){

    int zuLoeschen, i, anzElement;

    for (anzElement = 1, f->momentan=f->start;f->momentan = f->momentan->danach; ++anzElement);
    //Eingabe
    do {
        printf("\n\nWelcher Datensatz (Nummer) soll geloescht werden?\n");
        eingabeZahl(&zuLoeschen);
        if(zuLoeschen<1 || zuLoeschen>anzElement) printf("\nDie Eingabe entspricht nicht den Vorgaben."
                                                         "\nBitte gib eine nat\x81rliche Zahl gr\x94sser null und maximal die Anzahl der Elemente ein");
    }while(zuLoeschen<1 || zuLoeschen>anzElement);

    //Bis zum richtigen Datensatz navigieren
    f->momentan = f->start;
    for (i = 1; i < zuLoeschen; ++i) {
        f->momentan = f->momentan->danach;
    }
    loeschenMomentan(f);
}
void loescheAlle(t_feld * f){
    f->momentan = f->start;
    while (f->momentan) {
        loeschenMomentan(f);
    }
}
void loeschenMomentan(t_feld *f) {
    //Diese Funktion ist im Hintergrund und loescht f->momentan
    if (f->momentan) {
        if (f->momentan->davor && f->momentan->danach) {
            //Mitte
            f->momentan->davor->danach = f->momentan->danach;
            f->momentan->danach->davor = f->momentan->davor;
            f->momentan = f->momentan->danach;
        } else if (f->momentan->danach) {
            //Erstes
            f->momentan->danach->davor = 0;
            f->start = f->momentan->danach;
            free(f->momentan);
            f->momentan = f->start;
        } else if (f->momentan->davor) {
            //Letztes
            f->momentan->davor->danach = 0;
            f->letztes = f->momentan->davor;
            free(f->momentan);
        } else {
            //Einziges
            f->momentan = 0;
            f->start = 0;
            f->letztes = 0;
        }
    }
}
void loescheBereich(t_feld * f){

    int unterGrenze, oberGrenze, anzElement, i, j;

    //folgende for-Schleife kommt häufig im Sourcecode vor
    //Durch sie wird die Anzahl der Elemente bestimmt
    for (anzElement = 1, f->momentan=f->start;f->momentan = f->momentan->danach; ++anzElement);


    //Eingabe
    do {
        printf("\n\nAb welchem Datensatz (Nummer) soll geloescht werden?\n");
        eingabeZahl(&unterGrenze);
        if(unterGrenze>anzElement || unterGrenze < 1)printf("\nDie Eingabe ist nicht richtig. Die Zahl(!) darf maximal die Anzahl der Elemente betragen und muss trivialerweise mindestens eins sein.");
    }while(unterGrenze>anzElement || unterGrenze < 1);

    do {
        printf("\n\nBis zu welchem Datensatz (Nummer) soll geloescht werden?\n");
        eingabeZahl(&oberGrenze);
        if(oberGrenze<unterGrenze || oberGrenze > anzElement)printf("\nDie Eingabe ist nicht richtig. Die Zahl(!) muss mindestens vorige Zahl und darf maximal die Anzahl der Elemente betragen.");
    }while(oberGrenze<unterGrenze || oberGrenze > anzElement);

    //Zur Untergrenze navigieren
    f->momentan = f->start;
    for (i = 1; i < unterGrenze; ++i) {
        f->momentan = f->momentan->danach;
    }
    //Bis zur Obergrenze alle loeschen
    for(j = unterGrenze; j <= oberGrenze; ++j){
        loeschenMomentan(f);
    }
}
void loescheDoppelte(t_feld * f){

    m_buch * tempPtr = NULL;
    char eingabe;
    bool caseSensitive;

    //Eingabe
    do {
        printf("\nSoll beim l\x94schen zwischen Gross- und Kleinschreibung unterschieden werden?"
               "\n\t1. Ja"
               "\n\t0. Nein\n");
        eingabe=getch();
        if(eingabe=='\x1B') return;
        if(!(eingabe=='1' || eingabe=='0'))printf("Deine Auswahl stimmte nicht. Bitte versuche erneut.");
    }while(!(eingabe=='1' || eingabe=='0'));
    if(eingabe=='1') caseSensitive=1;
    else caseSensitive=0;

    for(f->momentan = f->start; f->momentan;f->momentan = f->momentan->danach){
        /* Diese for-Schleife geht die Liste durch und prüft für alle Elemente inkrementell,
         * ob eins der vorigen Elemente gleich das Element ist.
         * In diesem Fall wird dieses vorige Vorkommen geloescht.
         *
         * Mit den tempPtr "merkt" sich das Programm, mit welchem Datensatz momentan verglichen wird.
         * Mit ihm kann der Aufwand von Extra-Arrays oder dergleichen umgangen werden.
         */
        tempPtr = f->momentan;
        f->momentan = f->start;
        while((f->momentan)!=tempPtr){
            //Mit compareWord wird die Gleichheit von Titel, Autor und Inhalt untersucht
            if(!compareWords(f->momentan->titel, tempPtr->titel, 0, caseSensitive)
               && !compareWords(f->momentan->autor, tempPtr->autor, 0, caseSensitive)
               && !compareWords(f->momentan->inhalt, tempPtr->inhalt, 0, caseSensitive)){
                loeschenMomentan(f);
            } else {
                f->momentan = f->momentan->danach;
            }
        }
        f->momentan = tempPtr;
    }
}