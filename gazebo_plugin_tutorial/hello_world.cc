#include <gazebo/gazebo.hh>

namespace gazebo
{
    class WorldPluginTutorial : public WorldPlugin
    {
        public: WorldPluginTutorial() : WorldPlugin()
        {
            printf("Hello World from the Constructor\n");
        }

        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
        {
            printf("Hello from the Loading Function\n");
        }
    };
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
}
