#include <sge/assets/loaders/audio.hpp>
#include <iostream>

using namespace std;

namespace sge
{
    shared_ptr<Mix_Music> Audio::music()
    {
        if (loaded())
        {
            SDL_RWops *audiodata = asset();
            auto music = Mix_LoadMUS_RW(audiodata, 0);

            if (music != nullptr)
            {
                return shared_ptr<Mix_Music>(music, Mix_FreeMusic);
            }
            else
            {
                cerr << "[Audio][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }
        }

        return nullptr;
    }

    shared_ptr<Mix_Chunk> Audio::effect()
    {
        if (loaded())
        {
            SDL_RWops *audiodata = asset();
            auto effect = Mix_LoadWAV_RW(audiodata, 0);

            if (effect != nullptr)
            {
                return shared_ptr<Mix_Chunk>(effect, Mix_FreeChunk);
            }
            else
            {
                cerr << "[Audio][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }

        }

        return nullptr;
    }

    void AudioLoader::load(shared_ptr<BaseAsset> asset, SDL_RWops *input)
    {
        shared_ptr<Audio> audio = static_pointer_cast<Audio>(asset);
        audio->setAsset(input);
    }

    void AudioLoader::unload(BaseAsset *asset)
    {
        if (asset->loaded())
        {
            Audio *audio = static_cast<Audio *>(asset);
            SDL_RWclose(audio->asset());
        }
    }
}
