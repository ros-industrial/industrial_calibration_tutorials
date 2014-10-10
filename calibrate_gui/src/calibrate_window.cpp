#include <QtGui>
#include "../include/calibrate_gui/calibrate_window.hpp"
#include <ros/ros.h>
#include <ros/package.h>
#include <std_srvs/Empty.h>

namespace calibrate_gui {
  using namespace Qt;

  CalMainWindow::CalMainWindow(ros::NodeHandle nh, int argc, char** argv, QWidget *parent) :
    QMainWindow(parent), nh_(nh)
  {
    ui.setupUi(this);
 
   
  }

  CalMainWindow::~CalMainWindow()
  {

  }

  void CalMainWindow::on_CalibrateButton_clicked()
  {
    ros::ServiceClient client = nh_.serviceClient<std_srvs::Empty>("calibration_service");
    std_srvs::Empty srv;
    client.call(srv);
  }
}
