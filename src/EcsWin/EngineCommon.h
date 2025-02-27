#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace detail {
	
// We declare an explicit wrapper around type_info to allow copying/passing objects around. 
class type_id : std::reference_wrapper<const type_info>
{
    type_id() = delete;

public:
    using reference_wrapper::reference_wrapper;

    size_t hash_code() const { return get().hash_code(); }
    char const* name() const { return get().name(); }

    bool operator==(type_id const& other) const
    {
        return get() == other.get();
    }

    bool operator!=(type_id const& other) const
    {
        return !(*this == other);
    }

    bool operator<(type_id const& other) const
    {
        return get().before(other);
    }
};

template<typename T>
using unordered_type_map = std::unordered_map<type_id, T>;

template<typename T>
using type_map = std::map<type_id, T>;

}

template<typename... Args>
void debug_log(char const* formatStr, Args&&... args)
{
    if (IsDebuggerPresent())
    {
        static char buffer[1024];
        const int written = sprintf_s(buffer, _countof(buffer) - 2, formatStr, std::forward<Args>(args)...);
        buffer[written] = '\n';
        buffer[written+1] = '\0';
        OutputDebugStringA(buffer);
    }
}

inline void fail_fast(std::optional<std::string> message = std::nullopt)
{
    if (message) 
        debug_log(message.value().c_str());

    __debugbreak();
}

inline void fail_fast_if(bool condition, std::optional<std::string> message = std::nullopt)
{
    if (condition) fail_fast(std::move(message));
}


// Helper to cast between similar basic types, i.e. XMFLOAT3 and float3. Same memory layout, just different typenames
template<typename T1, typename T2>
T1& HelperCastRef(T2& val)
{
    static_assert(sizeof(T1) == sizeof(T2), "Sizes should be the same");
    return *reinterpret_cast<T1*>(&val);
}

template<typename T1, typename T2>
const T1& HelperCastRef(const T2& val)
{
    static_assert(sizeof(T1) == sizeof(T2), "Sizes should be the same");
    return *reinterpret_cast<const T1*>(&val);
}



template<typename Container, typename Predicate>
void erase_if(Container* container, Predicate&& predicate)
{
    container->erase(std::remove_if(container->begin(), container->end(), std::move(predicate)), container->end());
}

#if 0

class Destroyable
{
public:
    virtual ~Destroyable() = default;

    virtual void Destroy() { m_destroyed = true; }
    virtual bool IsDestroyed() const { return m_destroyed; }

    template<typename Container>
    static void PruneFromContainer(Container* container)
    {
        erase_if(container, [](const auto& obj)
        {
            return obj->IsDestroyed();
        });
    }

protected:
    bool m_destroyed{ false };
};

class Enableable
{
public:
    virtual ~Enableable() = default;

    virtual void SetEnabled(bool enable) { m_enabled = enable; }
    virtual bool IsEnabled() const { return m_enabled; }

protected:
    bool m_enabled{ true };
};

template<typename T, typename ProducerT>
class Factory
{
public:
    using Type = T;
    using Producer = ProducerT;

    void RegisterProducer(const detail::type_id& typeId, Producer producer)
    {
        auto it = m_producers.find(typeId);

        fail_fast_if(it != m_producers.end(), "multiple registrations for the same type is not allowed");

        m_producers.insert(it, { typeId, std::move(producer) });
    }

protected:
    detail::unordered_type_map<ProducerT> m_producers;
};

#endif


NAMESPACE_TOPSIDE_END


// Specialization for our type_id
namespace std {
template<>
struct hash<TS::detail::type_id> {
    size_t operator()(const TS::detail::type_id& id) const {
        return id.hash_code();
    }
};
}


