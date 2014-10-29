/* Cell options for cell2d4 - 4corners
 * cof - cell option field [celltype]
 *
 * */


#define CO_TARGET_VOLUME 2
#define N_CORNERS 4
#define n_cell_types 3

double cof_move_step_size[] = {0.06,0.07,0.03,0.04};

int cof_percent_of_cells_that_should_move_in_one_ts = 80;

int cof_volume_do_calc[] = {1,1,1};
double cof_volume_target[] = {4.0,1.3,2.0};
double cof_volume_alpha[] = {8.0,3.0,2.0};

int cof_surface_do_calc[] = {1,1,1};
double cof_surface_target[] = {8.0,14.1,6.0};
double cof_surface_alpha[] = {0.5,0.4,2.0};

int cof_convex_do_calc[] = {1,1,1};
//double cof_convex_alpha[] = {2.0,2.0,2.0};

int cof_contact_do_calc[] = {1,1,1};
double cof_contact_alpha[] = {4.0,4.0,4.0};
double cof_contact_distance[] = {0.1,0.1,0.1};
double cof_contact_medium[] = {1.11,1.1,2.0};
double cof_contact_depth[] = {0.15,0.15,0.2};
double cof_contact_edge[n_cell_types][n_cell_types] = {{-1.0,-1.0,2.0},{-2.5,-2.5,2.0},{2.0,2.0,2.0}};
double cof_contact_intersection[n_cell_types][n_cell_types] = {{180.0,180.0,52.0},{180.0,180.0,52.0},{52.0,52.0,52.0}};
