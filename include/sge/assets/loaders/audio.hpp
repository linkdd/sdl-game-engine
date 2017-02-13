#ifndef __SGE_AUDIO_LOADER_HPP
#define __SGE_AUDIO_LOADER_HPP

#include <sge/assets/loader.hpp>

#include <SDL.h>
#include <SDL_mixer.h>

namespace sge
{
    class Audio : public Asset<SDL_RWops *>
    {
        using Asset<SDL_RWops *>::Asset;

        public:
            std::shared_ptr<Mix_Music> music();
            std::shared_ptr<Mix_Chunk> effect();
    };

    class AudioDescriptor : public AssetDescriptor
    {
        using AssetDescriptor::AssetDescriptor;
    };

    class AudioLoader : public AssetLoader
    {
        public:
            virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_AUDIO_LOADER_HPP */