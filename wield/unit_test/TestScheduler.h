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

    typename Dispatcher::stage_t& nextStage(const std::size_t thread_id)
    {
        // this is where the magic happens...
        return dispatcher_[Dispatcher::stage_enum_t::Stage1];
    }

    inline std::size_t batchSize(typename Dispatcher::stage_enum_t stageName) const
    {
        // return the configured batchSize for this stage.
        return std::numeric_limits<std::size_t>::max();
    }

    inline std::size_t emptyRetryCount(typename Dispatcher::stage_enum_t stageName) const
    {
        return 10;
    }
    
    inline std::size_t numberOfThreads(void) const
    {
        return std::thread::hardware_concurrency();
    }

private:
    Dispatcher& dispatcher_;
};

typedef wield::SchedulerBase<SchedulingPolicy<TestDispatcher> > TestScheduler;
