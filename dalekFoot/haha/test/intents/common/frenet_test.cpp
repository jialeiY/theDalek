#include "intents/common/frenet.h"
#include "data/defs/position2d.h"
#include "data/defs/static_polyline_pod.h"
#include "test/utest.h"


// template<std::size_t N>
// PositionInFrenetPolyline locateSegmentInPolyline(const data::Position2D& poi,
//                                                  const data::StaticPolylinePod<N>& polyline) {

UTEST(FrenetTest, PoiBeforePolyline) {
    const cooboc::data::Position2D poi {0.0F, 0.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({1.0F, 0.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(0U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(-1.0F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(0.0F, actualResult.lateralDistance, 1e-3F, "lateral");
}


UTEST(FrenetTest, PoiOnStartPoint) {
    const cooboc::data::Position2D poi {1.0F, 0.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({1.0F, 0.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(0U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(0.0F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(0.0F, actualResult.lateralDistance, 1e-3F, "lateral");
}


UTEST(FrenetTest, PoiOnFirstSegmentOfPolyline) {
    const cooboc::data::Position2D poi {1.5F, 0.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({1.0F, 0.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(0U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(0.5F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(0.0F, actualResult.lateralDistance, 1e-3F, "lateral");
}

UTEST(FrenetTest, PoiOutOfPolyline) {
    const cooboc::data::Position2D poi {1.0F, 2.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({0.0F, 0.0F});
    polyline.push_back({1.0F, 1.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(1U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(-0.707107F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(0.707107F, actualResult.lateralDistance, 1e-3F, "lateral");
}

UTEST(FrenetTest, PoiOutOfPolyline_Below) {
    const cooboc::data::Position2D poi {1.0F, -2.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({0.0F, 0.0F});
    polyline.push_back({1.0F, -1.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(1U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(-0.707107F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(-0.707107F, actualResult.lateralDistance, 1e-3F, "lateral");
}

UTEST(FrenetTest, PoiEndOfPolyline_Below) {
    const cooboc::data::Position2D poi {3.0F, 1.0F};

    cooboc::data::StaticPolylinePod<100U> polyline;
    polyline.push_back({0.0F, 0.0F});
    polyline.push_back({1.0F, 0.0F});
    polyline.push_back({2.0F, 0.0F});


    const cooboc::intent::frenet::PositionInFrenetPolyline actualResult =
      cooboc::intent::frenet::locateSegmentInPolyline(poi, polyline);

    EXPECT_EQ_MSG(2U, actualResult.polylineIdx, "index");
    EXPECT_NEAR_MSG(1.0F, actualResult.longitudinalOffset, 1e-3F, "longitudinal");
    EXPECT_NEAR_MSG(1.0F, actualResult.lateralDistance, 1e-3F, "lateral");
}