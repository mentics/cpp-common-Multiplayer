#pragma once

#include <chrono>

#include "MenticsCommon.h"
#include "Scheduler.h"

namespace mentics { namespace game {

namespace sched = mentics::scheduler;
namespace cmn = mentics::common;

typedef uint64_t TimeOfType;

struct LocalTimeProvider : public sched::SchedulerTimeProvider<TimeOfType> {
	TimeOfType maxTimeAhead() {
		return 2000;
	}

	TimeOfType realTimeUntil(TimeOfType t) {
		return t - cmn::currentTimeMillis();
	}
};

}}