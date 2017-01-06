#include <sge/config.hpp>
#include <iostream>
#include <sstream>

using namespace std;

namespace sge
{
    template <typename T>
    string to_string(T value)
    {
        ostringstream ss;
        ss << value;
        return ss.str();
    }

    string Configuration::gets(string const &param, string const &_default) const
    {
        string result;

        if (kvdb.find(param) != kvdb.end())
        {
            result = kvdb.at(param);
        }
        else
        {
            result = _default;
        }

        return result;
    }

    int Configuration::geti(string const &param, int _default) const
    {
        return stoi(gets(param, to_string<int>(_default)));
    }

    bool Configuration::getb(string const &param, bool _default) const
    {
        return bool(geti(param, int(_default)));
    }

    float Configuration::getf(string const &param, float _default) const
    {
        return stof(gets(param, to_string<float>(_default)));
    }

    Configuration &Configuration::set(string const &param, string const &value)
    {
        kvdb[param] = value;
        return *this;
    }

    Configuration &Configuration::set(string const &param, int value)
    {
        return set(param, to_string<int>(value));
    }

    Configuration &Configuration::set(string const &param, bool value)
    {
        return set(param, int(value));
    }

    Configuration &Configuration::set(string const &param, float value)
    {
        return set(param, to_string<float>(value));
    }
}