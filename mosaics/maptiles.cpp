/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    if (theTiles.empty()) return NULL;
    map<Point<3>,int> indexKeeper;
    vector<Point<3>> treeBuilder;
    for(unsigned i = 0; i<theTiles.size();i++){
      LUVAPixel tileAvg = theTiles[i].getAverageColor();
      double arr[3] = {tileAvg.l,tileAvg.u,tileAvg.v};
      Point<3> p(arr);
      treeBuilder.push_back(p);
      indexKeeper[p] = i;
    }
    KDTree<3> tileTree(treeBuilder);

    MosaicCanvas* rtu = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for(int i = 0; i<theSource.getRows(); i++){
      for(int j = 0; j<theSource.getColumns(); j++){
        LUVAPixel target = theSource.getRegionColor(i,j);
        double arr1[3] = {target.l,target.u,target.v};
        Point<3> p1(arr1);
        Point<3> bestPixel = tileTree.findNearestNeighbor(p1);
        rtu->setTile(i, j, &(theTiles[indexKeeper[bestPixel]]));
      }
    }
    return rtu;
}
