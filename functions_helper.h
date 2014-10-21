/*
 *
 * */


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

int print_positions(fourpoints point)
{
    printf("positions: (%f,%f); (%f,%f); (%f,%f); (%f,%f); \n", point.p0.x,point.p0.y,point.p1.x,point.p1.y,point.p2.x,point.p2.y,point.p3.x,point.p3.y);
    return 0;
}

double rand_double_m_to_n(double m, double n)
{
    return m + (rand() / ( RAND_MAX / (n-m) ) ) ;
}
/* move a corner in a random direction
 *  */
int choose_and_move_one_of_4_corners(fourpoints *points2)
{
    double dx = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    double dy = rand_double_m_to_n(-(cof_move_step_size[TYPE]),cof_move_step_size[TYPE]);
    int r = rand() % 4;
    if (r==0){
        (*points2).p0.x += dx;
        (*points2).p0.y += dy;
    } else if(r==1){
        points2->p1.x += dx;
        points2->p1.y += dy;
    } else if(r==2){
        points2->p2.x += dx;
        points2->p2.y += dy;
    } else if(r==3){
        (*points2).p3.x += dx;
        (*points2).p3.y += dy;
    }
    //printf("move corner: dx: %f, dy: %f;\n", dx,dy);
    return 0;
}


int is_left_curve(point a, point c, point b){
    //true if ( you go from a --> b --> c; you turn left on point b
    //Where a = line point 1; c = line point 2; b = point to check against.


    if(((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) < 0){
        return 1;
    }else{
        return 0;
    }
}

double calc_H_convex(fourpoints points)
{
    //check if the 2. point lies right of the line between point 1 and 2:
    if (is_left_curve(points.p0,points.p1,points.p2)){
        if (is_left_curve(points.p1,points.p2,points.p3)){
            if (is_left_curve(points.p2,points.p3,points.p0)){
                if (is_left_curve(points.p3,points.p0,points.p1)){
                    //yes, every corner is convex
                    return 0.0;
                }
            }
        }
    }
    //at least one corner is not convex
    return 200.0;
}


double calc_distance_points(point p1, point p2)
{
    double dx = (p2.x-p1.x);
    double dy = (p2.y-p1.y);
    return sqrt(dx*dx + dy*dy);
}

double calc_distance_2d(double x1,double y1, double x2,double y2)
{
    double dx = (x2-x1);
    double dy = (y2-y1);
    return sqrt(dx*dx + dy*dy);
}

double calc_surface_length(fourpoints points)
{
    double l = calc_distance_points(points.p0,points.p1);
    l += calc_distance_points(points.p1,points.p2);
    l += calc_distance_points(points.p2,points.p3);
    l += calc_distance_points(points.p3,points.p0);
    return l;
}

double calc_H_surface(fourpoints points)
{
    //always positive. near 0 -> better
    double surface = calc_surface_length(points);
    double H = pow((surface - cof_surface_target[TYPE]), 2.0) * cof_surface_alpha[TYPE];
    printf(" | surface: %f| ", surface);
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

double calculate_fourpoints_area(fourpoints points)
{
    double X[] = {points.p0.x,points.p1.x,points.p2.x,points.p3.x};
    double Y[] = {points.p0.y,points.p1.y,points.p2.y,points.p3.y};
    return -calculate_polygon_area(X,Y,4); //negative because counterclockwise...
}


double calc_H_volume(fourpoints points)
{
    double area = calculate_fourpoints_area(points);
    double H = pow((cof_volume_target[TYPE] - area),2.0) * cof_volume_alpha[TYPE];
    printf(" | area: %f |",area);
    return H;
}



double calculate_deltaH_inside(fourpoints points2, fourpoints points1)
{
    double deltaH = 0.0;
    double H1 = 0.0;
    double H2 = 0.0;

    double H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2;
    
    if (cof_volume_do_calc[TYPE]){
        H_vol1 = calc_H_volume(points1);
        H_vol2 = calc_H_volume(points2);
    }
    if (cof_surface_do_calc[TYPE]){
        H_surf1 = calc_H_surface(points1);
        H_surf2 = calc_H_surface(points2);
    }
    if (cof_convex_do_calc[TYPE]){
        H_conv1 = calc_H_convex(points1);
        H_conv2 = calc_H_convex(points2);
    }
    H1 = H_vol1 + H_surf1 + H_conv1;
    H2 = H_vol2 + H_surf2 + H_conv2;

    deltaH = H2-H1;

    printf("\n H v1: %4.2f,v2: %4.2f; s1:%4.2f, s2:%4.2f; c1:%4.2f, c2: %4.2f", H_vol1,H_vol2,H_surf1,H_surf2,H_conv1,H_conv2);

    return deltaH;
}
