#ifndef _OpenLib_Common_h_
#define _OpenLib_Common_h_

NAMESPACE_OULU_BEGIN


template <typename T>
class TrackChanges
{
public:
    TrackChanges() = default;
    TrackChanges(TrackChanges<T>&& o) : value(std::move(o.value)) { }
    TrackChanges(const TrackChanges<T>& o) : value(o.Get()) { }

    TrackChanges<T>& operator=(TrackChanges<T>&& o)
    {
        ++change_count;
        value = std::move(o.value);
        return *this;
    }

    TrackChanges<T>& operator=(const TrackChanges<T>& o)
    {
        ++change_count;
        value = o.value;
        return *this;
    }

    template <typename Func>
    void Set(Func func)
    {
        ++change_count;
        func(value);
    }

    bool UpdateChangeCountBookmark(Atomic& change_count_bookmark) const {
        return change_count_bookmark.exchange(change_count) != change_count_bookmark;
    }

    const T& Get() const { return value; }

private:
    T value;
    Atomic change_count{ 0 };
};


NAMESPACE_OULU_END
#endif
