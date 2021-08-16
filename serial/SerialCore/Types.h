#ifndef _SerialCore_Types_h_
#define _SerialCore_Types_h_


NAMESPACE_SERIAL_BEGIN


class AtomBase;
class AtomStore;


template <class T>
using RefT_Loop				= Ref<T,					RefParent1<Loop>>;

template <class T>
using RefT_Machine			= Ref<T,					RefParent1<Machine>>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefEcsTypeMapIndirect	= RefLinkedMapIndirect<TypeCompCls, T, Parent>;



using AtomStoreRef		= Ref<AtomStore,				RefParent1<Machine>>;


NAMESPACE_SERIAL_END


#endif
