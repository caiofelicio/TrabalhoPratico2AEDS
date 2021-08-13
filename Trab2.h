#ifdef _WIN32 /*define o comando de limpar a tela com base no Sistema Operacional.*/
#define CLEAR "cls"
#define IS_WIN 1
#else
#define CLEAR "clear"
#define IS_WIN 0
#endif
#define MAX_CAND 3

typedef struct
{
    char nomeCandidato[50];
    char partido[7];
    int ID;
    int qntdVotos;
} Candidato;

typedef struct Info_Est
{
    int voterCard;
    char name[50];
    int vote;
    // int id;
} Info;

typedef struct Node_Est
{
    Info *info;
    struct Node_Est *left;
    struct Node_Est *right;
} Node;

Node *titleTree;
Node *voteTree;
Candidato candidatos[3];

// menu function
void showMenu();

// tree functions
void makeEmptyTree(Node **);
int insertOnTree(Node **, Info *);
Info *search(Node *, Info *);
int removeFromTree(Node **, Info *);
void next(Node **, Node *);
void inOrder(Node *);
int treeIsEmpty(Node *);
void freeTree(Node *);

// info about people
Info *addNewPerson();
int addCand(int);
void printCands(int);
void printParcial(int);

// extra functions
void cleanScreen();
void pauseExecution();