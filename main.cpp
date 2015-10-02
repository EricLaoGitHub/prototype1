#include <iostream>
#include <fstream>

#include <typeinfo>
#include "parameters.h"
#include "slicingNode.h"

using namespace std;

map<float, vector< vector<float> > >* createMapH(float widthmin, float widthmax, float heightmin, float heightmax, float nmax)
{
  float ldelta = (widthmax-widthmin)/nmax;
  float hdelta = (heightmax-heightmin)/nmax;
  map<float, vector< vector<float> > >* mapL = new map<float, vector< vector<float> > >();
  for (int i = 0; i <= nmax; i++){ 
    vector< vector<float> > vec;
    vector<float>           vec2;
    vec.push_back(vec2.push_back(widthmin+ldelta*i));
    mapL->insert(pair<float,float>(heightmax-hdelta*i, vec)); 
  }
  return mapL;
}
void createSlicingTreeData(SlicingNode* data, float tab[][4], int& i)
{
  for (vector<SlicingNode*>::const_iterator it = data->getChildren().begin(); it != data->getChildren().end(); it++)
    {
      if ((*it)->getType() == DeviceNode)
        {  
          tab[i][0]=(*it)->getX();
          tab[i][1]=(*it)->getY();
          tab[i][2]=(*it)->getWidth();
          tab[i][3]=(*it)->getHeight();
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
  map<float, vector < vector<float> > >* mapHWDP12 = createMapH(wMinDP12,wMaxDP12,hMinDP12,hMaxDP12,NDP12);
  
  cout << " -------------- CM34 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWCM34 = createMapH(wMinCM34,wMaxCM34,hMinCM34,hMaxCM34,NCM34);

  cout << " -------------- M5 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWM5 = createMapH(wMinM5,wMaxM5,hMinM5,hMaxM5,NM5);

  cout << " -------------- M6 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWM6 = createMapH(wMinM6,wMaxM6,hMinM6,hMaxM6,NM6);
  
  cout << " -------------- M7 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWM7 = createMapH(wMinM7,wMaxM7,hMinM7,hMaxM7,NM7);
  
  cout << " -------------- M8 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWM8 = createMapH(wMinM8,wMaxM8,hMinM8,hMaxM8,NM8);

  cout << " -------------- M9 -------------- " << endl;
  map<float, vector < vector<float> > >* mapHWM9 = createMapH(wMinM9,wMaxM9,hMinM9,hMaxM9,NM9);

  cout << endl;
  cout << " -------------- Build Slicing Tree -------------- " << endl;
  HSlicingNode* slicingTree = HSlicingNode::create(Middle);
  slicingTree->createPushBackNode(Vertical,Middle);
  slicingTree->createPushBackDevice(mapHWDP12);
  slicingTree->createPushBackNode(Vertical,Middle);
   
  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->print();
  cout << " -------------- Print Children -------------- " << endl;
  slicingTree->printChildren();

  cout << "-------------- 1st Hierarchy -------------- " << endl;
  slicingTree->getChild(0)->createPushBackDevice(mapHWM8, Middle);
  slicingTree->getChild(0)->createPushBackDevice(mapHWM5, Middle);
  slicingTree->getChild(0)->createPushBackDevice(mapHWM7);
  slicingTree->getChild(0)->printChildren();

  cout << "-------------- 2nd Hierarchy -------------- " << endl;
  slicingTree->getChild(2)->createPushBackDevice(mapHWM9  , Middle);
  slicingTree->getChild(2)->createPushBackDevice(mapHWCM34, Middle);
  slicingTree->getChild(2)->createPushBackDevice(mapHWM6  , Middle);
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

  cout << " -------------- Print SlicingTree Placement -------------- " << endl;
  float hvalue = 2.5;
  float wvalue = 30;
//slicingTree->getChild(2)->getChild(2)->setPairH(hvalue);

  slicingTree->place();

  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->print();
  cout << " -------------- Print Children -------------- " << endl;
  slicingTree->printChildren();

  cout << "-------------- 2nd Hierarchy -------------- " << endl;
  slicingTree->getChild(2)->printChildren();












/*
  
  cout << " -------------- Print getPair H & W -------------- " << endl;
  /* RETEST
  cout << "hvalue= " << hvalue << ", H: " << slicingTree->getChild(2)->getChild(2)->getPairH(hvalue).first << ", W: " << slicingTree->getChild(2)->getChild(2)->getPairH(hvalue).second << endl;
  cout << "wvalue= " << wvalue << ", H: " << slicingTree->getChild(2)->getChild(2)->getPairW(wvalue).first << ", W: " << slicingTree->getChild(2)->getChild(2)->getPairW(wvalue).second << endl;
  */
/*
  
  cout << " -------------- End -------------- " << endl;
*/
  // Writing Datas in a file to be plotted in matlab 
  ofstream myfile;
  myfile.open (SlicingTreeData);

  float tab[7][4]; 
  int i = 0;
  createSlicingTreeData(slicingTree, tab, i);
  for (int j = 0; j < 7; j++)
    {
      myfile << tab[j][0] << " " << tab[j][1] << " " << tab[j][2] << " " << tab[j][3] << endl;
    }
  myfile.close();

/*
  slicingTree->getChild(2)->setTolerance(0.5);
  slicingTree->getChild(2)->updateBandSize();
  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->getChild(2)->print();
*/



//cout << " -------------- Print Children -------------- " << endl;
//slicingTree->printChildren();

/*
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  itlow=mymap.upper_bound ('e');  
  if (itlow==mymap.end())
  cout <<"True"<< endl;*/






  return 0;
}
