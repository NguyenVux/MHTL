#pragma once
#include <type_traits>
#include "utils.h"
#include "signals/signals.hpp"



namespace MHTL
{

template<typename AccessKey, typename Signature> class signal_validator;

template<typename AccessKey, typename PublicType,typename PrivateType>
struct AccessImpl
{
    static const PrivateType &access(const PublicType& signal_val)
    {
		return signal_val.get_private_object();
    }
    static PrivateType &access(PublicType& signal_val)
    {
		return signal_val.get_private_object();
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

template<typename AccessKey, typename ...Args>
class signal_validator<AccessKey, void(Args...)> {
public:
    using public_t = signal_validator<AccessKey, void(Args...)>;
    using private_t = fteng::SignalImpl<void(Args...)>;


	template<auto PMF, class C>
	fteng::connection connect(C* object) const
	{
		return std::move(m_privateSignal.connect<PMF,C>(object));
	}

	template<auto func>
	fteng::connection connect() const
	{
		return std::move(m_privateSignal.connect(func));
	}

	fteng::connection connect(void(*func)(Args...)) const
	{
		return std::move(m_privateSignal.connect(func));
	}

	template<typename F>
	fteng::connection connect(F&& functor) const
	{
		return std::move(m_privateSignal.connect(functor));
	}
private:
    friend class AccessImpl<AccessKey, public_t, private_t>;
    inline private_t& get_private_object() { return m_privateSignal; }
    inline const private_t& get_private_object() const { return m_privateSignal; }
    mutable private_t m_privateSignal;
};



template<typename Signature,typename AccessKey>
using public_signal_t = signal_validator<AccessKey, Signature>;
} // namespace MHTL
