#include <QtGui>
#include "../include/calibrate_gui/calibrate_window.hpp"
#include <ros/ros.h>
#include <ros/package.h>
#include <std_srvs/Empty.h>
#include <industrial_extrinsic_cal/user_accept.h>
#include <industrial_extrinsic_cal/calibrationAction.h>

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
    ROS_ERROR("calibrate button clicked, calling run_calibration service");
    /* USE the action rather than the service to enable other interactions while collecting data
      ros::ServiceClient client = nh_.serviceClient<std_srvs::Empty>("calibration_service");
      std_srvs::Empty srv;
      client.call(srv);
    */
    CalibrationClient client("run_calibration", true);
    client.waitForServer();
    industrial_extrinsic_cal::calibrationGoal goal;
    goal.allowable_cost_per_observation = 0.4;
    client.sendGoal(goal, boost::bind(&CalMainWindow::calDoneCallback, this, _1, _2),
		    boost::bind(&CalMainWindow::calActiveCallback, this),
		    boost::bind(&CalMainWindow::calFeedbackCallback, this, _1));
    //    client.waitForResult();
  }

  void CalMainWindow::calDoneCallback(const actionlib::SimpleClientGoalState& state,
				      const industrial_extrinsic_cal::calibrationResultConstPtr& result)
  {
    ROS_INFO("Calibration Done");
  }

  void CalMainWindow::calFeedbackCallback(const industrial_extrinsic_cal::calibrationFeedbackConstPtr& feedback)
  {
    ROS_INFO("Calibration Feedback");
  }
  void CalMainWindow::calActiveCallback()
  {
    ROS_INFO("Calibration Active");
  }

  void CalMainWindow::on_AcceptButton_clicked()
  {
    ros::ServiceClient client = nh_.serviceClient<industrial_extrinsic_cal::user_accept>("UserAccept");
    industrial_extrinsic_cal::user_accept srv;
    ROS_ERROR("Calling UserAccept service");
    client.call(srv);
  }
}
