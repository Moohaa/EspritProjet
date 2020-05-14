#include "defs.h"
#include "personnage.h"
#include "ennemies.h"

typedef struct saveFile
{
    Personnage personnage;
    Ennemi ennemi;
    Ennemi ennemi2;
    int posX;
    int score;
    int vies;
} SaveFile;

void loadVars();
void SaveVars();