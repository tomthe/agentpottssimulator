/*
 *
 * */
#include "sat_intersection_test.h"

void copy_array_to_array(double *array1, double *array2, int n)
{
    for(int i=0; i<n;i++)
    {
        array2[i] = array1[i];
    }
}

int decide_if_cell_should_move()
{
    if ((rand() % 100) < cof_percent_of_cells_that_should_move_in_one_ts){
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
    return m + (rand() / ( RAND_MAX / (n-m) ) ) ;
}
/* move a corner in a random direction
 *  */
int choose_and_move_one_of_4_corners(double *corners)
{
    double dx = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    double dy = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    int r = rand() % 4; //int between 0 and 3
    corners[r*2] += dx; //x
    corners[r*2+1] += dy;
    //printf("move corner: dx: %f, dy: %f;\n", dx,dy);
    return 0;
}


int is_left_curve_old(double *a, double *c, double *b){
    //true if ( you go from a --> b --> c; you turn left on point b
    //Where a = line point 1; c = line point 2; b = point to check against.


    if(((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) < 0){
        return 1;
    }else{
        return 0;
    }
}
int is_left_curve(double *corners,int a,int b, int c){
    //true if ( you go from a --> b --> c; you turn left on point b
    //Where a = line point 1; c = line point 2; b = point to check against.
    if(((corners[b*2] - corners[a*2])*(corners[c*2+1] - corners[a*2+1]) - (corners[b*2+1] - corners[a*2+1])*(corners[c*2] - corners[a*2])) < 0){
        return 1;
    }else{
        return 0;
    }
}
double calc_H_convex(double *corners)
{

    //check if the 2. point lies right of the line between point 1 and 2:
    if (is_left_curve(corners,0,1,2)){
        if (is_left_curve(corners,1,2,3)){
            if (is_left_curve(corners,2,3,0)){
                if (is_left_curve(corners,3,0,1)){
                    //yes, every corner is convex
                    return 0.0;
                }
            }
        }
    }
    //at least one corner is not convex
    return 200.0;
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

double calc_surface_length(double *corners)
{
    double l = calc_distance_2corners(corners,0,1);
    l += calc_distance_2corners(corners,1,2);
    l += calc_distance_2corners(corners,2,3);
    l += calc_distance_2corners(corners,3,0);
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

/* X - x-coordinates [x0,x1,x2,x3]
 * adapted from: http://www.mathopenref.com/coordpolygonarea2.html
 * */
double calculate_polygon_area(double X[], double Y[], int num_points)
{
  double area = 0;         // Accumulates area in the loop
  int j = num_points-1;  // The last vertex is the 'previous' one to the first

  for (int i=0; i<num_points; i++)
    { area = area +  (X[j]+X[i]) * (Y[j]-Y[i]);
      j = i;  //j is previous vertex to i
    }
  return area/2;
}

double calculate_corners_area(double *corners)
{
    double area = 0;         // Accumulates area in the loop
    int j = N_CORNERS-1;  // The last vertex is the 'previous' one to the first

    for (int i=0; i<N_CORNERS; i++)
      { area = area +  (corners[j*2]+corners[i*2]) * (corners[j*2+1]-corners[i*2+1]);
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

    double H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2;

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
    H1 = H_vol1 + H_surf1 + H_conv1;
    H2 = H_vol2 + H_surf2 + H_conv2;

    deltaH = H2-H1;

    //printf("\n H v1: %4.2f,v2: %4.2f; s1:%4.2f, s2:%4.2f; c1:%4.2f, c2: %4.2f", H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2);

    return deltaH;
}
/*
 *
int is_point_inside_polygon(point p, fourpoints cell)
{

}
*/

int is_point_inside_cell(double *p, double *corners)
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
                H_contact += cof_contact_intersection[TYPE][cellposition_message->type];
                if(is_point_near_edge_of_polygon(p, cellposition_message->corners, cof_contact_distance[TYPE]))
                {
                    //corner is near the edge of a different cell --> H according to cof_contact
                    H_contact += cof_contact_edge[TYPE][cellposition_message->type];
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


double calculate_deltaH_interactions(double *corners2, double *corners1)
{
    //double deltaH = 0;
    double H_contact1, H_contact2;


    if (cof_contact_do_calc[TYPE])
    {
        H_contact1 = calc_H_contact(corners1);
        H_contact2 = calc_H_contact(corners2);
    }
    printf("||H1: %4.2f; Hc2: %4.2f||",H_contact1,H_contact2);
    return H_contact2-H_contact1;
}
