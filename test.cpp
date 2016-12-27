#include <sge/sge.hpp>
#include <iostream>

using namespace std;
using namespace sge;

int main()
{
    SGEConfiguration conf;
    int retcode = 0;

    conf.set("fps", 60)
        .set("display/width", 1024)
        .set("display/height", 768)
        .set("display/fullscreen", true)
        .set("display/resizable", false);

    try
    {
        SGEngine engine(configuration);

        engine.actions().register_keyboard_action("ui_quit", SDLK_ESCAPE);

        engine.mainloop().queue_process_handler(
            [](SGEMainLoop *mloop, Uint32 delta, SGEngine *engine)
            {
                if (engine->actions().is_action_pressed("ui_quit"))
                {
                    mloop->quit();
                }
            },
            &engine
        );

        SGEImageDescriptor descriptor("test.png");
        SGEImage *img = engine.assets().load<SGEImage, SGEImageDescriptor>(descriptor);

        engine.mainloop().run();

        engine.assets().unload(img);
    }
    catch (SGEException const &e)
    {
        cerr << "Error: " << e.what() << endl;
        retcode = 1;
    }

    return retcode;
}
