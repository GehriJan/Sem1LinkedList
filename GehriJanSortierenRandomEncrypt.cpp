//
// Created by Jannis Gehring on 31.01.2023.
//

#include "HeaderDatenGehring.h"

//------------------------------------
// FUNKTIONEN SORTIEREN
//------------------------------------

void up_tauschenManuell(t_feld * f){
    //Dieses Programm "bekleidet" den technischen Vorgang des Tauschens noch so mit Code, dass auch manuell getauscht werden kann.
    int zuTauschen, i, anzElement;

    if(f->start==0){
        printf("\nFehler. Da kein Datensatz existiert, kann auch nichts getauscht werden.");
        getch();
        return;
    }
    //Anzahl der Elemente
    for (anzElement = 1, f->momentan=f->start;f->momentan = f->momentan->danach; ++anzElement);
    //Eingabe
    do {
        printf("\n\nWelcher Datensatz soll mit seinem Nachfolger getauscht werden?\n");
        eingabeZahl(&zuTauschen);
        if(zuTauschen<1 || zuTauschen > anzElement)printf("\nDie Eingabe ist nicht richtig. Die Zahl(!) muss gr\x81sser null sein und darf maximal die Nummer des vorletzten Elements betragen.");
    }while(zuTauschen<1 || zuTauschen > anzElement);

    f->momentan = f->start;
    for (i = 1; i < zuTauschen; ++i) {
        f->momentan = f->momentan->danach;
    }
    up_tauschenVorgang(f, 0);
}
void up_tauschenVorgang(t_feld * f, bool sorting){
    //Dies ist der reinmechanische Tauschvorgang
    if(f->momentan->davor == 0) {

        f->momentan->danach->danach->davor = f->momentan;
        f->momentan->danach->davor = NULL;
        f->momentan->davor = f->momentan->danach;
        f->momentan->danach = f->momentan->davor->danach;
        f->momentan->davor->danach = f->momentan;
        f->momentan = f->momentan->davor;

        while(f->start->davor) {
            f->start = f->start->davor;
        }

    } else if(f->momentan==f->letztes || f->momentan->danach==f->letztes){
        f->momentan = f->letztes->davor;

        f->momentan->davor->danach = f->momentan->danach;
        f->momentan->danach->danach = f->momentan;
        f->momentan->danach->davor = f->momentan->davor;
        f->momentan->davor = f->momentan->danach;
        f->momentan->danach = NULL;

        f->letztes = f->momentan;

    } else if(f->momentan->danach == f->momentan->davor){
        if(!sorting) printf("\nFehler - Da nur ein Element existiert, kann nichts getauscht werden.");
    } else {
        f->momentan->davor->danach = f->momentan->danach;
        f->momentan->danach->danach->davor = f->momentan;
        f->momentan->danach->davor = f->momentan->davor;
        f->momentan->davor = f->momentan->danach;
        f->momentan->danach = f->momentan->davor->danach;
        f->momentan->davor->danach = f->momentan;
    }
}
void bubbleSort(t_feld * f){

    int anzElement, durchlauf, k, eingabe;
    char * linkesElement, rechtesElement;
    bool aufsteigend = 0, titelIstKriterium=0;
    
    //Eingabe
    do {
        printf("\nNach welchem Kriterium soll sortiert werden?"
               "\n\t1. Titel"
               "\n\t2. Name\n");
        eingabe=getch();
        if(eingabe=='\x1B') return;
        if(!(eingabe=='1' || eingabe=='2'))printf("Deine Auswahl stimmte nicht. Bitte versuche erneut.");
    }while(!(eingabe=='1' || eingabe=='2'));
    if(eingabe=='1') titelIstKriterium=1;

    do {
        printf("\nSoll ab- oder aufsteigend sortiert werden?"
               "\n\t1. Aufsteigend (A...Z)"
               "\n\t2. Absteigend (Z...A)\n");
        eingabe=getch();
        if(eingabe=='\x1B') return;
        if(!(eingabe=='1' || eingabe=='2'))printf("Deine Auswahl stimmte nicht. Bitte versuche erneut.");
    }while(!(eingabe=='1' || eingabe=='2'));
    if(eingabe=='1') aufsteigend=1;

    
    f->momentan = f->start;

    if(f->start==0) return;
    //Anzahl der Elemente bestimmen
    for (anzElement = 1;f->momentan = f->momentan->danach; ++anzElement); //ermittle Anzahl der Elemente

    
    //Da es sich nur um die Fallunterscheidung von 2 Sortierkriterien handelt
    //ist eine If-Unterscheidung dieser die einfachste Methode.
    if(titelIstKriterium) {
        for (durchlauf = 1; durchlauf < anzElement; ++durchlauf) {
            f->momentan = f->start;
            while(f->momentan->danach){
                if (compareWords(f->momentan->titel, f->momentan->danach->titel, aufsteigend, 0) == f->momentan->titel) {
                    up_tauschenVorgang(f, 1);
                } else {
                    f->momentan = f->momentan->danach;
                }
            }
        }
    } else {
        for (durchlauf = 1; durchlauf < anzElement; ++durchlauf) {
            f->momentan = f->start;
            while(f->momentan->danach){
                if (compareWords(f->momentan->autor, f->momentan->danach->autor, aufsteigend, 0) == f->momentan->autor) {
                    up_tauschenVorgang(f, 1);
                } else {
                    f->momentan = f->momentan->danach;
                }
            }
        }
    }
}

//------------------------------------
// FUNKTIONEN ZUFÄLLIG
//------------------------------------

void randomInput(t_feld * f){

    int i, anzDaten;

    //Eingabe
    do {
        printf("\nWieviele zuf\x84llige Datens\x84tze sollen erzeugt werden? (Max 10.000)\n");
        eingabeZahl(&anzDaten);
        if(anzDaten>10000|| anzDaten<1)printf("\nLeider ist die Eingabe falsch oder die Zahl zu gro\xE1. Bitte erneut eingeben.");
    }while(anzDaten>10000|| anzDaten<1);

    //Hinzufügen der Datensätze
    for (i = 0; i < anzDaten; ++i) {
        randomString(f->buch.titel);
        randomString(f->buch.autor);
        randomString2(f->buch.inhalt);
        up_liste_add(f);
    }
}
void randomString(char * stringDest){
    //Es werden zwei(!) zufällig (lange) Wörter erstellt
    int j, lenVorname, lenNachname ;

    //Wort 1 (bspw Vorname)
    lenVorname = (rand() % 5)+3;    //Bestimmung der Länge

    *(stringDest) = (rand()%26)+65; //Setzen des Großbuchstabens am Anfang

    for (j = 1; j < lenVorname; ++j) {
        *(stringDest+j) = (rand()%26)+97; //Setzen der weiteren Buchstaben
    }
    *(stringDest+lenVorname) = 32;        //Setzen des Leerzeichens (und unten des Null-terminators)

    //Wort 2 (bspw Nachname)
    lenNachname = (rand() % 5)+3;

    *(stringDest+lenVorname+1) = (rand()%26)+65;

    for (j = 1; j < lenNachname; ++j) {
        *(stringDest+j+lenVorname+1) = (rand()%26)+97;
    }
    *(stringDest+lenNachname+lenVorname+1) = '\0';
}
void randomString2(char * stringDest){
    //Es wird ein(!) zufällig (langes) Wort erstellt
    int j, length;

    length = (rand() % 8)+6;

    *(stringDest) = (rand()%26)+65;

    for (j = 1; j < length; ++j) {
        *(stringDest+j) = (rand()%26)+97;
    }
    *(stringDest+length) = '\0';

}

//------------------------------------
// FUNKTIONEN VERSCHLUESSELUNG
//------------------------------------

void allesVerschluesseln(t_feld * f){

    //Deklarationen und Initialisierungen
    FILE * schreiben;

    char key[LENKEY], temp[90];
    bool keyRichtig =1;

    schreiben = fopen("VerschluesselteAusgabeJannisGehring.txt", "w");

    //Eingabe Schlüssel
    do {
        printf("\nBitte gib den Schl\x81ssel ein."
               " Die maximale L\x84nge betr\x84gt %d, alles danach wird nicht gewertet.\n", LENKEY-1);
        fgets(key, LENKEY, stdin);
        for (int j = 0; j < LENKEY; ++j) {
            if (key[j] == '\n')key[j] = '\0';
        }
        for(int k = 0; k < strlen(key); ++k){
            if(key[k]<48 || key[k]>57) keyRichtig = 0;
        }
        if(strlen(key)==0) keyRichtig=0;
        if(!keyRichtig)printf("\nMit der Eingabe stimmt etwas nicht.");
    }while(!keyRichtig);

    //hier wird der Fall abgefangen, dass der FILE-Pointer NULL ist
    if(!schreiben){
        printf("\nEs gab leider einen Fehler.");
        return;
    }

    for(f->momentan=f->start;f->momentan;f->momentan=f->momentan->danach){
        /* Hier werden die Attribute in einem temporären Array abgespeichert,
         * dann verschlüsselt und in die Datei (jeweils als neue Zeile) geschrieben
         */
        strcpy(temp, f->momentan->titel);
        schluesseln(temp, key, 1);
        fprintf(schreiben, "%s\n", temp);

        strcpy(temp, f->momentan->autor);
        schluesseln(temp, key, 1);
        fprintf(schreiben, "%s\n", temp);

        strcpy(temp, f->momentan->inhalt);
        schluesseln(temp, key, 1);
        fprintf(schreiben, "%s\n", temp);
    }
    fclose(schreiben);
}
void allesEntschluesseln(t_feld * f){

    FILE * einlesen;
    char text[32], key[LENKEY];
    int index;
    bool keyRichtig=1;
    einlesen = fopen("VerschluesselteAusgabeJannisGehring.txt", "r");

    //Eingabe
    do {
        printf("\nBitte gib den Schl\x81ssel ein."
               " Die maximale L\x84nge betr\x84gt %d, alles danach wird nicht gewertet.\n", LENKEY-1);
        fgets(key, LENKEY, stdin);
        for (int j = 0; j < LENKEY; ++j) {
            if (key[j] == '\n')key[j] = '\0';
        }
        for(int k = 0; k < strlen(key); ++k){
            if(key[k]<48 || key[k]>57) keyRichtig = 0;
        }
        if(strlen(key)==0) keyRichtig=0;
        if(!keyRichtig)printf("\nMit der Eingabe stimmt etwas nicht.");
    }while(!keyRichtig);

    if(!einlesen) {
        printf("\nDatei kann leider nicht geöffnet werden."
               "Eventuell ist der Dateipfad zu lang, kurz oder falsch.\n");
        getch();
        return;
    }
    fgets(text,40, einlesen);
    while(!feof(einlesen)){
        for (int i = 0; i < strlen(text); ++i) {
            if(text[i]=='\n')text[i]='\0';
        }
        //Mit folgender Funktion wird jeweils der Inhalt von "text" entschluesselt
        schluesseln(text, key, 0);

        //durch den Index werden die Attribute nacheinander gefüllt
        switch (index%3){
            case 0: strcpy(f->buch.titel, text);break;
            case 1: strcpy(f->buch.autor, text);break;
            case 2:{
                strcpy(f->buch.inhalt, text);
                up_liste_add(f);
                break;
            }
        }
        fgets(text, 40, einlesen);
        index++;
    }
    fclose(einlesen);
}
void schluesseln(char * message, char * key, bool verschluesseln){
    /*diese Funktion verschluesselt den String "message":
     *
     * Die einzelnen chars werden hierbei um einen Wert geändert,
     * welcher vom Wert des Schluessels an einer bestimmten Stelle abhängt.
     * Auch werden Leerzeichen mit "[" substituiert, um den Wertebereich des Verschlüsselns anzupassen
     */
    for(int i = 0;message[i]!='\0';i++){
        if(verschluesseln){
            if(message[i]==32) message[i] = 91;
            message[i]-= (key[i%strlen(key)]-24);
        } else {
            message[i]+= (key[i%strlen(key)]-24);
            if(message[i]==91) message[i] = 32;
        }
    }
}