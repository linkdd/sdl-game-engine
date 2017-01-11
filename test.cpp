#include <sge/sge.hpp>
#include <iostream>
#include <memory>
#include <config.h>

using namespace std;
using namespace sge;

class TestScene : public Scene
{
    public:
        virtual void load(Engine &engine)
        {
            shared_ptr<TileMapNode> tmap = make_shared<TileMapNode>("tmap"s, engine);
            tmap->set_tilemap("rsrc/map.json");
            tmap->set_pos(50, 50);
            tmap->set_viewport(0, 0, 4, 4);

            root_node = tmap;
        }

        virtual void unload(Engine &engine)
        {
            root_node.reset();
        }
};

int main()
{
    Configuration conf;
    int retcode = 0;

    conf.set("fps", 60)
        .set("display/width", 1024)
        .set("display/height", 768)
        .set("display/fullscreen", true)
        .set("display/resizable", false)
        .set("assets/file/location", SGE_SOURCE_DIR);

    try
    {
        Engine engine(conf);

        engine.actions().register_keyboard_action("ui_quit", SDLK_ESCAPE);

        engine.mainloop().queue_process_handler(
            [&](Uint32 delta)
            {
                if (engine.actions().is_action_pressed("ui_quit"))
                {
                    engine.mainloop().quit();
                }
            }
        );

        auto testscene = make_shared<TestScene>();
        engine.scenes().add_scene("test", testscene);
        engine.scenes().switch_to_scene("test");

        engine.mainloop().run();
    }
    catch (const Exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        retcode = 1;
    }

    return retcode;
}
