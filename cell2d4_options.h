/* Cell options for cell2d4 - 4corners
 * cof - cell option field [celltype]
 *
 * */


#define CO_TARGET_VOLUME 2
#define N_CORNERS 10
#define n_cell_types 3
//type0:red, type1:green

#define cof_use_hamiltonian 1

#define cof_T 0.5

#define r 6.8

double cof_move_step_size[] = {0.5,0.5,0.0,0.01};
int cof_move_random_extra_probability[] = {10,10,0};
double cof_push_alpha[] = {0.02,0.02,0.0};
double cof_attraction_alpha[n_cell_types][n_cell_types] ={{0.0,0.0,0.0}, {0.00,0.0,0.0},{0.0,0.0,0.0}};

int cof_percent_of_cells_that_should_move_in_one_ts[] = {40,40,50};

int cof_volume_do_calc[] = {1,1,1};
double cof_volume_target[] = {5.0,5.0,0.5};
double cof_volume_alpha[] = {10.0,10.0,1.0};

int cof_surface_do_calc[] = {1,1,0};
double cof_surface_target[] = {9.0,9.0,6.0};
double cof_surface_alpha[] = {2.0,3.0,3.0};

int cof_convex_do_calc[] = {1,1,1};
//double cof_convex_alpha[] = {2.0,2.0,2.0};
int cof_straight_hull_do_calc[] = {1,1,1};
double cof_straight_hull_alpha[] = {10.0,150.0,1};

int cof_contact_do_calc[] = {1,1,1};
double cof_contact_alpha[] = {30.0,30.0,9.0};
double cof_contact_distance[] = {0.4,0.4,0.1}; //deprecated
double cof_contact_medium[] = {2.0,2.0,1.0};
double cof_contact_depth[] = {0.6,0.6,0.6,0.6};
double cof_contact_edge[n_cell_types][n_cell_types] = {{-26,-11.0,-5.0},{-11.0,-26,55},{0.0,0.0,0.0}};
double cof_contact_intersection[n_cell_types][n_cell_types] = {{25.0,35.0,10.0},{45.0,35.0,10.0},{52.0,52.0,52.0}};

int cof_signal_release_propab[] = {-1,-1,-1,-1};
double cof_signal_speed[] = {0.3,0.2,0.3};
int cof_signal_maxage[] = {200,250,3};
double cof_cell_signal[n_cell_types][n_cell_types] = {{-20.0,-1.0,0.0},{-1.0,-20.0,0.0},{-1.0,2.0,0.0}};

//death rate for each cell-type. -1: no death; n: death after ca n timesteps
long int cof_death_rate[] = {-1,-1,-1};
long int cof_divide_rate[] = {-1,-1,-1};
