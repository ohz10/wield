#pragma once
#include <wield/StageBase.h>

#include "TestProcessingFunctor.h"
#include "TestQueue.h"
#include "TestDispatcher.h"
#include "Stages.h"

typedef wield::StageBase<ProcessingFunctor, TestDispatcher, TestQueue, Stages> Stage;
