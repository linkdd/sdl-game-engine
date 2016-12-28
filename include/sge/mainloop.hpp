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
    using EventHandler = std::function<bool(SDL_Event *)>;
    using ProcessHandler = std::function<void(int)>;
    using DrawHandler = std::function<void(void)>;

    using ProcessEntry = std::tuple<ProcessHandler, SGETimer>;

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

            std::list<EventHandler> evtwatchers;
            std::unordered_map<Uint32, std::list<EventHandler>> events;
            std::list<ProcessEntry> processing;
            std::list<DrawHandler> drawing;
    };
}

#endif /* __SGE_MAINLOOP_HPP */
