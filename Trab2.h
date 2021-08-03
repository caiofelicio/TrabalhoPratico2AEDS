typedef struct Info_Est
{
    int voterCard;
    char name[50];
    int vote;
} Info;

typedef struct Node_Est
{
    Info *info;
    struct Node_Est *left;
    struct Node_Est *right;
} Node;

Node *titleTree;
Node *voteTree;

void makeEmptyTree(Node **);
void freeTree(Node *);
void addNewVoterCard();