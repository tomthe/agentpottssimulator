/* Cell options for cell2d4 - 4corners
 * cof - cell option field [celltype]
 *
 * */


#define CO_TARGET_VOLUME 2
#define N_CORNERS 6
#define n_cell_types 3

double cof_move_step_size[] = {0.04,0.04,0.03,0.04};
int cof_move_random_extra_probability[] = {2,1,0};

int cof_percent_of_cells_that_should_move_in_one_ts = 60;

int cof_volume_do_calc[] = {1,1,1};
double cof_volume_target[] = {6.5,3.25,2.0};
double cof_volume_alpha[] = {1.0,0.4,2.0};

int cof_surface_do_calc[] = {1,1,1};
double cof_surface_target[] = {6.5,6.5,6.0};
double cof_surface_alpha[] = {1.1,1.1,2.0};

int cof_convex_do_calc[] = {1,1,1};
//double cof_convex_alpha[] = {2.0,2.0,2.0};

int cof_contact_do_calc[] = {1,1,1};
double cof_contact_alpha[] = {9.0,9.0,4.0};
double cof_contact_distance[] = {0.4,0.4,0.1};
double cof_contact_medium[] = {1.0,6.0,2.0};
double cof_contact_depth[] = {0.3,0.3,0.2};
double cof_contact_edge[n_cell_types][n_cell_types] = {{-2.5,-1.25,2.0},{-1.25,-2.5,2.0},{2.0,2.0,2.0}};
double cof_contact_intersection[n_cell_types][n_cell_types] = {{180.0,180.0,52.0},{180.0,180.0,52.0},{52.0,52.0,52.0}};
