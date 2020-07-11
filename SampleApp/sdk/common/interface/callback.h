/*---------------------------------------------------------------------------*/
/* callback.h                                                                */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class UCallback {
public:
    virtual void Callback(class ICallback * source) = 0;
};

class ICallback {
public:
    virtual ~ICallback() {};
};

template <class ICallbackSubclass> class UCallbackSubclass : public UCallback {
    void Callback(ICallback * source) { Callback(static_cast<ICallbackSubclass *>(source)); };
public:
    virtual void Callback(ICallbackSubclass * source) = 0;
};

