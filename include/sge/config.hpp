#ifndef __SGE_CONFIG_HPP
#define __SGE_CONFIG_HPP

#include <unordered_map>
#include <string>

namespace sge
{
    class Configuration
    {
        public:
            std::string gets(std::string const &param, std::string const &_default = std::string()) const;
            int geti(std::string const &param, int _default = 0) const;
            bool getb(std::string const &param, bool _default = false) const;
            float getf(std::string const &param, float _default = 0.0) const;

            Configuration &set(std::string const &param, std::string const &value);
            Configuration &set(std::string const &param, int value);
            Configuration &set(std::string const &param, bool value);
            Configuration &set(std::string const &param, float value);

        private:
            std::unordered_map<std::string, std::string> kvdb;
    };
}

#endif /* __SGE_CONFIG_HPP */