#include "saveHander.h"

void loadVars()
{
    SaveFile savefile;
    FILE *file = fopen("save", "rb");
    if (file != NULL)
        if (file != NULL)
        {
            fread(&savefile, sizeof(SaveFile), 1, file);
            fclose(file);
        }
    offsetBG = savefile.posX;
    score = savefile.score;
    personnage = savefile.personnage;
    vies = savefile.vies;
}
void SaveVars()
{
    SaveFile savefile;
    savefile.posX = offsetBG;
    savefile.score = score;
    savefile.vies = vies;
    savefile.personnage = personnage;
    FILE *file = fopen("save", "wb");
    if (file != NULL)
    {
        fwrite(&savefile, sizeof(SaveFile), 1, file);
        fclose(file);
    }
}