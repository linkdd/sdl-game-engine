#ifndef __SGE_EXCEPTION_HPP
#define __SGE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace sge
{
    class Exception : public std::runtime_error
    {
        public:
            Exception(std::string const &domain, std::string const &msg) throw() : runtime_error("[" + domain + "] " + msg) {}
            virtual ~Exception() throw() {}
    };
}

#endif /* __SGE_EXCEPTION_HPP */
