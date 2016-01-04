

#ifndef BFC__DEF__H
#define BFC__DEF__H

#include <unistd.h>

#define NAMESPACE_BFC_BEGIN namespace bfc {
#define NAMESPACE_BFC_END   }

#define NAMESPACE_STD_BEGIN namespace std {
#define NAMESPACE_STD_END   }

NAMESPACE_BFC_BEGIN

template<class T>
class rc_ptr
{
public:
    typedef T element_type;
    typedef rc_ptr<T> my_type;

    void release() const
    {
        if (m_p) {
            m_p->release();
            m_p = NULL;
        }
    }

    void assign(const T* p)             {assign_internal(p);}
    void assign(const my_type &p)       {assign_internal(p.m_p);}
    template <class T1>
    void assign(const rc_ptr<T1>& r)    {assign_internal(static_cast<const T*>(r.get()));}

    T*   get() const  {return static_cast<T*>(m_p);}
    T*   detach()     {T *p = m_p; m_p = NULL; return p;}

    bool is_null() const  {return !m_p;}

    T* operator->() const {return m_p;}
    T& operator*()  const {return *m_p;}
    operator bool() const {return !!m_p;}
    operator T*()   const {return m_p;}

private:
    void assign_internal(const T* p) const
    {
        if (m_p == p)
            return;

        if (p)
            p->add_ref();

        release();
        m_p = const_cast<T*>(p);
    }

public:
    rc_ptr(): m_p(NULL)             {;}
    rc_ptr(const T* p): m_p(NULL)   {assign(p);}
    ~rc_ptr()                       {release();}

    rc_ptr(const my_type& r): m_p(NULL)   {assign(r);}
    my_type& operator=(const my_type& r)  {assign(r); return *this;}

    template <class T1>
    rc_ptr(const rc_ptr<T1>& r): m_p(NULL)  {assign(r);}
    template <class T1>
    my_type& operator=(const rc_ptr<T1>& r) {assign(r); return *this;}

private:
    mutable T *m_p;
};

NAMESPACE_BFC_END

#define BFC_RELEASE(x) do {if(x) {x->release(); x = NULL;}} while (0);

#endif
