#ifndef __SGE_AUDIOMANAGER_HPP
#define __SGE_AUDIOMANAGER_HPP

#include <sge/engine-forward.hpp>
#include <sge/assets/loaders/audio.hpp>

#include <unordered_map>
#include <utility>
#include <vector>

namespace sge
{
    using SoundTrack = std::pair<std::string, std::shared_ptr<Mix_Music>>;

    class SoundTrackManager
    {
        public:
            SoundTrackManager(Engine &engine);

            void add(const std::string &assetname);
            void remove(const std::string &assetname);
            void clear();

            void repeat(bool enabled);

            void play();
            void pause();
            void stop();

        private:
            void finished();

        private:
            Engine &engine;

            bool repeat_enabled{false};
            std::vector<SoundTrack> playlist;
            int track{0};
    };

    class SoundEffectManager
    {
        public:
            SoundEffectManager(Engine &engine);

            void add(const std::string &assetname);
            void remove(const std::string &assetname);
            void clear();

            void play(const std::string &assetname, int loops);

        private:
            void finished(int channel);

        private:
            Engine &engine;
            std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> effects;
            std::vector<int> available_channels;
    };

    class AudioManager
    {
        public:
            AudioManager(Engine &engine);

            SoundTrackManager &soundtrack();
            SoundEffectManager &soundeffects();

        private:
            SoundTrackManager soundtrackmgr;
            SoundEffectManager soundeffectmgr;
    };
}

#endif /* __SGE_AUDIOMANAGER_HPP */
