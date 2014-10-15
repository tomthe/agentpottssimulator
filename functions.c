#include "header.h"

#define kr 0.1 /* Stiffness variable for repulsion */
#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


int outputcellposition()
{
    /* read agent memory */
    int id = get_id();
    double points = get_points()
    int type = get_type()
    /* add message to "location" board  (id, range, x, y, z) */
    add_location_message(id, points, type);

    return 0;  /* remain alive. 1 = death */
}


int movecells()
{
    /* read agent memory */
    int id = get_id();
    double points[] = get_points();
    int type = get_type();

    double points_temp[] = points;    
	
    //  
    /* temp vars  */
    double points2;
    int id2,type2;
	
    /* Loop through all messages */
    START_LOCATION_MESSAGE_LOOP
        /* NOTE: this IF condition is not really required due to filters */
        if((location_message->id != id)) 
        {
            points2 = location_message->points;
            type2 = location_message->type;

            core_distance = distance(x1,y1,x2,y2);
            
		///
		
		
        }
    FINISH_LOCATION_MESSAGE_LOOP
    
    /* write forces to agent memory */
    set_points(points_temp);
    
    return 0; 
}
