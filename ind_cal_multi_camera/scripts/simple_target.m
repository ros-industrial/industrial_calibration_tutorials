spacing_meters = .0159;
half_thick = .025;
grid_pnts = make_grid(10, 10, spacing_meters);

Points = [];
q = 1;
for j=10:-1:1
  for i=1:10
          Points(q,1) = grid_pnts((i-1)*10 + j, 1);
          Points(q,2) = grid_pnts((i-1)*10 + j, 2);
          q = q+1;
     endfor       
endfor
rows = 10;
cols = 10;

print_points("modified_circle_target.yaml",Points, half_thick,rows,cols);
plot_points(grid_pnts,Points);
