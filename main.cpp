#include<bits/stdc++.h>
using namespace std;
struct interval {
	int start, end;
	bool flag = false; // 0 - empty, 1 - full
	
	interval(int a, int b, bool c) {
		start = a; end = b; flag = c;
	}
};
const double P = 0.5;
const double Q = 1-P;
const int LENGTH_P = 5;
const int LENGTH_Q = 9;
const int numberOfExp = 10000;
float floatPoint = 100;
double findMiddleMaxSpace(float l) {
	vector<int> r(LENGTH_Q*floatPoint, 0);
	vector<int> numb(500, 0);
	l *= floatPoint;
	double sumOfMaxSpaces = 0;
	double expVal = 0;
	for (int exp = 1; exp <= numberOfExp; exp++) {
		int maxSpace = 0;
		int counter = 0;
		int numberOfcar = 0;
		bool isParkingFull = false;
		vector<interval> parking;
		interval allSpace(0, l, 0);
		parking.push_back(allSpace);
		while (!isParkingFull) {
			int lengthOfNewObj;
			if (rand() % int(floatPoint) < P * floatPoint) {
				lengthOfNewObj = LENGTH_P * floatPoint;
			}
			else {
				lengthOfNewObj = LENGTH_Q * floatPoint;
			}
			int numbOfGoodSpaces = 0;
			for (int i = 0; i <= parking.size(); i++) {
				if (i == parking.size()) {
					if (numbOfGoodSpaces == 0) {
						isParkingFull = true;
					}
					break;
				}
				if (parking[i].flag == 0 && (parking[i].end - parking[i].start) >= lengthOfNewObj) {
					numbOfGoodSpaces++;
				}
			}
			if (isParkingFull) {
				break;
			}
			int newObjInd = rand() % numbOfGoodSpaces;
			for (int i = 0; i < parking.size(); i++) {
				if (parking[i].flag == 0 && (parking[i].end - parking[i].start) >= lengthOfNewObj) {
					if (newObjInd > 0) {
						newObjInd--;
					}
					else {
						int distForGen = (parking[i].end - parking[i].start - lengthOfNewObj);
						int startOfNewInterval;
						if (distForGen > 0) {
							startOfNewInterval = (rand() % distForGen) + parking[i].start;
						}
						else {
							startOfNewInterval = parking[i].start;
						}
						int oldIntStart = parking[i].start;
						int oldIntEnd = parking[i].end;
						int indOfNewObj = i;
						if (startOfNewInterval != parking[i].start) {
							parking.insert(parking.begin() + indOfNewObj, {oldIntStart, startOfNewInterval, 0});
							indOfNewObj++;
						}
						int endOfNewInterval = startOfNewInterval + lengthOfNewObj;
						parking.insert(parking.begin() + indOfNewObj, {startOfNewInterval, endOfNewInterval, 1});
						indOfNewObj++;
						if (endOfNewInterval != parking[indOfNewObj].end) {
							parking.insert(parking.begin() + indOfNewObj, {endOfNewInterval, oldIntEnd, 0});
							indOfNewObj++;
						}
						parking.erase(parking.begin() + indOfNewObj);
						break;
					}
				}
			}
		}
		//cout << l / floatPoint << " " << parking.size() << endl;
		for (int i = 0; i < parking.size(); i++) {
			//cout << parking[i].start / floatPoint << " " << parking[i].end / floatPoint << " " << parking[i].flag << endl;
			if (parking[i].flag == 0) {
				
				int dist = parking[i].end - parking[i].start;
				maxSpace = max(maxSpace, dist);
				if(dist >= 1) counter++;
				for (int j = dist; j > 0; j--) {
					r[j]++;
				}
			}
			else {
				numberOfcar++;
			}
		}
		numb[counter]++;
		//cout << r[1.4 * floatPoint] << endl;
		//cout << maxSpace / floatPoint << endl;
		sumOfMaxSpaces += maxSpace / floatPoint;
		expVal += numberOfcar;
	}

	//for (int i = 1; i < r.size(); i++) {
	//	double gr =  (r[i] / double(numberOfExp)) / (l / floatPoint + (LENGTH_Q + LENGTH_P) / 2.0);
	//		cout << gr << endl;
	//}
	//	for (int i = 0; i < numb.size(); i++) {
	//		cout << numb[i] / float(numberOfExp) << endl;
	//	}

	cout << r[1.5 * floatPoint] / (float(numberOfExp)) << endl;
	return expVal / numberOfExp;
}
int main() {
	srand(time(0));
	for (float l = 0; l < 20.01; l += 0.1) {
		 findMiddleMaxSpace(l);
	}
	return 0;
}

