#ifndef __SGE_CONFIG_HPP
#define __SGE_CONFIG_HPP

#include <unordered_map>
#include <string>

namespace sge
{
    class Configuration
    {
        public:
            std::string gets(const std::string &param, const std::string &_default = std::string()) const;
            int geti(const std::string &param, int _default = 0) const;
            bool getb(const std::string &param, bool _default = false) const;
            float getf(const std::string &param, float _default = 0.0) const;

            Configuration &set(const std::string &param, const std::string &value);
            Configuration &set(const std::string &param, int value);
            Configuration &set(const std::string &param, bool value);
            Configuration &set(const std::string &param, float value);

        private:
            std::unordered_map<std::string, std::string> kvdb;
    };
}

#endif /* __SGE_CONFIG_HPP */