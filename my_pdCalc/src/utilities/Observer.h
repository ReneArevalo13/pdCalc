#ifndef OBSERVER_H
#define OBSERVER_H

/*
   The Observer class serves as teh base class for all observer objects. The   Observer class is a mediator between the Publisher and the actual class
   that performs the observation. 
   A concrete observer should inherit from observer and contain a pointer to
   the actual observing object. This decouples the observing object from 
   knowing about publishers. Note that publishers call Observer's notify,
   which must be implemented in the concrete observer to respond to event
   notifications.

   Note that the semantics of Publishers to own the observer uniquely 
   enforced by std::unique_ptr
*/

#include <string>
#include <memory>

namespace pdCalc {
    class EventData;
    class Observer {
        public:
            explicit Observer(const std::string& name);
            virtual ~Observer();

            void notify(std::shared_ptr<EventData>);
            const std::string name() const {return observerName_;}
        private:
            virtual void notifyImpl(std::shared_ptr<EventData>) = 0;
            std::string observerName_;
    };
}

#endif
