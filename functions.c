#include "header.h"

#define kr 0.1 /* Stiffness variable for repulsion */
#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


int outputdata()
{
    /* read agent memory */
    int id = get_id();
    double x = get_x(), y = get_y();
    
    /* add message to "location" board  (id, range, x, y, z) */
    add_location_message(id, x, y);

    return 0;  /* remain alive. 1 = death */
}


int inputdata()
{
    /* read agent memory */
    int id = get_id();
    double x1 = get_x(), y1 = get_y();
    double diameter = get_radius() * 2;

    /* temp vars  */
    double p, x2, y2;
    double core_distance;
    double fx = 0, fy = 0;

    /* Loop through all messages */
    START_LOCATION_MESSAGE_LOOP
        /* NOTE: this IF condition is not really required due to filters */
        if((location_message->id != id)) 
        {
            x2 = location_message->x;
            y2 = location_message->y;

            core_distance = distance(x1,y1,x2,y2);
            
            if(core_distance < diameter)
            {
                p = kr * diameter / core_distance;
                
                /* accumulate forces */
                fx += (x1 - x2) * p; 
                fy += (y1 - y2) * p; 
            }
        }
    FINISH_LOCATION_MESSAGE_LOOP
    
    /* write forces to agent memory */
    set_fx(fx);
    set_fy(fy);
    
    return 0; 
}


int move()
{
    /* update position based on accumulated forces */
    set_x( get_x() + get_fx() );
    set_y( get_y() + get_fy() );
    
    return 0;
}
