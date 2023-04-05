#pragma once
#include <type_traits>
#include "utils.h"
#include "signals/signals.hpp"


namespace MHTL
{
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
class signal_validator{
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
using signal_t = signal_validator<fteng::SignalImpl<Signature>, AccessKey>;
} // namespace MHTL
