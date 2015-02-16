#include "signalagent_agent_header.h"
//#include "header.h"
//#include "functions_helper.h"

#define kr 0.1 /* Stiffness variable for repulsion */
#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


int outputsignalposition()
{
    /* read agent memory */
    //....
    /* add message to "location" board  (id, range, x, y, z) */
    //printf("        -post signal position.  %d, %d, xy:(%f,%f), %f,.\n",SID,STYPE,X,Y,AMOUNT);
    add_signalposition_message(SID, STYPE,X,Y,AMOUNT);

    //printf("Type: %d, id: (%3d - ), \n", TYPE, ID);
    return 0;  /* remain alive. 1 = death */
}


int moveandadjustsignal()
{

    //adjust the signal-agent variables:

    //remaining lifespan:
    REMAINDERLIFE--;
    if (REMAINDERLIFE<=0)
    {
        return 1;
    }

    //position:

    double dx = rand_double_m_to_n(-(SPEED),SPEED);
    double dy = rand_double_m_to_n(-(SPEED),SPEED);
    X += dx;
    Y += dy;

    //intensity/amount:
    AMOUNT *= FADE;

    return 0; 
}
