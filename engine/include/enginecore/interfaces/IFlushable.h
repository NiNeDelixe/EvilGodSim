#pragma once
#ifndef INTERFACES_IFLUSHABLE_H_
#define INTERFACES_IFLUSHABLE_H_

class IFlushable
{
public:
    IFlushable() = default;
    virtual ~IFlushable() = default;

public:
    virtual void flush() = 0;
};

#endif  // INTERFACES_IFLUSHABLE_H_
