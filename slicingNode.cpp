#include "slicingNode.h"

using namespace std;

// used for tests only
void printMap(map<float,float>* mapPrint)
{
  cout << "PrintMap - MapHW:" << endl;
  for (map <float,float>::iterator itPrint = mapPrint->begin(); itPrint != mapPrint->end(); itPrint++)
   { cout << "H = " << itPrint->first << ", W = " << itPrint->second << endl;}
  cout << endl;
}

bool compareMap(map<float,float>* map1, map<float,float>* map2) 
{
  bool comp = true;
  map<float,float>::const_iterator it2 = map2->begin();
  for (map<float,float>::const_iterator it1 = map1->begin(); it1 != map1->end(); it1++)
    {
      if( ((*it1).first != (*it2).first)||((*it1).second != (*it2).second) ){ comp = false; }
      if(it2 != map2->end()){ it2++; }
    }
  return comp;
  }

map <float,float>* cloneMapHW(map<float,float>* map1)
{
  map <float,float>* mapHW = new map <float,float>();
  for (map<float,float>::const_iterator it = map1->begin(); it != map1->end(); it++)
    { mapHW->insert(pair<float,float>((*it).first, (*it).second)); }
  return mapHW;
}

// class Node
SlicingNode::SlicingNode(
                         SlicingType       type, 
                         map<float,float>* mapHW,
                         CenteringType     c, 
                         float             x, 
                         float             y, 
                         float             w, 
                         float             h
                        ):_type(type),_c(c),_x(x),_y(y),_w(w),_h(h)
{ 
  if (mapHW == NULL){ _mapHW = new map <float,float>(); } 
  else              { _mapHW = mapHW; }
  _preset = false;
} 
SlicingNode::~SlicingNode(){}

SlicingType       SlicingNode::getType         () const { return _type; }
float             SlicingNode::getWidth        () const { return _w; }
float             SlicingNode::getHeight       () const { return _h; }
float             SlicingNode::getX            () const { return _x; }
float             SlicingNode::getY            () const { return _y; }
CenteringType     SlicingNode::getCenteringType() const { return _c; }
map<float,float>* SlicingNode::getMapHW        () const { return _mapHW; }
bool              SlicingNode::getPreset       () const { return _preset; }

pair<float,float> SlicingNode::getPairH(float h) const 
{
  float w        = 0;
  float hclosest = 0;
  for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++)
    { 
      if ( (itHW->first > hclosest) && (h >= itHW->first) )
        {
          hclosest = itHW->first;
          w        = itHW->second;
        }
    }
  if ( (w == 0) && (hclosest == 0) ){ cerr << "No solution for h = " << h << " has been found." << endl; }
  return pair<float,float>(hclosest,w);
}

pair<float,float> SlicingNode::getPairW(float w) const 
{
  float wclosest = 0;
  float h        = 0;
  for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++)
    { 
      if ( (itHW->second > wclosest) && (w >= itHW->second) )
        {
          h        = itHW->first;
          wclosest = itHW->second;
        }
    }
  if ( (h == 0) && (wclosest == 0) ){ cerr << "No solution for w = " << w << " has been found." << endl; }
  return pair<float,float>(h,wclosest);
}

void SlicingNode::setPairH(float h)
{
  pair<float,float> hw = this->getPairH(h);
  _h                   = hw.first;
  _w                   = hw.second;
}

void SlicingNode::setPairW(float w)
{
  pair<float,float> hw = this->getPairW(w);
  _h                   = hw.first;
  _w                   = hw.second;
}

void SlicingNode::setWidth        (float w)                { _w = w; }
void SlicingNode::setHeight       (float h)                { _h = h; }
void SlicingNode::setX            (float x)                { _x = x; }
void SlicingNode::setY            (float y)                { _y = y; }
void SlicingNode::setCenteringType(CenteringType c)        { _c = c; }
void SlicingNode::setPreset       (bool preset)            { _preset = preset; }
void SlicingNode::setMapHW        (map<float,float>* mapHW){ _mapHW  = mapHW; }

void SlicingNode::print() const
{
  cout << "- Print from Slicing Node - " << endl;
  if      (_type == Horizontal )
    { 
      cout << "SlicingType: Horizontal" << endl; 
      if      (_c == LB    ){ cout << "CenteringType: Left"    << endl; }
      else if (_c == Middle){ cout << "CenteringType: Middle"  << endl; }
      else if (_c == RT    ){ cout << "CenteringType: Right"   << endl; }
      else                  { cout << "CenteringType: Unknown" << endl; }
    }
  else if (_type == Vertical   )
    { 
      cout << "SlicingType: Vertical"   << endl; 
      if      (_c == LB    ){ cout << "CenteringType: Bot"     << endl; }
      else if (_c == Middle){ cout << "CenteringType: Middle"  << endl; }
      else if (_c == RT    ){ cout << "CenteringType: Top"     << endl; }
      else                  { cout << "CenteringType: Unknown" << endl; }
  }
  else if (_type == DeviceNode )
    { 
      cout << "SlicingType: Device"     << endl; 
      if      (_c == LB    ){ cout << "CenteringType: Left/Bot"  << endl; }
      else if (_c == Middle){ cout << "CenteringType: Middle"    << endl; }
      else if (_c == RT    ){ cout << "CenteringType: Right/Top" << endl; }
      else                  { cout << "CenteringType: Unknown"   << endl; }
    }
  else if (_type == RoutingNode )
    { 
      cout << "SlicingType: Routing space"     << endl; 
    }
  else { cout << "SlicingType: Unknown"    << endl; }
  
  cout << "preset    = " << _preset << endl;
  cout << "Height    = " << _h      << endl;
  cout << "Width     = " << _w      << endl;
  cout << "X         = " << _x      << endl;
  cout << "Y         = " << _y      << endl;
  cout << endl;

  if (_type != RoutingNode )
    {
      cout << "MapHW:" << endl;
      for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++){ cout << "H = " << itHW->first << ", W = " << itHW->second << endl;}
      cout << endl;
    }
}

// class HVSlicingNode
HVSlicingNode::HVSlicingNode(
                             SlicingType   type,
                             CenteringType c, 
                             float         toleranceH, 
                             float         toleranceW, 
                             float         x, 
                             float         y, 
                             float         w, 
                             float         h
                            ):SlicingNode(type,NULL,c,x,y,w,h),
                              _toleranceH(toleranceH),_toleranceW(toleranceW){}
HVSlicingNode::~HVSlicingNode(){}

void HVSlicingNode::createPushBackNode(
                                       SlicingType   type, 
                                       CenteringType c,
                                       float         toleranceH, 
                                       float         toleranceW, 
                                       float         x, 
                                       float         y, 
                                       float         w, 
                                       float         h
                                      ) 
{ 
  if (type == Horizontal)    { this->pushBackNode(HSlicingNode::create(c,toleranceH,toleranceW,x,y,w,h)); }
  else if (type == Vertical) { this->pushBackNode(VSlicingNode::create(c,toleranceH,toleranceW,x,y,w,h)); }
  else { cerr << " Error(void HSlicingNode::createPushBack(SlicingType type, CenteringType c, float x, float y, float w, float h)): Unknown type." << endl; }
}

void HVSlicingNode::createPushBackDevice(
                                         map<float,float>* mapHW,  
                                         CenteringType     c,
                                         float             x, 
                                         float             y, 
                                         float             w, 
                                         float             h
                                        )
{ this->pushBackNode(DSlicingNode::create(mapHW,c,x,y,w,h)); }


void HVSlicingNode::createPushBackRouting(float hw, float x, float y)
{ 
  if (this->getType() == Horizontal)    { this->pushBackNode(RHSlicingNode::create(hw,x,y)); }
  else if (this->getType() == Vertical) { this->pushBackNode(RVSlicingNode::create(hw,x,y)); } 
  else { cerr << " Error(void HVSlicingNode::createPushBackRouting(float hw, float x, float y)): Unknown type." << endl; }
}

int                         HVSlicingNode::getNbChild()        const { return _children.size(); }
SlicingNode*                HVSlicingNode::getChild(int index) const { return _children[index]; }
const vector<SlicingNode*>& HVSlicingNode::getChildren()       const { return _children; }

void HVSlicingNode::printChildren()
{
  int count = 1;
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (((*it)->getType() == DeviceNode)||((*it)->getType() == RoutingNode)){
          cout << "-- Children: " << count << "/" << _children.size() << " --" << endl;
          (*it)->print(); 
      }
      else
        {
          cout << "-- Children: " << count << "/" << _children.size() << " --" << endl;
          (*it)->print();
          (*it)->printChildren();
        }
      count++;
    }
}

void HVSlicingNode::insertNode (SlicingNode* node, int index)
{
  vector<SlicingNode*>::iterator it = _children.begin();
  for (int i = 0; i < index; i++){ if (it != _children.end()){it++;} }
  _children.insert(it,node);
}
void HVSlicingNode::pushBackNode  (SlicingNode* node){ _children.push_back(node); }
void HVSlicingNode::pushFrontNode (SlicingNode* node){ _children.insert(_children.begin(), node); }
void HVSlicingNode::removeAllNodes()                 { _children.clear(); }

void HVSlicingNode::removeNode    (SlicingNode* node) 
{ 
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    { 
      if (*it == node){  _children.erase(it); }
    }
}

float HVSlicingNode::updateHeight()
{
  float height = 0;
  if ((this->getType() == DeviceNode)||(this->getType() == RoutingNode)){ height = _h; }
  else if (this->getType() == Horizontal)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        { height += (*it)->updateHeight(); }
    }  
  else if (this->getType() == Vertical)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        { if (height < (*it)->updateHeight()){ height = (*it)->getHeight(); } }
    }
  else
    { cerr << " Error(HVSlicingNode::updateHeight()): Unknown type in SlicingTree." << endl; }
  _h = height;
  return height;
}

float HVSlicingNode::updateWidth()
{
  float width = 0;
  if ((this->getType() == DeviceNode)||(this->getType() == RoutingNode)){ width = _w; }
  else if (this->getType() == Vertical)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        { width += (*it)->updateWidth(); }
    }  
  else if (this->getType() == Horizontal)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        { if (width < (*it)->updateWidth()){ width = (*it)->getWidth(); } }
    }
  else
    { cerr << " Error(HVSlicingNode::updateWidth()): Unknown type in SlicingTree." << endl; }
  _w = width;
  return width;
}

CenteringType HVSlicingNode::getCenteringType() const{ return _c; }

void HVSlicingNode::place(float x, float y)
{
  float xref = x;
  float yref = y;
  if (this->getType() == Horizontal)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        { 
          if (((*it)->getType() == Horizontal)||((*it)->getType() == Vertical)){ 
            if ((*it)->getCenteringType() == LB)
              {
                (*it)->setX(xref);
                (*it)->setY(yref);
              }
            else if ((*it)->getCenteringType() == Middle)
              {
                (*it)->setX(xref + (_w/2) - ((*it)->getWidth()/2));
                (*it)->setY(yref);
              }
            else if ((*it)->getCenteringType() == RT)
              {
                (*it)->setX(xref + _w - (*it)->getWidth());
                (*it)->setY(yref);
              }
          }

          if      ((*it)->getCenteringType() == LB)     { (*it)->place(xref                                 , yref); }
          else if ((*it)->getCenteringType() == Middle) { (*it)->place(xref + (_w/2) - ((*it)->getWidth()/2), yref); }
          else if ((*it)->getCenteringType() == RT)     { (*it)->place(xref + _w     -  (*it)->getWidth()   , yref); }
          else { cerr << " Error(place(float x, float y)): Unknown CenteringType in SlicingTree." << endl; }

          xref = x;
          yref += (*it)->getHeight();
        }
    }
  else if (this->getType() == Vertical)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        {
          if (((*it)->getType() == Horizontal)||((*it)->getType() == Vertical))
            { 
              if ((*it)->getCenteringType() == LB)
              {
                (*it)->setX(xref);
                (*it)->setY(yref);
              }
            else if ((*it)->getCenteringType() == Middle)
              {
                (*it)->setX(xref);
                (*it)->setY(yref + (_h/2) - ((*it)->getHeight()/2));
              }
            else if ((*it)->getCenteringType() == RT)
              {
                (*it)->setX(xref);
                (*it)->setY(yref + _h - (*it)->getHeight());
              }
            }

          if      ((*it)->getCenteringType() == LB)     { (*it)->place(xref, yref); }
          else if ((*it)->getCenteringType() == Middle) { (*it)->place(xref, yref + (_h/2) - ((*it)->getHeight()/2)); }
          else if ((*it)->getCenteringType() == RT)     { (*it)->place(xref, yref +  _h    -  (*it)->getHeight())   ; }
          else { cerr << " Error(place(float x, float y)): Unknown CenteringType in SlicingTree." << endl; }


          xref += (*it)->getWidth();
          yref = y;
        }
    }
  else { cerr << " Error(place(float x, float y)): Unknown Slicingtype in SlicingTree." << endl; }
}

void  HVSlicingNode::setToleranceH   (float tolerance){ _toleranceH = tolerance; }
float HVSlicingNode::getToleranceH   () const         { return _toleranceH; }
void  HVSlicingNode::setAllToleranceH(float tolerance)
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (((*it)->getType() != DeviceNode)&&((*it)->getType() != RoutingNode))
        { (*it)->setAllToleranceH(tolerance); }
    }
  _toleranceH = tolerance; 
}

void  HVSlicingNode::setToleranceW   (float tolerance){ _toleranceW = tolerance; }
float HVSlicingNode::getToleranceW   () const         { return _toleranceW; }
void  HVSlicingNode::setAllToleranceW(float tolerance)
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (((*it)->getType() != DeviceNode)&&((*it)->getType() != RoutingNode))
        { (*it)->setAllToleranceW(tolerance); }
    }
  _toleranceW = tolerance; 
}

void HVSlicingNode::updateGlobalSize()
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      (*it)->updateGlobalSize();
    }
    
  if (this->getNbChild() == 1)
    {
      _mapHW = (*_children.begin())->getMapHW();
      cerr << "Error(void HVSlicingNode::updateGlobalSize()): You have a HVSlicingNode with only 1 child. This is an incorrect way to use HVSlicingNodes." << endl; 
    }
  else if (this->emptyChildrenMap() != true)
    {     
      if (this->getType() == Vertical)
        {
        // Clear the content of the map
          _mapHW->clear(); 

        // childrenpair represents 1 state of the combinations
          vector< pair<float,float> > childrenpair;
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            { 
              if ( (*it)->getType() != RoutingNode ) 
                { childrenpair.push_back((*(*it)->getMapHW()->begin())); }
              else 
                { childrenpair.push_back(pair<float,float>((*it)->getHeight(),(*it)->getWidth())); }
            }

          int   index = 0; // index used to modify childrenpair content
          float hmin  = (*_children.begin())->getMapHW()->upper_bound(index)->first; // min height from the current combinations
          float hmax  = (*_children.begin())->getMapHW()->upper_bound(index)->first; // max height from the current combinations
          
          list< pair<float,float> >             currentHs  = list< pair<float,float> >(); // heights from the current combination
          vector <int>                          modulos    = vector<int>();               // vectors of the modulos
          int                                   modulo     = 1;                           // to calculate modulos
          int                                   counter    = 1;                           // counter
          int                                   endCounter = 1;                           // end counter-1
          float                                 currentW   = 0;                           // total width of the current combination
          vector< pair<float,float> >::iterator itpair     = childrenpair.begin();        // iterator to go through childrenpair

        // check/adjust symmetries
          bool symmetryFound = false;
          this->checkSymmetries();

        // Set the modulos
          modulos.push_back(1);
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            {
              if (it != _children.begin()){ modulos.push_back(modulo); }
              if ( (*it)->getType() != RoutingNode )
                {
                // Check if the current child is a symmetry or not
                  for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                    { if ((*it2).second == index){ symmetryFound = true; }  }

                  if (symmetryFound == false)
                    {
                      modulo     *= (*it)->getMapHW()->size();
                      endCounter *= (*it)->getMapHW()->size();
                    }
                }
              index++;
              symmetryFound = false;
            }

          index = 0;
          pair<int,int> sympair = pair<int,int>();
            
          while( counter != endCounter+1 )
            {
            // Need to be reset at each loop
              index     = 0;
              itpair    = childrenpair.begin();
              currentW  = 0;
              currentHs.clear();
            //cout << "------ Element ------" << endl;
            //cout << "Counter: " << counter << endl;
            //cout << "index: " << index << endl;

              for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
                {
                //cout << "itpair h: " << (*itpair).first << ", w: " << (*itpair).second << endl;
                  
                // We check if the current child index is a symmetry
                  if (_symmetries.empty() != true)
                    {
                      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                        {
                          if ((*it2).second == index)
                            { 
                              sympair = pair<int,int>((*it2).first,(*it2).second); 
                              symmetryFound = true;
                            //cout << "SymmetryFound: original = " << (*it2).first << ", copy = " << (*it2).second << endl;
                            }
                        }
                    }
                  
                // If yes, use the previous values from its symmetric node
                  if (symmetryFound == true)
                    {
                      itpair - (sympair.second - sympair.first);
                      if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
                      currentW += (*itpair).second;
                      childrenpair[index] = childrenpair[sympair.first];
                      itpair + (sympair.second - sympair.first);
                  
                    }
                  else
                    {
                    // Collect the pair<float,float> of the combination in order sort them. Calculate the width of the combination.
                      if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
                      currentW += (*itpair).second;
                  
                    // Go through the different combinations 
                      if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ( (*it)->getType() != RoutingNode ))
                        {
                          if ( (*it)->getMapHW()->upper_bound((*itpair).first) != (*it)->getMapHW()->end() )
                            { childrenpair[index] = (*(*it)->getMapHW()->upper_bound((*itpair).first)); }
                          else
                            { childrenpair[index] = (*(*it)->getMapHW()->begin()); }
                        }
                    }
                  itpair++;
                  index++;
                  symmetryFound = false;
                }
            // Combination number, determining height max of the combination
              counter++;
              currentHs.sort();

              hmin = currentHs.front().first;
              hmax = currentHs.back().first;

            /* If the difference betwen the highest and the lowest height is allowed:
               1) Check if it's already in the map, yes: next step, no: add combination
               2) Compare previous width and the current width and keep the highest width.
             */
              if ((hmax-hmin) <= _toleranceH)
                {
                  if ( _mapHW->find(hmax) != _mapHW->end() )
                    {
                      if ( (*_mapHW->find(hmax)).second < currentW ) 
                        {( *_mapHW->find(hmax)).second = currentW; }
                    }
                  else 
                    { _mapHW->insert(pair<float,float> ( hmax, currentW) ); }
                }
            }
        }
      else if (this->getType() == Horizontal)
        {
        //cout << "------------------------ Hello I'm horizontal -------------------" << endl << endl<< endl<< endl<< endl;
        // Similar to Vertical type but instead, we pay attention to the width instead of the height
          _mapHW->clear(); 

          vector< pair<float,float> > childrenpair;
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            { 
              if ( (*it)->getType() != RoutingNode) 
                { childrenpair.push_back((*(*it)->getMapHW()->begin())); }
              else 
                { childrenpair.push_back(pair<float,float>((*it)->getHeight(),(*it)->getWidth())); }
            }
         
          int   index = 0; 
          float wmin  = (*_children.begin())->getMapHW()->upper_bound(index)->second; 
          float wmax  = (*_children.begin())->getMapHW()->upper_bound(index)->second; 

          list< pair<float,float> >             currentWs  = list< pair<float,float> >();
          vector <int>                          modulos    = vector<int>();
          int                                   modulo     = 1;
          int                                   counter    = 1;
          int                                   endCounter = 1;
          float                                 currentH   = 0;
          vector< pair<float,float> >::iterator itpair     = childrenpair.begin();

          bool symmetryFound = false;
          this->checkSymmetries();

          modulos.push_back(1);
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            {
              if (it != _children.begin()){ modulos.push_back(modulo); }
              if ( (*it)->getType() != RoutingNode )
                {
                  for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                    { if ((*it2).second == index){ symmetryFound = true; }  }

                  if (symmetryFound == false)
                    {
                      modulo     *= (*it)->getMapHW()->size();
                      endCounter *= (*it)->getMapHW()->size();
                    }
                }
              index++;
              symmetryFound = false;
            }
          
          index = 0;
          pair<int,int> sympair = pair<int,int>();

          while( counter != endCounter+1 )
            {
              index     = 0;
              itpair    = childrenpair.begin();
              currentH  = 0;
              currentWs.clear();
            //cout << "------ Element ------" << endl;
            //cout << "Counter: " << counter << endl;

              for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
                {
                //cout << "itpair h: " << (*itpair).first << ", w: " << (*itpair).second << endl;
                  if (_symmetries.empty() != true)
                    {
                      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                        {
                          if ((*it2).second == index)
                            { 
                              sympair = pair<int,int>((*it2).first,(*it2).second); 
                              symmetryFound = true;
                            }
                        }
                    }
                  
                  if (symmetryFound == true)
                    {
                      itpair - (sympair.second - sympair.first);
                      if ((*it)->getType() != RoutingNode ) 
                        { currentWs.push_back(pair<float,float>((*itpair).second, (*itpair).first)); }
                      currentH += (*itpair).first;
                      childrenpair[index] = childrenpair[sympair.first];
                      itpair + (sympair.second - sympair.first);
                    }
                  else
                    {
                      if ((*it)->getType() != RoutingNode ){ currentWs.push_back(pair<float,float>((*itpair).second,(*itpair).first)); }
                      currentH += (*itpair).first;
                      
                      if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ( (*it)->getType() != RoutingNode ))
                        {
                          if ( (*it)->getMapHW()->upper_bound((*itpair).first) != (*it)->getMapHW()->end() )
                            { childrenpair[index] = (*(*it)->getMapHW()->upper_bound((*itpair).first)); }
                          else
                            { childrenpair[index] = (*(*it)->getMapHW()->begin()); }
                        }
                    }
                  itpair++;
                  index++;
                  symmetryFound = false;
                }
              counter++;
              currentWs.sort();
              wmin = currentWs.front().first;
              wmax = currentWs.back().first;

              if ((wmax-wmin) <= _toleranceW)
                {
                  if ( _mapHW->find(currentH) != _mapHW->end() )
                    { if ( (*_mapHW->find(currentH)).second < wmax )
                        { (*_mapHW->find(currentH)).second = wmax; }  }
                  else 
                    { _mapHW->insert(pair<float,float> ( currentH, wmax )); }
                }
            }
        }
      if (_mapHW->empty()) { cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set a larger toleranceH or toleranceW." << endl; }
      printMap(_mapHW);
    }
}

bool HVSlicingNode::emptyChildrenMap() const
{
  bool flag = false;
  for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (((*it)->getMapHW() != NULL)&&((*it)->getType() != RoutingNode))
        { if ((*it)->getMapHW()->empty() == true) {flag = true;} }
    }
  return flag;
}

pair<float, float> HVSlicingNode::setGlobalSize(float height, float width) // Width = 0 would give you the min width. Very High width give you the max width
{
  float heightfinal = 0;
  float widthfinal  = 0;

// Find the closest (not higher) possible height for every children. Doing so will provide the lowest width possible.
  if ((this->getType() == Vertical)&&(this->emptyChildrenMap() != true))
    {
      vector< pair<float,float> > childrenpair;

    // childrenpair represents 1 state of the combinations, make sure that we take into account if the HVSlicingNode is preset.
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
        {   
          if ((*it)->getPreset() != true) 
            { childrenpair.push_back(pair<float,float>((*it)->getMapHW()->begin()->first,(*it)->getMapHW()->begin()->second)); }
          else 
            { childrenpair.push_back(pair<float,float>((*it)->getHeight(),(*it)->getWidth())); }
        }

    /* Best Height [height-toleranceH;height] means 1) Respect the toleranceH 2) Closest to the desired Height if not inside of the interval
       Best Width  [width-tolerance> ;Width ] means 1) Respect the toleranceW and have a acceptable height 2) Less and closest to Width but higher width are accepted if no lower width but still closest to Width.
     */
      int                                   index        = 0;
      float                                 hmin         = (*_children.begin())->getMapHW()->upper_bound(index)->first; // min height from the current combinations
      float                                 hmax         = (*_children.begin())->getMapHW()->upper_bound(index)->first; // max height from the current combinations
      float                                 hbest        = 0;                                                           // Current best Height 
      float                                 wbest        = 0;                                                           // Current best Width
      vector< pair<float,float> >           pairbest     = vector< pair<float,float> >();                               // Current bestPair
      vector< pair<float,float> >           currentPairs = vector< pair<float,float> >();                               // Current combination

      list< pair<float,float> >             currentHs    = list< pair<float,float> >();                                 // heights from the current combination
      vector<int>                           modulos      = vector<int>();                                               // vectors of the modulos
      int                                   modulo       = 1;                                                           // to calculate modulos
      int                                   counter      = 1;                                                           // counter
      int                                   endCounter   = 1;                                                           // end counter-1
      float                                 currentW     = 0;                                                           // total width of the current combination
      vector< pair<float,float> >::iterator itpair       = childrenpair.begin();                                        // iterator to go through childrenpair

    // check/adjust symmetries
      bool symmetryFound = false;
      this->checkSymmetries();

    // Set the modulos
      modulos.push_back(1);
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
        {
          if (it != _children.begin()){ modulos.push_back(modulo); }
          if ( (*it)->getType() != RoutingNode )
            {
            // check if the current child is a symmetry or not
              for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                { if ((*it2).second == index){ symmetryFound = true; }  }
              if (symmetryFound == false)
                {
                  modulo     *= (*it)->getMapHW()->size();
                  endCounter *= (*it)->getMapHW()->size();
                }
            }
          index++;
          symmetryFound = false;
        }
      index = 0;
      pair<int,int> sympair = pair<int,int>();
      
      while( counter != (endCounter+1) )
        {
        // Need to be reset at each loop
          index        = 0;
          itpair       = childrenpair.begin();
          currentPairs.clear();
          currentW     = 0; 
          currentHs.clear(); 
          
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            {
              if (_symmetries.empty() != true)
                {
                  for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                    if ((*it2).second == index)
                      { 
                        sympair = pair<int,int>((*it2).first,(*it2).second); 
                        symmetryFound = true;
                      }
                }
              if (symmetryFound == true)
                {
                  itpair - (sympair.second - sympair.first);
                  currentPairs.push_back((*itpair)); 
                  if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
                  currentW += (*itpair).second;
                  childrenpair[index] = childrenpair[sympair.first];
                  itpair + (sympair.second - sympair.first);
                }
              else
                {
                // Collect the pair<float,float> in vector (size order) and list (sort height) of the combination in order sort them. Calculate the width of the combination.
                  currentPairs.push_back((*itpair)); 
                  if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
                  currentW += (*itpair).second;
                  
                // Go through the different combinations
                  if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ((*it)->getPreset() != true))
                    {
                      if ( (*it)->getMapHW()->upper_bound((*itpair).first) != (*it)->getMapHW()->end() )
                        { childrenpair[index] = (*(*it)->getMapHW()->upper_bound((*itpair).first)); }
                      else
                        { childrenpair[index] = (*(*it)->getMapHW()->begin()); }
                    }
                }
              itpair++;
              index++;
              symmetryFound = false;
            }
        // Combination number, determining height max of the combination
          counter++;
          currentHs.sort();

          hmin = currentHs.front().first;
          hmax = currentHs.back().first;

        // Determine the best Height and the best Width
          if ((hmax-hmin) <= _toleranceH)
            {
              if (hmax <= height)
                {
                  if ( (height-hmax) <= _toleranceH )
                    {
                      if ( wbest == 0 )
                        {
                          pairbest = currentPairs; 
                          hbest = hmax;
                          wbest = currentW;
                        }
                      else
                        {
                          if ( (currentW > wbest)&&(currentW <= width) )
                            { 
                              pairbest = currentPairs; 
                              hbest = hmax;
                              wbest = currentW;
                            }
                          else if ( (currentW < wbest)&&(wbest > width) )
                            { 
                              pairbest = currentPairs; 
                              hbest = hmax;
                              wbest = currentW;
                            }
                        }
                    }
                  else if (hmax > hbest)
                    { 
                      pairbest = currentPairs; 
                      hbest = hmax;
                      wbest = currentW;
                    }
                }
            }
        }
    // If a valid pair is found, propate required sizes to lower hierarchy
      if (pairbest.empty() != true)
        {
          pair<float,float> pairreal = pair<float,float> (0,0);
          vector< pair<float,float> >::iterator it2 = pairbest.begin();
          for(vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++)
            {
              if ((*it3)->getPreset() != true){ pairreal = (*it3)->setGlobalSize(height,(*it2).second); }
              else { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth());}
              widthfinal += pairreal.second;
              if (heightfinal < pairreal.first) { heightfinal = pairreal.first; }
              it2++;
            }
        }
    }
  else if ((this->getType() == Horizontal)&&(this->emptyChildrenMap() != true))
    {
    // Similar to Vertical type but instead, we pay attention to the width instead of the height
      vector< pair<float,float> > childrenpair;

      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
        { 
          if ( (*it)->getPreset() != true ) 
            { childrenpair.push_back(pair<float,float>((*it)->getMapHW()->begin()->first,(*it)->getMapHW()->begin()->second)); }
          else 
            { childrenpair.push_back(pair<float,float>((*it)->getHeight(),(*it)->getWidth()));}
        }

      int                                   index        = 0;
      float                                 wmin         = (*_children.begin())->getMapHW()->upper_bound(0)->second; 
      float                                 wmax         = (*_children.begin())->getMapHW()->upper_bound(0)->second; 

      float                                 hbest        = 0;
      float                                 wbest        = 0;
      vector< pair<float,float> >           pairbest     = vector< pair<float,float> >();
      vector< pair<float,float> >           currentPairs = vector< pair<float,float> >();

      list< pair<float,float> >             currentWs    = list< pair<float,float> >();
      vector<int>                           modulos      = vector<int>();
      int                                   modulo       = 1;                         
      int                                   counter      = 1; 
      int                                   endCounter   = 1;
      float                                 currentH     = 0; 
      vector< pair<float,float> >::iterator itpair       = childrenpair.begin();

      bool symmetryFound = false;
      this->checkSymmetries();

      modulos.push_back(1);
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
        {
          if (it != _children.begin()){ modulos.push_back(modulo); }
          if ( (*it)->getType() != RoutingNode )
            {
              for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                { if ((*it2).second == index){ symmetryFound = true; }  }
              
              if (symmetryFound == false)
                {
                  modulo     *= (*it)->getMapHW()->size();
                  endCounter *= (*it)->getMapHW()->size();
                }
            }
          index++;
          symmetryFound = false;
        }

      index = 0;
      pair<int,int> sympair = pair<int,int>();
      
      while( counter != (endCounter+1) )
        {
          index        = 0;
          itpair       = childrenpair.begin();
          currentPairs.clear();
          currentH     = 0; 
          currentWs.clear(); 
        //cout << "------ Element ------" << endl;
        //cout << "Counter: " << counter << endl;
         
          for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
            {
            //cout << "itpair h: " << (*itpair).first << ", w: " << (*itpair).second << endl;
              if (_symmetries.empty() != true)
                {
                  for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++)
                    {
                      if ((*it2).second == index)
                        { 
                          sympair = pair<int,int>((*it2).first,(*it2).second); 
                          symmetryFound = true;
                        }
                    }
                }
              
              if (symmetryFound == true)
                {
                  itpair - (sympair.second - sympair.first);
                  currentPairs.push_back((*itpair));
                  if ((*it)->getType() != RoutingNode ) 
                    { currentWs.push_back(pair<float,float>((*itpair).second, (*itpair).first)); }
                  currentH += (*itpair).first;
                  childrenpair[index] = childrenpair[sympair.first];
                  itpair + (sympair.second - sympair.first);
                }
              else
                {
                  currentPairs.push_back(pair<float,float>((*itpair).first,(*itpair).second));
                  if ((*it)->getType() != RoutingNode ){ currentWs.push_back(pair<float,float>((*itpair).second,(*itpair).first)); }
                  currentH += (*itpair).first;
                  
                  if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ((*it)->getPreset() != true))
                    {
                      if ( (*it)->getMapHW()->upper_bound((*itpair).first) != (*it)->getMapHW()->end() )
                        { childrenpair[index] = (*(*it)->getMapHW()->upper_bound((*itpair).first)); }
                      else
                        { childrenpair[index] = (*(*it)->getMapHW()->begin()); }
                    }
                }
              index++;
              itpair++;
              symmetryFound = false;
            }
          counter++;
          currentWs.sort();
          wmin = currentWs.front().first;
          wmax = currentWs.back().first;

        // Checkin wmax and wmin difference first. Then check the height and then the most appropriate width.
          if ((wmax-wmin) <= _toleranceW)
            {
              if (currentH <= height)
                {
                  if ( (height-currentH) <= _toleranceH )
                    {
                      if (( hbest == 0 )||( wbest == 0 ))
                        {
                          pairbest = currentPairs; 
                          hbest = currentH;
                          wbest = wmax;
                        }
                      if ( (height-hbest > _toleranceH)&&(hbest < currentH) )
                        {
                          pairbest = currentPairs; 
                          hbest = currentH;
                          wbest = wmax;
                        }
                      else
                        {
                          if ( (wmax > wbest)&&(wmax <= width) )
                            { 
                              pairbest = currentPairs; 
                              hbest = currentH;
                              wbest = wmax;
                            }
                          else if ( (wmax < wbest)&&(wbest > width) )
                            { 
                              pairbest = currentPairs; 
                              hbest = currentH;
                              wbest = wmax;
                            }
                        }
                    }
                  else if (currentH > hbest)
                    { 
                      pairbest = currentPairs; 
                      hbest = currentH;
                      wbest = wmax;
                    }
                }
            }
        }
      if (pairbest.empty() != true)
        {
          pair<float,float> pairreal = pair<float,float> (0,0);
          vector< pair<float,float> >::iterator it2 = pairbest.begin();
          for(vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++)
            {
              if ((*it3)->getPreset() != true){ pairreal = (*it3)->setGlobalSize((*it2).first,width); }
              else { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth());}
              heightfinal += pairreal.first;
              if (widthfinal < pairreal.second)
                { widthfinal = pairreal.second; }
              it2++;
            }
        }
    }
  _h = heightfinal;
  _w = widthfinal;
  if ( (_h == 0)||(_w == 0) )
    { cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
  if ( (_h != 0)&&(_w != 0) ) { _preset = true; }
  return pair<float,float>(_h,_w);
}

void HVSlicingNode::createSymmetry(int childIndex, int copyIndex, Transformation tr)
{ 
  if (childIndex != copyIndex)
    {
      this->insertNode(this->getChild(childIndex)->clone(tr), copyIndex); 
      _symmetries.push_back(pair<int,int>(min(childIndex, copyIndex),max(childIndex, copyIndex)));
      this->updateGlobalSize();
    }
  else { cerr << "Error(HVSlicingNode::createSymmetry(int childIndex, int copyIndex)): Indexes cannot be the same." << endl; }

}

void HVSlicingNode::setSymmetry(int childIndex, int copyIndex)
{ 
  if (childIndex != copyIndex)
    {
      if (compareMap(this->getChild(childIndex)->getMapHW(), this->getChild(copyIndex)->getMapHW()) == true)
        { _symmetries.push_back(pair<int,int>(min(childIndex, copyIndex),max(childIndex, copyIndex))); }
      else
        { cerr << "Error(HVSlicingNode::setSymmetry(int childIndex, int copyIndex)): Child are not the same, symmetry cannot be set." << endl; }
    }
  else { cerr << "Error(HVSlicingNode::setSymmetry(int childIndex, int copyIndex)): Indexes cannot be the same." << endl; }
}

list<pair<int,int> > HVSlicingNode::getSymmetries() const { return _symmetries; }

int HVSlicingNode::getLeafNumber() const
{ 
  int cpt = 0;
  for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
    { cpt += (*it)->getLeafNumber(); }
  return cpt;  
}

void HVSlicingNode::print() const
{
  SlicingNode::print();
  if (_symmetries.empty() == false)
    {
      cout << "Symmetries: " << endl;
      for (list<pair<int,int> >::const_iterator it = _symmetries.begin(); it != _symmetries.end(); it++)
        { cout << "Children: " << (*it).first << " and " << (*it).second << endl;  }
      cout << endl;
    }
}

void HVSlicingNode::checkSymmetries()
{
  list<pair<int,int> > adjustedSymmetries = list<pair<int,int> >();
  for (list<pair<int,int> >::const_iterator it = _symmetries.begin(); it != _symmetries.end(); it++)
    { 
      if ((*it).first > (*it).second ){ adjustedSymmetries.push_back(pair<int,int >((*it).second,(*it).first)); } 
      else { adjustedSymmetries.push_back(pair<int,int >((*it).first,(*it).second)); } 
    }
  adjustedSymmetries.sort();
  
  bool next = false;
  list<pair<int,int> >::iterator it2 = adjustedSymmetries.begin();
  it2++;

  for (list<pair<int,int> >::iterator it = adjustedSymmetries.begin(); it != adjustedSymmetries.end(); it++)
    {
      it2 = it;
      it2++;
      while(next != true)
        {
          if ( (*it).second == (*it2).first ){ (*it2).first = (*it).first; }
          if ( (*it).second <  (*it2).first ){ next = true; }
          it2++;
          if ( it2 == adjustedSymmetries.end() ) { next = true; }
        }
      next = false;
    }
  _symmetries = adjustedSymmetries;
}

// class HSlicingNode
HSlicingNode* HSlicingNode::create(
                                   CenteringType c,
                                   float         toleranceH,
                                   float         toleranceW,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new HSlicingNode(Horizontal,c,toleranceH,toleranceW,x,y,w,h); }

HSlicingNode* HSlicingNode::clone(Transformation tr)
{
  HSlicingNode* node = HSlicingNode::create(
                                            this->getCenteringType(),
                                            this->getToleranceH(),
                                            this->getToleranceW(),
                                            0, 0,
                                            this->getWidth(),
                                            this->getHeight()
                                           );
  node->setMapHW(cloneMapHW(_mapHW));
  node->setPreset(_preset);
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (tr == MY){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
  return node;
}

HSlicingNode::HSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         toleranceH,
                           float         toleranceW,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,toleranceH,toleranceW,x,y,w,h){}
HSlicingNode::~HSlicingNode(){}

// class VSlicingNode
VSlicingNode* VSlicingNode::create(
                                   CenteringType c,
                                   float         toleranceH,
                                   float         toleranceW,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new VSlicingNode(Vertical,c,toleranceH,toleranceW,x,y,w,h); }

VSlicingNode* VSlicingNode::clone(Transformation tr)
{
  VSlicingNode* node = VSlicingNode::create(
                                            this->getCenteringType(),
                                            this->getToleranceH(),
                                            this->getToleranceW(),
                                            0, 0,
                                            this->getWidth(),
                                            this->getHeight()
                                           );
  node->setMapHW(cloneMapHW(_mapHW));
  node->setPreset(_preset);
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if (tr == MX){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
  return node;
}


VSlicingNode::VSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         toleranceH,
                           float         toleranceW,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,toleranceH,toleranceW,x,y,w,h){}
VSlicingNode::~VSlicingNode(){}

// class DSlicingNode
DSlicingNode* DSlicingNode::create(
                                   map<float,float>* mapHW, 
                                   CenteringType     c, 
                                   float             x, 
                                   float             y, 
                                   float             w, 
                                   float             h
                                  ){ return new DSlicingNode(DeviceNode,mapHW,c,x,y,w,h); }

DSlicingNode::DSlicingNode(
                           SlicingType       type, 
                           map<float,float>* mapHW, 
                           CenteringType     c,
                           float             x, 
                           float             y, 
                           float             w, 
                           float             h
                          ):SlicingNode(type,mapHW,c,x,y,w,h)
{
  if ((w == 0)&&(h == 0))
    {
      _h = _mapHW->begin()->first;
      _w = _mapHW->begin()->second;
    }
}
DSlicingNode::~DSlicingNode(){}

void DSlicingNode::place(float x, float y)
{
  _x = x;
  _y = y;
}

pair<float, float> DSlicingNode::setGlobalSize(float height, float width)
{
  if ( _preset != true ) { this->setPairH(height); }
  if ( (_h != 0)&&(_w != 0) ) { _preset = true; }
  return pair<float,float>(_h,_w);
}

float DSlicingNode::updateHeight    (){ return _h; }
float DSlicingNode::updateWidth     (){ return _w; }
void  DSlicingNode::updateGlobalSize(){} // just do nothing

DSlicingNode* DSlicingNode::clone(Transformation tr)
{
  DSlicingNode* node = DSlicingNode::create(
                                            cloneMapHW(this->getMapHW()),
                                            this->getCenteringType(),
                                            0, 0,
                                            this->getWidth(),
                                            this->getHeight()
                                           );
  node->setPreset(_preset);
  return node;
}

int DSlicingNode::getLeafNumber() const
{  return 1; }

// Error Message Methods
void DSlicingNode::createPushBackNode( SlicingType type, CenteringType c, float toleranceH, float toleranceW, float x, float y, float w, float h )
{ cerr << " Error(createPushBackNode(SlicingType type, CenteringType c, float toleranceH, toleranceW, float x, float y, float w, float h)): Device do not have child." << endl; }

void DSlicingNode::createPushBackDevice( map<float,float>* mapHW, CenteringType c, float x, float y, float w, float h )
{ cerr << " Error(createPushBackNode(map<float,float>* mapHW, CenteringType c, float x, float y, float w, float h)): Devices do not have child." << endl; }

void DSlicingNode::createPushBackRouting(float hw, float x, float y)
{ cerr << " Error(void DSlicingNode::createPushBackRouting(float hw, float x, float y)): Devices do not have child." << endl; }

int DSlicingNode::getNbChild() const
{
  cerr << " Error(int DSlicingNode::getNbChild()): Devices do not have child." << endl;
  return 0;
}

SlicingNode* DSlicingNode::getChild(int index) const
{
  cerr << " Error(SlicingNode* DSlicingNode::getChild(int index)): Devices do not have child." << endl;
  return NULL;
}

const vector<SlicingNode*>& DSlicingNode::getChildren() const
{
  cerr << " Error(vector<SlicingNode*> DSlicingNode::getChildren()): Devices do not have child." << endl;
  static vector<SlicingNode*> dummyVectorSlicingNode;
  return dummyVectorSlicingNode;
}

void DSlicingNode::printChildren()
{ cerr << " Error(void DSlicingNode::printChildren()): Devices do not have child." << endl; }

void DSlicingNode::insertNode(SlicingNode* node, int index)
{ cerr << " Error(void DSlicingNode::insertNode(SlicingNode* node, int index)): Devices do not have child." << endl; }

void DSlicingNode::pushBackNode(SlicingNode* node)
{ cerr << " Error(void DSlicingNode::pushBackNode(SlicingNode* node)): Devices do not have child." << endl; }

void DSlicingNode::pushFrontNode(SlicingNode* node)
{ cerr << " Error(void DSlicingNode::pushFrontNode(SlicingNode* node)): Devices do not have child." << endl; }

void DSlicingNode::removeAllNodes()
{ cerr << " Error(void DSlicingNode::removeAllNodes()): Devices do not have child." << endl; }

void DSlicingNode::removeNode(SlicingNode* node)
{ cerr << " Error(void DSlicingNode::removeNode(SlicingNode* node)): Devices do not have child." << endl; }

void DSlicingNode::setToleranceH(float tolerance)
{ cerr << " Error(void DSlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; }

void DSlicingNode::setAllToleranceH(float tolerance)
{ cerr << " Error(void DSlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; }

float DSlicingNode::getToleranceH() const
{
 cerr << " Error(DSlicingNode::getToleranceH()): Devices do not have tolerance parameter." << endl;
 return 0;
}

void DSlicingNode::setToleranceW(float tolerance)
{ cerr << " Error(void DSlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; }

void DSlicingNode::setAllToleranceW(float tolerance)
{ cerr << " Error(void DSlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; }

float DSlicingNode::getToleranceW() const
{
 cerr << " Error(DSlicingNode::getToleranceW()): Devices do not have tolerance parameter." << endl;
 return 0;
}

bool DSlicingNode::emptyChildrenMap() const
{
 cerr << " Error(DSlicingNode::emptyChildrenMap()): Devices do not have child." << endl;
 return true;
} 

void DSlicingNode::createSymmetry(int childIndex, int copyIndex, Transformation tr)
{ cerr << "DSlicingNode::createSymmetry(int childIndex, int copyIndex, Transformation tr = None) : RoutingNodes do not have symmetries." << endl; }

void DSlicingNode::setSymmetry(int childIndex, int copyIndex)
{ cerr << "RHVSlicingNode::setSymmetry(int childIndex, int copyIndex) : RoutingNodes do not have symmetries." << endl; }

list<pair<int,int> > DSlicingNode::getSymmetries() const
{ 
  cerr << "RHVSlicingNode::getSymmetries() const : RoutingNodes do not have symmetries." << endl; 
  return list<pair<int,int> >();
}

void DSlicingNode::checkSymmetries() 
{ cerr << "RHVSlicingNode::checkSymmetries() const : RoutingNodes do not have symmetries." << endl; }

// class RHVSlicingNode
RHVSlicingNode::RHVSlicingNode(
                           float             x, 
                           float             y, 
                           float             w, 
                           float             h
                          ):SlicingNode(RoutingNode,NULL,LB,x,y,w,h)
{ _preset = true; }
RHVSlicingNode::~RHVSlicingNode(){}

void RHVSlicingNode::place(float x, float y)
{
  _x = x;
  _y = y;
}

pair<float, float> RHVSlicingNode::setGlobalSize(float height, float width){ return pair<float, float> (_h,_w); }

void RHVSlicingNode::updateGlobalSize(){} // just do nothing

int RHVSlicingNode::getLeafNumber() const
{ return 1; }

// Error Message Methods
CenteringType RHVSlicingNode::getCenteringType () const
{
  cerr << " Error(getCenteringType () const): RoutingNodes do not have centering type." << endl;
  return LB;
}

map<float,float>* RHVSlicingNode::getMapHW () const
{
  cerr << " Error(getMapHW () const): RoutingNodes do not have mapHW." << endl;
  return NULL;
}

void RHVSlicingNode::setPreset(bool preset)
{ cerr << " Error(setPreset(bool preset)): RoutingNodes preset is always true." << endl; }

pair<float,float> RHVSlicingNode::getPairH (float h) const
{
  cerr << " Error(getPairH (float h) const): RoutingNodes do not have mapHW." << endl;
  return pair<float, float> (_h,_w);
}

pair<float,float> RHVSlicingNode::getPairW (float w) const
{
  cerr << " Error(getPairW (float w) const): RoutingNodes do not have mapHW." << endl;
  return pair<float, float> (_h,_w);
}

void RHVSlicingNode::setPairH (float h)
{ cerr << " Error(setPairH (float h)): RoutingNodes do not have mapHW." << endl; }

void RHVSlicingNode::setPairW (float w)  
{ cerr << " Error(setPairW (float w)): RoutingNodes do not have mapHW." << endl; }   

void RHVSlicingNode::createPushBackNode( SlicingType type, CenteringType c, float toleranceH, float toleranceW, float x, float y, float w, float h )
{
  cerr << " Error(createPushBackNode(SlicingType type, CenteringType c, float toleranceH, toleranceW, float x, float y, float w, float h)): RoutingNodes do not have child." << endl;
}

void RHVSlicingNode::createPushBackDevice( map<float,float>* mapHW, CenteringType c, float x, float y, float w, float h )
{ cerr << " Error(createPushBackNode(map<float,float>* mapHW, CenteringType c, float x, float y, float w, float h)): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::createPushBackRouting(float hw, float x, float y)
{ cerr << " Error(void RHVSlicingNode::createPushBackRouting(float hw, float x, float y): RoutingNodes do not have child." << endl; }

int RHVSlicingNode::getNbChild() const
{
  cerr << " Error(int RHVSlicingNode::getNbChild()): RoutingNodes do not have child." << endl;
  return 0;
}

SlicingNode* RHVSlicingNode::getChild(int index) const
{
  cerr << " Error(SlicingNode* RHVSlicingNode::getChild(int index)): RoutingNodes do not have child." << endl;
  return NULL;
}

const vector<SlicingNode*>& RHVSlicingNode::getChildren() const
{
  cerr << " Error(vector<SlicingNode*> RHVSlicingNode::getChildren()): RoutingNodes do not have child." << endl;
  static vector<SlicingNode*> dummyVectorSlicingNode;
  return dummyVectorSlicingNode;
}

void RHVSlicingNode::printChildren()
{ cerr << " Error(void RHVSlicingNode::printChildren()): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::insertNode(SlicingNode* node, int index)
{ cerr << " Error(void RHVSlicingNode::insertNode(SlicingNode* node, int index)): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::pushBackNode(SlicingNode* node)
{ cerr << " Error(void RHVSlicingNode::pushBackNode(SlicingNode* node)): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::pushFrontNode(SlicingNode* node)
{ cerr << " Error(void RHVSlicingNode::pushFrontNode(SlicingNode* node)): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::removeAllNodes()
{ cerr << " Error(void RHVSlicingNode::removeAllNodes()): RoutingNodes do not have child." << endl; }

void RHVSlicingNode::removeNode(SlicingNode* node)
{
 cerr << " Error(void RHVSlicingNode::removeNode(SlicingNode* node)): RoutingNodes do not have child." << endl;
}

float RHVSlicingNode::updateHeight(){ return _h; }

float RHVSlicingNode::updateWidth(){ return _w; }

void RHVSlicingNode::setToleranceH(float tolerance)
{ cerr << " Error(void RHVSlicingNode::setToleranceH(float tolerance)): RoutingNodes do not have tolerance parameter." << endl; }

void RHVSlicingNode::setAllToleranceH(float tolerance)
{ cerr << " Error(void RHVSlicingNode::setToleranceH(float tolerance)): RoutingNodes do not have tolerance parameter." << endl; }

float RHVSlicingNode::getToleranceH() const
{
 cerr << " Error(RHVSlicingNode::getToleranceH()): RoutingNode do not have tolerance parameter." << endl;
 return 0;
}

void RHVSlicingNode::setToleranceW(float tolerance)
{ cerr << " Error(void RHVSlicingNode::setToleranceW(float tolerance)): RoutingNodes do not have tolerance parameter." << endl; }

void RHVSlicingNode::setAllToleranceW(float tolerance)
{ cerr << " Error(void RHVSlicingNode::setToleranceW(float tolerance)): RoutingNodes do not have tolerance parameter." << endl; }

float RHVSlicingNode::getToleranceW() const
{
 cerr << " Error(RHVSlicingNode::getToleranceW()): RoutingNodes do not have tolerance parameter." << endl;
 return 0;
}

bool RHVSlicingNode::emptyChildrenMap() const
{
 cerr << " Error(RHVSlicingNode::emptyChildrenMap()): RoutingNodes do not have child." << endl;
 return true;
} 

void RHVSlicingNode::createSymmetry(int childIndex, int copyIndex, Transformation tr)
{ cerr << "Error(RHVSlicingNode::createSymmetry(int childIndex, int copyIndex, Transformation tr = None)) : RoutingNodes do not have symmetries." << endl; }

void RHVSlicingNode::setSymmetry(int childIndex, int copyIndex)
{ cerr << "Error(RHVSlicingNode::setSymmetry(int childIndex, int copyIndex)) : RoutingNodes do not have symmetries." << endl; }

list<pair<int,int> > RHVSlicingNode::getSymmetries() const
{ 
  cerr << "Error(RHVSlicingNode::getSymmetries() const) : RoutingNodes do not have symmetries.)" << endl; 
  return list<pair<int,int> >();
}

void RHVSlicingNode::checkSymmetries() 
{ cerr << "Error(RHVSlicingNode::checkSymmetries()) : RoutingNodes do not have symmetries." << endl; }

// class RHSlicingNode
RHSlicingNode::RHSlicingNode( float h, float x, float y ):RHVSlicingNode(x,y,0,h){}

RHSlicingNode* RHSlicingNode::clone(Transformation tr)
{
  RHSlicingNode* node = RHSlicingNode::create(this->getHeight(), 0, 0);
  return node; 
}

RHSlicingNode::~RHSlicingNode(){};

// Error Methods
RHSlicingNode* RHSlicingNode::create( float h, float x, float y ){ return new RHSlicingNode(h,x,y); }

void RHSlicingNode::setWidth( float w )
{ cerr << " Error(RHVSlicingNode::setHeight( float w )): RoutingNodes do not have width." << endl; }

// class RVSlicingNode
RVSlicingNode::RVSlicingNode( float w, float x, float y ):RHVSlicingNode(x,y,w,0){}

RVSlicingNode* RVSlicingNode::clone(Transformation tr)
{
  RVSlicingNode* node = RVSlicingNode::create(this->getWidth(), 0, 0);
  return node; 
}

RVSlicingNode::~RVSlicingNode(){};

// Error Methods
RVSlicingNode* RVSlicingNode::create( float w, float x, float y ){ return new RVSlicingNode(w,x,y); }

void RVSlicingNode::setHeight( float h )
{  cerr << " Error(RHVSlicingNode::setHeight( float h )): RoutingNodes do not have height." << endl; }
