//
// Created by esteban on 4/12/20.
//

#ifndef UNTITLED_LINKED_LIST_H
#define UNTITLED_LINKED_LIST_H

#include <cstdio>
#include <cassert>
#include "macros.h"
#include "node.h"

namespace utec
{
    
    template<class T>
    class linked_list
    {
    private:
        unsigned __size;
        node<T> * __head;
        node<T> * __tail;
        
        
        constexpr void
        __init__(const T & last);
        
        
        template<class ... Args>
        constexpr void
        __init__(const T & first, const Args & ... args);
        
        
        
    public:
        // Empty constructor
        linked_list();
        
        // Assignment constructors
        template<class ... Args>
        explicit
        linked_list(const Args& ... args);
        
        linked_list(const std::initializer_list<T> & init);
        
        // Copy constructor
        linked_list(linked_list& ll);
        
        // Move constructor
        linked_list(linked_list&& ll) noexcept;
        
        // Destructor
        ~linked_list();
        
        // Class methods
        
        // outputs the list to the console. Mainly for debug, i should've deleted it xd
        constexpr
        void
        show();
        
        constexpr
        unsigned
        size ();
        
        // places a new element at the back of the list
        constexpr
        void
        push_back(const T & value);
        
        // same thing, different place
        constexpr
        void
        push_front(const T & value);
        
        // deletes the last element of the list.
        constexpr
        void
        pop_back();
        
        // "" first element ""
        constexpr
        void
        pop_front();
        
        // inserts an element in the assigned position
        constexpr
        void
        insert(const size_t & position, const T & value);
        
        // deletes an element ...
        constexpr
        void
        remove(const size_t & position);
    
        constexpr
        node<T> *
        traverse(const size_t & position);
        
        // returns a reference to the value of the node in the desired position
        constexpr
        T&
        at(const size_t & position);
        
        // .at() but prettier
        constexpr
        T&
        operator [](const size_t & position);
        
        // brace enclosed assignment
        constexpr
        linked_list<T>&
        operator = (const std::initializer_list<T> & init);
        
        // move assignment
        constexpr
        linked_list<T>&
        operator = (linked_list<T>&& ll) noexcept;
    
        // copy assignment
        constexpr
        linked_list<T>&
        operator = (const linked_list<T>& ll);
        
        constexpr
        auto begin() {
            return traverse(0);
        }
        
        constexpr
        auto end() {
            return nullptr;
        }
    };
    
    template<class T>
    constexpr void
    linked_list<T>::__init__(const T& last)
    {
        push_back(last);
    }
    
    template<class T>
    template<class... Args>
    constexpr void linked_list<T>::__init__(const T& first, const Args& ... args)
    {
        push_back(first);
        __init__(args...);
    }
    
    template<class T>
    linked_list<T>::linked_list()
            : __size(0), __head(nullptr), __tail(nullptr)
    {
        DEBUG(std::cout << "linked list was created \n";)
    }
    
    template<class T>
    template<class... Args>
    linked_list<T>::linked_list(const Args & ... args)
            : __size(0)
    {
        DEBUG(std::cout << "linked list is constructed\n";)
        __init__(args ...);
    }
    
    template<class T>
    linked_list<T>::linked_list(const std::initializer_list<T> & init)
            : __size(0), __head(nullptr), __tail(nullptr)
    {
        DEBUG(std::cout << "init. list constructor was called\n";)
        
        for ( auto it = init.begin() ; it != init.end() ; ++it )
            this->push_back(*it);
    }
    
    template<class T>
    linked_list<T>::linked_list(linked_list & ll) : __size(0), __head(nullptr), __tail(nullptr)
    {
        DEBUG(std::cout << "copy constructor was called\n";)
        
        for ( auto it = ll.__head ; it != nullptr ; it = it->next )
            this->push_back(it->value);
    }
    
    template<class T>
    linked_list<T>::linked_list(linked_list && ll) noexcept
            : __size(std::move(ll.__size)), __head(std::move(ll.__head)), __tail(std::move(ll.__tail))
    {
        ll.__size = 0;
        ll.__head = nullptr;
        ll.__tail = nullptr;
    }
    
    template<class T>
    linked_list<T>::~linked_list()
    {
        while ( __size > 0 )
            this->pop_front();
        
        DEBUG(std::cout << "linked list was destroyed\n";)
    }
    
    template<class T>
    constexpr void
    linked_list<T>::show()
    {
        auto current = __head;
        while ( current != nullptr ) {
            std::cout << current->value << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }
    
    template<class T>
    constexpr node<T>*
    linked_list<T>::traverse(const size_t & position)
    {
        assert(position < __size && position >= 0);
        
        auto current = __head;
        for ( size_t i = 0 ; i < position ; ++i )
            current = current->next;
        
        return current;
    }
    
    template<class T>
    constexpr void
    linked_list<T>::push_back(const T & value)
    {
        auto nBack = new node<T>(value);
        
        ++__size;
        if (__size == 1) {
            __head = nBack;
            __tail = nBack;
            return;
        }
        
        __tail->insertNext(nBack);
        __tail = nBack;
        
    }
    
    template<class T>
    constexpr void
    linked_list<T>::push_front(const T & value)
    {
        auto temp = __head;
        auto nHead = new node<T>(value);
        
        __head = nHead;
        __head->insertNext(temp);
        ++__size;
    }
    
    template<class T>
    constexpr void
    linked_list<T>::pop_back()
    {
        assert(__size > 0);
        
        if (__size == 1) {
            __tail = nullptr;
            delete __head;
            __head = nullptr;
            
            --__size;
            return;
        }
        
        auto prev = traverse(__size - 2);
        prev->removeNext();
        
        --__size;
    }
    
    template<class T>
    constexpr void
    linked_list<T>::pop_front()
    {
        assert(__size > 0);
        
        auto temp = __head;
        __head = __head->next;
        delete temp;
        --__size;
        
    }
    
    template<class T>
    constexpr void
    linked_list<T>::insert(const size_t & position, const T & value)
    {
        assert(position <= __size && position >= 0);
        if (position == 0) {
            push_front(value);
            return;
        }
        if (position == __size) {
            push_back(value);
            return;
        }
        auto current = traverse(position - 1);
        auto temp = current->next;
        current->insertNext(new node<T>(value));
        current->next->next = temp;
        ++__size;
    }
    
    template<class T>
    constexpr void
    linked_list<T>::remove(const size_t & position) {
        assert(position < __size && position >= 0);
        
        if (position == 0) {
            pop_front();
            return;
        }
        
        auto prev = traverse(position - 1);
        prev->removeNext();
        --__size;
    }
    
    template<class T>
    constexpr T&
    linked_list<T>::at(const size_t & position) {
        return traverse(position)->value;
    }
    
    
    template<class T>
    constexpr T&
    linked_list<T>::operator [](const size_t & position) {
        return this->at(position);
    }
    
    template<class T>
    constexpr linked_list<T>&
    linked_list<T>::operator =(const std::initializer_list<T> & init)
    {
        while ( __size > 0 )
            this->pop_front();
        
        for ( auto it = init.begin() ; it != init.end() ; ++it )
            this->push_back(*it);
        
        return *this;
    }
    
    template<class T>
    constexpr linked_list<T>&
    linked_list<T>::operator = (linked_list<T>&& ll) noexcept
    {
        this->__size = std::move(ll.__size);
        this->__head = std::move(ll.__head);
        this->__tail = std::move(ll.__tail);
    
        ll.__size = 0;
        ll.__head = nullptr;
        ll.__tail = nullptr;
        
        return *this;
    }
    
    template<class T>
    constexpr linked_list<T>&
    linked_list<T>::operator = (const linked_list<T> & ll)
    {
        while (this->__size > 0)
            this->pop_front();
        
        for (auto it = ll.__head ; it != nullptr ; it = it->next )
            this->push_back(it->value);
        
        return *this;
    }
    
    template<class T>
    constexpr unsigned
    linked_list<T>::size()
    {
        return __size;
    }
}

#ifdef INDEBUG
#undef INDEBUG
#endif


#endif //UNTITLED_LINKED_LIST_H
