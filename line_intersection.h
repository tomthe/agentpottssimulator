//  public domain function by Darel Rex Finley, 2006


/**
* Determines the intersection point of the line segment defined by points A and B
* with the line segment defined by points C and D.
* Returns 1 if the intersection point was found, and stores that point in X,Y.
* Returns 0 if there is no determinable intersection point, in which case X,Y will
* be unmodified.
*/
int lineSegmentIntersection(
double Ax, double Ay,
double Bx, double By,
double Cx, double Cy,
double Dx, double Dy,
double *X, double *Y) {

  double  distAB, theCos, theSin, newX, ABpos ;

  //  Fail if either line segment is zero-length.
  if ((Ax==Bx && Ay==By) || (Cx==Dx && Cy==Dy)) return 0;

  //  Fail if the segments share an end-point.
  if ((Ax==Cx && Ay==Cy) || (Bx==Cx && By==Cy) || (Ax==Dx && Ay==Dy) || (Bx==Dx && By==Dy)) {
    return 0;}

  //  (1) Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;

  //  Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);

  //  (2) Rotate the system so that point B is on the positive X axis.
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;

  //  Fail if segment C-D doesn't cross line A-B.
  if ((Cy<0. && Dy<0.) || (Cy>=0. && Dy>=0.)) {return 0;}

  //  (3) Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

  //  Fail if segment C-D crosses line A-B outside of segment A-B.
  if (ABpos<0. || (ABpos>distAB)) {return 0;}

  //  (4) Apply the discovered position to line A-B in the original coordinate system.
  *X=Ax+ABpos*theCos;
  *Y=Ay+ABpos*theSin;

  //  Success.
  return 1;
}

int lineSegmentIntersection_Corners(double corners1[], int i_line1, double corners2[], int i_line2, double crosspoint[]){

  int i_a = i_line1;
  int i_b = (i_line1 + 1) % N_CORNERS;
  int j_c = i_line2;
  int j_d = (i_line2 + 1) % N_CORNERS;

  //printf("ia,bcd:(%d,%d,%d,%d); iline1,2: (%d,%d)\n",i_a,i_b,j_c,j_d,i_line1,i_line2);

  double Ax = corners1[i_a*2];
  double Ay = corners1[i_a*2+1];
  double Bx = corners1[i_b*2];
  double By = corners1[i_b*2+1];

  double Cx = corners2[j_c*2];
  double Cy = corners2[j_c*2+1];
  double Dx = corners2[j_d*2];
  double Dy = corners2[j_d*2+1];

  double  distAB, theCos, theSin, newX, ABpos ;

  //  Fail if either line segment is zero-length.
  if ((Ax==Bx && Ay==By) || (Cx==Dx && Cy==Dy)) {return 0;}

  //  Fail if the segments share an end-point.
  if ((Ax==Cx && Ay==Cy) || (Bx==Cx && By==Cy) || (Ax==Dx && Ay==Dy) || (Bx==Dx && By==Dy)) {
    return 0;}

  //  (1) Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;

  //  Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);

  //  (2) Rotate the system so that point B is on the positive X axis.
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;

  //  Fail if segment C-D doesn't cross line A-B.
  if ((Cy<0. && Dy<0.) || (Cy>=0. && Dy>=0.)) {return 0;}

  //  (3) Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

  //  Fail if segment C-D crosses line A-B outside of segment A-B.
  if (ABpos<0. || (ABpos>distAB)) {return 0;}

  //  (4) Apply the discovered position to line A-B in the original coordinate system.
  crosspoint[0] = Ax+ABpos*theCos;
  crosspoint[1] = Ay+ABpos*theSin;

  //  Success.
  return 1;

}


#define distance(x1,y1,x2,y2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))

double lineSegmentIntersection_Corners_intersection_length(double corners1[],double corners2[]){
  int i_line1,i_line2, i_crosspoint=0;
  double crosspoint_temp[2];
  double crosspoints[4];

  for (i_line1 = 0; i_line1<N_CORNERS; i_line1++){
    //i: 0,1,2,3,...
    //j: 3,0,1,2,...
    for (i_line2 = 0; i_line2<N_CORNERS; i_line2++){
      //i: 0,1,2,3,...
      //j: 3,0,1,2,...
        //printf("-na%d",i_crosspoint);
      if (lineSegmentIntersection_Corners(corners1,i_line1,corners2,i_line2,crosspoint_temp)!=0){
        //printf("-nU%d",i_crosspoint);
        crosspoints[i_crosspoint*2] = crosspoint_temp[0];
        crosspoints[i_crosspoint*2+1] = crosspoint_temp[1];
        i_crosspoint++;
        if (i_crosspoint>2){
          
          //printf("\n too many crossspoints!! --------------------------------%d \n",i_crosspoint);
          i_crosspoint--;
        }
      }
    }
  }


  if (i_crosspoint > 0){
    //printf("\n exactly so many crosspoints::::::::::----------------------%d distance: %f \n",i_crosspoint,distance(crosspoints[0],crosspoints[1],crosspoints[2],crosspoints[3]));
    return distance(crosspoints[0],crosspoints[1],crosspoints[2],crosspoints[3]);
  } 
  else {
    return 0.0;
  }
}