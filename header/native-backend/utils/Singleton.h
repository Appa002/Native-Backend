//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_SINGLETON_H
#define NATIVE_BACKEND_SINGLETON_H

#include <boost/shared_ptr.hpp>

namespace nvb{
    template <class T>
    class Singleton {
    public:
        static boost::shared_ptr<T> getInstance(){
            if (shared_instance.get() == nullptr)
                shared_instance = boost::shared_ptr<T>(new T());
            return shared_instance;
        }
    private:
        static boost::shared_ptr<T> shared_instance;
    };
}

template <class T>
boost::shared_ptr<T>
        nvb::Singleton<T>::shared_instance = boost::shared_ptr<T>();

#endif //NATIVE_BACKEND_SINGLETON_H
