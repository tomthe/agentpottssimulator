/*
 *
 * */
#include "sat_intersection_test.h"
#include "line_intersection.h"
//#include "cell2d4_options.h"

#define sqdistance(x1,y1,x2,y2) (((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))


void copy_array_to_array(double *array1, double *array2, int n)
{
    for(int i=0; i<n;i++)
    {
        array2[i] = array1[i];
    }
}

double abs_tom(double num)
{
    if (num < 0){
        return - num;
    }
    return num;
}

int decide_if_cell_should_move()
{
    if ((rand() % 100) < cof_percent_of_cells_that_should_move_in_one_ts[TYPE]){
        //move
        return 1;
    } else {
        //dont move
        return 0;
    }
}

int print_positions(double corners[])
{
    printf("positions: (%4.2f,%4.2f); (%4.2f,%4.2f); (%4.2f,%4.2f); (%4.2f,%4.2f); \n", corners[0],corners[1],corners[2],corners[3],corners[4],corners[5],corners[6],corners[7]);
    return 0;
}

double rand_double_m_to_n(double m, double n)
{
    return m + (rand() / (RAND_MAX / (n-m)));
}

/** Return a random Number from a Normal-Distribution with mu and sigma..
*
*/
double rand_normal_distr(double mu, double sigma)
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}

/** move a corner in a random direction
 *  */
int choose_and_move_one_of_4_corners(double *corners)
{
    double dx = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    double dy = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    int r = rand() % N_CORNERS; //int between 0 and N_CORNERS (=6)
    corners[r*2] += dx; //x
    corners[r*2+1] += dy;
    //printf("move corner: dx: %f, dy: %f;\n", dx,dy);
    return r;
}

/** move 1...N_CORNERS/2 corners in the same random direction
 *
 * not completly anisotrop!
 */
int choose_and_move_some_corners(double *corners)
{

    double dx = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    double dy = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    int start_corner = rand() % N_CORNERS;
    int number_of_corners = rand() % (N_CORNERS/2);
    int middle_point = (start_corner + number_of_corners/2) % N_CORNERS;
    int i_corner;
    double factor = 0.0;
    for(int i=0;i<number_of_corners;i++)
    {
        if (i<=number_of_corners/2){
            factor += 2.0/(float)number_of_corners;
        } else {
            factor -= 2.0/(float)number_of_corners;
        }
        i_corner = (i + start_corner) % N_CORNERS;
        corners[i_corner*2] += dx * factor; 
        corners[i_corner*2+1] += dy;
    }
    return middle_point; //moved_corner: the one in the middle
}

void get_divide_cell_new_corner_positions(double corners_old[],double corners_new1[],double corners_new2[])
{
    copy_array_to_array(corners_old,corners_new1,N_CORNERS*2);
    copy_array_to_array(corners_old,corners_new2,N_CORNERS*2);


    double d0x,d0y, dmx,dmy,x,y;
    int km,i_corner1,i_corner2;
    //define the new point d0: halfway between point 0 and max:
    d0x = (corners_old[0] + corners_old[(N_CORNERS-1)*2]) / 2.0;
    d0y = (corners_old[0+1] + corners_old[(N_CORNERS-1)*2+1]) /2.0;


    //define the new point dm: on opposit side of d0:
    if (N_CORNERS%2==0)
    {
        //printf("\ndivide_cell! inside ncorners is even");
        km = N_CORNERS / 2;
        dmx = (corners_old[(km-1)*2] + corners_old[(km)*2]) / 2.0;
        dmy = (corners_old[(km-1)*2+1] + corners_old[(km)*2+1]) / 2.0;
/*
        corners_new1[(N_CORNERS/2)*2] =dmx;
        corners_new1[(N_CORNERS/2)*2+1] =dmy;
        corners_new1[(N_CORNERS-1)*2] =d0x;
        corners_new1[(N_CORNERS-1)*2+1] =d0y;
*/
        
        int n_middle_points = N_CORNERS / 2; //(N_CORNERS-1) - (N_CORNERS/2+1);
        for(int i=0; i<n_middle_points;i++)
        {
            i_corner2 = i;
            i_corner1 = N_CORNERS - 1 - i;

            x = d0x + (dmx-d0x) * (float)(i) / (float)(n_middle_points-1);
            y = d0y + (dmy-d0y) * (float)(i) / (float)(n_middle_points-1);
            // (N_CORNERS/2+1) + i;
            corners_new1[i_corner1*2] = x;
            corners_new1[i_corner1*2+1] = y;
            corners_new2[i_corner2*2] = x;
            corners_new2[i_corner2*2+1] = y;
        }
    }
    else
    {
        //not implemented yet for odd numbers of corners...!!todo
        km = N_CORNERS / 2;
        dmx = corners_old[(km)*2];
        dmy = corners_old[(km)*2+1];
    }
}

void get_middle_point(double corners[], double middle_point[])
{
    middle_point[0] = 0.0;
    middle_point[1] = 0.0;

    for (int i_corner=0; i_corner<N_CORNERS;i_corner++)
    {
        middle_point[0] += corners[i_corner*2];
        middle_point[1] += corners[i_corner*2+1];
    }

    middle_point[0] = middle_point[0] / N_CORNERS;
    middle_point[1] = middle_point[1] / N_CORNERS;
}

void divide_cell(double corners[], int cell_type)
{    
    //print_positions(corners);
    double corners1[N_CORNERS*2],corners2[N_CORNERS*2];
    get_divide_cell_new_corner_positions(corners,corners1,corners2);
    //print_positions(corners1);
    //print_positions(corners2);
    copy_array_to_array(corners1,CORNERS, N_CORNERS*2);
    int id = rand();
    double middle_point[2];
    get_middle_point(corners,middle_point);
    AGE=0;
    add_cell2d4_agent(id, cell_type, corners2,middle_point[0],middle_point[1],0);
}

int divide_cell_random(int propability_fraction)
{
    if ((rand() % propability_fraction)==0)
        {
            printf("\ndivide_cell!  .start");
            divide_cell(CORNERS,TYPE);
            return 1;
        }
    return 0;
}


int asymettric_stem_cell_division(int propability_fraction){
    if (TYPE==0)
    {

        if ((rand() % propability_fraction)==0)
            {
                printf("\ndivide_cell!  .start");
                divide_cell(CORNERS, 1);
                return 1;
            }
        return 0;

    }
    return 0;
}

int stochastic_stem_cell_division(int propability_fraction){
    if (TYPE==0)
    {

        if ((rand() % propability_fraction)==0)
            {
                if(rand() % 2 == 1){
                    //both child-cells become stem-cells:
                    TYPE = 0;
                    divide_cell(CORNERS, 0);
                    printf("\ndivide_cell!  . 2 stem-cells");
                }else{
                    //both child-cells become differentiated-cells:
                    TYPE = 1;
                    divide_cell(CORNERS, 1);
                    printf("\ndivide_cell!  . 2 differentiated-cells");
                }
                return 1;
            }
        return 0;
    }
    return 0;
}

int random_extra_movement()
{
    if ((rand() % 100) < cof_move_random_extra_probability[TYPE]){
        choose_and_move_one_of_4_corners(CORNERS);
        choose_and_move_one_of_4_corners(CORNERS);
    }
    return 1;
}

int is_left_curve_old(double *a, double *c, double *b){
    ///true if ( you go from a --> b --> c; you turn left on point b
    ///Where a = line point 1; c = line point 2; b = point to check against.

    if(((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) < 0){
        return 1;
    }else{
        return 0;
    }
}
int is_left_curve(double *corners,int a,int b, int c){
    //true if ( you go from a --> b --> c; you turn left on point b
    //Where a = line point 1; c = line point 2; b = point to check against.
    if(((corners[b*2] - corners[a*2])*(corners[c*2+1] - corners[a*2+1]) - (corners[b*2+1] - corners[a*2+1])*(corners[c*2] - corners[a*2])) > 0){
        return 1;
    }else{
        return 0;
    }
}

/**
 * deprecated
 */
double calc_H_convex_4corners(double *corners)
{

    //check if the 2. point lies right of the line between point 1 and 2:
    if (is_left_curve(corners,0,1,2)!=0){
        if (is_left_curve(corners,1,2,3)!=0){
            if (is_left_curve(corners,2,3,0)!=0){
                if (is_left_curve(corners,3,0,1)!=0){
                    //yes, every corner is convex
                    return 0.0;
                }
            }
        }
    }
    //printf("  at least one corner is not convex!\n");
    //at least one corner is not convex
    return 200.0;
}



/**
 * check if the cell is convex by iterating over each adjacent corner triplet
 * if the
 */
double calc_H_convex_strict(double *corners)
{
    int i,b,c;
    for(i=0;i<N_CORNERS;i++)
    {
        // i->corner 0; b ist corner 2 and c is corner number 3.
        b=i+1; c=i+2;

        if(c==N_CORNERS){
           c=0;
        } else if(b==N_CORNERS){
            b=0;c=1;
        }
        if (is_left_curve(corners,i,b,c)==0)
        {
            //printf("  at least one corner is not convex!\n");
            //at least one corner is not convex
            //convex: always right curve. so here we are wrong:
            return 200.0;
        }
    }
    return 0.0;
}

/**
 * check if the cell is convex by iterating over each adjacent corner triplet
 * if the
 */
double calc_H_convex(double *corners)
{
    int i,b,c;
    int n_concave=0;
    for(i=0;i<N_CORNERS;i++)
    {
        // i->corner 0; b ist corner 2 and c is corner number 3.
        b=i+1; c=i+2;

        if(c==N_CORNERS){
           c=0;
        } else if(b==N_CORNERS){
            b=0;c=1;
        }
        if (is_left_curve(corners,i,b,c)==0)
        {
            //printf("  at least one corner is not convex!\n");
            //at least one corner is not convex
            //convex: always right curve. so here we are wrong:
            n_concave += 1;
        }
    }
    return n_concave;
}

double calc_H_straight_hull_3_corners(double *corners,int a,int b, int c)
{
    double point_between[2];
    point_between[0] = (corners[a*2] + corners[c*2]) / 2.0;
    point_between[1] = (corners[a*2+1] + corners[c*2+1]) / 2.0;

    return sqdistance(point_between[0],point_between[1],corners[b*2],corners[b*2+1]);
}


double calc_H_straight_hull(double *corners)
{
    int i,b,c;
    double sum_straightness = 0.0;
    for(i=0;i<N_CORNERS;i++)
    {
        // i->corner 0; b ist corner 2 and c is corner number 3.
        b=i+1; c=i+2;

        if(c==N_CORNERS){
           c=0;
        } else if(b==N_CORNERS){
            b=0;c=1;
        }

        if (is_left_curve(corners,i,b,c)==0)
        {
            sum_straightness += 3 * calc_H_straight_hull_3_corners(corners,i,b,c);
        } else {
            sum_straightness += 0.8 * calc_H_straight_hull_3_corners(corners,i,b,c);
        }
    }
    return sum_straightness;
}

double calc_distance_2corners(double *corners, int i1,int i2)
{
    double dx = (corners[i2*2]-corners[i1*2]);
    double dy = (corners[i2*2+1]-corners[i1*2+1]);
    return sqrt(dx*dx + dy*dy);
}

double calc_distance_points(double *p1, double *p2)
{
    double dx = (p2[0]-p1[0]);
    double dy = (p2[0]-p1[1]);
    return sqrt(dx*dx + dy*dy);
}

double calc_distance_2d(double x1,double y1, double x2,double y2)
{
    double dx = (x2-x1);
    double dy = (y2-y1);
    return sqrt(dx*dx + dy*dy);
}


/**deprecated - use cals_surface_length with any number of corners
*/
double calc_surface_length_4corners(double *corners)
{
    double l = calc_distance_2corners(corners,0,1);
    l += calc_distance_2corners(corners,1,2);
    l += calc_distance_2corners(corners,2,3);
    l += calc_distance_2corners(corners,3,0);
    return l;
}

double calc_surface_length(double *corners)
{
/**
 *
 */
    int i,b;
    double l=0;
    for(i=0;i<N_CORNERS;i++)
    {
        // i->corner 0; b ist corner 2 
        b=i+1;
        if(b==N_CORNERS){
           b=0;
        }
        l += calc_distance_2corners(corners,i,b);
    }
    return l;
}

double calc_H_surface(double *corners)
{
    //always positive. near 0 -> better
    double surface = calc_surface_length(corners);
    double H = pow((surface - cof_surface_target[TYPE]), 2.0) * cof_surface_alpha[TYPE];
    //printf(" | surface: %f| ", surface);
    return H;
}

/* Xv - x-coordinates [x0,x1,x2,x3]
 * adapted from: http://www.mathopenref.com/coordpolygonarea2.html
 * */
double calculate_polygon_area(double Xv[], double Yv[], int num_points)
{
  double area = 0;         // Accumulates area in the loop
  int j = num_points-1;  // The last vertex is the 'previous' one to the first

  for (int i=0; i<num_points; i++)
    { area = area +  (Xv[j]+Xv[i]) * (Yv[j]-Yv[i]);
      j = i;  //j is previous vertex to i
    }
  return area/2;
}

/* calculate the area of the (convex/konkave...) Polygon, with the *corners as input
 * adapted from: http://www.mathopenref.com/coordpolygonarea2.html
 * */
double calculate_corners_area(double corners[])
{
    double area = 0;         // Accumulates area in the loop
    int j = N_CORNERS-1;  // The last vertex is the 'previous' one to the first

    for (int i=0; i<N_CORNERS; i++){ 
        area = area +  (corners[j*2]+corners[i*2]) * (corners[j*2+1]-corners[i*2+1]);
        j = i;  //j is previous vertex to i
    }
    return -area/2;    //negative because counterclockwise...
}

double calc_H_volume(double *corners)
{
    double area = calculate_corners_area(corners);
    double H = pow((cof_volume_target[TYPE] - area),2.0) * cof_volume_alpha[TYPE];
    //printf(" | area: %f |",area);
    return H;
}



double calculate_deltaH_inside(double *corners2, double *corners1)
{
    double deltaH = 0.0;
    double H1 = 0.0;
    double H2 = 0.0;

    double H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2,H_straight1,H_straight2;

    if (cof_volume_do_calc[TYPE]){
        H_vol1 = calc_H_volume(corners1);
        H_vol2 = calc_H_volume(corners2);
    }
    if (cof_surface_do_calc[TYPE]){
        H_surf1 = calc_H_surface(corners1);
        H_surf2 = calc_H_surface(corners2);
    }
    if (cof_convex_do_calc[TYPE]){
        H_conv1 = calc_H_convex(corners1);
        H_conv2 = calc_H_convex(corners2);
    }
    if (cof_straight_hull_do_calc[TYPE]){
        H_straight1 = cof_straight_hull_alpha[TYPE] * calc_H_straight_hull(corners1);
        H_straight2 = cof_straight_hull_alpha[TYPE] * calc_H_straight_hull(corners2);
    }
    H1 = H_vol1 + H_surf1 + H_conv1 + H_straight1;
    H2 = H_vol2 + H_surf2 + H_conv2 + H_straight2;

    deltaH = H2-H1;

    //printf("\n H v1: %4.2f,v2: %4.2f; s1:%4.2f, s2:%4.2f; c1:%4.2f, c2: %4.2f", H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2);

    return deltaH;
}

/*deprecated*/
int is_point_inside_cell_4Corners(double *p, double *corners)
{
  #define nvert 4
  double vertx[4] = {corners[0],corners[2],corners[4],corners[6]};
  double verty[4] = {corners[1],corners[3],corners[5],corners[7]};

  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>p[1]) != (verty[j]>p[1])) &&
     (p[0] < (vertx[j]-vertx[i]) * (p[1]-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}

int is_point_inside_cell(double *p, double *corners)
{
  int i, j, c = 0;
  
  for (i = 0, j = N_CORNERS-1; i < N_CORNERS; j = i++) {
    //i: 0,1,2,3,...
    //j: 3,0,1,2,...
    if ( ((corners[i*2+1]>p[1]) != (corners[j*2+1]>p[1])) && (p[0] < (corners[j*2]-corners[i*2]) * (p[1]-corners[i*2+1]) / (corners[j*2+1]-corners[i*2+1]) + corners[i*2]) )
       c = !c;
  }
  return c;
}


double sqr(double x){ return x * x;}
/*
double dist2(double *v, double *w) { return sqr(v[0] - w[0]) + sqr(v[1] - w[1]); }
double dist_to_segment_squared(double *p,double *v, double *w)
{
  double l2 = dist2(v, w);
  if (l2 == 0)
      return dist2(p, v);
  double t = ((p[0] - v[0]) * (w[0] - v[0]) + (p[1] - v[1]) * (w[1] - v[1])) / l2;
  if (t < 0)
      return dist2(p, v);
  if (t > 1)
      return dist2(p, w);
  double *p2;
  p2[0] = v[0] + t * (w[0] - v[0]);
  p2[1] = v[1] + t * (w[1] - v[1]);
  return dist2(p, p2);
}*/

double dist4(double vx,double vy, double wx,double wy) { return sqr(vx - wx) + sqr(vy - wy); }
double dist_to_segment_squared(double px,double py,double vx,double vy, double wx,double wy)
{
  double l2 = dist4(vx,vy, wx,wy);
  if (l2 == 0)
      return dist4(px,py, vx,vy);
  double t = ((py - vy) * (wy - vy) + (px - vx) * (wx - vx)) / l2;
  if (t < 0)
      return dist4(px,py, vx,vy);
  if (t > 1)
      return dist4(px,py, wx,wy);
  double p2x,p2y;
  p2y = vy + t * (wy - vy);
  p2x = vx + t * (wx - vx);
  return dist4(px,py, p2x,p2y);
}
//double dist_to_segment(p, v, w) { return sqrt(dist_to_segment_squared(p, v, w));}

int is_point_near_edge_of_polygon(double *p, double *cell, double d)
{
    if (dist_to_segment_squared(p[0],p[1],cell[6],cell[7],cell[0],cell[1])<d)
        { return 1;}

    for (int i=0;i<(N_CORNERS-1);i++)
    {
        if (dist_to_segment_squared(p[0],p[1],cell[i*2],cell[i*2+1],cell[(i+1)*2],cell[(i+1)*2+1])<d)
        {
            return 1;
        }
    }
    return 0;
}


void get_repelling_vector(double corners1[], double corners2[], double overlap, double rep1[])
{
    double middle1[2],middle2[2];
    get_middle_point(corners1,middle1);
    get_middle_point(corners2,middle2);
    //printf(" | mid1(%5.3f,%5.3f); ", middle1[0],middle1[1]);
    //from1to2 = middle2 - middle1;
    rep1[0] = middle1[0] - middle2[0];
    rep1[1] = middle1[1] - middle2[1];
    //rep1 = - from1to2; //direction in that cell1 should move
    //normalize(rep1);
    normalize(rep1);

    //printf(" | rep1(%5.3f,%5.3f); overlap: %5.3f   ", rep1[0],rep1[1],abs_tom(overlap));
    //multiply with overlap and invert
    rep1[0] *= -abs_tom(overlap);
    rep1[1] *= -abs_tom(overlap);
    //printf("   ((over rep1(%5.3f,%5.3f); ", rep1[0],rep1[1]);
}

double calc_H_contact(double *corners)
{
    double H_contact = cof_contact_medium[TYPE];
    //for every near other_cell:
      //for every corner of points:
        //check if corner is inside other_cell
    START_CELLPOSITION_MESSAGE_LOOP
        //...for every other_cell...
        for (int i=0;i<N_CORNERS;i++)
        {
            double p[2] = {corners[i*2],corners[i*2+1]};
            if (is_point_inside_cell(p, cellposition_message->corners))
            {
                //corner is inside other cell --> high H, according to cof...intersection
                if(is_point_near_edge_of_polygon(p, cellposition_message->corners, cof_contact_distance[TYPE]))
                {
                    //corner is near the edge of a different cell --> H according to cof_contact
                    H_contact += cof_contact_edge[TYPE][cellposition_message->type];
                } else{
                    H_contact += cof_contact_intersection[TYPE][cellposition_message->type];
                }
            }
        }
    FINISH_CELLPOSITION_MESSAGE_LOOP
    if (H_contact >cof_contact_medium[TYPE])
    {
        printf("Contact! H: %5.3f",H_contact);
    }
    return H_contact;
}

#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))

int get_number_of_same_corners(double corners1[], double corners2[])
{
    double d;
    int n=0;
    for (int i1=0; i1<N_CORNERS;i1++)
    {
        for (int i2=0; i2<N_CORNERS;i2++)
        {
            d=distance(corners1[i1*2],corners1[i1*2+1],corners2[i2*2],corners2[i2*2+1]);
            if (d<cof_contact_depth[TYPE])
            {
                n++;
            }
        }
    }
    return n;
}


double calc_H_contact_sat(double *corners, int moved_corner)
{
    double H_contact = 0;
    double contact_length,contact_length_total = 0;
    double H_contact_length = 0.0;
    double overlap_temp, overlap=0, corner_overlap;
    //double corner_overlap_status[N_CORNERS] = {0,0,0,0};
    double mtv[2];
    double repelling_vector[2];
    int n_near_corners=0;
    //for every near other_cell:
      //for every corner of points:
        //check if corner is inside other_cell

    double r = 2.8;
    START_CELLPOSITION_MESSAGE_LOOP
        //...for every other_cell...

        if ((cellposition_message->x > (current_xmachine_cell2d4->x - r)) && (cellposition_message->x < (current_xmachine_cell2d4->x + r)))
        {
            if ((cellposition_message->y > (current_xmachine_cell2d4->y - r)) && (cellposition_message->y < (current_xmachine_cell2d4->y + r)))
            {
                
                overlap_temp = get_intersect_and_mtv(corners,cellposition_message->corners,N_CORNERS,mtv);

                //n_near_corners += get_number_of_same_corners(corners,cellposition_message->corners);

                //printf(" (overlap_temp: %5.3f", overlap_temp);
                //print_positions(cellposition_message->corners);
                if (overlap_temp > 0)
                {
                    overlap +=overlap_temp;

                    if (overlap_temp > cof_contact_depth[TYPE]) {
                        //big intersection
                        //printf(" 88overlap_temp_big: %5.3f", overlap_temp);
                        H_contact += overlap_temp * cof_contact_intersection[TYPE][cellposition_message->type];
                        get_repelling_vector(corners,cellposition_message->corners,0.1,repelling_vector);
                        add_repulsion_message(cellposition_message->id, repelling_vector, TYPE);

                        break;
                        //printf("Contact-big ! H: %5.3f\n",H_contact);
                        //send repellation-message
                    } else {
                        //small intersection --> contact
                        //H_contact += cof_contact_edge[TYPE][cellposition_message->type] + overlap * 1.5;
                        //printf("Contact-smal! H: %5.3f\n",H_contact);
                        //printf("\n-----------------contaaaaaaaa????????????????????????: %f, %f", H_contact,H_contact_length);

                        contact_length = lineSegmentIntersection_Corners_intersection_length(corners,cellposition_message->corners);
                        if (contact_length>0.0){
                            contact_length_total += contact_length;
                            H_contact_length += contact_length * cof_contact_edge[TYPE][cellposition_message->type];
                            //printf("\n-----------------contaaaaaaaaaaaaaaaaaaact!!!!!jo: %f, %f", H_contact,H_contact_length);
                        }

                        /*
                        for (int i_corner=0; i_corner<N_CORNERS;i_corner++)
                        {
                            corner_overlap = get_corner_overlap(&corners[i_corner*2],cellposition_message->corners,N_CORNERS);
                            if (corner_overlap > 0.0)
                            {
                                //printf("coner_overlap: %5.3f; id(%d-%d)corner: %d \n", corner_overlap,ID, cellposition_message->id, i_corner);
                                corner_overlap_status[i_corner] = corner_overlap;
                                //H_contact += cof_contact_edge[TYPE][cellposition_message->type] + corner_overlap * 1.5;
                            }
                        }
                        */
                    }

                }
            }
        }
        //printf(" |o%4.2f",overlap_temp);

        /* todo:
         * different energies (-levels), depending on overlap;
         * */
    FINISH_CELLPOSITION_MESSAGE_LOOP



    double H_signal=0;
    double sqdist, attraction;

    START_SIGNALPOSITION_MESSAGE_LOOP
        //printf("signalposloooop.... %f \n", signalposition_message->x);
        sqdist = sqdistance(corners[moved_corner*2],corners[moved_corner*2+1],signalposition_message->x,signalposition_message->y);
        if (sqdist < 25.0)
        {   
            attraction = cof_cell_signal[TYPE][signalposition_message->type];            
            H_signal += attraction / sqrt(sqdist);
        }
    FINISH_SIGNALPOSITION_MESSAGE_LOOP
    //H_contact = overlap * 10;

    /*
    for (int i_corner=0; i_corner<N_CORNERS;i_corner++)
    {
        //printf("coner_h: %5.3f; id(%2d-%2d)corner: %d \n", corner_overlap_status[i_corner],ID, 0, i_corner);

        if (corner_overlap_status > 0)
        {
            H_contact += 0.5 * corner_overlap_status[i_corner] / cof_contact_distance[TYPE] + cof_contact_edge[TYPE][0] ;
        } else
        {
            H_contact += cof_contact_medium[TYPE];
        }
    }
    */
    
    //H_contact = H_contact - (n_near_corners*3.0); //cornerH

    double contact_length_medium;
    contact_length_medium = calc_surface_length(corners) - contact_length_total;
    H_contact_length += contact_length_medium * cof_contact_medium[TYPE];

    if (H_contact >3.0)
    {
    }
    //printf("\nH_contact: %f, %f", H_contact,H_contact_length);
    H_contact = H_contact + H_contact_length + H_signal;
    
    //printf("overlap: %4.2f;  H: %5.3f; o_temp: %4.2f; ID: %d contact_edge: %4.2f type: %d \n",overlap, H_contact,overlap_temp, ID,cof_contact_edge[TYPE][0],TYPE);
    return H_contact;
}


double calculate_deltaH_interactions(double *corners2, double *corners1, int moved_corner)
{
    //double deltaH = 0;
    double H_contact1, H_contact2;


    if (cof_contact_do_calc[TYPE])
    {
        H_contact1 = calc_H_contact_sat(corners1, moved_corner);
        H_contact2 = calc_H_contact_sat(corners2, moved_corner);
    }
    //printf("|| H1: %4.2f; Hc2: %4.2f ||",H_contact1,H_contact2);
    return H_contact2-H_contact1;
}

void move_all_corners_by_vector(double *corners, double vector[])
{
    for (int i_corner=0; i_corner<N_CORNERS;i_corner++)
    {
        corners[i_corner*2] += vector[0];
        corners[i_corner*2+1] += vector[1];
    }
}

