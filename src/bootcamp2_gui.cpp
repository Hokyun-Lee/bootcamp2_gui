#include "bootcamp2_gui/bootcamp2_gui.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace bootcamp2_gui
{

  bootcamp2Plugin::bootcamp2Plugin()
      : rqt_gui_cpp::Plugin(), widget_(0)
  {
    TOTALDOF = 6;
    // Constructor is called first before initPlugin function, needless to say.

    // give QObjects reasonable names
    setObjectName("bootcamp2Plugin");
  }

  void bootcamp2Plugin::initPlugin(qt_gui_cpp::PluginContext &context)
  {
    // access standalone command line arguments
    QStringList argv = context.argv();
    // create QWidget
    widget_ = new QWidget();
    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);

    bool real_robot;
    ros::param::get("real", real_robot);
    if(real_robot == true)
    {
      jointstatesReal_Sub = nh_.subscribe("/motor/joint_states", 100, &bootcamp2Plugin::realSubCallback, this);
    }
    else
    {
      jointstates_Sub = nh_.subscribe("/joint_states", 100, &bootcamp2Plugin::subCallback, this);
    }
  
    connect(ui_.SendButton, SIGNAL(clicked()), this, SLOT(sendbutton()));
    connect(ui_.SendInitButton, SIGNAL(clicked()), this, SLOT(sendinitbutton()));
    connect(ui_.EMSTOP, SIGNAL(clicked()), this, SLOT(sendemstop()));
    connect(ui_.Start, SIGNAL(clicked()), this, SLOT(sendstart()));

    myParam = nh_.advertise<std_msgs::Float32MultiArray>("/guiparam", 1);
    myCommand = nh_.advertise<std_msgs::String>("/commanding", 1);
    exec_pub_ = nh_.advertise<std_msgs::Float32>("/exec_time", 1);
  }

  void bootcamp2Plugin::sendbutton()
  {
    std_msgs::Float32MultiArray data_msg;
    std_msgs::Float32 time_msg;

    data_msg.data.push_back(0);
    data_msg.data.push_back(0);
    data_msg.data.push_back(0);
    data_msg.data[0] = ui_.lineEdit_6->text().toFloat();
    data_msg.data[1] = ui_.lineEdit_7->text().toFloat();
    data_msg.data[2] = ui_.lineEdit_8->text().toFloat();
    time_msg.data = ui_.Exec_Time->text().toFloat();

    myParam.publish(data_msg);
    exec_pub_.publish(time_msg);
  }

  void bootcamp2Plugin::sendinitbutton()
  {
    std_msgs::String msg;
    msg.data = "initpose";
    myCommand.publish(msg);
  }

  void bootcamp2Plugin::sendemstop()
  {
    std_msgs::String msg;
    msg.data = "em";
    myCommand.publish(msg);
  }

  void bootcamp2Plugin::sendstart()
  {
    std_msgs::String msg;
    msg.data = "start";
    myCommand.publish(msg);
  }

  void bootcamp2Plugin::subCallback(const sensor_msgs::JointStateConstPtr &msg)
  {
    // std::cout << "subcallback" << std::endl;
    ui_.lineEdit_0->setText(QString::number(rad2deg(msg->position[0])));
    ui_.lineEdit_1->setText(QString::number(rad2deg(msg->position[1])));
    ui_.lineEdit_2->setText(QString::number(rad2deg(msg->position[2])));
    ui_.lineEdit_3->setText(QString::number(rad2deg(msg->position[3])));
    ui_.lineEdit_4->setText(QString::number(rad2deg(msg->position[4])));
    ui_.lineEdit_5->setText(QString::number(rad2deg(msg->position[5])));
  }

  void bootcamp2Plugin::realSubCallback(const sensor_msgs::JointStateConstPtr &msg)
  {
    // std::cout << "subcallback" << std::endl;
    ui_.lineEdit_0->setText(QString::number(rad2deg(msg->position[0])));
    ui_.lineEdit_1->setText(QString::number(rad2deg(msg->position[1])));
    ui_.lineEdit_2->setText(QString::number(rad2deg(msg->position[2])));
    ui_.lineEdit_3->setText(QString::number(rad2deg(msg->position[3])));
    ui_.lineEdit_4->setText(QString::number(rad2deg(msg->position[4])));
    ui_.lineEdit_5->setText(QString::number(rad2deg(msg->position[5])));
  }

  void bootcamp2Plugin::shutdownPlugin()
  {
    // TODO unregister all publishers here
  }

  void bootcamp2Plugin::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
  {
    // TODO save intrinsic configuration, usually using:
    // instance_settings.setValue(k, v)
  }

  void bootcamp2Plugin::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
  {
    // TODO restore intrinsic configuration, usually using:
    // v = instance_settings.value(k)
  }

  /*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

} // namespace

PLUGINLIB_EXPORT_CLASS(bootcamp2_gui::bootcamp2Plugin, rqt_gui_cpp::Plugin)
