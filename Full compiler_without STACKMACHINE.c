#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int c = 0; // awel index f tableau taa symboles

// Projet Ayoub Hammami Med Aziz Rebhi II2C PARTIE 1 ET 2 AVEC TEST IN MAIN
//La Partie qui concerne les fonctions de pile sont ecrit a part et non implementé dans la phase de test.
//Ce code comporte la partie syntaxique,semantique,lexicale,et trdaucterur de code intermediaire qui tous fonctionnent correctement, la partie de la pile est ecrit(les fonctions de cours sont tous implementé) a part et non implementé dans la phase de teste


int if_counter = 0;


int counter = 0;
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
#define and 28 // hedhom des attributs zeydin f OPMUL OPADD OPAFF khw!!!!
#define or 29
#define addi 30  
#define modd 31
#define divi 32
#define sous 33
#define multi 34
#define lt 35   //hedhom des attributs zeydin lil opprel bch naarfou enehi superieur inf etc lt par exp heya less than
#define bt 36 
#define leq 37
#define beq 38
#define eq 39
#define diff 40
#define errX 41


typedef struct unitelex { //Unite lexical defini par ul w att
    int ul;
    int att; //indexation in case ID w lo5rin type or 7aja arbitraire.
}unitelex;






int type_table[20]; // hedhi bch ykoun fiha les types ta3 les variables(with indexation) par exp if we have [x,y,z] tq x,y int w z char , type_table=[integer,integer,char]

char mot_cle[20][20]={"program", "begin", "var",
"integer", "char", "end", "then", "if", "else", "read",
"readln", "write", "writeln", "do", "while"};//tableau ta3 les mots clés




int id_mot_cle[16]={1,10,4,8,9,11,14,13,15,21,23,20,22,17,16}; // hedhom les defines taa les mots clé b tartib (program 1 , begin 10 etc ....)
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
void S(int typehdsq);// Exp prime
int Exp_S();//Exp simple
void E(int typehjqs);//Exp simple prime
int Terme();
void T(int h);
int Facteur();
// Fonctions partie Semantique 
int chercher_type(char* variable); // va accepter index f tableau ta3 les symboles w traj3elna chnowa type ta3 l variable
void ajouter_type(int index_dans_tabID , int tp);
int compatible(int t1 , int t2 );
int creer_etiq();
char* return_current_op();


// erreur w accepter w emettre si we choose nektbou f fichier
void erreur(int T);
void emettre(char* ch);
void accepter(int T);
unitelex symbole;
// on va l'utiliser lors du parcours
int z=0 ; //parcours du ch


 // trouver l'indexation du mot cle 


FILE *fs;  //fichier source

int sym;   // Variable globale contenat le retour du analyseur synatxique

char ch[30]; // chaine pour sauvegarder la ligne parcouru

void emettre(char* cha){
    FILE* fd;
    fd = fopen("codeInterm.txt","a+"); 
    if (fd != NULL) {
        printf("%s\n", cha); // On ecrit avec cette ligne sur le "fichier codeInterm.txt"
        fprintf(fd, "%s\n", cha); // On ecrit avec cette ligne sur le "fichier codeInterm.txt"
        
    } else {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier 'codeInterm.txt'\n");
    }
    fclose(fd);
}// hedhi fonction nestaamlouha ken n7ebou nektbou fi ficher l output but we will write it on terminal ashel

//Partie Semantique 

void ajouter_type(int index_dans_tabID , int tp){
    if(tp == integer){
        type_table[index_dans_tabID]= integer;
        
    }
    else if (tp == rchar){
        type_table[index_dans_tabID] = rchar;
        
    }
    else{
        type_table[index_dans_tabID]= errX;
        
    }
    //printf("ADDED TYPE of %s , %d\n",tab_iden[index_dans_tabID],type_table[index_dans_tabID]); // Debugging w bara 
}

int compatible(int t1 , int t2){
    if (t1 == t2){
        return 1;
    }
    else if (t1 == integer && t2 == nb){
        return 1;
    }
    else if (t1 == nb && t2 == integer){
        return 1;
    }
    else{
        return 0;
    }
}
int chercher_type(char* variable){
    int i = 0 ; 
    while(i<c){
        if (strcmp(tab_iden[i], variable)!=0){
            i++;
        }else{
            if(type_table[i]==8){
            //printf("La variable %s est de type %s\n",tab_iden[i],"Integer");
            return type_table[i];
            }
            else if (type_table[i] == 9){
                //printf("La variable %s est de type %s\n",tab_iden[i], "Char");
                return type_table[i];
            }
            else{
                //printf("Variable Introuvable %s! EXIT FAILIRE!",tab_iden[i]);
                exit(0);
                return -1;
                
            }
        }
    }

}
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
    case (28): printf("Or is wrong written;");break;
    case (29): printf("And is wrong written!");break;
    case (30): printf("VARIABLE INTROUVABLE !");break;
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
        //printf("Lkelma rahi deja mawjouda ! %s\n",tab_iden[index]); // HEDHOM RAHOM DEBUGGING NA7IWHOM NHAR L VALIDATION XD
        return index;                               // Ken l id mawjoud mn 9bal just n returni l index te3ou f table de symboles
    } else {                                        // mal9inech l id donc nzidouh fi e5er table de symbole , attribut taa l id bch ykoun houwa l index f table!
        (*c)++;
         strcpy(tab_iden[*c - 1], ch);
        //printf("Rana zedna l kelma hedhi f tableau identificateurs %s\n",tab_iden[*c - 1]);
         return *c - 1 ;                            // l'index f tableau de symboles (tableau d'identificateurs)
    }}

    
    else{ // l'attribut t3 les mots clés mayhmnich barcha 5ater menich bch nsaljou f table de symbole najem nhot arbitraiement kenou mot clé rahou attribut par exp 1000
       return 1000;
        }
}// variable index just staamlneha lil parcours (recherche)


char* return_current_op(){
    switch(symbole.att){
        case 28: return "and";
        case 29: return "or";
        case 30: return "+";
        case 31: return "mod";
        case 32: return "div";
        case 33: return "-";
        case 34: return "*";
        case 35: return "<";
        case 36: return ">";
        case 37: return "<=";
        case 38: return ">=";
        case 39: return "==";
        case 40: return "<>";        case 41: return "errX";
        default: return "Erreur de compilation";
    }   
}



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
                }else if (car == '|'){
                    etat = 21;
                }
                else if (car == '&'){
                    etat = 22;
                }
                else if (car == '+' || car == '-'){
                    etat = 23;
                }
                else if (car == '%' || car == '/'){
                    etat = 24;
                }
                else if (car == '*'){
                    etat = 25;
                }
                
                 else {
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
                symbole.att = RangerId(symbole.ul, &c);
                
                 // attribut kima 9olna ken id rahou l index sinon rahou 1000 yaani mot clé (arbitraire 5tarneh )
                // hedhom zednehom juste bch ndebugiw bihom 
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
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
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                
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
                symbole.att = eq;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 10:
                
                car = carSuivant();
                if (car == '=') {
                    etat = 11;
                } else {
                    symbole.ul = oprel;
                    symbole.att = bt;
                    
                    //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }
            case 11:
                symbole.ul = oprel;
                symbole.att = beq;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 6:
                symbole.ul = oprel;
                symbole.att = leq;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 7:
                symbole.ul = oprel;
                symbole.att = diff;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 8:
                Reculer(1);
                symbole.ul = oprel;
                symbole.att = lt;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 12:
                symbole.ul = oprel;
                symbole.att = oprel;
            
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 13:
                symbole.ul = 100;
                symbole.att = 0;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 14:
                etat = 0;
                break;
            case 15:
                symbole.ul = pv;
                symbole.att = 0;
                
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 16:
                symbole.ul = v;
                symbole.att = 0;
                
           //     printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 17:
                symbole.ul = po;
                symbole.att = 0;
             //   printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 18:
                car = carSuivant();
                if (car == '=') {
                    symbole.ul = opaf;
                    symbole.att = 0;
               //     printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                } else {
                    
                    Reculer(1); 
                    symbole.ul = dp;
                    symbole.att = 0;
                    
                 //   printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }

            case 19:
                symbole.ul = pf;
                symbole.att = 0;
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;
            case 20:
                    symbole.ul = p;
                    symbole.att = 0;// un attribut arbitraire pour pt li deja 7atinehom lkol 0 b5lef jme3t l id w les mots clé
                  //  printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;


            case 21:
                car = carSuivant();
                if(car == '|'){
                    symbole.ul = opadd;
                    symbole.att = or;
                //    printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }
                else{
                    erreur(28);
                }

            case 22 : 
                car = carSuivant();
                if(car == '&'){
                    symbole.ul = opmul;
                    symbole.att  = and ; 
                  //  printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                    return symbole.ul;
                }
                else{
                    erreur(29);
                }
            case 23:
                symbole.ul = opadd;

                if(car == '+'){
                    symbole.att = addi;
                }
                else{
                    symbole.att = sous;
                }
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;

            case 24:
                symbole.ul = opmul;
                if(car == '%'){
                    symbole.att = modd;
                }
                else{
                    symbole.att = divi;
                }
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
                return symbole.ul;

            case 25 : 
                symbole.ul = opmul;
                symbole.att = multi;
                //printf("Symbol: %d, Attribute: %d\n", symbole.ul, symbole.att);
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
        accepter(3); 
 
        
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
{   counter = 0;
    if(sym == var )
    {
        accepter(var);//var
                
        List_id(); //liste_id
                
        accepter(5);//:
        Type();
        accepter(2);//;
        //printf("Counter %d\n",counter);
        D();
    }
}

void List_id()
{
    if(sym == 6)
    { 
        counter++;
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
        counter++;
        L();
    }
}

void Type()
{
    if(sym == 8)
    {
        accepter(8);
        for (int i = c-1;i>= c - counter ; i--){
            ajouter_type(i,8);
        }
    }
    else if(sym == 9)
    {
        accepter(9);
            for (int i = c-1;i>= c - counter ; i--){
            ajouter_type(i,9);
        }
    }
}

void Inst_compose()
{
    if (sym == begin)
    {
        accepter(begin);
        Inst();
       // printf("finished\n");
        accepter(end);
        
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
        accepter(2);//pt virgule
        I();
        L_I();
    }

}


char *strconcatChaine (const char *chaine1, const char *chaine2) {
    size_t len1 = strlen(chaine1);
    size_t len2 = strlen(chaine2);
    size_t lenTotal = len1 + len2 + 1;
    char *result = (char *)malloc(lenTotal);
    if (result == NULL) {
        perror("Erreur lors de l'allocation de m�moire");
        exit(EXIT_FAILURE);
    }
    strcpy(result, chaine1);
    strcat(result, chaine2);

    return result;
}


char* valeurd(const char* chaine1){
    
    char* result = strconcatChaine("valeurd @",chaine1);
    return result;
}

char* valeurg(const char* chaine1){
    char* result = strconcatChaine("valeurg @",chaine1);
    return result;
}

char* empiler(const char* chaine1){
    char* result = strconcatChaine("empiler ",chaine1);
    return result;
}

char* elsortie(const char* chaine1){
    char* result = strconcatChaine("Etiq Sortie:",chaine1);
    return result;
}

char* allersifaux(const char* chaine1){
    char* result = strconcatChaine("AllerSifaux Sortie:",chaine1);
    return result;
}

char* allera(const char* chaine1){
    char* result = strconcatChaine("AllerA test:",chaine1);
    return result;
}
char* eltest(const char* chaine1){
    char* result = strconcatChaine("Etiq Test:",chaine1);
    return result;
}

int creer_etiq(){
    if_counter++;
    return if_counter;
}

void I()
{
    if (sym == 6)
    {   char* var1 = ch;
        emettre(valeurg(var1));
        accepter(6);
        int I_type = chercher_type(var1);
        accepter(12);
        int final_type = Exp_S();
        int type_IF = compatible(I_type,final_type);
        if (type_IF == 0){
            printf("Erreur de type !");
            exit(0);
        }
        else{
            //printf("type is %d\n",final_type);
        }
        emettre(":=");
    }
    else if(sym == iff)
    {
        accepter(iff);
        Exp();
        int sortie_num = creer_etiq();
        char sortie[3];
        sprintf(sortie,"%d",sortie_num);
        emettre(allersifaux(sortie));
        accepter(then);
        I();
        accepter(elsee);
        emettre(elsortie(sortie));
        I();
    }
    else if(sym == whilee)
    {   int test_num = creer_etiq();
        int sortie_num = creer_etiq();   
        char test[3];
        char sortie[3];
        sprintf(test,"%d",test_num);
        sprintf(sortie,"%d",sortie_num);
        accepter(whilee);
        eltest(test);
        Exp();
        emettre(allersifaux(sortie));
        accepter(doo);

        I();
        emettre(allera(test));
        emettre(elsortie(sortie)); //etiqsortie
    } 
    else if(sym == 21)
    {
        accepter(21);
        accepter(18);
        char* variable = ch;
        chercher_type(variable);
        accepter(6);
        accepter(19);
    }
    else if (sym == 23)
    {
        accepter(23);
        accepter(18);
        char* variable = ch;
        chercher_type(variable);
        accepter(6);
        accepter(19);
    }
    else if(sym == 20)
    {
        accepter(20);
        accepter(18);
        char* variable = ch;
        chercher_type(variable);
        accepter(6);
        accepter(19);
    }
    else if(sym == 22)
    {
        accepter(22);
        accepter(18);
        char* variable = ch;
        chercher_type(variable);
        accepter(6);
        accepter(19);
    }

    else
    {
        printf("Syntaxe invalide");
    }

}

void Exp()
{   int typeq;
    typeq = Exp_S();
    S(typeq);
}

void S(int typeq)
{   
    if (sym == oprel){
        char* oprelx = return_current_op();
        accepter(oprel);
        int typez = Exp_S();
        int typeS = compatible(typez,typeq);
        if(typeS == 0){
            printf("Erreur_de_type\n");
            exit(0);
        }
        emettre(oprelx);
}
    
}

int Exp_S()
{   
    int type6 = Terme();
    E(type6);
    return type6;
}

void E(int type6) //expsimple prime
{
    if(sym == opadd)
    {   char* opaddx = return_current_op();

        accepter(opadd);
        int typeh = Terme();
        int E_type = compatible(type6,typeh);
        if(E_type == 0){
            printf("Erreur_de_type!\n");
            exit(0);
        }
        emettre(opaddx);
        E(type6);
    }
}

int Terme()
{   int typex;
    typex = Facteur();
    T(typex);
    return typex;
}

void T(int typex) //terme prime
{
    if (sym == opmul)
    {   char* opmulx = return_current_op();
        accepter(opmul);
        int type2 = Facteur();
        int T_type = compatible(typex,type2);
        if(T_type == 0){
            printf("Erreur de type!\n");
            exit(0);
        }
        emettre(opmulx);
        T(typex);
    }
}

int Facteur()
{
    if(sym == 6)
    {   int type1;
        char* var2 = ch;
        type1 = chercher_type(var2);
        //printf("Le type de %s est %d\n",var2,type1);
        emettre(valeurd(var2));
        accepter(6);
        return type1;

    }
    else if( sym == 27)
    {   emettre(empiler(ch));
        accepter(27);
        return 27;
    }
    else if(sym == 18)
    {
        accepter(18);
        int u = Exp_S();
        accepter(19);
        return u;
    }
}


//La Partie qui concerne les fonctions de pile sont ecrit a part et non implementé dans la phase de test.

// Partie fonctions de pile 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
    int elements[50];
    int sommet;
} Pile;

// Créer une nouvelle pile
Pile* creer_pile() {
    Pile* stack = (Pile*)malloc(sizeof(Pile));
    if (stack != NULL) {
        stack->sommet = -1;
    }
    return stack;
}

// Vérifier si la pile est vide
int est_vide(Pile* stack) {
    return stack->sommet == -1;
}

// Vérifier si la pile est pleine
int est_pleine(Pile* stack) {
    return stack->sommet == 50 - 1;
}

// Empiler une valeur
void empiler_real_stack(Pile* stack, int valeur) {
    if (!est_pleine(stack)) {
        stack->elements[++stack->sommet] = valeur;
        printf("Empilé: %d\n", valeur);
    } else {
        printf("Pile pleine!\n");
    }
}

// Dépiler une valeur
int depiler(Pile* stack) {
    if (!est_vide(stack)) {
        return stack->elements[stack->sommet--];
    }
    printf("Pile vide!\n");
    return -1;
}

// Consulter le sommet
int sommet(Pile* stack) {
    if (!est_vide(stack)) {
        return stack->elements[stack->sommet];
    }
    printf("Pile vide!\n");
    return -1;
}



//fonction copier
void copier(Pile* stack) {
    if (!est_vide(stack)) {
        int valeur = sommet(stack);
        empiler_real_stack(stack, valeur);
        printf("Copié: %d\n", valeur);
    } else {
        printf("Pile vide!\n");
    }
}

//fonction *
void multiplier(Pile* stack) {
    if (stack->sommet >= 1) {  // Besoin d'au moins deux éléments
        int a = depiler(stack);
        int b = depiler(stack);
        depiler(stack);// on enleve le signe *
        empiler_real_stack(stack, a * b);
        printf("Multiplication: %d * %d = %d\n", b, a, a * b);
    } else {
        printf("Pas assez d'éléments pour multiplier!\n");
    }
}

//fonction +
void additionner(Pile* stack) {
    if (stack->sommet >= 1) {  // Besoin d'au moins deux éléments
        int a = depiler(stack);
        int b = depiler(stack);
        depiler(stack);// on enleve le signe +
        empiler_real_stack(stack, a + b);
        printf("Addition: %d + %d = %d\n", b, a, a + b);
    } else {
        printf("Pas assez d'éléments pour additionner!\n");
    }
}

// Définir une étiquette
void etiq(char* nom) {
    printf("Étiquette définie : %s\n", nom);
}

// fonction :=
void affectation(Pile* stack) {
    if (stack->sommet >= 1) {  // Besoin d'au moins deux éléments
        int valeur = depiler(stack);
        int* adresse = (int*)depiler(stack);  // On suppose que c'est une adresse
        *adresse = valeur;
        printf("Affectation : %d placé à l'adresse %p\n", valeur, (void*)adresse);
    } else {
        printf("Pas assez d'éléments pour affecter!\n");
    }
}
void comparer_si_sup(Pile* stack) {
    if (stack->sommet >= 1) {
        int a = depiler(stack);
        int b = depiler(stack);
        empiler_real_stack(stack, b > a ? 1 : 0);
        printf("Comparer-si-sup: %d > %d = %d\n", b, a, b > a ? 1 : 0);
    } else {
        printf("Pas assez d'éléments pour comparer!\n");
    }
}

// Comparer si inférieur
void comparer_si_inf(Pile* stack) {
    if (stack->sommet >= 1) {
        int a = depiler(stack);
        int b = depiler(stack);
        depiler(stack);// on enleve le signe <  
        empiler_real_stack(stack, b < a ? 1 : 0);
        printf("Comparer-si-inf: %d < %d = %d\n", b, a, b < a ? 1 : 0);
    } else {
        printf("Pas assez d'éléments pour comparer!\n");
    }
}

// Comparer si égal
void comparer_si_egal(Pile* stack) {
    if (stack->sommet >= 1) {
        int a = depiler(stack);
        int b = depiler(stack);
        depiler(stack);// on enleve le signe ==
        empiler_real_stack(stack, b == a ? 1 : 0);
        printf("Comparer-si-égal: %d == %d = %d\n", b, a, b == a ? 1 : 0);
    } else {
        printf("Pas assez d'éléments pour comparer!\n");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// LA PARTIE MACHINE A PILE NEST PAS IMPLEMENTE EN TEST , SEUELENT LES FONCTIONS DU COURS SONT IMPLEMENTEES
// Partie test

int main()
{int x ;

    fs = fopen("pascallikecoded.txt","rt");
    
    sym = analyLex();
    P();
        printf("Programme a bien complie !");
        scanf("%d",&x);
    fclose(fs);
    
    return 0;
}

