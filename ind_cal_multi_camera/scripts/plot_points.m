function plot_points(grid_pnts, Points)
hold off;
plot(grid_pnts(:,1), grid_pnts(:,2), "+r");
hold on;

plot(Points(:,1),Points(:,2),"ob");
plot(Points(1:2,1), Points(1:2,2),"g");
axis('square');
return
