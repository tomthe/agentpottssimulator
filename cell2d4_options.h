/* Cell options for cell2d4 - 4corners
 * cof - cell option field [celltype]
 *
 * */


#define CO_TARGET_VOLUME 2
#define N_CORNERS 20
#define n_cell_types 3

double cof_move_step_size[] = {0.04,0.04,0.04,0.01};
int cof_move_random_extra_probability[] = {10,10,10};

int cof_percent_of_cells_that_should_move_in_one_ts = 70;

int cof_volume_do_calc[] = {1,1,1};
double cof_volume_target[] = {5.0,2.0,4.5};
double cof_volume_alpha[] = {1.0,5.0,1.0};

int cof_surface_do_calc[] = {1,1,1};
double cof_surface_target[] = {4.0,2.0,6.0};
double cof_surface_alpha[] = {2.0,1.0,3.0};

int cof_convex_do_calc[] = {0,0,1};
//double cof_convex_alpha[] = {2.0,2.0,2.0};
int cof_straight_hull_do_calc[] = {1,1,1};
double cof_straight_hull_alpha[] = {100.0,5.0,1};

int cof_contact_do_calc[] = {1,1,1};
double cof_contact_alpha[] = {25.0,25.0,9.0};
double cof_contact_distance[] = {0.4,0.4,0.1};
double cof_contact_medium[] = {2.0,3.0,1.0};
double cof_contact_depth[] = {0.2,0.2,0.2};
double cof_contact_edge[n_cell_types][n_cell_types] = {{-45.5,5.0,-1.0},{1.0,-19.5,0.5},{-1.0,0.0,-5.0}};
double cof_contact_intersection[n_cell_types][n_cell_types] = {{180.0,30.0,52.0},{30.0,180.0,52.0},{52.0,52.0,52.0}};

int cof_signal_release_propab[] = {-1,-1,-1,-1};
double cof_cell_signal[n_cell_types][n_cell_types] = {{-10.0,0.0,0.0},{0.0,-10.0,0.0},{-1.0,2.0,0.0}};

//death rate for each cell-type. -1: no death; n: death after ca n timesteps
long int cof_death_rate[] = {-1,-1,-1};
long int cof_divide_rate[] = {7000,-1,-1};