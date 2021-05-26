#ifndef __ACTION_ODOMETRY_ODOMETRY_ACTION_H__
#define __ACTION_ODOMETRY_ODOMETRY_ACTION_H__

#include "action/i_action.h"
#include "framework/entity_agency.h"
#include "module/data_types/action/odometry.h"
#include <string>

namespace action {
namespace odometry {


class OdometryAction : public IAction {
	public:
		OdometryAction(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~OdometryAction();
		virtual void execute(void);


		Odometry getOdometry(void) const {return mOdometry;};
	private:
		Odometry mOdometry;

		int16_t mPreviousEncoderValue;
		int16_t mSpeed;

};




}
}


#endif
