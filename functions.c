#include "header.h"
#include "cell2d4_agent_header.h"
#include "cell2d4_options.h"
#include "functions_helper.h"
#include "signalagent_agent_header.h"
#include "functions_signal.c"

#define kr 0.1 /* Stiffness variable for repulsion */
#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


int outputcellposition()
{
    /* read agent memory */
    int id = get_id();
    int type = get_type();
    /* add message to "location" board  (id, range, x, y, z) */
    add_cellposition_message(id, CORNERS, type);

    //printf("Type: %d, id: (%3d - ), \n", TYPE, ID);
    return 0;  /* remain alive. 1 = death */
}


int movecornersandcalculateenergy()
{
    double corners2[(N_CORNERS * 2)];
    int i=0;
    double deltaH=0.0, deltaH_interaction, deltaH_inside;
    int moved_corner;

	
    //choose randomly if this cell should move
    if (decide_if_cell_should_move() !=0)
    {
        do {
            i++;
            copy_array_to_array(CORNERS,corners2,N_CORNERS*2);

            //choose which of the corners should move and  move this corner
            //print_positions(points2);
            moved_corner = choose_and_move_one_of_4_corners(corners2);
            //print_positions(points2);

            //calculate deltaH for the inside of the cell
            deltaH_inside = calculate_deltaH_inside(corners2,CORNERS);
            //printf("deltatH: %f\n",  deltaH_inside);
            deltaH_interaction = calculate_deltaH_interactions(corners2,CORNERS,moved_corner);
            //printf("-------- deltaHinside: %f | deltaH_interaction: %f  \n ", deltaH_inside,deltaH_interaction);
            //calculate deltaH for the interactions with its neighbours

            // add up all delta-energies
            deltaH = deltaH_inside + deltaH_interaction;
            //printf("Type: %d, id: %d, deltatH: %f\n", TYPE, ID, deltaH);
            if (deltaH <= 0)
            {
                copy_array_to_array(corners2,CORNERS,N_CORNERS*2);
            }

            // decide if delta-energy is negative ... if the whole energy decreases
            // write new position to agent memory  or go back to old position //
            //set_points(points_temp);
        } while((i<4) && (deltaH > 0.0));
        //printf("Type: %d, id: %d, deltatH: %5.3f (%4.2f, %4.2f) \n", TYPE, ID, deltaH, deltaH_inside,deltaH_interaction);

    }
    //printf("-------------------------donedone -------------i: %d \n ",i );

    //random_extra_movement();

    return 0; 
}

int cell_functions()
{

    //stochastic_
    asymettric_stem_cell_division(cof_divide_rate[TYPE]);
    //stochastic_stem_cell_division(cof_divide_rate[TYPE]);
    //divide_cell_random(cof_divide_rate[TYPE]);

    //random cell-death:
    if ((rand() % cof_death_rate[TYPE]) ==0)
    {
        printf("        -celldeath.  .\n");
        //return 1;
    }
    //

    //create a signal-agent:
    if ((rand() % 5000000) ==0)
    {
        //printf("        -add signalagent...  .\n");
        //add_signalagent_agent(ID,TYPE,X,Y,AMOUNT,FADE,SPEED,REMAINDERLIFE);
        int ic = rand() % N_CORNERS; //choose a random corner
        //add_signalagent_agent(rand(),TYPE,CORNERS[ic*2],CORNERS[ic*2+1],2.0,1.0,0.4,100);
    }
    

    return 0;
}


int pushcells()
{

    //printf("-----------------------%d--------------",get_first_repulsion_message());
    //printf("Type: %d, id: (%3d - ww),------------------------------ \n", TYPE, ID);
    //printf("Type: %d, id: (%3d - ), \n", TYPE, ID);

    //printf("----wwwwwwwwwwwwwwwwwww pushcells -------------i:  \n " );
    double pushsum[2] = {0};

    for(repulsion_message = get_first_repulsion_message(); repulsion_message != NULL; repulsion_message = get_next_repulsion_message(repulsion_message))
    {
        //printf("Type: %d, id: (%3d - %3d), (%6.3f, %6.3f) \n", TYPE, ID,repulsion_message->receiver_id,repulsion_message->mtv[0],repulsion_message->mtv[1]);
        pushsum[0] += repulsion_message->mtv[0];
        pushsum[1] += repulsion_message->mtv[1];
    }
    pushsum[0] *= 0.33;
    pushsum[1] *= 0.33;
    //printf("----wwwwwwwwwwwwwwwwwww pushcells oooooooooooooooooooooooo end-----i:  \n " );

    move_all_corners_by_vector(CORNERS,pushsum);
    //printf("----wwwwwwwwwwwwwwwwwww pushcells oooooooooooooooooooooooo end-end-----i:  \n " );
    return 0;
}
