// Implement the Stack class
// This will be an adapter for STL deque

#ifndef STACK_H
#define STACK_H

#include "../utilities/Publisher.h"
#include <vector>
#include <memory>
#include <string>

namespace pdCalc {

class StackEventData : public EventData 
{
public:
        enum class ErrorConditions {Empty, TooFewArguments};
        explicit StackEventData(ErrorConditions e) : err_(e){ }

        static const char* Message(ErrorConditions ec);
        const char* message() const;
        ErrorConditions error() const {return err_;}
private:
        ErrorConditions err_;
};

class Stack : private Publisher 
{
    class StackImpl;   // implementation can raise events

public: 
    static Stack& Instance();
    void push(double, bool suppressChangeEvent = false);
    double pop(bool suppressChangeEvent = false);
    void swapTop();

    // return first min(n,stackSize) elements from the stack, top at pos 0
    std::vector<double> getElements(size_t n) const;
    void getElements(size_t n, std::vector<double>&) const;

    using Publisher::attach;
    using Publisher::detach;

    // these are needed for testing
    size_t size() const;
    void clear() const;

    static const std::string StackChanged;
    static const std::string StackError;

private:
    Stack();
    ~Stack();
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack& operator=(const Stack&&) = delete;

    std::unique_ptr<StackImpl> pimpl_;
};

}

#endif
