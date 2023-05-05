#ifndef ALG_H_
#define ALG_H_

#include <cmath>
#include <iostream>
#include <vector>
#include "vector3.h"

using V3 = Vector3;
static class Algorithms {
    public:
        const final double passWeight = 100;
        const final double droneWeight = 250;
        const final double maxSpeed = 50;
        const final double maxBatVal = 100;
        const final double gainRateC = 5; //constant for battery gain rate
        double batLossRate(double speed, bool hasPassenger, double curBatVal, double inclineAngle) {
            double pw = passWeight;
            if(!hasPassenger) {
                pw = 0;
            }
            double weight = pw + droneWeight;
            double speedFactor = speed / maxSpeed;
            double batFactor = curbatVal > 50 ? 1 : 1 - (50 - curBatVal) / 100;
            double lossRate = ((weight * speedFactor) + ( weight * speedFactor * sin(inclineAngle))) * batFactor;
            return lossRate;
        }

        double batLossDx(double speed, bool hasPassenger, double curBatVal) {

        }

        double batGainRate(double curBatVal, double stationQuality) {
            double invQuality = 1 / (stationQuality / 100);
            double invBatVal = (100 - curBatVal) / 100;
            double gainRate = gainRateC * invQuality * invBatVal;
            return gainRate;

        }
        double batGainDx(double curBatVal, double stationQuality) {

        }

        bool isRouteSafe(V3 curLoc, V3 passLoc, V3 passDest, V3[] stationLocs) {
            int closestStationIndex = 0;
            double closestStationDist = distanceBetween(passDest, stationLocs[0]);
            for(int i = 1; i < stationLocs.length; i++) {
                double dist = distanceBetween(passDest, stationLocs[i]);
                if(dist < closestStationDist) {
                    closestStationDist = dist;
                    closestStationIndex = i;
                }
            }
            

        }

        double distanceBetween(V3 loc1, V3 loc2) {
            return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2) + pow(loc1.z - loc2.z, 2));
        }

        double timeToCharge(double curBatVal, double desiredBatVal) {

        }

        double timeToTravel(double speed, V3 curLoc, V3 destLoc) {

        }

        V3 [] getRoute(V3 curLoc, V3 passLoc, V3 passDest, V3[] stationLocs, double[] stationEfficiency, double curBatVal) {

        }
};

#endif /* ALG_H_ */