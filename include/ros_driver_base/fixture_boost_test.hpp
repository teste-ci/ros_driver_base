#ifndef ROS_DRIVER_BASE_BOOST_HPP
#define ROS_DRIVER_BASE_BOOST_HPP

#include <boost/test/unit_test.hpp>
#include <ros_driver_base/fixture.hpp>

#define ROS_DRIVER_BASE_MOCK() ros_driver_base::Fixture<fixture_driver_t>::BoostMockContext __context(this);

namespace ros_driver_base {
    template<typename Driver>
    class Fixture<Driver>::BoostMockContext
    {
    public:
        Fixture* fixture;
        BoostMockContext(Fixture* fixture): fixture(fixture)
        {
            fixture->setMockMode(true);
        }

        void tearDown()
        {
            try
            {
                fixture->validateExpectationsAreEmpty();
            }
            catch(TestEndsWithExpectationsLeftException e)
            {
                BOOST_ERROR("ROS_DRIVER_BASE_MOCK Error: Test reached its end without satisfying all expecations.");
            }
        }

        ~BoostMockContext()
        {
            tearDown();
            fixture->setMockMode(false);
        }

    };
}

#endif
