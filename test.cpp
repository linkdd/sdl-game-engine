#include <sge/sge.hpp>
#include <iostream>
#include <memory>
#include <config.h>

using namespace std;
using namespace sge;

int main()
{
    Configuration conf;
    int retcode = 0;

    conf.set("fps", 60)
        .set("display/width", 1024)
        .set("display/height", 768)
        .set("display/fullscreen", true)
        .set("display/resizable", false)
        .set("assets/file/location", string(SGE_SOURCE_DIR));

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

        ImageDescriptor descriptor("test.png");
        Image *img = engine.assets().load<Image, ImageDescriptor>(descriptor);

        engine.mainloop().run();

        engine.assets().unload(img);
    }
    catch (Exception const &e)
    {
        cerr << "Error: " << e.what() << endl;
        retcode = 1;
    }

    return retcode;
}
