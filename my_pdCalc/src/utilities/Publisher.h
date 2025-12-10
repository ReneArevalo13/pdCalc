// Implementation of Publisher class

#ifndef PUBLISHER_H
#define PUBLISHER_H

/*
   The Publisher class is a class capable of receiving observers.
   They are stored by string name in a table. 
   Since each event may have multiple observers, the table stores a collection of observers.

Important: Publishers own thememory for their observers(enforced by std::unique_ptr)
*/

#include <string>
#include <vector>
#include <memory>
#include <set>

namespace pdCalc {

class EventData 
{
public:
    virtual ~EventData();
};

class Publisher
{
    class PublisherImpl;
public:
    Publisher();

    void attach(const std::string& eventName, std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string& eventName, const std::string& observerName);
    std::set<std::string> listEvents() const;
    std::set<std::string> listEventObservers(const std::string& eventName)const;
protected:
    ~Publisher();
    void raise(const std::string& eventName, std::shared_ptr<EventData>)const;
    void registerEvent(const std::string& eventName);
    void registerEvents(const std::vector<std::string>& eventNames);
private:
    std::unique_ptr<PublisherImpl> publisherImpl_;
};

}

#endif

