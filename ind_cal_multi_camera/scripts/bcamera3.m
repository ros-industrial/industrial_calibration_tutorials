spacing_meters = .1143;
half_thick = .025;
grid_pnts = make_bgrid(10, 20, spacing_meters);
Points = [];
q = 1;
for i=1:3
  for j=3:1:15
          Points(q,1) = grid_pnts((i-1)*20 + j, 1);
          Points(q,2) = grid_pnts((i-1)*20 + j, 2);
          q = q+1;
     endfor       
endfor
rows = 3;
cols = 13;

print_points("bcamera3.yaml",Points, -half_thick, rows, cols);
plot_points(grid_pnts,Points);
