#ifndef _EcsMach_TypeTraits_h_
#define _EcsMach_TypeTraits_h_


NAMESPACE_ECS_BEGIN

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

NAMESPACE_ECS_END

#endif
