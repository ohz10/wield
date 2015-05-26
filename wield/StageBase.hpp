#pragma once
#include <wield/DispatcherInterface.hpp>
#include <wield/MessageBase.hpp>

#include <wield/details/SmartPtrCreator.hpp>

namespace wield {

    /* Stage
       @StageEnum the enum defining names of all stages.
       @ProcessingFunctor this stage's processing function.
       @QueueType the type of queue this stage will get inputs from.
       @DispatcherType the type of the dispatcher the stage will use to dispatch messages to other stages.
     
       A stage is the basic unit of processing in a SEDA architecture. It consists of a queue, and a function
       to apply to messages in the queue. 
    */
    template<typename StageEnum, class ProcessingFunctor, class Message, class QueueType>
    class StageBase 
    {
    public:
        static_assert(std::is_enum<StageEnum>::value, "StageEnum parameter is not an enum type.");
        using MessageType = Message;
        
        StageBase(const StageEnum stageName, DispatcherInterface<StageEnum, StageBase>& dispatcher, QueueType& queue, ProcessingFunctor& processingFunctor)
            : processingFunctor_(processingFunctor)
            , queue_(queue)
            , stageName_(stageName)
        {
            dispatcher.registerStage(stageName, this);
        }

        // make container friendly.
        StageBase(StageBase&& stage)
            : processingFunctor_(stage.processingFunctor_)
            , queue_(stage.queue_)
            , stageName_(stage.stageName_)
        {
        }

        ~StageBase()
        {
        }

        // Insert a message onto the stage's queue
        // @m the message to insert
        void push(const typename MessageType::ptr& m)
        {
            queue_.push(m);
        }

        /* process a message
           
           pump the queue, if there is a message, process it.
           
           @return true if a message was processed, false otherwise.
        */
        bool process(void)
        {
            typename MessageType::ptr m = nullptr;
            if(queue_.try_pop(m))
            {
                typename MessageType::smartptr message(details::create_smartptr<MessageType>(m, no_increment));

                message->processWith(processingFunctor_);
                return true;
            }

            return false;
        }

        // get the stage's name
        inline StageEnum name(void) const
        {
            return stageName_;
        }

    private:
        StageBase(const StageBase&) = delete;
        StageBase& operator=(const StageBase&) = delete;

    private:
        ProcessingFunctor& processingFunctor_;
        QueueType& queue_;

        const StageEnum stageName_;
    };
}
