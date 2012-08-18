#pragma once
#include <wield/SchedulerBase.h>

#include "Stages.h"
#include "TestStage.h"
#include "TestDispatcher.h"

#include <thread>

template<typename Dispatcher>
class SchedulingPolicy
{
public:
    typedef typename Dispatcher::stage_t stage_t;

    SchedulingPolicy(Dispatcher& dispatcher)
        : dispatcher_(dispatcher)
    {
    }

    typename Dispatcher::stage_t& nextStage(std::thread::id thread_id)
    {
        // this is where the magic happens...
        return dispatcher_[Dispatcher::stage_enum_t::Stage1];
    }

    size_t batchSize(typename Dispatcher::stage_enum_t stageName)
    {
        // return the configured batchSize for this stage.
        return 0;
    }

private:
    Dispatcher& dispatcher_;
};

typedef wield::SchedulerBase<SchedulingPolicy<TestDispatcher> > TestScheduler;
