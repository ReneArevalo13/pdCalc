/*
Implementation of the publisher class
    Publisher implementation holds an associative array to lists of observers. In this manner, each publisher can have multiple distinct events, each of which only notifies observers interested in watching that particular event.
*/

#include "Publisher.h"
#include "Observer.h"
#include "Exception.h"

#include <sstream>
#include <unordered_map>
#include <set>

using std::string;
using std::vector;
using std::set;
using std::ostringstream;
using std::unique_ptr;
using std::shared_ptr;

namespace pdCalc {

class Publisher::PublisherImpl {
    // ObserverList is the unordered_map of strings, and unique_ptr to obsv
    using ObserverList = std::unordered_map<string, unique_ptr<Observer>>;
    using Events = std::unordered_map<string, ObserverList>;

    void attach(const string& eventName, unique_ptr<Observer> observer);
}
    unique_ptr<Observer> detach(const string& eventName, const string& observer);
    void notify(const string& eventName, shared_ptr<EventData> d) const;
    void registerEvent(const string& eventName);
    void registerEvents(const vector<string>& eventNames);
    set<string> listEvents() const;
    set<string> listEventObservers(const string& eventName) const;

    Events::const_iterator findCheckedEvent(const string& eventName) const;
    Events::iterator findCheckedEvent(const string& );

private:
    Events events_;
};

Publisher::PublisherImpl::PublisherImpl() {}
Publisher::PublisherImpl::~PublisherImpl() {}

Publisher::PublisherImpl::Events::const_iterator Publisher::PublisherImpl::
findCheckedEvent(const string& eventName) const {
    auto ev = events_.find(eventName);
    if (ev == events_.end()) {
        ostringstream oss;    // another way to handle strings
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception{oss.str()};
    }
    return ev;
}

Publisher::PublisherImpl::Events::iterator Publisher::PublisherImpl::
findCheckedEvent(const string& eventName) const {
    auto ev = events_.find(eventName);
    if (ev == events_.end()) {
        ostringstream oss;    // another way to handle strings
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception(oss.str());
    }
    return ev;
}
// unordered map in pairs: (first, second) -> (name, observer object)
// We are attaching an observer to a particular EventName
void Publisher::PublisherImpl::attach(const string& eventName, unique_ptr<Observer> observer) {
    auto ev = findCheckedEvent(eventName);   // check for eventName 
    auto& obsList = ev->second;   // List of observers for that given event 

    auto obs = obsList.find(obsever->name()); // look for event/obsv pair 

    if (obs != obsList.end()) {
        throw Exception("Observer already attached to publisher");
    }
    // insert into publisher list of observers, for that event
    obsList.insert(std::make_pair(observer->name(), std::move(observer)));
    return;
}

unique_ptr<Observer> Publisher::PublisherImpl::detach(const string& eventName, const string&& observer) {
    auto ev = findCheckedEvent(eventName);
    auto& obsList = ev->second;

    auto obs = obsList.find(observer);
    if (obs == obsList.end()) {
        throw Exception("Cannot detach observer because observer not found");
    } 
    // retrieve pointer to observer to be removed
    auto tmp = std::move(obs->second);
    // delete that entry in the map
    obsList.erase(obs);
    return tmp;
}

void Publisher::PublisherImpl::notify(const string& eventName, shared_ptr<EventData> d) const {
    auto ev = findCheckedEvent(eventName);
    const auto& obsList = ev->second;

    for (const auto& obs:obsList) {
        obs.second->notify(d);
    }
    return;
}

void Publisher::PublisherImpl::registerEvent(const string& eventName) {
    auto i = events_.find(eventName);
    if (i != events_.end()) {
        throw Exception{"Event already registered"};
    }
    // events_ is an unorderdMap of Observers for a given event
    events_[eventName] = ObserverList{};  // empty ObserverList to be filled
    return;
}

void Publisher::PublisherImpl::registerEvents(const vector<string>& eventNames) {
    // go through all events
    for (auto i:eventNames) {
        registerEvent(i);
    }
    return;
}

set<string> Publisher:PublisherImpl::listEvents() const {
    set<string> tmp;
    for (const auto& i : events) {
        tmp.insert(i.first);
    }
    return tmp;
}

set<string> Publisher::PublisherImpl::listEventObservers(const string& eventName) const {
    auto ev = findCheckedEvent(eventName);
    set<string> tmp;
    // go through all the observer objects for this event
    for (const auto& kvp : ev->second) {
        tmp.insert(kvp.first);
    }
    return tmp;
}
////////////////////////////////////////////////////////////
Publisher::Publisher() {
    publisherImpl_ = std::make_unique<PublisherImpl>();
}

Publisher::~Publisher() {
    /* std::unique ptr requires a definition of the destructor instead of 
       using the default because the destructor must appear in a scope 
       in which the complete definition of the template argument for 
       std::unique_ptr is known
    */
}

void Publisher::attach(const string& eventName, unique_ptr<Observer> observer) {
    publisherImpl_->attach(eventName, std::move(observer));
    return;
}

unique_ptr<Observer> Publisher::detach(const string& eventName, const string& observer) {
    return publisherImpl_->detach(eventName, observer);
}

void Publisher::raise(const string& eventName, std::shared_ptr<EventData> d)const {
    publisherImpl_->notify(eventName, d);
    return;
}

void Publisher::registerEvent(const string& eventName) {
    publisherImpl_->registerEvent(eventName);
    return;
}

void Publisher::registerEvents(const vector<string> eventNames) {
    publisherImpl_->registerEvents(eventNames);
    return;
}

set<string> Publisher::listEvents() const {
    return publisherImpl_->listEvents();
}

set<string> Publisher::listEventObservers(const string& eventName) const {
    return publisherImpl_->listEventObservers(eventName);
}

EventData::~EventData() {}

}
