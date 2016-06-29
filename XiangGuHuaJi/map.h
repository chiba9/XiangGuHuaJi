/* XiangGuHuaJi 2016, map.h
 *
 */

#ifndef _XIANGGUHUAJI_MAP_H__
#define _XIANGGUHUAJI_MAP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cassert>

#include "definition.h"
#include "converter.hpp"

#include "json/json.h"
#pragma comment(lib, "lib_json.lib")

namespace XGHJ {

using namespace std;

class Map
{
public:
    Map();
    ~Map();

    TMapSize	x, y;

    cv::Mat/*TMatMapPara*/	    MapResource_, MapDefenseRatio_, MapAttackRatio_;
    vector<vector<TMapPara> >	MapResource, MapDefenseRatio, MapAttackRatio;

	//装载指定文件名的地图。返回装载成功时true。
	bool load(string file_name);

private:
    //将cv::Mat转为vector<vector<T>>, 在加载完毕后使用
    void convertMyMat();
};

}

#endif