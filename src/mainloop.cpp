#include <sge/mainloop.hpp>

using namespace std;

namespace sge
{
    template<typename T, typename... U>
    static bool functions_equal(function<T(U...)> a, function<T(U...)> b)
    {
        typedef T(*fptr)(U...);
        fptr **pa = a.template target<fptr*>();
        fptr **pb = b.template target<fptr*>();

        return (*pa) == (*pb);
    }

    SGEMainLoop::SGEMainLoop(int fps) : running(false), fps(fps)
    {}

    void SGEMainLoop::add_event_watcher(EventHandler handler)
    {
        evtwatchers.push_back(std::move(handler));
    }

    void SGEMainLoop::remove_event_watcher(EventHandler handler)
    {
        for (auto it = evtwatchers.begin(); it != evtwatchers.end(); it++)
        {
            if (functions_equal(*it, handler))
            {
                evtwatchers.erase(it);
                break;
            }
        }
    }

    void SGEMainLoop::queue_event_handler(Uint32 evtype, EventHandler handler)
    {
        events[evtype].push_back(std::move(handler));
    }

    void SGEMainLoop::dequeue_event_handler(Uint32 evtype, EventHandler handler)
    {
        if (events.find(evtype) != events.end())
        {
            auto handlers = events[evtype];

            for (auto it = handlers.begin(); it != handlers.end(); it++)
            {
                if (functions_equal(*it, handler))
                {
                    handlers.erase(it);
                    break;
                }
            }
        }
    }

    void SGEMainLoop::queue_process_handler(ProcessHandler handler)
    {
        SGETimer timer;
        timer.start();

        processing.push_back(std::make_tuple(std::move(handler), std::move(timer)));
    }

    void SGEMainLoop::dequeue_process_handler(ProcessHandler handler)
    {
        for (auto it = processing.begin(); it != processing.end(); it++)
        {
            if (functions_equal(get<0>(*it), handler))
            {
                processing.erase(it);
                break;
            }
        }
    }

    void SGEMainLoop::queue_draw_handler(DrawHandler handler)
    {
        drawing.push_back(std::move(handler));
    }

    void SGEMainLoop::dequeue_draw_handler(DrawHandler handler)
    {
        for (auto it = drawing.begin(); it != drawing.end(); it++)
        {
            if (functions_equal(*it, handler))
            {
                drawing.erase(it);
                break;
            }
        }
    }

    void SGEMainLoop::run()
    {
        running = true;

        while (running)
        {
            fps_timer.start();

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                bool accepted = true;

                for (auto it = evtwatchers.begin(); it != evtwatchers.end(); it++)
                {
                    auto handler = *it;

                    if(!handler(&event))
                    {
                        accepted = false;
                        break;
                    }
                }

                if (accepted && events.find(event.type) != events.end())
                {
                    auto handlers = events[event.type];

                    for (auto it = handlers.begin(); it != handlers.end(); it++)
                    {
                        auto handler = *it;

                        if (!handler(&event))
                        {
                            break;
                        }
                    }
                }
            }

            for (auto it = processing.begin(); it != processing.end(); it++)
            {
                auto handler = get<0>(*it);
                auto timer = get<1>(*it);

                handler(timer.get_ticks());
                timer.start();
            }

            for (auto it = drawing.begin(); it != drawing.end(); it++)
            {
                auto handler = *it;

                handler();
            }

            Uint32 ticks = fps_timer.get_ticks();
            if (fps > 0 && ticks < 1000.0 / fps)
            {
                SDL_Delay((1000.0 / fps) - ticks);
            }
        }
    }

    void SGEMainLoop::quit()
    {
        running = false;
    }
}
