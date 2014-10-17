#include "header.h"
#include "cell2d4_agent_header.h"
#include "cell2d4_options.h"
#include "functions_helper.h"

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
    
    /* temp vars  */
    int type2;
    fourpoints points2 = POINTS;	
	
    //choose randomly if this cell should move
    if (decide_if_cell_should_move() !=0)
    {
		
        //choose which of the corners should move and  move this corner
        choose_and_move_one_of_4_corners(points2);
		
	    //calculate deltaH for the inside of the cell
        double deltaH_inside = calculate_deltaH_inside(points2,POINTS);


	    //calculate deltaH for the interactions with its neighbours
		
	 //    /* Loop through all messages */
	 //    START_CELLPOSITION_MESSAGE_LOOP
		// /* NOTE: this IF condition is not really required due to filters */
		// if((cellposition_message->id != id)) 
		// {
		//     points2 = cellposition_message->points;
		//     type2 = cellposition_message->type;

		    
			
		// }
	 //    FINISH_CELLPOSITION_MESSAGE_LOOP
		
	    // add up all delta-energies
		
	    // decide if delta-energy is positive ... if the whole energy decreases
	    /* write new position to agent memory  or go back to old position */
	    //set_points(points_temp);
    }
    return 0; 
}
