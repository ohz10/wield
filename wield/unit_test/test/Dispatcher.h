#pragma once
#include <wield/DispatcherBase.h>

#include "Stages.h"
#include "Stage.h"

namespace test {
    using Dispatcher = wield::DispatcherBase<Stages, Stage>;
}
