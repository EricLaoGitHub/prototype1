#include <iostream>
#include "slicingNode.h"
#include "parameters.h"
#include <typeinfo>

using namespace std;

map <float,float>* setMapW(map <float,float>* mapL)
{
  map <float,float>* mapW = new map <float,float>();
  map <float,float>::const_iterator itL = mapL->begin();
  for (; itL != mapL->end(); itL++)
  {
    mapW->insert(pair<float,float>( itL->second, itL->first ));
  }
  return mapW;
}

map <float,float>* createMapH(float widthmin, float widthmax, float heightmin, float heightmax, float nmax)
{
  float ldelta = (widthmax-widthmin)/nmax;
  float hdelta = (heightmax-heightmin)/nmax;
  map <float,float>* mapL = new map <float,float>();
  for (int i = 0; i <= nmax; i++){ mapL->insert(pair<float,float>(heightmax-hdelta*i, widthmin+ldelta*i)); }
  return mapL;
}

int main(int argc, char* argv[])
{
  cout << " -------------- Start -------------- " << endl;


  cout << " -------------- DP12 -------------- " << endl;
  map <float,float>* mapHDP12 = createMapH(wMinDP12,wMaxDP12,hMinDP12,hMaxDP12,NDP12);
  map <float,float>* mapWDP12 = setMapW(mapHDP12);
  
  cout << " -------------- CM34 -------------- " << endl;
  map <float,float>* mapHCM34 = createMapH(wMinCM34,wMaxCM34,hMinCM34,hMaxCM34,NCM34);
  map <float,float>* mapWCM34 = setMapW(mapHCM34);

  cout << " -------------- M5 -------------- " << endl;
  map <float,float>* mapHM5 = createMapH(wMinM5,wMaxM5,hMinM5,hMaxM5,NM5);
  map <float,float>* mapWM5 = setMapW(mapHM5);

  cout << " -------------- M6 -------------- " << endl;
  map <float,float>* mapHM6 = createMapH(wMinM6,wMaxM6,hMinM6,hMaxM6,NM6);
  map <float,float>* mapWM6 = setMapW(mapHM6);
  
  cout << " -------------- M7 -------------- " << endl;
  map <float,float>* mapHM7 = createMapH(wMinM7,wMaxM7,hMinM7,hMaxM7,NM7);
  map <float,float>* mapWM7 = setMapW(mapHM7);
  
  cout << " -------------- M8 -------------- " << endl;
  map <float,float>* mapHM8 = createMapH(wMinM8,wMaxM8,hMinM8,hMaxM8,NM8);
  map <float,float>* mapWM8 = setMapW(mapHM8);

  cout << " -------------- M9 -------------- " << endl;
  map <float,float>* mapHM9 = createMapH(wMinM9,wMaxM9,hMinM9,hMaxM9,NM9);
  map <float,float>* mapWM9 = setMapW(mapHM9);

  cout << endl;
  cout << " -------------- Build Slicing Tree -------------- " << endl;
  HSlicingNode* slicingTree = HSlicingNode::create();
  slicingTree->createPushBackNode(Vertical);
  slicingTree->createPushBackNode(DeviceNode, mapHDP12, mapWDP12);
  slicingTree->createPushBackNode(Vertical);
   
  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->print();
  cout << " -------------- Print Children -------------- " << endl;
  slicingTree->printChildren();

  cout << "-------------- 1st Hierarchy -------------- " << endl;
  slicingTree->getChild(0)->createPushBackNode(DeviceNode, mapHM8, mapWM8);
  slicingTree->getChild(0)->createPushBackNode(DeviceNode, mapHM5, mapWM5);
  slicingTree->getChild(0)->createPushBackNode(DeviceNode, mapHM7, mapWM7);
  slicingTree->getChild(0)->printChildren();

  // 2nd Hierarchy
  cout << "-------------- 2nd Hierarchy -------------- " << endl;
  slicingTree->getChild(2)->createPushBackNode(DeviceNode, mapHM9, mapWM9);
  slicingTree->getChild(2)->createPushBackNode(DeviceNode, mapHCM34, mapWCM34);
  slicingTree->getChild(2)->createPushBackNode(DeviceNode, mapHM6, mapWM6);
  slicingTree->getChild(2)->printChildren();

  cout << " -------------- Print Global H/W -------------- " << endl;
  cout << "Global Height = " << slicingTree->updateHeight() << endl;
  cout << "Global Width  = " << slicingTree->updateWidth() << endl;

  cout << " -------------- Print 1st Hierarchy H/W -------------- " << endl;
  cout << "1st Hierarchy Height = " << slicingTree->getChild(0)->updateHeight() << endl;
  cout << "1st Hierarchy Width  = " << slicingTree->getChild(0)->updateWidth() << endl;
  cout << " -------------- Print 2nd Hierarchy H/W -------------- " << endl;

  cout << "2nd Hierarchy Height = " << slicingTree->getChild(2)->updateHeight() << endl;
  cout << "2nd Hierarchy Width  = " << slicingTree->getChild(2)->updateWidth() << endl;

  cout << " -------------- End -------------- " << endl;
  return 0;
}
