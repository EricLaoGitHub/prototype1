#include <iostream>
#include <fstream>

#include <typeinfo>
#include "parameters.h"
#include "SlicingNode.h"

using namespace std;
using namespace SlicingTree;

map <float,float>* createMapH(float widthmin, float widthmax, float heightmin, float heightmax, float nmax)
{
  float ldelta = (widthmax-widthmin)/nmax;
  float hdelta = (heightmax-heightmin)/nmax;
  map <float,float>* mapL = new map <float,float>();
  for (int i = 0; i < nmax; i++){ mapL->insert(pair<float,float>(heightmin+hdelta*i, widthmax-ldelta*i)); }
  return mapL;
}


NodeSets createNodeSets(float widthmin, float widthmax, float heightmin, float heightmax, float nmax)
{
  float ldelta = (widthmax-widthmin)/nmax;
  float hdelta = (heightmax-heightmin)/nmax;
  
  NodeSets nodeset = NodeSets();
  for (int i = 0; i < nmax; i++){ nodeset.push_back(DSingleNodeSet::create(heightmin+hdelta*i, widthmax-ldelta*i)); }
  return nodeset;
}

  
void createSlicingTreeData(SlicingNode* data, float tab[][5], int& i)
{
  for (vector<SlicingNode*>::const_iterator it = data->getChildren().begin(); it != data->getChildren().end(); it++)
    {
      if ( (*it)->isDevice() )
        {  
          tab[i][0]=(*it)->getX();
          tab[i][1]=(*it)->getY();
          tab[i][2]=(*it)->getWidth();
          tab[i][3]=(*it)->getHeight();
          tab[i][4]=1;
          i++;
        }
      else if ( (*it)->isRouting() )
        {  
          tab[i][0]=(*it)->getX();
          tab[i][1]=(*it)->getY();
          tab[i][2]=(*it)->getWidth();
          tab[i][3]=(*it)->getHeight();
          tab[i][4]=0;
          i++;
        }
      else if ( ((*it)->isHorizontal()) || ((*it)->isVertical()) )
        {
          createSlicingTreeData((*it), tab, i);
        }
    }
}

int main(int argc, char* argv[])
{
  cout << " -------------- Start -------------- " << endl;


  cout << " -------------- DP12 -------------- " << endl;
  NodeSets nodeSetsDP12 = createNodeSets(wMinDP12,wMaxDP12,hMinDP12,hMaxDP12,NDP12);
  
  cout << " -------------- CM34 -------------- " << endl;
  NodeSets nodeSetsCM34 = createNodeSets(wMinCM34,wMaxCM34,hMinCM34,hMaxCM34,NCM34);

  cout << " -------------- M5 -------------- " << endl;
  NodeSets nodeSetsM5 = createNodeSets(wMinM5,wMaxM5,hMinM5,hMaxM5,NM5);

  cout << " -------------- M6 -------------- " << endl;
  NodeSets nodeSetsM6 = createNodeSets(wMinM6,wMaxM6,hMinM6,hMaxM6,NM6);
  
  cout << " -------------- M7 -------------- " << endl;
//NodeSets nodeSetsM7 = createNodeSets(wMinM7,wMaxM7,hMinM7,hMaxM7,NM7);
  
  cout << " -------------- M8 -------------- " << endl;
  NodeSets nodeSetsM8 = createNodeSets(wMinM8,wMaxM8,hMinM8,hMaxM8,NM8);

  cout << " -------------- M9 -------------- " << endl;
  NodeSets nodeSetsM9 = createNodeSets(wMinM9,wMaxM9,hMinM9,hMaxM9,NM9);

  cout << endl;
  cout << " -------------- Build Slicing Tree -------------- " << endl;
  HSlicingNode* slicingTree = HSlicingNode::create(); 
  slicingTree->setToleranceRatioH(1); // toleranceH = 1 - test Vertical
  slicingTree->setToleranceRatioW(0); // toleranceW = 1 - test Horizontal
  slicingTree->setToleranceBandH(1); // toleranceH = 1 - test Vertical
  slicingTree->setToleranceBandW(5); // toleranceW = 1 - test Horizontal

  slicingTree->createChild(Vertical,AlignCenter);     // VSlicingNode
  slicingTree->createChild(nodeSetsDP12,AlignCenter); // DeviceNode
  slicingTree->createChild(Vertical,AlignCenter);     // VSlicingNode
  slicingTree->createRouting(1);                      // RoutingNode H
  slicingTree->createChild(nodeSetsDP12,AlignCenter); // DeviceNode

  cout << " -------------- 1st Hierarchy -------------- " << endl;
  slicingTree->getChild(0)->createChild(nodeSetsM8,AlignCenter); // DeviceNode
  slicingTree->getChild(0)->createChild(nodeSetsM5,AlignCenter); // DeviceNode
  slicingTree->getChild(0)->createRouting(1);                    // RoutingNode V
  slicingTree->getChild(0)->createChild(1,3);                    // Symmetry, <1,3>
  slicingTree->getChild(0)->createChild(3,4);                    // Symmetry, <3,4>
  slicingTree->getChild(0)->createChild(nodeSetsM8,AlignCenter); // DeviceNode
  slicingTree->getChild(0)->setSymmetry(5,0);                    // Symmetry, <5,0>

  cout << " -------------- 2nd Hierarchy -------------- " << endl;
  slicingTree->getChild(2)->createChild(nodeSetsM9  ,AlignCenter); // DeviceNode
  slicingTree->getChild(2)->createChild(nodeSetsCM34,AlignCenter); // DeviceNode
  slicingTree->getChild(2)->createChild(nodeSetsM6  ,AlignCenter); // DeviceNode

//slicingTree->pushBackNode(slicingTree->clone());

  
  cout << " -------------- UpdateGlobalSize -------------- " << endl;
  slicingTree->updateGlobalSize();

  cout << " -------------- Print Children -------------- " << endl;
//slicingTree->printChildren();
  cout << " -------------- Print Root -------------- " << endl;
//slicingTree->print();
//cout << "Occupation Area is : " << slicingTree->getOccupationArea() << "%." << endl;
  cout << " -------------- SetGlobalSize -------------- " << endl;
  slicingTree->setGlobalSize2(15, 20); 
//cout << " -------------- Print Root -------------- " << endl;
//slicingTree->print();
//cout << "Number of leaf: " <<  slicingTree->getLeafNumber() << endl;
  

// Writing Datas in a file to be plotted in matlab 
  cout << " -------------- Placement -------------- " << endl;
  slicingTree->place();
  cout << " -------------- Print Children -------------- " << endl;
  slicingTree->printChildren();
  cout << " -------------- Print Root -------------- " << endl;
  slicingTree->print();
  cout << " -------------- end Root -------------- " << endl;  
  cout << "Occupation Area is : " << slicingTree->getOccupationArea() << "%." << endl;

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
  cout << "Placement matlab file saved" << endl;

  myfile.open (SlicingTreeData2);
  
  NodeSets test = slicingTree->getNodeSets();
  for (vector <SingleNodeSet*>::const_iterator itPrint = test.begin(); itPrint != test.end(); itPrint++)
    {
    //myfile << (*itPrint)->getWidth() << " " << (*itPrint)->getHeight() << " " << (*itPrint)->getCount() << endl;
      myfile << (*itPrint)->getWidth() << " " << (*itPrint)->getHeight() << endl;
    }
  
  myfile.close();
  cout << "Ratio     matlab file saved" << endl;

//SingleNodeSet* test1 = slicingTree->getNodeSets().getNodeSetsHW(20.8, 22.2, 0); 
//pair<float,float> paire = slicingTree->getChild(0)->getPairHW(20.9, 22.1);
//cout << "H; " << paire.first;
//cout << ", W: "  << paire.second << endl;

  return 0;
}
