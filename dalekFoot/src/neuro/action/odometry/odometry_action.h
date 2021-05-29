#ifndef __ACTION_ODOMETRY_ODOMETRY_ACTION_H__
#define __ACTION_ODOMETRY_ODOMETRY_ACTION_H__

#include "action/i_action.h"
#include "framework/entity_agency.h"
#include "module/data_types/action/odometry_data.h"
#include <string>
#include <cstdint>

namespace action {
namespace odometry {


class OdometryAction : public IAction {
	public:
		OdometryAction(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~OdometryAction();
		virtual void execute(std::uint64_t cycleCount);

	private:
		
		int16_t mPreviousEncoderValue;
		int16_t mSpeed;
	
};




}
}


#endif
