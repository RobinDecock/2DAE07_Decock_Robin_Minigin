#pragma once

class GameObject;


    constexpr int MAX_OBSERVERS = 10;

    class Observer
    {
        friend class Subject;
    public:
        Observer()
            : next_(nullptr)
        {}
        virtual ~Observer() = default;
        virtual void onNotify(int event, GameObject* obj = nullptr) = 0;
    private:
        Observer* next_;

    };


    class Subject
    {
    public:
        Subject()
            : head_(NULL)
        {}

        void AddObserver(Observer* observer)
        {
            observer->next_ = head_;
            head_ = observer;
        }

        void RemoveObserver(Observer* observer)
        {
            if (head_ == observer)
            {
                head_ = observer->next_;
                observer->next_ = NULL;
                return;
            }

            Observer* current = head_;
            while (current != NULL)
            {
                if (current->next_ == observer)
                {
                    current->next_ = observer->next_;
                    observer->next_ = NULL;
                    return;
                }

                current = current->next_;
            }
        }

    protected:
        void Notify(int event, GameObject* obj = nullptr)
        {
            Observer* observer = head_;
            while (observer != NULL)
            {
                observer->onNotify(event, obj);
                observer = observer->next_;
            }
        }

    private:
        int numObservers_ = 0;
        Observer* head_;
    };
