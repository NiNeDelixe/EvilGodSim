#pragma once
#ifndef INTERFACES_IBINDABLE_H_
#define INTERFACES_IBINDABLE_H_

class IBindable 
{
public:
    IBindable() = default;
    virtual ~IBindable() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

#endif  // INTERFACES_IBINDABLE_H_
