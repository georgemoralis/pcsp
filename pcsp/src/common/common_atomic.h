#ifndef common_atomic_h__
#define common_atomic_h__

template< typename T > class Atomic {}

template< > class Atomic< int > : public QBasicAtomicInt
{
public:
    Atomic(int value = int())
    {
        this->fetchAndStoreRelease(value);
    }

    Atomic(Atomic const &another)
    {
        this->fetchAndStoreRelease(another);
    }

    inline bool operator ==(int value) const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) == value;
    }

    inline bool operator !=(int value) const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) != value;
    }

    inline bool operator !() const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) == 0;
    }

    inline operator int() const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0);
    }

    inline Atomic &operator =(int value)
    {
        this->fetchAndStoreRelease(value);
        return *this;
    }

    inline Atomic &operator =(Atomic const &another)
    {
        this->fetchAndStoreRelease(another);
        return *this;
    }
};

template< typename T > class Atomic< T * > : public QBasicAtomicPointer
{
public:
    Atomic(T *pointer = 0)
    {
        this->fetchAndStoreRelease(value);
    }

    inline bool operator ==(T *pointer) const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) == pointer;
    }

    inline bool operator !=(T *pointer) const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) != pointer;
    }

    inline bool operator !() const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0) == 0;
    }

    inline operator int() const
    {
        return const_cast< Atomic const * >(this)->fetchAndAddAcquire(0);
    }

    inline Atomic &operator =(T *pointer)
    {
        this->fetchAndStoreRelease(pointer);
        return *this;
    }
};

#endif // common_atomic_h__