#ifndef common_skew_heap_h__
#define common_skew_heap_h__

template< typename T >
struct SkewHeap 
{
    T *m_lnode;
    T *m_rnode;

    typedef SkewHeap Node;

    __forceinline bool Empty() const { return !this->m_lnode; }
    __forceinline void Clear() { this->m_lnode = 0; this->m_rnode = 0; }
    __forceinline void Merge(T &heap) { if (heap.m_lnode) if (this->m_lnode) Merge(this->m_lnode, heap.m_lnode, &this->m_lnode); else this->m_lnode = heap.m_lnode; }

    __forceinline T const &Front() const { return *this->m_lnode; }
    __forceinline T &Front() { return *this->m_lnode; }
    __forceinline void Enqueue(T &node) { Merge(&node, this->m_lnode, &this->m_lnode); }
    __forceinline void Dequeue() { Merge(this->m_lnode->m_lnode, this->m_lnode->m_rnode, &this->m_lnode); }

private:
    static __forceinline T *Merge(T *lnode, T *rnode)
    {
        if (!lnode)
        {
            return rnode;
        }

        if (!rnode)
        {
            return lnode;
        }

        if (*lnode <= *rnode)
        {
            // h1:(e1, l1, r1) `union` h2:(e2, l2, r2) and e1 <= e2 -> (e1, (h2 `union` r1), l1)
            T *llnode = lnode->m_lnode;
            T *lrnode = lnode->m_rnode;
            lnode->m_rnode = llnode;
            lnode->m_lnode = Merge(rnode, lrnode);
            return lnode;
        }

        // h1:(e1, l1, r1) `union` h2:(e2, l2, r2) and e1 > e2 -> (e2, (h1 `union` r2), l2)
        T *rlnode = rnode->m_lnode;
        T *rrnode = rnode->m_rnode;
        rnode->m_rnode = rlnode;
        rnode->m_lnode = Merge(lnode, rrnode);
        return rnode;
    }

    static __forceinline void Merge(T *lnode, T *rnode, T **result)
    {
        if (!lnode)
        {
            *result = rnode;
            return;
        }

loop:
        if (!rnode)
        {
            *result = lnode;
            return;
        }
      
        if (*lnode <= *rnode)
        {
            // h1:(e1, l1, r1) `union` h2:(e2, l2, r2) and e1 <= e2 -> (e1, (h2 `union` r1), l1)
            T *llnode = lnode->m_lnode;
            T *lrnode = lnode->m_rnode;

            *result        = lnode;
            lnode->m_rnode = llnode;
            result         = &lnode->m_lnode;
            lnode          = rnode;
            rnode          = lrnode;
        }
        else
        {
            // h1:(e1, l1, r1) `union` h2:(e2, l2, r2) and e1 > e2 -> (e2, (h1 `union` r2), l2)
            T *rlnode = rnode->m_lnode;
            T *rrnode = rnode->m_rnode;

            *result        = rnode;
            rnode->m_rnode = rlnode;
            result         = &rnode->m_lnode;
            rnode          = rrnode;
        }

        goto loop;
    }
};

#endif