#pragma once


NAMESPACE_TOPSIDE_BEGIN


// ListenerCollection
// Collection of weak_ptr's and helper functions to remove objects that don't exist anymore
template<typename T, typename Parent=T::Parent>
class ListenerCollection
{
public:
	using R = Ref<T,Parent>;
	
    void Add(R listener)
    {
        TODO
        /*std::unique_lock<std::mutex> lock(m_mutex);
        m_listeners.push_back(std::move(listener));*/
    }

    void Remove(R listener)
    {
        TODO
        /*std::unique_lock<std::mutex> lock(m_mutex);
        erase_if(&m_listeners, [&listener](const std::weak_ptr<T>& weak)
        {
            std::shared_ptr<T> ptr = weak.lock();
            return ptr == listener;
        });*/
    }

    Array<R> PurgeAndGetListeners()
    {
        TODO
        /*Array<Ref<T>> result;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            erase_if(&m_listeners, [&result](const std::weak_ptr<T>& weak)
            {
                std::shared_ptr<T> ptr = weak.lock();
                if (ptr)
                {
                    result.push_back(std::move(ptr));
                    return false;
                }
                else
                {
                    return true;
                }
            });
        }
        return result;*/
    }

    virtual ~ListenerCollection()
    {
        TODO
        //fail_fast_if(!m_listeners.empty());
    }

private:
    Mutex m_mutex;
    Array<R> m_listeners;
    
    
};


NAMESPACE_TOPSIDE_END
