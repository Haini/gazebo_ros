/**
 * Taken with inspiration from: gazebosim.org/tutorials?tut=plugins_model
 * www.answer.gazebosim.org/question/2341/set-and-get-position-of-gazebo-model-using-ros-plugin/
 */

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Point.h"

//#include <boost/bind.hpp>
//#include <gazebo/common/common.hh>
//#include <gazebo/common/Plugin.hh>
//#include <stdio.h>

namespace gazebo {
	class QuadModel : public ModelPlugin
	{
		public: QuadModel() {}

		public: virtual void Load(physics::ModelPtr _model,  sdf::ElementPtr _sdf)
		{
			std::cerr << "Model Name is: [" << _model->GetName() << "]\n";
			printf("Loading Plugin!\n\r");
			if (!ros::isInitialized())
			{
				int argc = 0;
				char **argv = NULL;
				printf("Starting ROS!\n\r");
				ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
				printf("ROS start success...\n\r");
			}

			this->model = _model;
			std::cerr << "Model Name is: " + this->model->GetName() << "\n";
			
			this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
			ros::SubscribeOptions so = ros::SubscribeOptions::create<geometry_msgs::Point>("/" + this->model->GetName() + "/position_O", 1, boost::bind(&QuadModel::OnRosMsg, this, _1), ros::VoidPtr(), &this->rosQueue);
			this->rosSub = this->rosNode->subscribe(so);
			
			this->rosQueueThread = std::thread(std::bind(&QuadModel::QueueThread, this));
		}	

		private: std::unique_ptr<ros::NodeHandle> rosNode;
		private: ros::Subscriber rosSub;
		private: ros::CallbackQueue rosQueue;
		private: std::thread rosQueueThread;
		private: physics::ModelPtr model;

		public: void OnRosMsg(const geometry_msgs::PointConstPtr &_msg)
		{
			double x = _msg->x;
			double y = _msg->y;
			double z = _msg->z;
			math::Pose pose = math::Pose(x,y,z, 0, 0, 0);
			this->model->SetWorldPose(pose);
		}

		private: void QueueThread()
		{
			static const double timeout = 0.01;
			while (this->rosNode->ok()) {
				this->rosQueue.callAvailable(ros::WallDuration(timeout));
			}
		}

	};
	GZ_REGISTER_MODEL_PLUGIN(QuadModel)
}
