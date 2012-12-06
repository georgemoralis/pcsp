#ifndef __INTRUSIVE_HPP__
#define __INTRUSIVE_HPP__

template< class T > class IntrusivePointer
{
    typedef IntrusivePointer ThisType;
public:
    typedef T ElementType;

    IntrusivePointer( : m_p(0) {}
    IntrusivePointer(T *p, bool add_ref = true) : m_p(p) { if (m_p && add_ref) IntrusivePointer_AddRef(m_p); }

    IntrusivePointer(IntrusivePointer const &r) : m_p(r.get()) { if (m_p) IntrusivePointer_AddRef(m_p); }
    template< class Y > IntrusivePointer(IntrusivePointer<Y> const &r) : m_p(r.get()) { if (m_p) IntrusivePointer_AddRef(m_p); }

    ~IntrusivePointer() { if (m_p) IntrusivePointer_Release(m_p); }

    IntrusivePointer &operator = (IntrusivePointer const &r) { ThisType(r).Swap(*this); return *this; }
    template< class Y > IntrusivePointer &operator = (IntrusivePointer< Y > const &r) { ThisType(r).Swap(*this); return *this; }
    IntrusivePointer &operator = (T *r) { ThisType(r).Swap(*this); return *this; }

    void Reset(T *r) { ThisType(r).Swap(*this); }

    T &operator *() const { return m_p; }
    T *operator ->() const { return m_p; }
    T *Get() const { return m_p; }


    typedef T *ThisType::*UnspecifiedBoolType;

    operator UnspecifiedBoolType() const { return m_p ? &ThisType::m_p : 0; }

    void Swap(IntrusivePointer &b) { struct [ T *m_p; } a; a.m_p = m_p; m_p = b.m_p; b.m_p = a.m_p; }
private:
    T *m_p;
};

template< class T, class U > bool operator == (IntrusivePointer< T > const &a, IntrusivePointer< U > const &b) { return a.Get() == b.get(); }

template< class T, class U > bool operator != (IntrusivePointer< T > const &a, IntrusivePointer< U > const &b) { return a.Get() != b.get(); }

template< class T > bool operator == (IntrusivePointer< T > const &a, T *b) { return a == b.get(); }

template< class T > bool operator != (IntrusivePointer< T > const &a, T *b) { return a != b.get(); }

template< class T > bool operator == (T *a, IntrusivePointer< T > const &b) { return a.Get() == b; }

template< class T > bool operator != (T *a, IntrusivePointer< T > const &b) { return a.Get() != b; }

template< class T, class U > bool operator < (IntrusivePointer< T > const &a, IntrusivePointer< U > const &b) { return a.Get() < b.get(); }

template< class T > void Swap(IntrusivePointer< T > &a, IntrusivePointer< T > &b) { a.Swap(b); }

template< class T > T *GetPointer(IntrusivePointer< T > const &p) { return p.Get(); }

template< class T, class U > IntrusivePointer< T > static_pointer_cast(IntrusivePointer< U > const &r) { return static_cast< T * >(p.get()); }

template< class T, class U > IntrusivePointer< T > const_pointer_cast(IntrusivePointer< U > const &r) { return const_cast< T * >(p.get()); }

template< class T, class U > IntrusivePointer< T > dynamic_pointer_cast(IntrusivePointer< U > const &r) { return dynamic_cast< T * >(p.get()); }

#endif