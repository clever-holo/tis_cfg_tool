#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
    struct object_creator
    {
        object_creator()
        {
            Singleton<T>::Instance();
        }
        inline void do_nothing()const{}
    };
    static object_creator create_object;

public:

    static T& Instance()
    {
        static T obj;
        create_object.do_nothing();
        return obj;
    }
};

// 定义静态成员（给静态成员分配内存）
template <typename T> typename Singleton<T>::object_creator Singleton<T>::create_object;


#endif // SINGLETON_H
