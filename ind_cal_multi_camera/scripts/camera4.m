spacing_meters = .1143;
half_thick = .025;
grid_pnts = make_grid(10, 20, spacing_meters);

Points = [];
q = 1;
  for j=16:20
for i=10: -1 : 1
          Points(q,1) = grid_pnts((i-1)*20 + j, 1);
          Points(q,2) = grid_pnts((i-1)*20 + j, 2);
          q = q+1;
     endfor       
endfor
rows  = 5;
cols = 10;
print_points("camera4.yaml",Points, half_thick, rows, cols);
plot_points(grid_pnts,Points);


