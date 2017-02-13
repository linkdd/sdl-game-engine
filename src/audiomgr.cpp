#include <sge/utils/callback.hpp>
#include <sge/audiomgr.hpp>
#include <sge/engine.hpp>
#include <iostream>

using namespace std;

namespace sge
{
    typedef void(*music_finished_cb)(void);
    typedef void(*effect_finished_cb)(int);

    SoundTrackManager::SoundTrackManager(Engine &engine) : engine(engine)
    {
        Callback<void(void)>::func = std::bind(&SoundTrackManager::finished, this);
        music_finished_cb fn = static_cast<music_finished_cb>(Callback<void(void)>::callback);

        Mix_HookMusicFinished(fn);
    }

    void SoundTrackManager::finished()
    {
        track++;

        if (track > playlist.size())
        {
            track = 0;
        }
    }

    void SoundTrackManager::add(const string &assetname)
    {
        for (auto &soundtrack : playlist)
        {
            if (soundtrack.first == assetname)
            {
                return;
            }
        }

        AudioDescriptor d(assetname);
        auto asset = engine.assets().load<Audio>(d);

        if (asset != nullptr)
        {
            auto music = asset->music();

            if (music != nullptr)
            {
                playlist.push_back(make_pair(assetname, music));
            }
        }
    }

    void SoundTrackManager::remove(const string &assetname)
    {
        auto it = playlist.begin();

        while (it != playlist.end())
        {
            if (it->first == assetname)
            {
                break;
            }

            it++;
        }

        if (it != playlist.end())
        {
            playlist.erase(it);
        }
    }

    void SoundTrackManager::clear()
    {
        playlist.clear();
    }

    void SoundTrackManager::repeat(bool enabled)
    {
        repeat_enabled = enabled;
    }

    void SoundTrackManager::play()
    {
        if (Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
        else
        {
            auto music = playlist[track];

            if (Mix_PlayMusic (music.second.get(), 1) != 0)
            {
                cerr << "[SoundTrackManager][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }
        }
    }

    void SoundTrackManager::pause()
    {
        if (Mix_PlayingMusic())
        {
            Mix_PauseMusic();
        }
    }

    void SoundTrackManager::stop()
    {
        Mix_HaltMusic();
    }

    SoundEffectManager::SoundEffectManager(Engine &engine) : engine(engine)
    {
        Callback<void(int)>::func = std::bind(&SoundEffectManager::finished, this, std::placeholders::_1);
        effect_finished_cb fn = static_cast<effect_finished_cb>(Callback<void(int)>::callback);

        Mix_ChannelFinished(fn);
    }

    void SoundEffectManager::finished(int channel)
    {
        available_channels.push_back(channel);
    }

    void SoundEffectManager::add(const string &assetname)
    {
        if (effects.find(assetname) == effects.end())
        {
            AudioDescriptor d(assetname);
            auto audio = engine.assets().load<Audio>(d);

            if (audio != nullptr)
            {
                auto effect = audio->effect();

                if (effect != nullptr)
                {
                    effects[assetname] = effect;

                    int nchannels = Mix_AllocateChannels(-1);
                    int expected = effects.size();

                    if (nchannels < expected)
                    {
                        Mix_AllocateChannels(expected);
                    }

                    for (int i = nchannels; i < expected; i++)
                    {
                        available_channels.push_back(i);
                    }
                }
            }
        }
    }

    void SoundEffectManager::remove(const string &assetname)
    {
        if (effects.find(assetname) != effects.end())
        {
            effects.erase(assetname);
        }
    }

    void SoundEffectManager::clear()
    {
        effects.clear();
    }

    void SoundEffectManager::play(const string &assetname, int loops)
    {
        if (effects.find(assetname) != effects.end())
        {
            if (!available_channels.empty())
            {
                cerr << "[SoundEffectManager][ERROR] Impossible to play sound effect: no available channel" << endl;
                return;
            }

            auto effect = effects[assetname];
            int channel = available_channels.back();
            available_channels.pop_back();

            if (Mix_PlayChannel(channel, effect.get(), loops) < 0)
            {
                cerr << "[SoundEffectManager][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }
        }
    }

    AudioManager::AudioManager(Engine &engine) : soundtrackmgr(engine), soundeffectmgr(engine) {}

    SoundTrackManager &AudioManager::soundtrack()
    {
        return soundtrackmgr;
    }

    SoundEffectManager &AudioManager::soundeffects()
    {
        return soundeffectmgr;
    }
}
