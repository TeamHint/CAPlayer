

#ifndef BFC__OBJECT__H
#define BFC__OBJECT__H

#include <assert.h>
#include "bfc__def.h"

NAMESPACE_BFC_BEGIN

class object
{
public:
    int add_ref() const
    {
        return __sync_add_and_fetch(&m_ref_count, 1);
    }

    int release() const
    {
        int ref_count = __sync_sub_and_fetch(&m_ref_count, 1);
        assert(ref_count >= 0);
        if (ref_count == 0)
            delete this;
        return ref_count;
    }

    int _get_ref() const {return m_ref_count;}

private:
    volatile int m_ref_count;

protected:
    object(): m_ref_count(0) {;}
    virtual ~object() {;}

private:
    object(const object&);
    object &operator=(const object&);
};

typedef rc_ptr<object> object_ptr;

NAMESPACE_BFC_END

#endif
