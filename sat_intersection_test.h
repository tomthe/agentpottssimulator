
double max(double a, double b) { return a > b ? a : b; }
double max3(double a, double b, double c) { return max(a,c) > b ? max(a,c) : b; }
double min(double a, double b) { return a < b ? a : b; }

//projection:
double dot_product_2d(double a[], double b[])
{
    return a[0]*b[0]+a[1]*b[1];
}

void project_corners_on_axis(double axis[],double corners[], double result_projection[])
{
    //double min = axis.dot(shape.vertices[0]);
    double min = dot_product_2d(axis,&corners[0]);
    double max = min;

    for (int i = 1; i < N_CORNERS; i++) {
      // NOTE: the axis must be normalized to get accurate projections
      double p = dot_product_2d(axis,&corners[i*2]);//    axis.dot(shape.vertices[i]);
      if (p < min) {
        min = p;
      } else if (p > max) {
        max = p;
      }
    }
    result_projection[0] = min;
    result_projection[1] = max;
}


double get_overlap(double p1[], double p2[])
{
    return max(0.0, (min(p1[1], p2[1]) - max(p1[0], p2[0])));
/*
    if (p1[1]>p2[0] && p1[1]<p2[1])//end of p1 lies in p2
    {
        return min((p1[1]-p1[0]), p1[1]-p2[0]);
    } else if (p1[0]>p2[0] && p1[0]<p2[1])//start of p1 lies in p2
    {
        return min((p1[1]-p1[0]), p2[1]-p1[0]);
    } else if (p2[0]>p1[0] && p2[1]<p1[1])//p2 is surrounded by p1
    {
        return p2[1]-p2[0];
    }
    return 0;
    //return max(0.0, (min(p1[1], p2[1]) - max(p1[0], p2[0])));
    */
}

//

void subtract(double p1[],double p2[], double result[])
{
    result[0] = p1[0] - p2[0];
    result[1] = p1[1] - p2[1];
}
void perp(double v1[],double result[])
{
    // the perp method is just (x, y) => (-y, x) or (y, -x)
    result[0] = -v1[1];
    result[1] =  v1[0];
}

void axes_from_corners(double *corners,int n1, double axes[])
{
    double *p1ptr; //p1[2];
    double *p2ptr; //[2];
    double edge[2];
    double normal[2];

    for (int i = 0; i < n1; i++)
    {
      // get the current vertex
      p1ptr = &corners[i*2];
      // get the next vertex
      if (i<n1-1) {p2ptr = &corners[(i+1)*2];}
      else {p2ptr = &corners[0];}
      // subtract the two to get the edge vector
      subtract(p2ptr,p1ptr,edge);//p1.subtract(p2);
      // get either perpendicular vector
      perp(edge,normal);
      // the perp method is just (x, y) => (-y, x) or (y, -x)
      axes[i*2] = normal[0];
      axes[i*2+1] = normal[1];

    }
}

double get_intersect(double *corners1, double *corners2, int n1)
{
    double overlap = 20000.0;// really large value;
    double overlap_temp;
    //#double smallest_axis[2], axis_temp[2];
    double *axis_temp_ptr;
    double projection1[2],projection2[2];

    double axes1[N_CORNERS*2];
    axes_from_corners(corners1,n1,axes1);
    double axes2[N_CORNERS*2];
    axes_from_corners(corners2,n1,axes2);

    // loop over the axes1
    for (int i = 0; i < N_CORNERS; i++)
    {
        axis_temp_ptr = &axes1[i*2];
        // project both shapes onto the axis
        project_corners_on_axis(axis_temp_ptr,corners1,projection1);
        project_corners_on_axis(axis_temp_ptr,corners2,projection2);
        // do the projections overlap?
        overlap_temp = get_overlap(projection1,projection2);
        if (overlap_temp==0)
        {
            //printf("get_intersect: i: %d; proj1:(%4.2f,%4.2f), proj2:(%4.2f,%4.2f)\n",i,projection1[0],projection1[1],projection2[0],projection2[1]);
            // then we can guarantee that the shapes do not overlap
            return 0;
        } else if (overlap_temp < overlap) {
            // then set this one as the smallest
            overlap = overlap_temp;
            //# *smallest_axis = &axis_temp_ptr;
        }
    }

    // loop over the axes2
    for (int i = 0; i < N_CORNERS; i++)
    {
        axis_temp_ptr = &axes2[i*2];
        // project both shapes onto the axis
        project_corners_on_axis(axis_temp_ptr,corners1,projection1);
        project_corners_on_axis(axis_temp_ptr,corners2,projection2);
        // do the projections overlap?
        overlap_temp = get_overlap(projection1,projection2);
        if (overlap_temp==0)
        {
            // then we can guarantee that the shapes do not overlap
            return 0;
        } else if (overlap_temp < overlap) {
            // then set this one as the smallest
            overlap = overlap_temp;
            //#*smallest_axis = &axis_temp_ptr;
        }
    }
    // MTV mtv = new MTV(smallest, overlap);
    // if we get here then we know that every axis had overlap on it
    // so we can guarantee an intersection
    return overlap;
}



/*
//Algorithm:

double overlap = // really large value;
Axis smallest = null;
Axis[] axes1 = shape1.getAxes();
Axis[] axes2 = shape2.getAxes();
// loop over the axes1
for (int i = 0; i < axes1.length; i++) {
  Axis axis = axes1[i];
  // project both shapes onto the axis
  Projection p1 = shape1.project(axis);
  Projection p2 = shape2.project(axis);
  // do the projections overlap?
  if (!p1.overlap(p2)) {
    // then we can guarantee that the shapes do not overlap
    return false;
  } else {
    // get the overlap
    double o = p1.getOverlap(p2);
    // check for minimum
    if (o < overlap) {
      // then set this one as the smallest
      overlap = o;
      smallest = axis;
    }
  }
}
// loop over the axes2
for (int i = 0; i < axes2.length; i++) {
  Axis axis = axes2[i];
  // project both shapes onto the axis
  Projection p1 = shape1.project(axis);
  Projection p2 = shape2.project(axis);
  // do the projections overlap?
  if (!p1.overlap(p2)) {
    // then we can guarantee that the shapes do not overlap
    return false;
  } else {
    // get the overlap
    double o = p1.getOverlap(p2);
    // check for minimum
    if (o < overlap) {
      // then set this one as the smallest
      overlap = o;
      smallest = axis;
    }
  }
}
MTV mtv = new MTV(smallest, overlap);
// if we get here then we know that every axis had overlap on it
// so we can guarantee an intersection
return mtv;


*/
