#pragma once
#include <type_traits>
namespace MHTL
{
template<class T,template<class> class BASE_TEMPLATE>
struct is_template_of : std::false_type{

};

template<class T,template<class> class BASE_TEMPLATE>
struct is_template_of<BASE_TEMPLATE<T>,BASE_TEMPLATE> : std::true_type{

};

}

