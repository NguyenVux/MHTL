#pragma once
#include <functional>
#include <type_traits>
#include <iostream>
#include <string>
#include "utils.h"


namespace MHTL
{
template<class FUNC>
class signalImpl_t{
public:
    using signature = FUNC;
    static_assert(std::is_function<FUNC>::value,"cannot create non-callable signal");
private:
    std::function<FUNC> m_function;
   
public:
    void emit()
    {
        m_function();
    }
    void connect(std::function<signature> function)
    {
        m_function = function;
    }
};

template<typename AccessKey, typename PublicType, typename PrivateType>
class AccessImpl {
public:
    static const PrivateType& access(const PublicType& publicType) {
        return publicType.get_private_object();
    }

    static PrivateType& access(PublicType& publicType) {
        return publicType.get_private_object();
    }
};


template<typename AccessKey,typename PublicType>
auto access(PublicType& signal) -> typename PublicType::private_t&
{
    return AccessImpl<AccessKey,PublicType,typename PublicType::private_t>::access(signal);
}
template<typename AccessKey,typename PublicType>
auto access(const PublicType& signal) -> const typename PublicType::private_t&
{
    return AccessImpl<AccessKey, PublicType, typename PublicType::private_t>::access(signal);
}

template<class SignalImpl,class AccessKey>
class public_signal_t{
    static_assert(is_template_of<SignalImpl, signalImpl_t>::value,"This is not a signal impl");
public:
    using public_t = public_signal_t<SignalImpl,AccessKey>;
    using private_t = SignalImpl;
    void connect(std::function<typename private_t::signature> function)
    {
        m_privateSignal.connect(function);
    }
private:
    friend class AccessImpl<AccessKey, public_t, private_t>;
    inline private_t& get_private_object() { return m_privateSignal; }
    inline const private_t& get_private_object() const { return m_privateSignal; }
    mutable private_t m_privateSignal;
};



template<typename Signature,typename AccessKey>
using signal_t = public_signal_t<signalImpl_t<Signature>, AccessKey>;
} // namespace MHTL
