int count_intersection_points(void) {
  int intersections_ct = 0;
  double e = 1.0e-5;

  for (int i=0; i<CIRCLE_COUNT; i++) {
    double cx = c_pos[i][0];
    double cy = c_pos[i][1];
    double r = radius[i];

    for (int j=0; j<LINE_COUNT; j++) {
      double a = line_a[j];
      double b = line_b[j];

      double distance = distance_line_point(a, b, cx, cy);

      if (distance < r - e) {
        printf("(%f, %f) r=%f vs y = %fx + %f --- distance %f intersect\n", cx, cy, r, a, b, distance);
        intersections_ct += 2;
      } else if (r - e <= distance && distance <= r + e) {
        printf("(%f, %f) r=%f vs y = %fx + %f --- distance %f contact\n", cx, cy, r, a, b, distance);
        intersections_ct++;
      }
    }
  }

  return intersections_ct;
}