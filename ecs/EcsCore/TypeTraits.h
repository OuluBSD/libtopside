#ifndef _EcsCore_TypeTraits_h_
#define _EcsCore_TypeTraits_h_


NAMESPACE_OULU_BEGIN

template<typename T>
using IsComponent = std::is_base_of<ComponentBase, T>;

template<typename T>
using IsSystem = std::is_base_of<SystemBase, T>;

template<typename... Ts>
using AllComponents = AllBaseOf<ComponentBase, Ts...>;

template<typename... Ts>
using AllSystems = AllBaseOf<SystemBase, Ts...>;

template <typename Tuple>
struct RTupleAllComponents : std::false_type {};

template <typename... Ts>
struct RTupleAllComponents<RTuple<Ts...>> : AllBaseOf<ComponentBase, Ts...> {};

NAMESPACE_OULU_END

#endif
