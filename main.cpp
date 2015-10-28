#include <iostream>
#include <fstream>

#include <typeinfo>
#include "parameters.h"
#include "slicingNode.h"

using namespace std;

map <float,float>* createMapH(float widthmin, float widthmax, float heightmin, float heightmax, float nmax)
{
  float ldelta = (widthmax-widthmin)/nmax;
  float hdelta = (heightmax-heightmin)/nmax;
  map <float,float>* mapL = new map <float,float>();
  for (int i = 0; i < nmax; i++){ mapL->insert(pair<float,float>(heightmin+hdelta*i, widthmax-ldelta*i)); }
  return mapL;
}
void createSlicingTreeData(SlicingNode* data, float tab[][5], int& i)
{
  for (vector<SlicingNode*>::const_iterator it = data->getChildren().begin(); it != data->getChildren().end(); it++)
    {
      if ((*it)->getType() == DeviceNode)
        {  
          tab[i][0]=(*it)->getX();
          tab[i][1]=(*it)->getY();
          tab[i][2]=(*it)->getWidth();
          tab[i][3]=(*it)->getHeight();
          tab[i][4]=1;
          i++;
        }
      else if ((*it)->getType() == RoutingNode)
        {  
          tab[i][0]=(*it)->getX();
          tab[i][1]=(*it)->getY();
          tab[i][2]=(*it)->getWidth();
          tab[i][3]=(*it)->getHeight();
          tab[i][4]=0;
          i++;
        }
      else if (((*it)->getType() == Horizontal)||((*it)->getType() == Vertical))
        {
          createSlicingTreeData((*it), tab, i);
        }
    }
}

int main(int argc, char* argv[])
{
  cout << " -------------- Start -------------- " << endl;


  cout << " -------------- DP12 -------------- " << endl;
  map <float,float>* mapHWDP12 = createMapH(wMinDP12,wMaxDP12,hMinDP12,hMaxDP12,NDP12);
  
  cout << " -------------- CM34 -------------- " << endl;
  map <float,float>* mapHWCM34 = createMapH(wMinCM34,wMaxCM34,hMinCM34,hMaxCM34,NCM34);

  cout << " -------------- M5 -------------- " << endl;
  map <float,float>* mapHWM5 = createMapH(wMinM5,wMaxM5,hMinM5,hMaxM5,NM5);

  cout << " -------------- M6 -------------- " << endl;
  map <float,float>* mapHWM6 = createMapH(wMinM6,wMaxM6,hMinM6,hMaxM6,NM6);
  
  cout << " -------------- M7 -------------- " << endl;
  map <float,float>* mapHWM7 = createMapH(wMinM7,wMaxM7,hMinM7,hMaxM7,NM7);
  
  cout << " -------------- M8 -------------- " << endl;
  map <float,float>* mapHWM8 = createMapH(wMinM8,wMaxM8,hMinM8,hMaxM8,NM8);

  cout << " -------------- M9 -------------- " << endl;
  map <float,float>* mapHWM9 = createMapH(wMinM9,wMaxM9,hMinM9,hMaxM9,NM9);

  cout << endl;
  cout << " -------------- Build Slicing Tree -------------- " << endl;
  HSlicingNode* slicingTree = HSlicingNode::create();
  slicingTree->createPushBackNode(Vertical,Middle);
  slicingTree->createPushBackDevice(mapHWDP12,Middle);
  slicingTree->createPushBackNode(Vertical,Middle);
  slicingTree->createPushBackRouting(1);
  slicingTree->createPushBackDevice(mapHWDP12,Middle);

  cout << "-------------- 1st Hierarchy -------------- " << endl;
  slicingTree->getChild(0)->createPushBackDevice(mapHWM8,Middle);
  slicingTree->getChild(0)->createPushBackDevice(mapHWM5,Middle);
  slicingTree->getChild(0)->createPushBackRouting(1);
  slicingTree->getChild(0)->createSymmetry(1,3);
  slicingTree->getChild(0)->createSymmetry(3,4);
  slicingTree->getChild(0)->createPushBackDevice(mapHWM8,Middle);
  slicingTree->getChild(0)->setSymmetry(5,0);

  cout << "-------------- 2nd Hierarchy -------------- " << endl;
  slicingTree->getChild(2)->createPushBackDevice(mapHWM9  ,Middle);
  slicingTree->getChild(2)->createPushBackDevice(mapHWCM34,Middle);
  slicingTree->getChild(2)->createPushBackDevice(mapHWM6  ,Middle);

  slicingTree->setAllToleranceH(100); // toleranceH = 1 - test Vertical
  slicingTree->setAllToleranceW(100); // toleranceW = 1 - test Horizontal

//slicingTree->createSymmetry(0,5);
//slicingTree->updateGlobalSize();
//slicingTree->pushBackNode(slicingTree->clone());
  slicingTree->updateGlobalSize();
 
  /* cout << "-------------- Test updateGlobalsize: Vertical/Horizontal -------------- " << endl;

     0)Check Routing Space 
     1)Child(0) Vertical or Horizontal
     2)Test on Child n°0 with these parameters
    #define wMinM5 1
    #define wMaxM5 6
    #define hMinM5 1
    #define hMaxM5 6
    #define NM5    5
    
    #define wMinM7 1
    #define wMaxM7 6
    #define hMinM7 1
    #define hMaxM7 6
    #define NM7    5
    
    #define wMinM8 1
    #define wMaxM8 6
    #define hMinM8 1
    #define hMaxM8 6
    #define NM8    5
    3) Verify by hand the values of the map
  */

 /* cout << "-------------- Test updateGlobalsize: Vertical/Horizontal -------------- " << endl; 
     0) Use updateGlobalSize results to choose values for H/W
     1) Test on root with these parameters
     #define wMinM9 1
     #define wMaxM9 6
     #define hMinM9 1
     #define hMaxM9 6
     #define NM9    5
     
     #define wMinM6 1
     #define wMaxM6 6
     #define hMinM6 1
     #define hMaxM6 6
     #define NM6    5
     
     #define wMinCM34 1
     #define wMaxCM34 6
     #define hMinCM34 1
     #define hMaxCM34 6
     #define NCM34    5
    2) Verify the evolution of the values of HW with toleranceH, different achivable width
    3) Test preset status
  */

  cout << " -------------- Test Symmetries -------------- " << endl;
/*
#define wMinDP12 3.1  
#define wMaxDP12 25.1 
#define hMinDP12 1.7  
#define hMaxDP12 7.7  
#define NDP12   10   

#define wMaxM9 6
#define hMinM9 1
#define hMaxM9 6
#define NM9    5

#define wMinM6 1
#define wMaxM6 7
#define hMinM6 2
#define hMaxM6 7
#define NM6    5

#define wMinCM34 1
#define wMaxCM34 8
#define hMinCM34 3
#define hMaxCM34 8
#define NCM34    5

//
#define wMinM5 1
#define wMaxM5 6
#define hMinM5 1
#define hMaxM5 6
#define NM5    5

#define wMinM7 1
#define wMaxM7 7
#define hMinM7 2
#define hMaxM7 7
#define NM7    5

#define wMinM8 1
#define wMaxM8 8
#define hMinM8 3
#define hMaxM8 8
#define NM8    5

1) Test symmetries with child(0) composition, change the symmetries
2) Do it for both Vertical and Horizontal type 
 */
//slicingTree->updateGlobalSize();
  cout << " -------------- Print Children -------------- " << endl;
  slicingTree->printChildren();
  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->print();
  slicingTree->setGlobalSize(1000,1000); 
//cout << " -------------- Print Root -------------- " << endl;
//slicingTree->print();
  cout << "Number of leaf: " <<  slicingTree->getLeafNumber() << endl;
  

  // Writing Datas in a file to be plotted in matlab 
  slicingTree->place();
  ofstream myfile;
  myfile.open (SlicingTreeData);

  float tab[slicingTree->getLeafNumber()][5]; 
  int i = 0;
  createSlicingTreeData(slicingTree, tab, i);
  for (int j = 0; j < slicingTree->getLeafNumber(); j++)
    {
      myfile << tab[j][0] << " " << tab[j][1] << " " << tab[j][2] << " " << tab[j][3] << " " << tab[j][4] << endl;
    }
    myfile.close();

  return 0;
}
