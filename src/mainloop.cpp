#include <sge/mainloop.hpp>

namespace sge
{
    SGEMainLoop::SGEMainLoop(int fps) : running(false), fps(fps)
    {}

    void SGEMainLoop::add_event_watcher(EventHandler handler, void *user_data)
    {
        evtwatchers.push_back(EventEntry(handler, user_data));
    }

    void SGEMainLoop::remove_event_watcher(EventHandler handler)
    {
        for (auto it = evtwatchers.begin(); it != evtwatchers.end(); it++)
        {
            if (it->get<0>() == handler)
            {
                evtwatchers.erase(it);
                break;
            }
        }
    }

    void SGEMainLoop::queue_event_handler(Uint32 evtype, EventHandler handler, void *user_data)
    {
        events[evtype].push_back(EventEntry(handler, user_data));
    }

    void SGEMainLoop::dequeue_event_handler(Uint32 evtype, EventHandler handler)
    {
        if (events.find(evtype) != events.end())
        {
            auto handlers = events[evtype];

            for (auto it = handlers.begin(); it != handlers.end(); it++)
            {
                if (it->get<0>() == handler)
                {
                    handlers.erase(it);
                    break;
                }
            }
        }
    }

    void SGEMainLoop::queue_process_handler(ProcessHandler handler, void *user_data)
    {
        SGETimer timer;
        timer.start();

        processing.push_back(ProcessEntry(handler, timer, user_data));
    }

    void SGEMainLoop::dequeue_process_handler(EventHandler handler)
    {
        for (auto it = processing.begin(); it != processing.end(); it++)
        {
            if (it->get<0>() == handler)
            {
                processing.erase(it);
                break;
            }
        }
    }

    void SGEMainLoop::queue_draw_handler(DrawHandler, void *user_data)
    {
        drawing.push_back(DrawEntry(handler, user_data))
    }

    void SGEMainLoop::dequeue_draw_handler(EventHandler handler)
    {
        for (auto it = drawing.begin(); it != drawing.end(); it++)
        {
            if (it->get<0>() == handler)
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
                    auto handler = it->get<0>();
                    auto user_data = it->get<1>();

                    if(!handler(this, &event, user_data))
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
                        auto handler = it->get<0>();
                        auto user_data = it->get<1>();

                        if (!handler(this, &event, user_data))
                        {
                            break;
                        }
                    }
                }
            }

            for (auto it = processing.begin(); it != processing.end(); it++)
            {
                auto handler = it->get<0>();
                auto timer = it->get<1>();
                auto user_data = it->get<2>();

                handler(this, timer.get_ticks(), user_data);
                timer.start();
            }

            for (auto it = drawing.begin(); it != drawing.end(); it++)
            {
                auto handler = it->get<0>();
                auto user_data = it->get<1>();

                handler(this, user_data);
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
