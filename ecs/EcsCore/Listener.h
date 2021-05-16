#ifndef _EcsCore_Listener_h_
#define _EcsCore_Listener_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


template<typename T>
class ListenerCollection {
public:
	void Add(Ref<T> listener) {
		Mutex::Lock lock(mtx);
		m_listeners.Add(listener);
	}
	
	void Remove(Ref<T> listener) {
		Mutex::Lock lock(mtx);
		EraseIf(&m_listeners, [&listener](const Weak<T>& weak) {
			Ref<T> ptr = weak.Enter();
			return ptr == listener;
		});
	}
	
	Vector<Ref<T>> PurgeAndGetListeners() {
		Vector<Ref<T>> result;
		{
			Mutex::Lock lock(mtx);
			EraseIf(&m_listeners, [&result](const Weak<T>& weak) {
				Ref<T> ptr = weak.Enter();
				if (ptr) {
					result.Add(pick(ptr));
					return false;
				} else {
					return true;
				}
			}
				   );
		}
		return result;
	}
	
	virtual ~ListenerCollection() {
		ASSERT(m_listeners.IsEmpty());
	}
	
private:
	Mutex mtx;
	Array < Weak < T >> m_listeners;
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif

