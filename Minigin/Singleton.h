#pragma once
template<typename T>
class Singleton
{
    friend T;
public:
    Singleton() = default;

private:
    virtual ~Singleton() = default;

	
public:

    static void SetInstance(T* inst)
    {
        m_pInstance = inst;
    }
	
    static auto GetInstance()-> T&
    {
        return *m_pInstance;
    }
    static void DestroyInstance()
    {
        delete m_pInstance; // REM : it works even if the pointer is NULL (does nothing then)
        m_pInstance = NULL; // so GetInstance will still work.
    }
protected:
    static T* m_pInstance;
};

template<typename T>
T* Singleton<T>::m_pInstance = nullptr;