// \file WMGravityModule.h
// \brief Declaration of gravity module.
// Created by kevin on 07/03/2019.

#ifndef WM_GRAVITY_MODULE_H
#define WM_GRAVITY_MODULE_H

#include <string>
#include <vector>
#include <ros/ros.h>
#include <tf/transform_listener.h>
//#include <sensor_msgs/Imu.h>
#include <urdf/model.h>

namespace wm_admitance
{
    /**
     * \brief Type of vector of compensated torque
     */
    using CompensatedTorqueVector = std::vector<double>;


    // Note: Il faudra faire une classe WMAdmitance qui utiliser WMGravityModule.
    class WMGravityModule final
    {
    public:
        WMGravityModule(const std::vector<std::string>& pTFNames, const std::string& pURDFFilePath, size_t pActuatorCount);
        ~WMGravityModule() noexcept = default;

        CompensatedTorqueVector process();

    private:

        std::vector<tf::StampedTransform> retrievePositionFromTF();
        void retriveRobotConfiguration();

        // Plusieurs IMU, voir si c'est possible d'avoir une liste?
        //void imuCallback(const sensor_msgs::Imu::ConstPtr& pIMUMessage); //  On subscribe à cette fonction pour le imu

        ros::NodeHandle aGravityNode;
        const tf::TransformListener aListener;
        //ros::Subscriber aIMUSubHandle;
        urdf::Model aURDFModel;
        size_t aActuatorCount;

        const std::vector<std::string> aTFNames;
        const std::string aURDFFilePath;

        std::vector<double> aLinkMass;
    };
} // namespace wm_admitance
#endif // WM_GRAVITY_MODULE_H
