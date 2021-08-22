#ifdef _WIN32 /*define o comando de limpar a tela com base no Sistema Operacional.*/
#define CLEAR "cls"
#define IS_WINDOWS 1
#else
#define CLEAR "clear"
#define IS_WINDOWS 0
#endif

typedef struct Info_Est
{
    int voterCard;
    char name[50];
    int hasVoted;
    int vote;
    int qntdVotes;
} Info;

typedef struct Node_Est
{
    Info *info;
    struct Node_Est *left;
    struct Node_Est *right;
} Node;

Node *titleTree;
Node *voteTree;

// menu function
void showMenu();

// tree functions
void makeEmptyTree(Node **);
int insertOnTree(Node **, Info *);
Info *search(Node *, int);
int removeFromTree(Node **, Info *);
void next(Node **, Node *);
void inOrder(Node *);
int treeIsEmpty(Node *);
void resetData(Node **root);
int getNumberOfNodes(Node *);
void freeTree(Node *);

// info about people
Info *addNewPerson();

// extra functions
void copyTreeToArray(Node *, Info *, int *);
void sortArrayByNumberOfVotes(Info *, int);
void cleanScreen();
void pauseExecution();