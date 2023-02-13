#ifndef BOOTCAMP2_H
#define BOOTCAMP2_H

#include <rqt_gui_cpp/plugin.h>
#include <bootcamp2_gui/ui_bootcamp2_gui.h>
#include <QWidget>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/JointState.h>
#include <iostream>

#include <ros/ros.h>

#define PI 3.14159265359
#define deg2rad(deg)  ((deg) * PI / 180.0)
#define rad2deg(rad)  ((rad) * 180.0 / PI)

namespace bootcamp2_gui {

class bootcamp2Plugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  bootcamp2Plugin();
  int TOTALDOF;
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  ros::Subscriber jointstates_Sub;
  ros::Subscriber jointstatesReal_Sub;
  void subCallback(const sensor_msgs::JointStateConstPtr &msg);
  void realSubCallback(const sensor_msgs::JointStateConstPtr &msg);
  
  ros::Publisher myParam;
  ros::Publisher myCommand;
  ros::Publisher exec_pub_;
  

protected slots:
  virtual void sendbutton();
  virtual void sendinitbutton();
  virtual void sendemstop();
  virtual void sendstart();

//signals:
  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();
private:
  Ui::bootcamp2GuiWidget ui_;
  QWidget* widget_;
  ros::NodeHandle nh_;
};
} // namespace

#endif // my_namespace__my_plugin_H
