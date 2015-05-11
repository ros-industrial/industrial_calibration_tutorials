#include <QtGui>
#include <QtGui/QApplication>
#include "../include/calibrate_gui/calibrate_window.hpp"
// ros includes
#include <ros/ros.h> 

using calibrate_gui::CalMainWindow;

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "calibrate_gui");
  ros::NodeHandle nh;
  
  QApplication qt_app(argc, argv);
  CalMainWindow w(nh, argc, argv);
  w.show();
  qt_app.connect(&qt_app, SIGNAL(lastWindowClosed()), &qt_app, SLOT(quit()));
  return qt_app.exec();
}
