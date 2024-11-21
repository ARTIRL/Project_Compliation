#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int c = 0; // awel index f tableau taa symboles

// Projet Ayoub Hammami Med Aziz Rebhi II2C PARTIE 1 ET 2 AVEC TEST IN MAIN


















// Hedha aka tableau li f classe aamlneh w zedlenou l ne9s kima program w ghirou
// Zedna E zeyda fl while w else bch yod5olch baaadhou maa syntaxe t3 C w if zeda; lbe9i mrigel

#define program 1
#define pv 2 // point virgule
#define p 3 //point
#define var 4
#define dp 5 //2 points
#define id 6
#define v 7 // virgule
#define integer 8
#define rchar 9
#define begin 10
#define end 11
#define opaf 12
#define iff 13
#define then 14
#define elsee 15
#define whilee 16
#define doo 17
#define po 18 //parenthese ouvrant
#define pf 19 //parenthese fermant
#define write 20
#define read 21
#define writeln 22
#define readln 23
#define oprel 24
#define opadd 25
#define opmul 26
#define nb 27

typedef struct unitelex { //Unite lexical defini par ul w att
    int ul;
    int att;
}unitelex;

char mot_cle[20][20]={"program", "begin", "var",
"integer", "char", "end", "then", "if", "else", "read",
"readln", "write", "writeln", "do", "while"};//tableau ta3 les mots clés




int id_mot_cle[20]={1,10,4,8,9,11,14,13,15,21,23,20,22,17,16}; // hedhom les defines taa les mots clé b tartib (program 1 , begin 10 etc ....)
char tab_iden[100][20]; // tableau des identificateurs



// Les fonctions taa l partie 2 analex
int symbole_suivant();
void erreur(int T);
void accepter(int T);
int analyLex();
void emettre(char* ch);
char carSuivant();
void Reculer(int k);
int UniLexId();
int RangerId(int k, int *c);

// Fonctions taa3 l pârtie 1 syntaxique 
void P(); // P 
void DCL(); // DCL 
void D(); // DCL PRIME 
void List_id(); // List Id
void L(); //List id prime
void Type(); // Type
void Inst_compose();// Insta composo
void Inst();// Inst
void List_inst();// Linst int
void L_I();// List inst prime
void I();// I 
void Exp();// Exp 
void S();// Exp prime
void Exp_S();//Exp simple
void E();//Exp simple prime
void Terme();
void T();
void Facteur();

// erreur w accepter w emettre si we choose nektbou f fichier
void erreur(int T);
//void emettre(char* ch);
void accepter(int T);
unitelex symbole;

int symbole_lu; // on va l'utiliser lors du parcours
int z=0 ; //parcours du ch


 // trouver l'indexation du mot cle 


FILE *fs;  //fichier source

FILE *fd; 

int sym;   // Variable globale contenat le retour du analyseur synatxique

char ch[30]; // chaine pour sauvegarder la ligne parcouru

/*void emettre(char* ch){
    if (fd != NULL) {
        fprintf(fd, "%s\n", ch); // On ecrit avec cette ligne sur le "fichier codeInterm.txt"
        
    } else {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier 'codeInterm.txt'\n");
    }
}*/ // hedhi fonction nestaamlouha ken n7ebou nektbou fi ficher l output but we will write it on terminal ashel

















// Partie  Lexical ///////////////////////////////////////////////////////////////////////////////////////////////////



void erreur(int T) // changement de fonction erreur 
{
    switch(T){
    case(2): printf("point virgule manquant");break;
    
    case(4): printf("var manquant");break;
    case(5): printf("deux points manquantes");break;
    case(6): printf("id manquant");break;
    case(7): printf("virgule manquante");break;
    case(8): printf("integer manquant");break;
    case(9): printf("char manquant");break;
    case(10): printf("begin manquant");break;
    case(11): printf("end manquant");break;
    case(12): printf(":= manquant");break;
    case(13): printf("if manquant");break;
    case(14): printf("then manquant");break;
    case(15): printf("else manquant");break;
    case(16): printf("while manquant");break;
    case(17): printf("do manquant");break;
    case(18): printf("parenthese ouvrante manquante");break;
    case(19): printf("parenthese fermante manquante");break;
    case(3): printf("Erreur manque point!");break;
    case(20): printf("write manquant");break;
    case(21): printf("read manquant");break;
    case(22): printf("writeln manquant");break;
    case(23): printf("readln manquant");break;
    case(24): printf("operation relationelle manquante");break;
    case(25): printf("operation d/'addition manquante");break;
    case(26): printf("operation de multiplication manquante");break;
    case(27): printf("nb manquant");break;
    default: printf("erreur detecté de compliation");
    }
    exit(0);

}
char carSuivant(){
    return(fgetc(fs));
    
}
void Reculer(int k)
{fflush(stdout);
    fseek(fs, -k, SEEK_CUR);
} // Reculer le pointeur de k index
void accepter(int T)
{
	if (sym==T) // si le symbol est accepte en passe l'autre
	{   
		sym=symbole_suivant();
	}
	else
	{
		erreur(T);
	}
} 
int UniLexId()
{
    int k=0;
    int i=0;
    while (i<14&&(!k)) { // 3anna 14 mot clé dheka aaleh i<14 w variable k nestaamlouha bch nverifiw si l kelma (unite lex) mawjouda wla lé
        if(strcmp(mot_cle[i],ch)== 0){
            k=1;
        }else{
           i++;
        }
    }
    if (k==1){
        return id_mot_cle[i]; // une fois l9ina l mot clé , nraj3ou l ID te3ou yaani aka Define li aamlneha mlowel (btbi3thom ktebnehom mratbin nafes tartib f mot clé w id mot clé)
    }
    else {
        return id; // ken kamlna boucle w mal9inech mot clé yaani base l kelma li 9rineha id (par exp var xaqs , 9rina xaqs li houwa id) donc we return 6
    }
}

int RangerId(int k, int* c)                     // return l index where in memory l'UL te3na, w c mele5er heya index li wsolnelha for now f tableau
                                                // also 3addina pointeur c lhné bch najmou nbadlou real value te3ha
{
    int index=0;                                      //index de parcours tab_iden et *c pointeur win wfé l array tab_iden e5er mara
    if (k == id) {                                   // Ken lkelma li jetna ID nemchiw l aka tableau t3 les symboles w nhotou kelma li 9rineha ONLY KENHA MCH MAWJOUDA MN 9BAL 
    while ((strcmp(tab_iden[index], ch) != 0) && (index < (*c)))
        index++;
    if (index < *c) {
         printf("Lkelma rahi deja mawjouda ! %s\n",tab_iden[index]); // HEDHOM RAHOM DEBUGGING NA7IWHOM NHAR L VALIDATION XD
        return index;                               // Ken l id mawjoud mn 9bal just n returni l index te3ou f table de symboles
    } else {                                        // mal9inech l id donc nzidouh fi e5er table de symbole , attribut taa l id bch ykoun houwa l index f table!
        (*c)++;
         strcpy(tab_iden[*c - 1], ch);
          printf("Rana zedna l kelma hedhi f tableau identificateurs %s\n",tab_iden[*c - 1]);
         return *c - 1 ;                            // l'index f tableau de symboles (tableau d'identificateurs)
    }}

    
    else{ // l'attribut t3 les mots clés mayhmnich barcha 5ater menich bch nsaljou f table de symbole najem nhot arbitraiement kenou mot clé rahou attribut par exp 1000
       return 1000;
        }
}// variable index just staamlneha lil parcours (recherche)



int analyLex() {
    int etat = 0;
    char car;
    int colonne = 0, ligne = 1;
    while (1) {
        
        switch (etat) {
            case 0:
                car = carSuivant(); 
                
                if (car == ' ') {              
                    colonne++;
                    etat = 0;
                } else if (car == '\n') {
                    ligne++;
                    colonne = 0;
                    etat = 0;
                } else if (car == '\t') {
                    colonne += 3;
                    etat = 0;
                } else if (isalpha(car)) {
                    z = 0;
                    ch[0] = car;
                    etat = 1;
                } else if (isdigit(car)) {
                    Reculer(1);
                    etat = 3;
                  
                }
                 else if (car == '<') {
                    etat = 5;
                } else if (car == '>') {
                    etat = 10;
                } else if (car == '=') {
                    etat = 9;
                } else if (car == '$') {
                    etat = 13;
                } else if (car == ';') {
                    etat = 15;
                } else if (car == ',') {
                    etat = 16;
                } else if (car == '(') {
                    etat = 17;
                } else if (car == ':') {
                    etat = 18;
                } else if (car == ')') {
                    etat = 19;
                }else if (car == '.'){
                    etat = 20;
                } else {
                    etat = 14;
                }
                break;
            case 1:
                car = carSuivant();
                if (isalpha(car) || isdigit(car)) {
                    z++;
                    ch[z] = car;
                } else {
                    etat = 2;
                    ch[z + 1] = '\0';
                    z = 0;
                }
                break;
            case 2:
                Reculer(1);
                symbole.ul = UniLexId(); // Get the symbol ID
                symbole.att = RangerId(symbole.ul, &c); // attribut kima 9olna ken id rahou l index sinon rahou 1000 yaani mot clé (arbitraire 5tarneh )
                // hedhom zednehom juste bch ndebugiw bihom 
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 3:
                
                car = carSuivant();
                if (isdigit(car)) {
                    
                    ch[z] = car;
                    z++;
                } else {
                    
                    etat = 4;
                    ch[z] = '\0';
                    z = 0;
                }
                break;
            case 4:
                
                symbole.ul = nb;
                symbole.att = atoi(ch); // hedhi une fois chla9na li 9rina nombre nconvertiwh l entier kima f C++ b atoi
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                
                return symbole.ul;
            case 5:
                car = carSuivant();
                switch (car) {
                    case '=':
                        etat = 6;
                        break;
                    case '>':
                        etat = 7;
                        break;
                    default:
                        etat = 8;
                }
                break;
            case 9:
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 10:
                Reculer(1);
                car = carSuivant();
                if (car == '=') {
                    etat = 11;
                } else {
                    symbole.ul = oprel;
                    symbole.att = oprel;
                    
                    printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }
            case 11:
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 6:
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 7:
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 8:
                Reculer(1);
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 12:
                symbole.ul = oprel;
                symbole.att = oprel;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 13:
                symbole.ul = 100;
                symbole.att = 0;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 14:
                etat = 0;
                break;
            case 15:
                symbole.ul = pv;
                symbole.att = 0;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 16:
                symbole.ul = v;
                symbole.att = 0;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 17:
                symbole.ul = po;
                symbole.att = 0;
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 18:
                car = carSuivant();
                if (car == '=') {
                    symbole.ul = opaf;
                    symbole.att = 0;
                    printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                } else {
                   
                    Reculer(1); 
                    symbole.ul = dp;
                    symbole.att = 0;
                    
                    printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }

            case 19:
                symbole.ul = pf;
                symbole.att = 0;
                
                printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 20:
                    symbole.ul = p;
                    symbole.att = 0;// un attribut arbitraire pour pt li deja 7atinehom lkol 0 b5lef jme3t l id w les mots clé
                    printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
        }   
    }
}


int symbole_suivant(){
    return analyLex();
} 
// partie1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void P()
{
    if(sym == 1) //verifie program
    {
        accepter(1); //passe au symbol suivant : id
        
        accepter(6); //verifie et passe au symbol suivant ;
        
        accepter(2); //;
        
        DCL(); //dcl
        Inst_compose();//inst_compsoe
   // accepter(3); Hedhi still bugging menich fehem aaleh
 
        
    }
    else
    {
        printf("Votre programme manque le mot Program ?... Compliation terminé ECHEC!!"); //afficher erreur
    }
}

void DCL()
{
    D();
}

void D()
{
    if(sym == 4 )
    {
        accepter(4);//var
                

        List_id(); //liste_id
                

        accepter(5);//:
               

        Type();
        

        accepter(2);//;
        D();
    }
}

void List_id()
{
    if(sym == 6)
    {
        accepter(6);
        L();
    }
    else
    {
        printf("id manquant");
    }
}

void L()
{
    if(sym == 7)
    {
        accepter(7);
        accepter(6);
        L();
    }
}

void Type()
{
    if(sym == 8)
    {
        accepter(8);
    }
    else if(sym == 9)
    {
        accepter(9);
    }
}

void Inst_compose()
{
    if (sym == 10)
    {
        accepter(10);
        Inst();
        accepter(11);
        
    }
    else
    {
        printf("begin manquant");
    }
}

void Inst()
{
    List_inst();
}

void List_inst()
{
    I();
    L_I();
}

void L_I()
{
    if(sym == 2)
    {
        accepter(2);
        I();
        L_I();
    }

}

void I()
{
    if (sym == 6)
    {
        accepter(6);
        accepter(12);
        Exp_S();
    }
    else if(sym == 13)
    {
        accepter(13);
        Exp();
        accepter(14);
        I();
        accepter(15);
        I();
    }
    else if(sym == 16)
    {
        accepter(16);
        Exp();
        accepter(17);
        I();
    }
    else if(sym == 21)
    {
        accepter(21);
        accepter(18);
        accepter(6);
        accepter(19);
    }
    else if (sym == 23)
    {
        accepter(23);
        accepter(18);
        accepter(6);
        accepter(19);
    }
    else if(sym == 20)
    {
        accepter(20);
        accepter(18);
        accepter(6);
        accepter(19);
    }
    else if(sym == 22)
    {
        accepter(22);
        accepter(18);
        accepter(6);
        accepter(19);
    }

    else
    {
        printf("Syntaxe invalide");
    }

}

void Exp()
{
    Exp_S();
    S();
}

void S()
{
    Exp_S();
}

void Exp_S()
{
    Terme();
    E();
}

void E()
{
    if(sym == 24)
    {
        accepter(24);
        Exp_S();
        E();
    }
}

void Terme()
{
    Facteur();
    T();
}

void T()
{
    if (sym == 24)
    {
        accepter(24);
        Facteur();
        T();
    }
}

void Facteur()
{
    if(sym == 6)
    {
        accepter(6);
    }
    else if( sym == 27)
    {
        accepter(27);
    }
    else if(sym == 18)
    {
        accepter(18);
        Exp_S();
        accepter(19);
    }

}








// Partie test

int main()
{int x ;
    fs = fopen("pascallikecoded.txt","rt");
    //fd = fopen("codeInterm.txt","wt"); voir commantaire sur emettre
    sym = analyLex();
    P();
        printf("Programme a bien complie !");
        scanf("%d",&x);
    fclose(fs);
    //fclose(fd);
    return 0;
}

