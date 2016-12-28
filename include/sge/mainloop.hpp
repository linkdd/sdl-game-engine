#ifndef __SGE_MAINLOOP_HPP
#define __SGE_MAINLOOP_HPP

#include <sge/timer.hpp>
#include <SDL.h>

#include <unordered_map>
#include <functional>
#include <tuple>
#include <list>

namespace sge
{
    class SGEMainLoop;

    using EventHandler = std::function<bool(SGEMainLoop *, SDL_Event *)>;
    using ProcessHandler = std::function<void(SGEMainLoop *, int)>;
    using DrawHandler = std::function<void(SGEMainLoop *)>;

    using EventEntry = std::tuple<EventHandler>;
    using ProcessEntry = std::tuple<ProcessHandler, SGETimer>;
    using DrawEntry = std::tuple<DrawHandler>;

    class SGEMainLoop
    {
        public:
            SGEMainLoop(int fps);

            void add_event_watcher(EventHandler handler);
            void remove_event_watcher(EventHandler handler);

            void queue_event_handler(Uint32 evtype, EventHandler handler);
            void dequeue_event_handler(Uint32 evtype, EventHandler handler);

            void queue_process_handler(ProcessHandler handler);
            void dequeue_process_handler(ProcessHandler handler);

            void queue_draw_handler(DrawHandler handler);
            void dequeue_draw_handler(DrawHandler handler);

            void run();
            void quit();

        private:
            int fps;
            bool running;
            SGETimer fps_timer;

            std::list<EventEntry> evtwatchers;
            std::unordered_map<Uint32, std::list<EventEntry>> events;
            std::list<ProcessEntry> processing;
            std::list<DrawEntry> drawing;
    };
}

#endif /* __SGE_MAINLOOP_HPP */
