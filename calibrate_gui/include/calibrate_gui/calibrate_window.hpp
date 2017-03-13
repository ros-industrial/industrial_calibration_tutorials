#ifndef CALIBRATEWINDOW_HPP
#define CALIBRATEWINDOW_HPP

#include <QMainWindow>
#include <QtGui>
#include <QtGui/QMainWindow>
#ifndef Q_MOC_RUN
#include "ui_calibrate_window.h"
#include <iostream>
#include <ros/ros.h> 
#include <actionlib/client/simple_action_client.h>
#include <industrial_extrinsic_cal/calibrationAction.h>
#include <industrial_extrinsic_cal/calibrate.h>
#endif

namespace calibrate_gui{

  typedef actionlib::SimpleActionClient<industrial_extrinsic_cal::calibrationAction> CalibrationClient;

  class CalMainWindow : public QMainWindow
  {
    Q_OBJECT
    
  public:
    explicit CalMainWindow(ros::NodeHandle nh, int argc, char** argv, QWidget *parent = 0);
    ~CalMainWindow();
    
     private Q_SLOTS:
    void on_CalibrateButton_clicked();
    void on_AcceptButton_clicked();
  private:
    Ui::MainWindow ui;
    ros::NodeHandle nh_;
    void calDoneCallback(const actionlib::SimpleClientGoalState& state,
			 const industrial_extrinsic_cal::calibrationResultConstPtr& result);
    void calActiveCallback();
    void calFeedbackCallback(const industrial_extrinsic_cal::calibrationFeedbackConstPtr& feedback);
  };
} // end of namespace
#endif // CALIBRATEWINDOW_HPP
