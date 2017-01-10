#ifndef __SGE_EXCEPTION_HPP
#define __SGE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace sge
{
    class Exception : public std::runtime_error
    {
        public:
            Exception(const std::string &domain, const std::string &msg) throw() : runtime_error("[" + domain + "] " + msg) {}
            virtual ~Exception() noexcept {}
    };
}

#endif /* __SGE_EXCEPTION_HPP */
