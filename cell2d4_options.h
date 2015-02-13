/* Cell options for cell2d4 - 4corners
 * cof - cell option field [celltype]
 *
 * */


#define CO_TARGET_VOLUME 2
#define N_CORNERS 6
#define n_cell_types 3

double cof_move_step_size[] = {0.01,0.01,0.01,0.01};
int cof_move_random_extra_probability[] = {10,10,10};

int cof_percent_of_cells_that_should_move_in_one_ts = 70;

int cof_volume_do_calc[] = {1,1,1};
double cof_volume_target[] = {6.0,4.5,4.5};
double cof_volume_alpha[] = {1.0,2.0,1.0};

int cof_surface_do_calc[] = {1,1,1};
double cof_surface_target[] = {6.0,6.0,6.0};
double cof_surface_alpha[] = {1.0,1.0,3.0};

int cof_convex_do_calc[] = {1,1,1};
//double cof_convex_alpha[] = {2.0,2.0,2.0};

int cof_contact_do_calc[] = {1,1,1};
double cof_contact_alpha[] = {15.0,15.0,9.0};
double cof_contact_distance[] = {0.4,0.4,0.1};
double cof_contact_medium[] = {-1.0,2.0,1.0};
double cof_contact_depth[] = {0.2,0.2,0.2};
double cof_contact_edge[n_cell_types][n_cell_types] = {{-4.5,-2.0,-1.0},{-2.0,-4.5,0.5},{-1.0,0.0,-5.0}};
double cof_contact_intersection[n_cell_types][n_cell_types] = {{180.0,180.0,52.0},{180.0,180.0,52.0},{52.0,52.0,52.0}};

double cof_cell_signal[n_cell_types][n_cell_types] = {{-1.0,2.0,0.0},{0.0,-2.0,0.0},{-1.0,2.0,0.0}};

int cof_death_rate[] = {31000,11000,5500};
int cof_divide_rate[] = {30000,10000,5000};