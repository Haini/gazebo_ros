#include <ignition/math/Pose3.hh>
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"
#include <string>

namespace gazebo
{
class Factory : public WorldPlugin
{
  public: void Load(physics::WorldPtr _parent, sdf::ElementPtr /*_sdf*/)
  {
    // Option 2: Insert model from string via function call.
    // Insert a sphere model from string

    double x = 1;
    double y = 0;
    double z = 0;

    std::string strX;
    std::string strY;
    std::string strZ;
    std::string strI;

    std::string strDimX;
    std::string strDimY;
    std::string strDimZ;

    double tData[90] =  {  
    -8.1000,    0.1000,    2.0000,    0.2000,    0.2000,    4.0000, 
    8.1000,    0.1000,    2.0000,    0.2000,    0.2000,    4.0000,
         0,    0.1000,    3.9000,   16.0000,    0.2000,    0.2000,
   -8.1000,   29.9000,    2.0000,    0.2000,    0.2000,    4.0000,
    8.1000,   29.9000,    2.0000,    0.2000,    0.2000,    4.0000,
         0,   29.9000,    3.9000,   16.0000,    0.2000,    0.2000,
         0,    3.0000,    1.0000,    1.0000,    0.5000,    2.0000,
    2.0000,   10.0000,    0.5000,    4.0000,    0.5000,    1.0000,
    4.5000,   10.0000,    2.0000,    1.0000,    0.5000,    4.0000,
   -2.0000,   18.0000,    2.0000,    2.0000,    0.5000,    4.0000,
   -1.0000,   20.0000,    2.0000,    0.5000,    4.0000,    4.0000,
   -3.0000,   15.0000,    3.5000,    0.5000,    6.0000,    1.0000,
   -3.0000,   10.0000,    2.0000,    0.5000,    4.0000,    4.0000,
    1.5000,   25.0000,    2.0000,    1.0000,    0.5000,    4.0000,
    4.0000,   25.0000,    3.0000,    4.0000,    0.5000,    2.0000};

    double tShape[3] = {0,0,0};
    double tCoord[3] = {0,0,0};

    for (int i=0;i <  85; i+=6) {
        sdf::SDF boxSDF;
        strI = std::to_string(i%15);

        tCoord[0] = tData[i];
        tCoord[1] = tData[i+1];
        tCoord[2] = tData[i+2];
        tShape[0] = tData[i+3];
        tShape[1] = tData[i+4];
        tShape[2] = tData[i+5];
    
        strX = std::to_string(tCoord[0]);
        strY = std::to_string(tCoord[1]);
        strZ = std::to_string(tCoord[2]);

        strDimX = std::to_string(tShape[0]);
        strDimY = std::to_string(tShape[1]);
        strDimZ = std::to_string(tShape[2]);

        boxSDF.SetFromString(
           "<sdf version ='1.5'>\
              <model name ='box"+strI+"'>\
                <pose>"+strX+" "+strY+" "+strZ+" 0 0 0</pose>\
                <static>1</static>\
                <link name ='link'>\
                  <pose>0 0 0 0 0 0</pose>\
                  <collision name ='collision'>\
                    <geometry>\
                      <box><size>"+strDimX+" "+strDimY+" "+strDimY+"</size></box>\
                    </geometry>\
                  </collision>\
                  <visual name ='visual'>\
                    <geometry>\
                      <box><size>"+strDimX+" "+strDimY+" "+strDimZ+"</size></box>\
                    </geometry>\
                  </visual>\
                </link>\
              </model>\
            </sdf>");
        // Demonstrate using a custom model name.
        sdf::ElementPtr model = boxSDF.Root()->GetElement("model");
        model->GetAttribute("name")->SetFromString("unique_i"+strI);
        _parent->InsertModelSDF(boxSDF);
        
        std::cerr << tCoord[0] << " " <<  tCoord[1] << " " <<  tCoord[2] << " " <<   "\n";
        std::cerr << tShape[0] << " " <<  tShape[1] << " " <<  tShape[2] << " " <<   "\n";
    }

  }
};

// Register this plugin with the simulator
GZ_REGISTER_WORLD_PLUGIN(Factory)
}
