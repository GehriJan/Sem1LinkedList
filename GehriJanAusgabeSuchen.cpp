//
// Created by Jannis Gehring on 12.02.2023.
//

#include "HeaderDatenGehring.h"

//------------------------------------
// FUNKTIONEN AUSGABE
//------------------------------------

void up_hex(t_feld *f){

    int i, j, datensatz=1, abschnitt=1;
    char balken[MAXLEN+7], balkenDuenn[MAXLEN+7], balkenKurz[6], balkenDuennKurz[6];
    for (i = 0; i < 27; ++i) {
        balken[i] = 205;
        balkenDuenn[i] = 196;
    }
    for (j = 0; j < 6; ++j) {
        balkenKurz[j] = 205;
        balkenDuennKurz[j] = 196;
    }
    balken[MAXLEN+6] = '\0';
    balkenDuenn[MAXLEN+6] = '\0';
    balkenKurz[5] = '\0';
    balkenDuennKurz[5] = '\0';

    f->momentan = f->start;
    printf("\n\xC9%s\xCB%s\xCB%s%s\xCD\xCB%s%s\xCD\xCB%s%s\xCD\xBB", balkenKurz, balken, balkenKurz, balkenKurz, balkenKurz, balkenKurz, balkenKurz, balkenKurz);
    printf("\n\xBA Nr. \xBA Titel                    \xBA Davor     \xBA Momentan  \xBA Danach    \xBA");
    printf("\n\xBA%s\xBA%s\xBA%s%s\xC4\xBA%s%s\xC4\xBA%s%s\xC4\xBA", balkenDuennKurz, balkenDuenn, balkenDuennKurz, balkenDuennKurz, balkenDuennKurz, balkenDuennKurz,balkenDuennKurz, balkenDuennKurz);
    do {

        while (f->momentan && datensatz<=25) {
            printf("\n\xBA%5d\xBA %-25s\xBA %-10x\xBA %-10x\xBA %-10x\xBA", ((abschnitt-1)*25)+datensatz, f->momentan->titel,
                   f->momentan->davor,
                   f->momentan, f->momentan->danach);
            f->momentan = f->momentan->danach;
            datensatz++;
        }
        if(f->momentan) {
            printf("\n...weitere Datens\x84tze anzeigen mit Leertaste, ansonsten Ausgabe verlassen...");
            datensatz=1;
            abschnitt++;
        } else {
            printf("\n\xC8%s\xCA%s\xCA%s%s\xCD\xCA%s%s\xCD\xCA%s%s\xCD\xBC", balkenKurz, balken, balkenKurz, balkenKurz, balkenKurz, balkenKurz, balkenKurz, balkenKurz);
            printf("\n... Datenende. Dr\x81""cke Taste, um zum Men\x81 zur\x81""ckzukehren...");
            getch();
            return;
        }
    }while(getch()=='\x20');





}
void up_ausgeben(t_feld *f) {

    int i, j, datensatz=1, abschnitt=1;
    //folgende Zeilen dienen nur zum Darstellen der Datensätze und kommen (evtl leicht abgeändert) öfters im Quellcode vor.
    //Es wäre zu überlegen, ob diese Arrays global definiert werden sollten, jedoch klärt sich diese Frage im Blick
    //auf die Projektvorgaben von alleine
    char balken[MAXLEN+7], balkenDuenn[MAXLEN+7], balkenKurz[6], balkenDuennKurz[6];
    for (i = 0; i < 27; ++i) {
        balken[i] = 205;
        balkenDuenn[i] = 196;
    }
    for (j = 0; j < 6; ++j) {
        balkenKurz[j] = 205;
        balkenDuennKurz[j] = 196;
    }
    balken[MAXLEN+6] = '\0';
    balkenDuenn[MAXLEN+6] = '\0';
    balkenKurz[5] = '\0';
    balkenDuennKurz[5] = '\0';

    f->momentan = f->start;
    //Ausgabenkopf
    printf("\n\xC9%s\xCB%s\xCB%s\xCB%s\xBB", balkenKurz, balken, balken, balken, balken);
    printf("\n\xBA Nr. \xBA Titel                    \xBA Autor                    \xBA Inhalt                   \xBA");
    printf("\n\xBA%s\xBA%s\xBA%s\xBA%s\xBA", balkenDuennKurz, balkenDuenn, balkenDuenn, balkenDuenn);
    //Datensätze
    do {

        while (f->momentan && datensatz<=25) {
            printf("\n\xBA%5d\xBA %-25s\xBA %-25s\xBA %-25s\xBA", ((abschnitt-1)*25)+datensatz, f->momentan->titel,
                   f->momentan->autor,
                   f->momentan->inhalt);
            f->momentan = f->momentan->danach;
            datensatz++;
        }
        //Unterbrechung
        if(f->momentan) {
            printf("\n...weitere Datens\x84tze anzeigen mit Leertaste, ansonsten Ausgabe verlassen...");
            datensatz=1;
            abschnitt++;
        } else {
            //Ende
            printf("\n\xC8%s\xCA%s\xCA%s\xCA%s\xBC", balkenKurz, balken, balken, balken);
            printf("\n... Datenende. Dr\x81""cke Taste, um zum Men\x81 zur\x81""ckzukehren...");
            getch();
            return;
        }
    }while(getch()=='\x20');
}
void up_dateiSchreiben(t_feld *f){

    FILE * schreiben;
    int i;
    char balken[MAXLEN+7], datum[30];

    schreiben = fopen("AusgabeJannisGehring.txt", "w");
    up_datum(datum);
    fprintf(schreiben, "***Datenverwaltung, exportiert am %s***", datum);

    for (i = 0; i < 27; ++i) {
        balken[i] = 95;         //Das Array balken[] dient der übersichtlicheren Darstellung der fprintf's
    }
    balken[MAXLEN+6] = '\0';

    f->momentan = f->start;
    //Tabellenkopf
    fprintf(schreiben, "\n %s_%s_%s ", balken, balken, balken);
    fprintf(schreiben, "\n| Titel                    | Autor                    | Inhalt                   |");
    fprintf(schreiben, "\n|%s|%s|%s|", balken, balken, balken);
    while (f->momentan) {
        //Datensätze
        fprintf(schreiben, "\n| %-25s| %-25s| %-25s|", f->momentan->titel,
                f->momentan->autor,
                f->momentan->inhalt);
        f->momentan = f->momentan->danach;
    }
    fprintf(schreiben, "\n|%s|%s|%s|", balken, balken, balken);
    printf("\nDaten wurden in die Datei geschrieben. Bitte bet\x84tige eine Taste, um zum Men\x81 zur\x81""ckzukehren.");getch();
    fclose(schreiben);
    return;
}

//------------------------------------
// FUNKTIONEN SUCHE
//------------------------------------

void up_suchen(t_feld * f){
    //Bei der Suche von Datensätzen wurde keine Abschnittsausgabe mit je 25 Datensätzen implementiert,
    //hierdurch können alle Datensätze ohne Unterbrechung durch die Suche nach " " angezeigt werden
    bool caseSensitive;
    int index=1, i, j;
    char suche[MAXLEN+1], balken[MAXLEN+7], balkenDuenn[MAXLEN+7], balkenKurz[6], balkenDuennKurz[6];
    char eingabe;
    for (i = 0; i < 27; ++i) {
        balken[i] = 205;
        balkenDuenn[i] = 196;
    }
    for (j = 0; j < 6; ++j) {
        balkenKurz[j] = 205;
        balkenDuennKurz[j] = 196;
    }
    balken[MAXLEN+6] = '\0';
    balkenDuenn[MAXLEN+6] = '\0';
    balkenKurz[5] = '\0';
    balkenDuennKurz[5] = '\0';

    //Eingabe
    printf("\nGib den String ein, nach dem du Suchen willst. Deine Suche kann maximal %d Zeichen lang sein, alle Zeichen danach werden nicht beachtet.\n", MAXLEN);
    fflush(stdin);
    fgets(suche, MAXLEN+1, stdin);
    for (j = 0; j < MAXLEN+1; ++j) {    //Da fgets \n auch einließt, muss dieser durch die terminierende Null ersetzt werden
        if(suche[j]=='\n') suche[j]='\0';
    }
    do {
        printf("\nSoll die suche Klein- und Grossschreibung beachten? (0: Nein, ungleich null: Ja)"
               "\n\t1. Ja"
               "\n\t2. Nein");
        eingabe=getch();
        if(eingabe=='\x1B') return;
        if(!(eingabe=='1' || eingabe=='2'))printf("Deine Auswahl stimmte nicht. Bitte versuche erneut.");
    }while(!(eingabe=='1' || eingabe=='2'));
    if(eingabe=='1') caseSensitive=1;
    else caseSensitive=0;

    f->momentan = f->start;
    //Tabellenkopf
    printf("\n\xC9%s\xCB%s\xCB%s\xCB%s\xBB", balkenKurz, balken, balken, balken, balken);
    printf("\n\xBA Nr. \xBA Titel                    \xBA Autor                    \xBA Inhalt                   \xBA");
    printf("\n\xBA%s\xBA%s\xBA%s\xBA%s\xBA", balkenDuennKurz, balkenDuenn, balkenDuenn, balkenDuenn);
    while(f->momentan){

        if(strSearch(f->momentan->titel, suche, caseSensitive)
           || strSearch(f->momentan->autor, suche, caseSensitive)
           || strSearch(f->momentan->inhalt, suche, caseSensitive)){
            printf("\n\xBA%5d\xBA %-25s\xBA %-25s\xBA %-25s\xBA", index, f->momentan->titel,
                   f->momentan->autor,
                   f->momentan->inhalt);
        }
        f->momentan = f->momentan->danach;
        index++;
    }
    printf("\n\xC8%s\xCA%s\xCA%s\xCA%s\xBC", balkenKurz, balken, balken, balken);
    printf("\n...bitte beliebige Taste dr\x81""cken ...");
    getch();
}
void amazonManuell(t_feld * f){

    int anzElement, suche;
    char titel[MAXLEN+1], autor[28], systemCommand[95]="START ", link[85]="https://www.amazon.de/s?k=";

    //Error-meldung
    if(!(f->start)){
        printf("\n!Fehler! Da kein Element existiert kann auch nach keinem auf Amazon gesucht werden."
               "\nBitte bet\x84tige eine Taste um zum Men\x81 zur\x81""ckzukehren");
        getch();
        return;
    }
    //Bestimmung der Elementanzahl
    for(anzElement = 1, f->momentan=f->start;f->momentan = f->momentan->danach; ++anzElement);

    //Eingabe
    do {
        printf("\n\nNach welchem Datensatz soll geschaut werden?\n");
        scanf("%d", &suche);
        if(suche>anzElement || suche < 1)printf("\nDie Zahl ist nicht richtig. Sie darf maximal die Anzahl der Elemente betragen und muss trivialerweise mindestens eins sein.");
    }while(suche>anzElement || suche < 1);

    //Navigation zum Element
    f->momentan = f->start;
    for(int j = 1; j < suche; ++j, f->momentan = f->momentan->danach);

    strcpy(titel, f->momentan->titel); //Leerzeichen mit Plus ersetzten, damit es in Link eingefügt werden kann
    for (int i = 0; i <= strlen(titel); ++i) {
        if(titel[i]==32) titel[i]='+';
    }

    strcpy(autor, f->momentan->autor); //da hier nur der Nachname verwendet wird, wird =\0 getsetzt
    for (int j = 0; j <= strlen(autor); ++j) {
        if(autor[j]==32) autor[j]='\0';
    }

    strcat(link, titel);                //zusammenklammüstern der Strings zu vollem Befehl
    strcat(link, "+");
    strcat(link, autor);

    strcat(systemCommand, link);

    system(systemCommand);
    return;
}
