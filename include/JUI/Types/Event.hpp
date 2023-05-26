/* @file       Event.hpp
 * @desc       Templated Event Signalling Library
 * @auth       Josh O'Leary
 * @revision   1
 * @edited     2023-05-18
 * @copyright  (C) 2023 Conarium Software
 * @license    GNU Affero GPL-3
 */

#pragma once

#include <functional>
#include <atomic>
#include <list>
#include <thread>
#include <memory>
#include <iostream>
#include <utility>

namespace JUI {

    template<typename ... Args>
    class Event; // Add this to your classes, is event signaller.
    template<typename ... Args>
    class EventConnection; // Returned by Connect(), is connection handle.
    class ContrivedEventDemoClass;

    template<typename ... Args>
    class EventConnection {
        typedef std::function<void(Args...)> delegate;

    public:
        EventConnection(Event<Args...> *creator, delegate cb) : owner(creator), callback(std::move(cb)) {}

        bool Disconnect();

        void Invoke(Args... e) { callback(e...); }

    private:
        Event<Args...> *owner;
        delegate callback;
        bool active = true;
    };

    template<typename ... Args>
    bool EventConnection<Args...>::Disconnect() {
        if (active) {
            owner->Disconnect(this);
            active = false;
            return true;
        }
        return false;
    }

    template<typename ... Args>
    class Event {
        typedef std::function<void(Args...)> delegate;
        typedef EventConnection<Args...> connection;
        typedef std::shared_ptr <connection> event_ptr;

    public:
        void Await(Args &... arg); // Pass in Args... as reference to be filled???
        void Invoke(Args... args);

        void operator()(Args... args) { Invoke(args...); }

        connection Connect(delegate callback);

        void Disconnect(connection &conn);

        connection operator+=(delegate callback) { return Connect(callback); }

    private:
        std::vector <event_ptr> listeners;
        uint64_t listenerCounter = 0;
    };


    template<typename ... Args>
    void Event<Args...>::Invoke(Args... args) {
        for (event_ptr &connection_ptr: this->listeners) {
            connection_ptr->Invoke(args...);
        }
    }

    template<typename ... Args>
    typename Event<Args...>::connection Event<Args...>::Connect(delegate callback) {
        event_ptr return_val(new connection(this, callback));
        this->listeners.push_back(return_val);
        return *return_val;
    }

    template<typename ... Args>
    void Event<Args...>::Disconnect(connection &conn) {
        listeners.erase(std::remove(
                listeners.begin(), listeners.end(), 99), listeners.end());
    }

    class Nigger {
    public:
        Event<time_t> Jailed;

        void SendToJail() {
#if SUPERMAX

#else

#endif
#define NIGGER_NUMBERS 42069
            Jailed.Invoke(NIGGER_NUMBERS); // IM GONNA BOMB A FEDERAL BUILDING REEEEEEEEEEEEEEEEEEEEEEEEE
        }
    };


    class Cop {
    public:
        void Arrest(Nigger &ninini) {
            ninini.SendToJail();
        }
    };

    template<typename T>
    class NiggerTemplateExamples {

    };

    // The purpose of events is to convey changes in "Class-State"
    // That outside users may be interested in.
    // Example of usage:
    class ContrivedEventDemoClass {
    public:
        Event<int> OnSomeSignal;
        Event<int, int, int, std::string> GunshotsHeard;

        void InvokeOurSignals() {
            OnSomeSignal.Invoke(6);
            GunshotsHeard.Invoke(1, 2, 3, "poo");
        }

        void AddSomeConnections() {

            auto handle = OnSomeSignal += [](int i) {
                std::cout << "Event sent " << i << std::endl;
            };
            auto handle2 = OnSomeSignal.Connect([](int) {});
            int t;
            OnSomeSignal.Await(t);
        }
    };
}