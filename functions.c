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
    add_cellposition_message(id, CORNERS, type);

    return 0;  /* remain alive. 1 = death */
}


int movecells()
{
    double corners2[(N_CORNERS * 2)];
    copy_array_to_array(CORNERS,corners2,N_CORNERS*2);
    //print_positions(corners2);
	
    //choose randomly if this cell should move
    if (decide_if_cell_should_move() !=0)
    {
		
        //choose which of the corners should move and  move this corner
        //print_positions(points2);
        choose_and_move_one_of_4_corners(corners2);
        //print_positions(points2);

        //calculat e deltaH for the inside of the cell
        double deltaH_inside = calculate_deltaH_inside(corners2,CORNERS);
        //printf("deltatH: %f\n",  deltaH_inside);
        double deltaH_interaction = calculate_deltaH_interactions(corners2,CORNERS);
        //calculate deltaH for the interactions with its neighbours
        printf("deltaH_interaction: %5.2f; dH_inside: %5.2f\n middle: %4.2f \n", deltaH_interaction,deltaH_inside);
     //      Loop through all messages
     //    START_CELLPOSITION_MESSAGE_LOOP
        //  NOTE: this IF condition is not really required due to filters
        // if((cellposition_message->id != id))
        // {
        //     points2 = cellposition_message->points;
        //     type2 = cellposition_message->type;


        // }
     //    FINISH_CELLPOSITION_MESSAGE_LOOP

        // add up all delta-energies
        double deltaH = deltaH_inside + deltaH_interaction;
        //printf("Type: %d, id: %d, deltatH: %f\n", TYPE, ID, deltaH);
        if (deltaH <= 0)
        {
            copy_array_to_array(corners2,CORNERS,N_CORNERS*2);
        }

        // decide if delta-energy is negative ... if the whole energy decreases
        // write new position to agent memory  or go back to old position //
        //set_points(points_temp);
    }
    return 0; 
}
