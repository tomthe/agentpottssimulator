#include "header.h"
#include "cell2d4_agent_header.h"

#define kr 0.1 /* Stiffness variable for repulsion */
#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


int outputcellposition()
{
    /* read agent memory */
    int id = get_id();
    int type = get_type();
    /* add message to "location" board  (id, range, x, y, z) */
    add_cellposition_message(id, POINTS, type);

    return 0;  /* remain alive. 1 = death */
}


int movecells()
{
    /* read agent memory */
    int id = get_id();
    int type = get_type();
    
    int changedp = 0; //or 1;2;3
    double changedx,changedy;
    fourpoints points2;
	
	
    printf("Hallo Welt\n");printf("Hallo Welt %d", POINTS.p1.x);
    //  
    /* temp vars  */
    int id2,type2;
	
    /* Loop through all messages */
    START_CELLPOSITION_MESSAGE_LOOP
        /* NOTE: this IF condition is not really required due to filters */
        if((cellposition_message->id != id)) 
        {
            points2 = cellposition_message->points;
            type2 = cellposition_message->type;

            
		
        }
    FINISH_CELLPOSITION_MESSAGE_LOOP
    
    /* write forces to agent memory */
    //set_points(points_temp);
    
    return 0; 
}
