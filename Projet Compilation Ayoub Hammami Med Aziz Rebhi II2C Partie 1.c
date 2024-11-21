#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
FILE *f;




// On a utilisé un fichier pour tester le code (un simple programme a analyser sur notre machine)

// on a utiliser strcmp pour la comparaison 

// on a utilisé strcmp avant d'accepter le mot (le mot sera lu d'un fichier texte a analyser)

//utilsation de accepter comme mentionné dans le cours 

// on a utilisé pour chaque non terminal une fonction pour l'accepter recursivement 

// on a utlisé aussi AnalEx comme dans le cours pour la lecture et la verification des mots de grammaire (comme program , var , etc ....)

// tout les fonctions sont prototypés pour eviter "undefined behaviour lors de l'execution"

//Veuiller lire la grammaire apres la transformation(elimination de la recursivité a gauche) en fichier PDF dans le classroom

// Analex : Elle lit chaque caractère du fichier à l'aide de fgetc

// DANS ANALEX : La variable caractere est de type int et est utilisée pour stocker temporairement le caractère lu du fichier lors de l'analyse lexicale. Lecture : La fonction fgetc(f) lit un caractère du fichier et le stocke dans caractere

//Ce program compile lorsque on specifie au poiteur 'f' le fichier que on veut faire l'analyse sur.
























// Code Ayoub Hammami & Med Aziz Rebhi
void P();
void DCL();
void DCL_prime();
void inst_composee();
void list_id();
void list_id_prime();
void type();
void liste_inst();
void liste_inst_prime();
void I();
void exp();
void exp_simple();
void exp_simple_prime();
void exp_prime();
void terme();
void terme_prime();
void facteur();
void facteur_prime();
void accepter(const char *T);
void erreur(const char *msg);
char *analLex();
char *symbole;  
typedef struct {
    char att[100]; 
} SymbolTableEntry;

SymbolTableEntry tablesSymboles[100]; 
int indiceALex = 0; // Pour le parcours de tablesymbole
//att : C'est un tableau de caractères (chaîne de caractères) qui stocke l'attribut du symbole, c'est-à-dire son nom ou son identifiant.
void accepter(const char *T) {
    if (strcmp(symbole, T) == 0) {
        symbole = analLex();
    } else {
        printf("Erreur de syntaxe: \"%s\" attendu, mais \"%s\" trouvé.\n", T, symbole);
        exit(0);
    }
}


void P() {
    symbole = analLex();
    accepter("program");
    accepter("id");
    accepter(";");
    DCL();
    inst_composee();
    accepter(".");
    printf("\nCompilation correcte !\n");
}


void DCL() {
    DCL_prime(); 
}


void DCL_prime() {
    if (strcmp(symbole, "var") == 0) {
        accepter("var");
        list_id();
        accepter(":");
        type();
        accepter(";");
        DCL_prime(); 
    }
}


void list_id() {
    accepter("id");
    list_id_prime(); 
}

void list_id_prime() {
    if (strcmp(symbole, ",") == 0) {
        accepter(",");
        accepter("id");
        list_id_prime(); 
    }
}


void type() {
    if (strcmp(symbole, "integer") == 0) {
        accepter("integer");
    } else if (strcmp(symbole, "char") == 0) {
        accepter("char");
    } else {
        printf("Erreur de type: \"%s\" n'est pas un type valide.\n", symbole);
        exit(0);
    }
}


void inst_composee() {
    accepter("begin");
    liste_inst();
    accepter("end");
}


void liste_inst() {
    I();
    liste_inst_prime(); 
}


void liste_inst_prime() {
    if (strcmp(symbole, ";") == 0) {
        accepter(";");
        I();
        liste_inst_prime(); 
    }
}


void I() {
    if (strcmp(symbole, "id") == 0) {
        accepter("id");
        accepter(":=");
        exp();
    } else if (strcmp(symbole, "if") == 0) {
        accepter("if");
        exp();
        accepter("then");
        I();
        if (strcmp(symbole, "else") == 0) {
            accepter("else");
            I();
        }
    } else if (strcmp(symbole, "while") == 0) {
        accepter("while");
        exp();
        accepter("do");
        I();
    } else if (strcmp(symbole, "read") == 0) {
        accepter("read");
        accepter("(");
        accepter("id");
        accepter(")");
    } else if (strcmp(symbole, "readln") == 0) {
        accepter("readln");
        accepter("(");
        accepter("id");
        accepter(")");
    } else if (strcmp(symbole, "write") == 0) {
        accepter("write");
        accepter("(");
        accepter("id");
        accepter(")");
    } else if (strcmp(symbole, "writeln") == 0) {
        accepter("writeln");
        accepter("(");
        accepter("id");
        accepter(")");
    } else {
        printf("Erreur: instruction \"%s\" non reconnue.\n", symbole);
        exit(0);
    }
}


void exp() {
    exp_simple();

    if (strcmp(symbole, "oprel") == 0) {
        accepter(symbole); 
        exp_simple(); 
    }
}


void exp_prime() {
    if (strcmp(symbole, "oprel") == 0) {
        accepter(symbole); 
        exp_simple(); 
        exp_prime(); 
    }
}


void exp_simple() {
    terme(); 
    exp_simple_prime(); 
}


void exp_simple_prime() {
    if (strcmp(symbole, "opadd") == 0) {
        accepter(symbole); 
        terme(); 
        exp_simple_prime(); 
    }
}


void terme() {
    facteur(); 
    terme_prime(); 
}


void terme_prime() {
    if (strcmp(symbole, "opmul") == 0) {
        accepter(symbole); 
        facteur(); 
        terme_prime(); 
    }
}


void facteur() {
    if (strcmp(symbole, "id") == 0) {
        accepter("id");
        facteur_prime(); 
    } else if (strcmp(symbole, "nb") == 0) {
        accepter("nb");
        facteur_prime(); 
    } else if (strcmp(symbole, "(") == 0) {
        accepter("(");
        exp_simple(); 
        accepter(")"); 
        facteur_prime(); 
    } else {
        printf("Erreur: facteur non valide à \"%s\".\n", symbole);
        exit(0);
    }
}


void facteur_prime() {
    // EPSILONE ICI
}


char *analLex() { // responsable de l'analyse lexicale, c'est-à-dire qu'elle lit le fichier source et identifie les différents tokens (éléments lexicaux) du code source, tels que les identifiants, les mots-clés, les opérateurs et les nombres.
    int etat = 0;
    int caractere;
    while (1) {
        switch (etat) {
            case 0:
                caractere = fgetc(f);
                if (isalpha(caractere)) {
                    etat = 1; 
                } else if (isdigit(caractere)) {
                    etat = 2; 
                } else if (caractere == ':') {
                    etat = 3; 
                } else if (caractere == ',') {
                    return ",";
                } else if (caractere == ';') {
                    return ";";
                } else if (caractere == '.') {
                    return ".";
                } else if (caractere == '+') {
                    return "opadd";
                } else if (caractere == '-') {
                    return "opadd";
                } else if (caractere == '=') {
                    return "oprel";
                } else if (caractere == '<') {
                    return "oprel";
                } else if (caractere == '>') {
                    return "oprel";
                } else if (caractere == '(') {
                    return "(";
                } else if (caractere == ')') {
                    return ")";
                } else if (caractere == EOF) {
                    return "EOF";
                } else {
                    printf("Erreur lexicale à caractère \"%c\".\n", caractere);
                    exit(0);
                }
                break;

            case 1: 
                ungetc(caractere, f);
                fscanf(f, "%s", tablesSymboles[indiceALex].att);
                symbole = tablesSymboles[indiceALex].att;
                indiceALex++;

                
                if (strcmp(symbole, "program") == 0 || 
                    strcmp(symbole, "var") == 0 || 
                    strcmp(symbole, "integer") == 0 || 
                    strcmp(symbole, "char") == 0 || 
                    strcmp(symbole, "if") == 0 || 
                    strcmp(symbole, "then") == 0 || 
                    strcmp(symbole, "else") == 0 || 
                    strcmp(symbole, "while") == 0 || 
                    strcmp(symbole, "do") == 0 || 
                    strcmp(symbole, "begin") == 0 || 
                    strcmp(symbole, "end") == 0 || 
                    strcmp(symbole, "read") == 0 || 
                    strcmp(symbole, "readln") == 0 || 
                    strcmp(symbole, "write") == 0 || 
                    strcmp(symbole, "writeln") == 0) {
                    return symbole; 
                }
                return "id"; 

            case 2:
                ungetc(caractere, f);
                return "nb";

            case 3: 
                return ":=";
        }
    }
}


int main() {
    
    f = fopen("ayoub_hammami.txt", "r"); 
    if (f == NULL) {
        perror("Erreur à l'ouverture du fichier");
        return 1;
    }

    P(); 
    fclose(f); 
    return 0;
}
