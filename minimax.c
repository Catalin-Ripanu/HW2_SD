#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000000
#define MAX1 10000
/* Structura necesara pentru a defini toate proprietatile unui arbore generic*/
typedef struct NextTree
{				/* Tabla de joc */
  char **gametable;
  /*Caracterul ce se afla intr-o anumita zona ('X' sau 'O') */
  char caracter;
  /*Numarul de muchii */
  int muchie;
  /*Valoarea numerica stocata de un nod */
  int val;
  /*Mutarea spre un nod */
  struct NextTree **Next_Node;
}
GenericTree;
/*Structura necesara pentru accesarea nodurilor din stiva*/
typedef struct Node_Stack_Tree
{
/*Informatia stocata intr-un nod din stiva*/
GenericTree* data;
/*Merg mai departe in stiva*/
struct Node_Stack_Tree *next;
}
Node_Stack_Tree;
/* Structura necesara pentru a defini coordonatele unui punct pe tabla*/
typedef struct PozGame
{ /*Abscisa*/
  int X_ABS;
  /*Ordonata*/
  int Y_ORD;
}
PozTable;
/*Stiva pentru memorarea nodurilor*/
typedef struct Stack
{
/*Capul listei*/
struct Node_Stack_Tree *top;
/*Lungimea listei*/
int len;
}
Stack;
/*Afisarea arborelui in cazul in care se foloseste -c3*/
void Afisare_MINIMAX (GenericTree *, FILE *, int);
/*Afisarea arborelui in cazul in care se foloseste -c1*/
void Afisare_ARBORE (GenericTree *, FILE *, int);
/*Distruge arborele*/
void Eliberare_Memorie (GenericTree *);
/*Afisarea arborelui in cazul in care se foloseste -c2*/
void Afisare_ARBORE_TF (GenericTree *, FILE *, int);
/*Adaugare in stiva*/
int Add_Stack (Stack *,GenericTree *);
int contor1 = 0;
/*Functia de initiere*/
void 
Init_Stack(Stack** s)
 {
    *s=(Stack *)calloc(1 ,sizeof(Stack));
    (*s)->top=NULL;
    (*s)->len=0;
 }
 
 /*Functia de adaugare in tabla de joc(pentru prima problema)*/
GenericTree *
Adaugare (GenericTree * Tree, char **tablegame, int x_abs, int y_ord,
	  int value, char X_O_char,Stack* Stack_Tree)
{				/*Variabile ajutatoare */
  int contor4, contor11, contor12, contor13, contor14, contor15 = 1;
  int contor16 =
    0, contor17, contor18, contor19, contor20, contor21, contor22, contor23,
    contor24 = 0;
  PozTable prel;
  char **prelucrare = (char **) calloc (10 ,sizeof (char *));
  char char1 = 'X', char2 = 'O', char3= '-';
  for (contor4 = 1; contor4 <= 3; contor4++)
    prelucrare[contor4] = (char *) calloc (10 ,sizeof (char));
  GenericTree *rz = NULL ;
  PozTable *v = (PozTable *) calloc ((value + 1) ,sizeof (PozTable));
  if (value >= 0)
    {				/* Construiesc arborele de joc */
      Tree = (GenericTree *) calloc (1 ,sizeof (GenericTree));
      /*Aloc memorie pentru tabla de joc asociata arborelui */
      Tree->gametable = (char **) calloc (10 ,sizeof (char *));
      for (contor4 = 1; contor4 <= 3; contor4++)
	Tree->gametable[contor4] = (char *) calloc (10 ,sizeof (char));
      /*Daca punctul nu se afla la inceput */
      if (x_abs != 0 && y_ord != 0)
	/*Adaug in tabla ajutatoare */
	tablegame[x_abs][y_ord] = X_O_char;
      for (x_abs = 1; x_abs <= 3; x_abs++)
	for (y_ord = 1; y_ord <= 3; y_ord++)
	  /*Adaug in tabla principala */
	  Tree->gametable[x_abs][y_ord] = tablegame[x_abs][y_ord];
      /*Daca s-a plasat O */
      if (X_O_char == char2)
	{			/*Plasez X */
	  Tree->caracter = char1;
	}
      else
	{
	  Tree->caracter = char2;
	}
      /*Memorez numarul de muchii */
      Tree->muchie = value;
      if (Tree->muchie != 0)
	{			/*Aloc memorie pentru nodurile ce vor reprezenta starile intregului joc
				   Evident,fiecare nod are cate o tabla de joc asociata */
	  Tree->Next_Node =
	    (GenericTree **) calloc ((value + 1) ,sizeof (GenericTree *));
	  for (contor4 = 1; contor4 <= value; contor4++)
	    Tree->Next_Node[contor4] = NULL;
	}			/*Un algoritm construit pentru a vedea/numara pozitiile lui X folosind contori */
      for (contor17 = 1; contor17 <= 3; contor17++)
	for (contor18 = 1; contor18 <= 3; contor18++)
	  if (Tree->gametable[contor17][contor18] == char3)
	    /*Numar spatiile goale din tabla de joc */
	    contor16++;
      for (contor19 = 1; contor19 <= 3; contor19++)
	{
	  contor17 = 0;
	  contor18 = 0;
	  for (contor20 = 1; contor20 <= 3; contor20++)
	    {
	      if (Tree->gametable[contor19][contor20] == char1)
		contor17 = contor17 + 1;
	      if (Tree->gametable[contor20][contor19] == char1)
		contor18 = contor18 + 1;
	    }
	  if (contor17 == 3 || contor18 == 3)
	    contor16 = -1;
	}
      contor21 = 0;
      contor22 = 0;
      for (contor23 = 1; contor23 <= 3; contor23++)
	if (Tree->gametable[contor23][contor23] == char1)
	  contor21 = contor21 + 1;
      contor19 = 1;
      contor20 = 3;
      while (contor19 <= 3 && contor20 >= 1)
	{
	  if (Tree->gametable[contor19][contor20] == char1)
	    contor22 = contor22 + 1;
	  contor19++;
	  contor20--;
	}
      if (contor21 == 3 || contor22 == 3)
	contor16 = -1;
      /*Acelasi algoritm pentru 'O' */
      /*Initializez totul cu 0 */
      contor17 = 0;
      contor18 = 0;
      contor19 = 0;
      contor20 = 0;
      contor21 = 0;
      contor22 = 0;
      contor23 = 0;
      for (contor17 = 1; contor17 <= 3; contor17++)
	for (contor18 = 1; contor18 <= 3; contor18++)
	  if (Tree->gametable[contor17][contor18] == char3)
	    /*Numar spatiile goale din tabla de joc */
	    contor24++;
      for (contor19 = 1; contor19 <= 3; contor19++)
	{
	  contor17 = 0;
	  contor18 = 0;
	  for (contor20 = 1; contor20 <= 3; contor20++)
	    {
	      if (Tree->gametable[contor19][contor20] == char2)
		contor17 = contor17 + 1;
	      if (Tree->gametable[contor20][contor19] == char2)
		contor18 = contor18 + 1;
	    }
	  if (contor17 == 3 || contor18 == 3)
	    contor24 = -1;
	}
      contor21 = 0;
      contor22 = 0;
      for (contor23 = 1; contor23 <= 3; contor23++)
	if (Tree->gametable[contor23][contor23] == char2)
	  contor21 = contor21 + 1;
      contor19 = 1;
      contor20 = 3;
      while (contor19 <= 3 && contor20 >= 1)
	{
	  if (Tree->gametable[contor19][contor20] == char2)
	    contor22 = contor22 + 1;
	  contor19++;
	  contor20--;
	}
      if (contor21 == 3 || contor22 == 3)
	contor24 = -1;
      /*Initializez totul cu 0 */
      contor17 = 0;
      contor18 = 0;
      contor19 = 0;
      contor20 = 0;
      contor21 = 0;
      contor22 = 0;
      contor23 = 0;
      /*Daca am completat corespunzator cu 'X' si 'O' */
      if (contor16 == -1 || contor24 == -1)
	{
	  for (contor4 = 1; contor4 <= 3; contor4++)
	    /*Eliberez memoria pentru 'prelucrare' si returnez arborele de joc */
	    free (prelucrare[contor4]);
	  free (prelucrare);
	  free (v);
	  return Tree;
	}
      for (contor11 = 1; contor11 <= 3; contor11++)
	for (contor12 = 1; contor12 <= 3; contor12++)
	  /*Daca mai am de completat */
	  /*Salvez intr-un vector de pozitii anumite coordonate */
	  if (Tree->gametable[contor11][contor12] == char3)
	    {
	      v[contor15].X_ABS = contor11;
	      v[contor15].Y_ORD = contor12;
	      contor15++;
	    }
      contor15 = contor15 - 1;
      /* Completez respectand acea conditie din cerinta */
      for (contor13 = 1; contor13 < contor15; contor13++)
	for (contor14 = contor13 + 1; contor14 <= contor15; contor14++)
	  if (v[contor14].X_ABS * 3 + v[contor14].Y_ORD <
	      v[contor13].X_ABS * 3 + v[contor13].Y_ORD)
	    {
	      prel = v[contor14];
	      v[contor14] = v[contor13];
	      v[contor13] = prel;
	    }
      for (contor4 = 1; contor4 <= value; contor4++)
	{
	  for (x_abs = 1; x_abs <= 3; x_abs++)
	    for (y_ord = 1; y_ord <= 3; y_ord++)
	      /*Apelez recursiv pentru a continua procesul de completare */
	      prelucrare[x_abs][y_ord] = Tree->gametable[x_abs][y_ord];
	  /*Daca am completat cu 'X' */
	  if (X_O_char == char1)
	  {
	    /*Creez tabla de joc a unui nod */
	    /*Continui cu 'O' daca am avut 'X' */
	    /*Decrementez 'value' */
	    Tree->Next_Node[contor4] =
	      Adaugare (Tree->Next_Node[contor4], prelucrare,
			v[contor4].X_ABS, v[contor4].Y_ORD, value - 1, char2, Stack_Tree);
			/*Salvez in stiva*/
	    Add_Stack(Stack_Tree, Tree->Next_Node[contor4]);
	    }
	  else
	  {
	    Tree->Next_Node[contor4] =
	      /*Continui cu 'X' daca am avut 'O' */
	      /*Decrementez 'value' */
	      Adaugare (Tree->Next_Node[contor4], prelucrare,
			v[contor4].X_ABS, v[contor4].Y_ORD, value - 1, char1, Stack_Tree);
			/*Salvez in stiva*/
	       Add_Stack(Stack_Tree, Tree->Next_Node[contor4]);
	   }
	}
      /*Eliberez memoria si returnez arborele prelucrat */
      for (contor4 = 1; contor4 <= 3; contor4++)
	free (prelucrare[contor4]);
      free (prelucrare);
      free (v);
      return Tree;
    }
  for (contor4 = 1; contor4 <= 3; contor4++)
    free (prelucrare[contor4]);
  free (prelucrare);
  free (v);
  return rz;
}
/*Functia de verificare*/
 int 
 Verif_Empty_Stack(Stack *s)
 {
   if(s->top==NULL && s->len==0)
   return 0;
   else
   return 1;
 }
 
 /*Adaugare in stiva*/
 int 
 Add_Stack(Stack *s,GenericTree* data)
 {  Node_Stack_Tree* nou;
    nou=(Node_Stack_Tree*)calloc(1,sizeof(Node_Stack_Tree));
    nou->data=data;
    nou->next=s->top;
    s->top=nou;
    s->len++;
    if(s->top!=NULL)
    {
    /*Returnez 1 daca adaugarea s-a efectuat cu succes*/
    return 1;
    s->len++;
    }
    /*Returnez 0 daca adaugarea a dat gres*/
    return 0;
 }
 
/*Functia de adaugare in tabla de joc(pentru a doua problema)*/
void
Prelucrare_Arbore_TF (GenericTree * Tree, char X_O_char,Stack * Stack_Tree)
{				/*Variabile ajutatoare */
  int index, index_1, contor = 0;
  char char1 = 'T', char2 = 'F', char3 = 'X', char4 = 'O',char5 = '-';
  int contor16 =
    0, contor17, contor18, contor19, contor20, contor21, contor22, contor23;
  int contor24 = 0, contor25 = 0;
  /*Formez tabla T_F fiecarui nod(recursivitate) */
  for (index = 1; index <= Tree->muchie; index++)
    if (Tree->Next_Node[index] != NULL)
    {
      Prelucrare_Arbore_TF (Tree->Next_Node[index], X_O_char, Stack_Tree);
      /*Adaug nodul in stiva*/
      Add_Stack (Stack_Tree, Tree->Next_Node[index]);
     }
  /*Un algoritm construit pentru a vedea/numara pozitiile variabilei X_O_char folosind contori */
  for (contor17 = 1; contor17 <= 3; contor17++)
    for (contor18 = 1; contor18 <= 3; contor18++)
      /*Numar spatiile goale */
      if (Tree->gametable[contor17][contor18] == char5)
	contor16++;
  for (contor19 = 1; contor19 <= 3; contor19++)
    {
      contor17 = 0;
      contor18 = 0;
      for (contor20 = 1; contor20 <= 3; contor20++)
	{
	  if (Tree->gametable[contor19][contor20] == X_O_char)
	    contor17 = contor17 + 1;
	  if (Tree->gametable[contor20][contor19] == X_O_char)
	    contor18 = contor18 + 1;
	}
      if (contor17 == 3 || contor18 == 3)
	contor16 = -1;
    }
  contor21 = 0;
  contor22 = 0;
  for (contor23 = 1; contor23 <= 3; contor23++)
    if (Tree->gametable[contor23][contor23] == X_O_char)
      contor21 = contor21 + 1;
  contor19 = 1;
  contor20 = 3;
  while (contor19 <= 3 && contor20 >= 1)
    {
      if (Tree->gametable[contor19][contor20] == X_O_char)
	contor22 = contor22 + 1;
      contor19++;
      contor20--;
    }
  if (contor21 == 3 || contor22 == 3)
    contor16 = -1;
  /*Initializez totul cu 0 */
  contor17 = 0;
  contor18 = 0;
  contor19 = 0;
  contor20 = 0;
  contor21 = 0;
  contor22 = 0;
  contor23 = 0;
  /*Acelasi algoritm pentru 'O' */
  for (contor17 = 1; contor17 <= 3; contor17++)
    for (contor18 = 1; contor18 <= 3; contor18++)
      /*Numar spatiile goale */
      if (Tree->gametable[contor17][contor18] == char5)
	contor24++;
  for (contor19 = 1; contor19 <= 3; contor19++)
    {
      contor17 = 0;
      contor18 = 0;
      for (contor20 = 1; contor20 <= 3; contor20++)
	{
	  if (Tree->gametable[contor19][contor20] == char4)
	    contor17 = contor17 + 1;
	  if (Tree->gametable[contor20][contor19] == char4)
	    contor18 = contor18 + 1;
	}
      if (contor17 == 3 || contor18 == 3)
	contor24 = -1;
    }
  contor21 = 0;
  contor22 = 0;
  for (contor23 = 1; contor23 <= 3; contor23++)
    if (Tree->gametable[contor23][contor23] == char4)
      contor21 = contor21 + 1;
  contor19 = 1;
  contor20 = 3;
  while (contor19 <= 3 && contor20 >= 1)
    {
      if (Tree->gametable[contor19][contor20] == char4)
	contor22 = contor22 + 1;
      contor19++;
      contor20--;
    }
  if (contor21 == 3 || contor22 == 3)
    contor24 = -1;
  /*Initializez totul cu 0 */
  contor17 = 0;
  contor18 = 0;
  contor19 = 0;
  contor20 = 0;
  contor21 = 0;
  contor22 = 0;
  contor23 = 0;
  /*Acelasi algoritm pentru 'X' */
  for (contor17 = 1; contor17 <= 3; contor17++)
    for (contor18 = 1; contor18 <= 3; contor18++)
      /*Numar spatiile goale */
      if (Tree->gametable[contor17][contor18] == char5)
	contor25++;
  for (contor19 = 1; contor19 <= 3; contor19++)
    {
      contor17 = 0;
      contor18 = 0;
      for (contor20 = 1; contor20 <= 3; contor20++)
	{
	  if (Tree->gametable[contor19][contor20] == char3)
	    contor17 = contor17 + 1;
	  if (Tree->gametable[contor20][contor19] == char3)
	    contor18 = contor18 + 1;
	}
      if (contor17 == 3 || contor18 == 3)
	contor25 = -1;
    }
  contor21 = 0;
  contor22 = 0;
  for (contor23 = 1; contor23 <= 3; contor23++)
    if (Tree->gametable[contor23][contor23] == char3)
      contor21 = contor21 + 1;
  contor19 = 1;
  contor20 = 3;
  while (contor19 <= 3 && contor20 >= 1)
    {
      if (Tree->gametable[contor19][contor20] == char3)
	contor22 = contor22 + 1;
      contor19++;
      contor20--;
    }
  if (contor21 == 3 || contor22 == 3)
    contor25 = -1;
  /*Initializez totul cu 0 */
  contor17 = 0;
  contor18 = 0;
  contor19 = 0;
  contor20 = 0;
  contor21 = 0;
  contor22 = 0;
  contor23 = 0;
  /*Daca indeplinesc conditia */
  if (contor16 == -1)
    /*Plasez 'T' */
    Tree->caracter = char1;
  /*Daca indeplinesc cealalta conditie */
  else
    if ((X_O_char == char3 && contor24 == -1)
	|| (X_O_char == char4 && contor25 == -1))
    /*Plasez 'F' */
    Tree->caracter = char2;
  else if (Tree->muchie == 0)
    Tree->caracter = char2;
  /*Ma mut pe celalalt nivel */
  else
    {
      for (index_1 = 1; index_1 <= Tree->muchie; index_1++)
	if (Tree->Next_Node[index_1]->caracter == char1)
	  contor++;
      /*Daca nu am gasit 'T' */
      if (!contor)
	Tree->caracter = char2;
      else if (contor == Tree->muchie)
	Tree->caracter = char1;
      /*Daca jucatorul cu 'X'/'O' castiga */
      else if (Tree->caracter == X_O_char)
	Tree->caracter = char1;
      else
	Tree->caracter = char2;
    }
}

/*Functia de golire*/
GenericTree* 
Eliminate_Stack(Stack *s)
{  GenericTree* val;
   if(s->top==NULL)
   return NULL;
   Node_Stack_Tree* elem;
   elem=s->top;
   val=elem->data;
   s->top=elem->next;
   s->len--;
   if(s->len==0)
   s->top=NULL;
   free(elem);
   return val;
}

/*Functia de formare a arborelui folosind algoritmul minimax(pentru a treia problema)*/
void
Arbore_Minimax (GenericTree * Tree, int value_1, int value,Stack * Stack_Tree)
{
  int index, max, min, contor0;
  if (value > 0 && value != 1 && value != 2)
    {
      /*Ma indrept spre nivelul inferior(recursivitate) */
      for (index = 1; index <= Tree->muchie; index++)
	if (value_1 != 1)
	{ 
	/*Salvez in stiva*/
	  Add_Stack(Stack_Tree, Tree->Next_Node[index]);
	  Arbore_Minimax (Tree->Next_Node[index], 
	                  1, value - 1, Stack_Tree);
	 }
	else
	{ /*Salvez in stiva*/
	  Add_Stack(Stack_Tree, Tree->Next_Node[index]);
	  Arbore_Minimax (Tree->Next_Node[index], 
	                 - 1, value - 1, Stack_Tree);
	}  
      if (Tree->muchie != 0)
	{
	  if (value_1 == 1)
	    {			/*Algoritm pentru a determina valoarea lui max */
	      max = Tree->Next_Node[1]->val;
	      for (contor0 = 2; contor0 <= Tree->muchie; contor0++)
		/*Parcurg toate valorile numerice stocate de noduri */
		if (Tree->Next_Node[contor0]->val > max)
		  max = Tree->Next_Node[contor0]->val;
	      /*Adaug in nod valoarea gasita */
	      Tree->val = max;
	    }
	  else
	    {			/*Algoritm pentru a determina valoarea lui min */
	      min = Tree->Next_Node[1]->val;
	      for (contor0 = 2; contor0 <= Tree->muchie; contor0++)
		/*Parcurg toate valorile numerice stocate de noduri */
		if (Tree->Next_Node[contor0]->val < min)
		  min = Tree->Next_Node[contor0]->val;
	      /*Adaug in nod valoarea gasita */
	      Tree->val = min;
	    }
	}
    }
  /*Ramura pentru completarea nivelului inferior ('value' tot scade) */
  else
    {
      if (Tree->muchie != 0)
	{
	  if (value_1 == 1)
	    {			/*Algoritm pentru a determina valoarea lui max */
	      max = Tree->Next_Node[1]->val;
	      for (value = 2; value <= Tree->muchie; value++)
		/*Parcurg toate valorile numerice stocate de noduri */
		if (Tree->Next_Node[value]->val > max)
		  max = Tree->Next_Node[value]->val;
	      /*Adaug in nod valoarea gasita */
	      Tree->val = max;
	    }
	  else
	    {			/*Algoritm pentru a determina valoarea lui min */
	      min = Tree->Next_Node[1]->val;
	      for (contor0 = 2; contor0 <= Tree->muchie; contor0++)
		/*Parcurg toate valorile numerice stocate de noduri */
		if (Tree->Next_Node[contor0]->val < min)
		  min = Tree->Next_Node[contor0]->val;
	      /*Adaug in nod valoarea gasita */
	      Tree->val = min;
	    }
	}
    }
}

int
main (int argc, char *argv[])
{				/*Variabila ce reprezinta arborele */
  GenericTree *Tree = NULL;
  /*Variabila ce prelucreaza arborele */
  /*Variabile auxiliare folosite pentru eliberarea memoriei(cele cu _Free) */
  GenericTree **Tree_Build = NULL;
  GenericTree **Tree_Aux = NULL, **Tree_Aux_Free1 = NULL, ** *Tree_Aux_Free2 =
    NULL;
  /*Formez stiva*/
  Stack *Stack_Tree = NULL;
  Init_Stack(&Stack_Tree);
  FILE *f;
  FILE *f1;
  /*Variabile folosite pentru extragerea informatiilor din fisierul de intrare */
  char *sir1 = NULL, *sir2 = NULL, *sir3 = NULL;
  char letter, char1 = 'X',char2 = 'O',char3 = '-';
  /*Variabile ajutatoare pentru prelucrare */
  /*Vectorii vr si br vor fi folositi pentru eliberarea memoriei */
  int contor8 = 1, contor9, contor7 =
    1, contor2, contor3, contor4, contor5, contor6, contor10 =
    1, elem, vr[MAX1 * 10] = { 0
  }, br[MAX1 * 10] =
  {
  0}, mi = 1, li = 0, semn = 1;
  long numar = 0;
  /*Variabile ajutatoare pentru algoritmii folositi */
  int contor17, contor18, contor19, contor20, contor21, contor22, contor23;
  int contor16 = 0, contor24 = 0, contor25 = 2, gh = 0;
  /*Aloc memorie */
  sir1 = (char *) calloc (MAX, sizeof (char));
  sir2 = (char *) calloc (MAX, sizeof (char));
  sir3 = sir2;
  /*Extrag tabla initiala din fisier (pentru problema 1 si pentru problema 2) */
  char **table = (char **) calloc (MAX, sizeof (char *));
  for (contor3 = 1; contor3 <= 3; contor3++)
    table[contor3] = (char *) calloc (MAX, sizeof (char));
  f = freopen (argv[2], "r+", stdin);
  f1 = fopen (argv[3], "w");
  /*Procesul de citire si scriere */
  while (fgets (sir1, MAX, f))
    {				/*Prelucrarea liniilor din fisierul de intrare */
      while (sir1[li] == ' ' || sir1[li] == '\n' || sir1[li] == '\t')
	{
	  li++;
	}
      if (sir1[li] == '+' || sir1[li] == '-')
	{
	  if (sir1[li] == '-')
	    {
	      semn = -1;
	    }
	  li++;
	}
      while (sir1[li] && (sir1[li] >= '0' && sir1[li] <= '9'))
	{
	  numar = numar * 10 + (sir1[li] - '0');
	  li++;
	}
      if (strlen (sir1) == 1 || strlen (sir1) == 2 || strlen (sir1) == 3)
	if ((numar * semn) != 0)
	  {
	    elem = semn * numar;
	  }
	else
	  /*Daca se rezolva problema1 sau problema2 */
	  letter = sir1[0];
      else
	{			/*Salvez tabla initiala din fisierul de intrare */
	  if (argv[1][2] != '3')
	    {
	      for (contor9 = 0; contor9 < 3; contor9++)
		{
		  table[contor8][contor9 + 1] = sir1[contor25 * contor9];
		}
	      contor8++;
	    }
	  /*Ramura pentru rezolvarea problemei 3 */
	  else
	    {
	      if (!Tree)
		{		/*Aloc memorie pentru arbori */
		  Tree = (GenericTree *) calloc (1 ,sizeof (GenericTree));
		  numar = 0;
		  li = 0;
		  semn = 1;
		  while ((sir1 + 1)[li] == ' ' || (sir1 + 1)[li] == '\n'
			 || (sir1 + 1)[li] == '\t')
		    {
		      li++;
		    }
		  if ((sir1 + 1)[li] == '+' || (sir1 + 1)[li] == '-')
		    {
		      if ((sir1 + 1)[li] == '-')
			{
			  semn = -1;
			}
		      li++;
		    }
		  while ((sir1 + 1)[li]
			 && ((sir1 + 1)[li] >= '0' && (sir1 + 1)[li] <= '9'))
		    {
		      numar = numar * 10 + ((sir1 + 1)[li] - '0');
		      li++;
		    }
		  Tree->muchie = numar * semn;
		  Tree->Next_Node =
		    (GenericTree **) calloc ((Tree->muchie + 1) ,
					     sizeof (GenericTree *));
		  Tree_Build =
		    (GenericTree **) calloc (contor25 ,sizeof (GenericTree *));
		  Tree_Build[1] = Tree;
		  contor7 = 1;
		}
	      else
		{
		   sir2 = strtok (sir1, " ");
		  contor6 = 0;
		  /*Realocarea memoriei este necesara intrucat se tot formeaza muchii */
		  for (contor4 = 1; contor4 <= contor7; contor4++)
		    contor6 = contor6 + Tree_Build[contor4]->muchie;
		  /*Aloc memorie pentru variabilele ajutatoare */
		  if (Tree_Aux_Free2 == NULL)
		    Tree_Aux_Free2 =
		      (GenericTree ***) calloc (MAX, sizeof (GenericTree **));
		  if (Tree_Aux_Free1 == NULL)
		    Tree_Aux_Free1 =
		      (GenericTree **) calloc (MAX, sizeof (GenericTree *));
		  Tree_Aux =
		    (GenericTree **) realloc (Tree_Aux,
					      (contor6 +
					       1) * sizeof (GenericTree *));
		  contor10 = 1;
		  /*Parcurg sirul de forma (num1) [num2] (num3)... */
		  while (sir2)
		    {
		      contor1 = 1;
		      /*Cunosc numarul de fii */
		      if (sir2[0] == '(')
			{
			  numar = 0;
			  li = 0;
			  semn = 1;
			  while ((sir2 + 1)[li] == ' '
				 || (sir2 + 1)[li] == '\n'
				 || (sir2 + 1)[li] == '\t')
			    {
			      li++;
			    }
			  if ((sir2 + 1)[li] == '+' || (sir2 + 1)[li] == '-')
			    {
			      if ((sir2 + 1)[li] == '-')
				{
				  semn = -1;
				}
			      li++;
			    }
			  while ((sir2 + 1)[li]
				 && ((sir2 + 1)[li] >= '0'
				     && (sir2 + 1)[li] <= '9'))
			    {
			      numar = numar * 10 + ((sir2 + 1)[li] - '0');
			      li++;
			    }
			  if (vr[contor10] == 1 || br[contor10] == 1)
			    Tree_Aux_Free1[mi] = Tree_Aux[contor10];
			  /*Construiesc nodurile */
			  Tree_Aux[contor10] =
			    (GenericTree *) calloc (1 ,sizeof (GenericTree));
			  /*Adaug numarul de fii */
			  Tree_Aux[contor10]->muchie = numar * semn;
			  Tree_Aux[contor10]->val = 0;
			  /*Mai multi arbori */
			  Tree_Aux[contor10]->Next_Node =
			    (GenericTree **)
			    calloc ((Tree_Aux[contor10]->muchie +
				     1) ,sizeof (GenericTree *));
			  /*Acea variabila triplu-pointer contribuie la eliberarea memoriei */
			  Tree_Aux_Free2[mi] = Tree_Aux[contor10]->Next_Node;
			  vr[contor10] = 1;
			}
		      else
			/*Cunosc valoarea stocata de nod(frunza) */
		      if (sir2[0] == '[')
			{
			  numar = 0;
			  li = 0;
			  semn = 1;
			  while ((sir2 + 1)[li] == ' '
				 || (sir2 + 1)[li] == '\n'
				 || (sir2 + 1)[li] == '\t')
			    {
			      li++;
			    }
			  if ((sir2 + 1)[li] == '+' || (sir2 + 1)[li] == '-')
			    {
			      if ((sir2 + 1)[li] == '-')
				{
				  semn = -1;
				}
			      li++;
			    }
			  while ((sir2 + 1)[li]
				 && ((sir2 + 1)[li] >= '0'
				     && (sir2 + 1)[li] <= '9'))
			    {
			      numar = numar * 10 + ((sir2 + 1)[li] - '0');
			      li++;
			    }
			  if (vr[contor10] == 1 || br[contor10] == 1)
			    Tree_Aux_Free1[mi] = Tree_Aux[contor10];
			  /*Construiesc nodurile */
			  Tree_Aux[contor10] =
			    (GenericTree *) calloc (1 ,sizeof (GenericTree));
			  /*Adaug valoarea in nod */
			  Tree_Aux[contor10]->val = numar * semn;
			  /*O frunza nu are fii */
			  Tree_Aux[contor10]->muchie = 0;
			  br[contor10] = 1;
			}
		      /*Merg mai departe */
		      contor10++;
		      mi++;
		      /*Continui parcurgerea */
		      sir2 = strtok (NULL, " ");
		    }
		  contor10--;
		  contor6 = 0;
		  /*Salvez in arborele principal */
		  for (contor4 = 1; contor4 <= contor7; contor4++)
		    {
		      for (contor5 = 1;
			   contor5 <= Tree_Build[contor4]->muchie; contor5++)
			{
			  Tree_Build[contor4]->Next_Node[contor5] =
			    Tree_Aux[contor6 + contor5];
			}
		      contor6 = contor6 + Tree_Build[contor4]->muchie;
		    }
		  /*Realocarea este necesara intrucat adaug muchii */
		  contor7 = contor10;
		  Tree_Build =
		    (GenericTree **) realloc (Tree_Build,
					      (contor7 +
					       1) * sizeof (GenericTree *));
		  for (contor4 = 1; contor4 <= contor7; contor4++)
		    Tree_Build[contor4] = Tree_Aux[contor4];
		}
	    }
	}
    }
/*Partea principala din program*/
/*Acest algoritm rezolva toate problemele*/
  if (argv[1][2] != '3')
    {				/*Pentru problema 1 sau problema 2 */
      for (contor7 = 1; contor7 < 2; contor7++)
	{			/*Daca se incepe cu 'O' */
	  if (letter == char2)
	    /*Continui cu 'X' */
	    letter = char1;
	  else
	    letter = char2;
	  /*Un algoritm construit pentru a vedea/numara pozitiile caracterului 'X' folosind contori */
	  for (contor17 = 1; contor17 <= 3; contor17++)
	    for (contor18 = 1; contor18 <= 3; contor18++)
	      /*Numar spatiile goale */
	      if (table[contor17][contor18] == char3)
		contor16++;
	  for (contor19 = 1; contor19 <= 3; contor19++)
	    {
	      contor17 = 0;
	      contor18 = 0;
	      for (contor20 = 1; contor20 <= 3; contor20++)
		{
		  if (table[contor19][contor20] == char1)
		    contor17 = contor17 + 1;
		  if (table[contor20][contor19] == char1)
		    contor18 = contor18 + 1;
		}
	      if (contor17 == 3 || contor18 == 3)
		contor16 = -1;
	    }
	  contor21 = 0;
	  contor22 = 0;
	  for (contor23 = 1; contor23 <= 3; contor23++)
	    if (table[contor23][contor23] == char1)
	      contor21 = contor21 + 1;
	  contor19 = 1;
	  contor20 = 3;
	  while (contor19 <= 3 && contor20 >= 1)
	    {
	      if (table[contor19][contor20] == char1)
		contor22 = contor22 + 1;
	      contor19++;
	      contor20--;
	    }
	  if (contor21 == 3 || contor22 == 3)
	    contor16 = -1;
	  /*Initializez totul cu 0 */
	  contor2 = contor16;
	  contor17 = 0;
	  contor18 = 0;
	  contor19 = 0;
	  contor20 = 0;
	  contor21 = 0;
	  contor22 = 0;
	  contor23 = 0;
	  /*Un algoritm construit pentru a vedea/numara pozitiile caracterului 'O' folosind contori */
	  for (contor17 = 1; contor17 <= 3; contor17++)
	    for (contor18 = 1; contor18 <= 3; contor18++)
	      if (table[contor17][contor18] == char3)
		contor24++;
	  for (contor19 = 1; contor19 <= 3; contor19++)
	    {
	      contor17 = 0;
	      contor18 = 0;
	      for (contor20 = 1; contor20 <= 3; contor20++)
		{
		  if (table[contor19][contor20] == char2)
		    contor17 = contor17 + 1;
		  if (table[contor20][contor19] == char2)
		    contor18 = contor18 + 1;
		}
	      if (contor17 == 3 || contor18 == 3)
		contor24 = -1;
	    }
	  contor21 = 0;
	  contor22 = 0;
	  for (contor23 = 1; contor23 <= 3; contor23++)
	    if (table[contor23][contor23] == char2)
	      contor21 = contor21 + 1;
	  contor19 = 1;
	  contor20 = 3;
	  while (contor19 <= 3 && contor20 >= 1)
	    {
	      if (table[contor19][contor20] == char2)
		contor22 = contor22 + 1;
	      contor19++;
	      contor20--;
	    }
	  if (contor21 == 3 || contor22 == 3)
	    contor24 = -1;
	  contor2 = contor24;
	  contor17 = 0;
	  contor18 = 0;
	  contor19 = 0;
	  contor20 = 0;
	  contor21 = 0;
	  contor22 = 0;
	  contor23 = 0;
	  /*Apelez functia pentru construirea arborelui */
	  Tree = Adaugare (Tree, table, contor19, contor23, contor2, letter, Stack_Tree);
	  if (argv[contor7][2] == '1')
	    {			/*Daca se cere problema1 rezolvata */
	      Afisare_ARBORE (Tree, f1, Tree->muchie);
	    }
	  if (argv[contor7][2] == '2')
	    {			/*Daca se cere problema2 rezolvata */
	      Prelucrare_Arbore_TF (Tree, Tree->caracter, Stack_Tree);
	      Afisare_ARBORE_TF (Tree, f1, Tree->muchie);
	    }
	}
      /*Eliberez toata memoria */
      Eliberare_Memorie (Tree);
      for (contor3 = 1; contor3 <= 3; contor3++)
	free (table[contor3]);
      free (table);
    }
  else
    /*Pentru problema 3 */
    {				/*Construiesc arborele */
      Arbore_Minimax (Tree, 1, elem, Stack_Tree);
      /*Afisez */
      Afisare_MINIMAX (Tree, f1, gh);
      /*Eliberez intreaga memorie */
      for (contor3 = 1; contor3 <= 3; contor3++)
	free (table[contor3]);
      free (table);
      for (contor7 = 1; contor7 <= contor10; contor7++)
	{
	  free (Tree_Aux[contor7]);
	}
      for (contor7 = 1; contor7 < mi; contor7++)
	{
	  free (Tree_Aux_Free2[contor7]);
	  free (Tree_Aux_Free1[contor7]);
	}
      free (Tree_Aux_Free2);
      free (Tree_Aux_Free1);
      free (Tree_Aux);
      free (Tree_Build);
      free (Tree->Next_Node);
      free (Tree);
    }
  /*Eliberez memoria */
  if (contor1 == 1)
    free (sir3);
  else
    free (sir2);
  free (sir1);
  /*Distrug stiva*/
  while(Verif_Empty_Stack(Stack_Tree))
  Eliminate_Stack(Stack_Tree);
  free(Stack_Tree);
  /*Inchid fisierele */
  fclose (f);
  fclose (f1);
  return 0;
}

/*Functia de afisare pentru problema 3*/
void
Afisare_MINIMAX (GenericTree * Tree, FILE * fisier_iesire, int value)
{
  int index, index_1;
  /*Identare corespunzatoare */
  for (index = 1; index <= value; index++)
    fprintf (fisier_iesire, "\t");
  fprintf (fisier_iesire, "%d\n", Tree->val);
  for (index_1 = 1; index_1 <= Tree->muchie; index_1++)
    if (Tree->Next_Node[index_1])
      Afisare_MINIMAX (Tree->Next_Node[index_1], fisier_iesire, value + 1);
}

/*Functia de afisare pentru problema 1*/
void
Afisare_ARBORE (GenericTree * Tree, FILE * fisier_iesire, int n)
{
  int index, index_1, index_2, index_3;
  for (index_1 = 1; index_1 <= 3; index_1++)
    {
      for (index_3 = 1; index_3 <= n - Tree->muchie; index_3++)
	/*Identare corespunzatoare */
	fprintf (fisier_iesire, "\t");
      for (index_2 = 1; index_2 <= 3; index_2++)
	if (index_2 < 3)
	  /*Tabla de joc */
	  fprintf (fisier_iesire, "%c ", Tree->gametable[index_1][index_2]);
	else
	  fprintf (fisier_iesire, "%c\n", Tree->gametable[index_1][index_2]);
    }
  fprintf (fisier_iesire, "\n");
  for (index = 1; index <= Tree->muchie; index++)
    if (Tree->Next_Node[index])
      Afisare_ARBORE (Tree->Next_Node[index], fisier_iesire, n);
}

/*Distrugerea arborelui (pentru problema 1/problema 2)*/
void
Eliberare_Memorie (GenericTree * Tree)
{
  int index, index_1;
  for (index = 1; index <= Tree->muchie; index++)
    if (Tree->Next_Node[index])
      Eliberare_Memorie (Tree->Next_Node[index]);
  for (index_1 = 1; index_1 <= 3; index_1++)
    free (Tree->gametable[index_1]);
  free (Tree->gametable);
  if (Tree->muchie != 0)
    free (Tree->Next_Node);
  free (Tree);
}

/*Functia de afisare pentru problema 2*/
void
Afisare_ARBORE_TF (GenericTree * Tree, FILE * fisier_iesire, int n)
{
  int index, index_1;
  for (index_1 = 1; index_1 <= n - Tree->muchie; index_1++)
    /*Identare corespunzatoare */
    fprintf (fisier_iesire, "\t");
  fprintf (fisier_iesire, "%c\n", Tree->caracter);
  for (index = 1; index <= Tree->muchie; index++)
    if (Tree->Next_Node[index])
      Afisare_ARBORE_TF (Tree->Next_Node[index], fisier_iesire, n);
}
