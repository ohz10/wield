#pragma once

#include <atomic>
#include <boost/intrusive_ptr.hpp>

namespace wield {

    template<class ProcessingFunctor>
	class MessageBase
	{
	public:
        typedef boost::intrusive_ptr<MessageBase> smartptr;
        MessageBase()
            : reference_count_(0)
        {
        }

        virtual ~MessageBase(){}

		virtual void ProcessWith(ProcessingFunctor& process) = 0;

    private:
        std::atomic<size_t> reference_count_;

        template<class ProcessingFunctor>
        friend void intrusive_ptr_add_ref(MessageBase<ProcessingFunctor>* m);

        template<class ProcessingFunctor>
        friend void intrusive_ptr_release(MessageBase<ProcessingFunctor>* m);
    };

    template<class ProcessingFunctor>
    void intrusive_ptr_add_ref(MessageBase<ProcessingFunctor>* m)
    {
        ++m->reference_count_;
    }

    template<class ProcessingFunctor>
    void intrusive_ptr_release(MessageBase<ProcessingFunctor>* m)
    {
        if( 0 == --m->reference_count_)
        {
            delete m;
        }
    }
}