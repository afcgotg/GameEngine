#ifndef __Callback__
#define __Callback__ 

class Callback
{
public:
    virtual void call() = 0;
};

class StaticCallback : public Callback{
    public:
        
        StaticCallback(void (*func)()) : mFunc(func){
        }
        
        virtual void call(){
            mFunc();
        }
        
    private:
        void (*mFunc)();
};

#endif