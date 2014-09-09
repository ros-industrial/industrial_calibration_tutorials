function print_points(file_name, Points, z_value,rows,cols)

fp = fopen(file_name,"w");
fprintf(fp,"    target_rows: %d\n",rows);
fprintf(fp,"    target_cols: %d\n",cols);
fprintf(fp,"    num_points: %d\n",cols*rows);
fprintf(fp,"    points:\n");
[m,n] = size(Points);
if(m !=(rows*cols)) 
    shit = "rows*cols not equal"
endif
for i=1:m;
    fprintf(fp,"    - pnt: [%7.4f, %7.4f, %7.4f]\n",Points(i,1),Points(i,2), z_value);
endfor
fclose(fp);

end

return
