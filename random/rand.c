#include "rand.h"

void setStarCoord(noaction_t* noact)
{
    int count;

    #define LEFTSKYBORDER noact->border->border[borderLeft].w
    #define RIGHTSKYBORDER noact->border->border[borderRight].x
    #define UPSKYBORDER noact->border->border[borderUp].y +\
                        noact->border->border[borderUp].h
    #define DOWNSKYBORDER noact->border->border[borderDown].y

    for (count = 0; count < fastStarMax; ++count)
    {
        noact->sky->fast[count].x = getRand(LEFTSKYBORDER, RIGHTSKYBORDER);
        noact->sky->fast[count].y = getRand(UPSKYBORDER, DOWNSKYBORDER);
        noact->sky->fast[count].w = noact->sky->starTexture->objRect->w;
        noact->sky->fast[count].h = noact->sky->starTexture->objRect->h;
    }

    for (count = 0; count < slowStarMax; ++count)
    {
        noact->sky->slow[count].x = getRand(LEFTSKYBORDER, RIGHTSKYBORDER);
        noact->sky->slow[count].y = getRand(UPSKYBORDER, DOWNSKYBORDER);
        noact->sky->slow[count].w = noact->sky->starTexture->objRect->w;
        noact->sky->slow[count].h = noact->sky->starTexture->objRect->h;
    }
    #undef LEFTSKYBORDER
    #undef RIGHTSKYBORDER
    #undef UPSKYBORDER
    #undef DOWNSKYBORDER
}

int getRand(int a, int b)
{
    return (a + rand()%(b - a + 1));
}
