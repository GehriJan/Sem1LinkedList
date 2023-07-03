//
// Created by Jannis Gehring on 12.02.2023.
//

//------------------------------------
// INCLUDES
//------------------------------------

#include "HeaderDatenGehring.h"

//------------------------------------
// FUNKTIONEN
//------------------------------------

void trim(char*string){
    //trim(): entfernt Leerzeichen, Tabs, NewLines und CarriageReturn-Zeichen am Ende eines Strings

    int i = strlen(string)-1;

    while(i>0){
        if(string[i]==' ' || string[i]=='\t' || string[i]=='\n' || string[i]=='\r' || string[i]=='\0' || string[i]=='\004') i--;
        else break;
    }
    string[i+1]='\0';
}
void up_datum(char*datum){      //fuer Datum bei der Ausgabe in eine Datei nötig
    char hilfstext[80+1];
    struct tm *zeit;
    time_t sek;

    time(&sek);
    zeit = localtime(&sek);

    switch(zeit->tm_wday){
        case 0: strcpy(datum,"Sonntag"); 	break;
        case 1: strcpy(datum,"Montag"); 	break;
        case 2: strcpy(datum,"Dienstag"); 	break;
        case 3: strcpy(datum,"Mittwoch"); 	break;
        case 4: strcpy(datum,"Donnerstag");	break;
        case 5: strcpy(datum,"Freitag"); 	break;
        case 6: strcpy(datum,"Samstag"); 	break;
    }
    strcat(datum, ", ");
    itoa((zeit->tm_mday), hilfstext, 10);
    strcat(datum, hilfstext);
    strcat(datum, ". ");
    switch(zeit->tm_mon){
        case 0: strcpy(hilfstext,"Januar");		break;
        case 1: strcpy(hilfstext,"Februar");	break;
        case 2: strcpy(hilfstext,"M\xE4rz");	break;
        case 3: strcpy(hilfstext,"April");		break;
        case 4: strcpy(hilfstext,"Mai");		break;
        case 5: strcpy(hilfstext,"Juni");		break;
        case 6: strcpy(hilfstext,"Juli");		break;
        case 7: strcpy(hilfstext,"August");		break;
        case 8: strcpy(hilfstext,"September");	break;
        case 9: strcpy(hilfstext,"Oktober");	break;
        case 10:strcpy(hilfstext,"November");	break;
        case 11:strcpy(hilfstext,"Dezember");	break;
    }
    strcat(datum, hilfstext);
    itoa(zeit->tm_year+1900, hilfstext, 10);
    strcat(datum, " ");
    strcat(datum, hilfstext);
}
void up_liste_add(t_feld *f){
    f->momentan = (t_buch*) malloc(sizeof(t_buch));

    up_struct_liste(f);

    f->momentan->davor=f->letztes;
    f->momentan->danach=0;

    if(f->letztes == 0) f->start = f->momentan;
    else f->letztes->danach = f->momentan;

    f->letztes = f->momentan;
}
void up_struct_liste(t_feld *f){
    strcpy(f->momentan->autor, f->buch.autor);
    strcpy(f->momentan->titel, f->buch.titel);
    strcpy(f->momentan->inhalt, f->buch.inhalt);
}
char * strSearch(char * string, char * subString, bool caseSensitive){
    //Diese Funktion such substring in string und returned entweder dessen Vorkommen
    //Oder den Nullpointer, wenn Substring nicht in String vorkommt
    int i=0, k=0,j=0, l=0;
    char stringTemp[strlen(string)], subStringTemp[strlen(subString)];

    strcpy(stringTemp, string);
    strcpy(subStringTemp, subString);

    //Buchstaben klein machen
    if(!caseSensitive) {
        for (k = 0; k < strlen(stringTemp); ++k) {
            if (isupper(stringTemp[k]))stringTemp[k] += 32;
        }
        for (i = 0; i < strlen(subStringTemp); ++i) {
            if (isupper(subStringTemp[i]))subStringTemp[i] += 32;
        }
    }


    for (j = 0; j <= strlen(stringTemp)-strlen(subStringTemp) && strlen(stringTemp)>=strlen(subStringTemp); ++j) {                   //durch j werden alle Stellen, an denen der zum Substring identische Teil anfangen könnte, abgedeckt
        if(stringTemp[j]==subStringTemp[0]){                                                    //checkt ob der string an der Stelle j gleich dem Anfang des Substrings ist, wenn nicht, kann j inkrementiert werden
            l=0;
            while((stringTemp[j+l]==subStringTemp[l])&&(l<strlen(subStringTemp))){
                l++;
            }                                                                                   //bricht ab, wenn chars ungleich sind oder das letzte Element des
            if(subStringTemp[l]=='\0') return(&(string[l]));
        }
    }
    return(NULL);
}
void eingabeZahl(int * eingabe){
    /*diese Funktion dient dazu, Zahleingaben, die nicht der Steuerung dienen Fool-Proof zu machen
     *wenn sich ein Zeichen in ihnen befindet, das keine Zahl liefert, dann wird die Eingabe null,
     *ansonsten wird die Zahl als int zurückgegeben.
     */
    char arrayEingabe[11];

    fgets(arrayEingabe, 11, stdin);
    fflush(stdin);

    for(int j = 0; j<11; j++){
        if(arrayEingabe[j]=='\n') arrayEingabe[j]='\0';
    }

    for (int i = 0; i < strlen(arrayEingabe); ++i) {
        if(arrayEingabe[i]<48 || arrayEingabe[i]>57){
            *eingabe = 0;
            return;
        }
    }
    *eingabe = atoi(arrayEingabe);
    return;
}
char *  compareWords(char * string1, char * string2, bool returnBigger, bool caseSensitive) {
    //Diese Funktion returned einen Pointer auf das größere Wort, oder, wenn beide gleich groß sind, den NULL-Pointer
    //Mit der Variable "direction" kann beim Sortieren die Sortierrichtung gesteuert werden

    int i = 0, k = 0, j = 0, l = 0;
    char string1Temp[strlen(string1)+1], string2Temp[strlen(string2)+1];

    strcpy(string1Temp, string1);
    strcpy(string2Temp, string2);

    if(!caseSensitive) {
        //Buchstaben klein machen
        for (k = 0; k < strlen(string1Temp); ++k) {
            if (isupper(string1Temp[k]))string1Temp[k] += 32;
        }
        for (l = 0; l < strlen(string2Temp); ++l) {
            if (isupper(string2Temp[l]))string2Temp[l] += 32;
        }
    }

    for (i = 0; (*(string1Temp + i) == *(string2Temp + i)) && i < MAXLEN && *(string1Temp + i) != '\0'; ++i);

    if (*(string1Temp + i) > *(string2Temp + i)) {
        if(returnBigger) return (string1);
        else return (string2);
    } else if (*(string1Temp + i) < *(string2Temp + i)) {
        if(returnBigger) return (string2);
        else return (string1);
    } else {
        return (NULL);
    }
}

bool eingabeText(char * eingabe){
    /*diese Funktion dient dazu, Texteingaben Fool-Proof zu machen
     *wenn sich ein Zeichen in der Eingabe befindet, das kein Buchstabe ist, dann wird der Output false,
     *ansonsten true.
     */
    char arrayEingabe[30];
    strcpy(arrayEingabe, eingabe);

    for(int j = 0; j<30; j++){
        if(arrayEingabe[j]=='\n') arrayEingabe[j]='\0';
    }

    for (int i = 0; i < strlen(arrayEingabe); ++i) {
        if(arrayEingabe[i]<65 || (arrayEingabe[i]>90 && arrayEingabe[i]<97) || arrayEingabe[i]>122){
            return(0);
        }
    }
    return(1);
}