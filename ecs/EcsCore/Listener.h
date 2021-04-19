#ifndef _EcsCore_Listener_h_
#define _EcsCore_Listener_h_


NAMESPACE_OULU_BEGIN


template<typename T>
class ListenerCollection {
public:
	void Add(Shared<T> listener) {
		Mutex::Lock lock(mtx);
		m_listeners.Add(listener);
	}
	
	void Remove(Shared<T> listener) {
		Mutex::Lock lock(mtx);
		EraseIf(&m_listeners, [&listener](const Weak<T>& weak) {
			Shared<T> ptr = weak.Enter();
			return ptr == listener;
		});
	}
	
	Vector<Shared<T>> PurgeAndGetListeners() {
		Vector<Shared<T>> result;
		{
			Mutex::Lock lock(mtx);
			EraseIf(&m_listeners, [&result](const Weak<T>& weak) {
				Shared<T> ptr = weak.Enter();
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


NAMESPACE_OULU_END

#endif
