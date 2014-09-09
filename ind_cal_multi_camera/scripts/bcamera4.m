spacing_meters = .1143;
half_thick = .025;
grid_pnts = make_bgrid(10, 20, spacing_meters);

Points = [];
q = 1;
  for j=13:20
for i=10: -1 : 2
          Points(q,1) = grid_pnts((i-1)*20 + j, 1);
          Points(q,2) = grid_pnts((i-1)*20 + j, 2);
          q = q+1;
     endfor       
endfor
rows = 8;
cols = 9;
print_points("bcamera4.yaml",Points, -half_thick, rows, cols);
plot_points(grid_pnts,Points);
