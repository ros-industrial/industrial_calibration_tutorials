#ifndef CALIBRATEWINDOW_HPP
#define CALIBRATEWINDOW_HPP

#include <QMainWindow>
#include <QtGui>
#include <QtGui/QMainWindow>
#include "ui_calibrate_window.h"
#include <iostream>
#include <ros/ros.h> 

namespace calibrate_gui{

  class CalMainWindow : public QMainWindow
  {
    Q_OBJECT
    
  public:
    explicit CalMainWindow(ros::NodeHandle nh, int argc, char** argv, QWidget *parent = 0);
    ~CalMainWindow();
    
	       private Q_SLOTS:
	       void on_CalibrateButton_clicked();

  private:
    Ui::MainWindow ui;
    ros::NodeHandle nh_;
  };
} // end of namespace
#endif // CALIBRATEWINDOW_HPP
