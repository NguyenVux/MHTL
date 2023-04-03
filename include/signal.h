#pragma once
#include <functional>
#include <type_traits>
#include <iostream>
#include <string>
#include "utils.h"


namespace MHTL
{

template<class FUNC>
class signal_t{
    static_assert(std::is_function<FUNC>::value,"cannot create non-callable signal");
    std::function<FUNC> m_function;
    
};

template<class Signal,class AccessKey>
class Access
{
public:
    //static_assert(is_template_of<Signal, public_signal_t>::value,"This is not a signal");
    static void access(const Signal& signal)
    {
        std::cout << signal.t << std::endl;
    }
};

template<class SignalImpl,class AccessKey>
class public_signal_t{
    //static_assert(is_template_of<SignalImpl,signal_t>::value,"This is not a signal impl");
    using public_t = public_signal_t<SignalImpl,AccessKey>;
    using private_t = signal_t<SignalImpl>;
private:
    friend class Access<public_t,AccessKey>;
    mutable private_t m_privateSignal;
    std::string t = "test";
    
};



} // namespace MHTL
