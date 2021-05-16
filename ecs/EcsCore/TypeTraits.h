#ifndef _EcsCore_TypeTraits_h_
#define _EcsCore_TypeTraits_h_


NAMESPACE_TOPSIDE_BEGIN

template <typename Base, typename... Ts>
using AllRefBaseOf = AllTrue<std::is_base_of<Base, typename Ts::Type>::value...>;

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
struct RTupleAllComponents<RTuple<Ts...>> : AllRefBaseOf<ComponentBase, Ts...> {};

NAMESPACE_TOPSIDE_END

#endif
