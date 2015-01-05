#include <stdio.h>

main()
{
  FILE *fp = fopen("ical_caljob.yaml", "w");
  fprintf(fp,"---\n");
  fprintf(fp,"reference_frame: world_frame\n");
  fprintf(fp,"scenes:\n");
  int scene_id = 0;
  int roi_width;
  int roi_height;
  int image_width = 1920;
  int image_height = 1080;
  float t1 = image_width;
  float t2 = image_height;
  float n1 = 5;
  float n2 = 4;


  for(int roisize = 500; roisize<=800; roisize +=50){
    roi_width = roisize*12/10;
    roi_height = roisize;
    float po1 = n1*roi_width/image_width - 1.0;
    float po2 = n2*roi_height/image_height - 1.0;
    printf("percent overlap in width = %f in height = %f\n", po1*100, po2*100);
    for(int i=0; i<n1; i++){
      for(int j=0; j<n2; j++){
	int x = i*(image_width- roi_width)/(n1-1.0);
	int y = j*(image_height-roi_height)/(n2-1.0);
	fprintf(fp,"-\n");
	fprintf(fp,"    scene_id: %d\n", scene_id++);
	fprintf(fp,"    trigger: ROS_CAMERA_OBSERVER_TRIGGER\n");
	fprintf(fp,"    trigger_parameters:\n");
	fprintf(fp,"    -\n");
	fprintf(fp,"         service_name: ObserverTrigger\n");
	fprintf(fp,"         instructions: Center target within region of interest\n");
	fprintf(fp,"         image_topic: /basler1/rgb/image\n");
	fprintf(fp,"         target_type: 1\n");
	fprintf(fp,"         roi_min_x: %d\n", x);
	fprintf(fp,"         roi_max_x: %d\n", x+roi_width);
	fprintf(fp,"         roi_min_y: %d\n", y);
	fprintf(fp,"         roi_max_y: %d\n", y+roi_height);
	fprintf(fp,"    observations:\n");
	fprintf(fp,"    -\n");
	fprintf(fp,"        camera: basler1\n");
	fprintf(fp,"        target: mytarget\n");
	fprintf(fp,"        roi_x_min: %d\n", x);
	fprintf(fp,"        roi_x_max: %d\n", x+roi_width);
	fprintf(fp,"        roi_y_min: %d\n", y);
	fprintf(fp,"        roi_y_max: %d\n", y+roi_height);
	fprintf(fp,"        cost_type: CameraReprjErrorWithDistortionPK\n");
      }
    }
  }
  fprintf(fp,"optimization_parameters: xx\n");
  fclose(fp);
  printf("created  %d scenes\n" ,scene_id);

}
