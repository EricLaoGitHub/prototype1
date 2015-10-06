#include "slicingNode.h"

using namespace std;

// class Node
SlicingNode::SlicingNode(
                         SlicingType       type, 
                         map<float,float>* mapHW,
                         CenteringType     c, 
                         float             x, 
                         float             y, 
                         float             w, 
                         float             h
                        ):_type(type),
                          _c(c),
                          _x(x),
                          _y(y),
                          _w(w),
                          _h(h)
{ 
  if (mapHW == NULL){ _mapHW = new map <float,float>(); } 
  else              { _mapHW = mapHW; }
} 
SlicingNode::~SlicingNode(){}

SlicingType       SlicingNode::getType         ()        const { return _type; }
float             SlicingNode::getWidth        ()        const { return _w; }
float             SlicingNode::getHeight       ()        const { return _h; }
float             SlicingNode::getX            ()        const { return _x; }
float             SlicingNode::getY            ()        const { return _y; }
CenteringType     SlicingNode::getCenteringType()        const { return _c; }
map<float,float>* SlicingNode::getmapHW        ()        const { return _mapHW; }

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

void SlicingNode::setWidth        (float w)        { _w = w; }
void SlicingNode::setHeight       (float h)        { _h = h; }
void SlicingNode::setX            (float x)        { _x = x; }
void SlicingNode::setY            (float y)        { _y = y; }
void SlicingNode::setCenteringType(CenteringType c){ _c = c; }

void SlicingNode::print() const
{
  cout << "- Print from Slicing Node- " << endl;
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
  else { cout << "SlicingType: Unknown"    << endl; }

  cout << "Height = "  << _h << endl;
  cout << "Width  = "  << _w << endl;
  cout << "X      = "  << _x << endl;
  cout << "Y      = "  << _y << endl;
  cout << endl;

  cout << "MapHW:" << endl;
  for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++){ cout << "H = " << itHW->first << ", W = " << itHW->second << endl;}
  cout << endl;
}


// class HVSlicingNode
HVSlicingNode::HVSlicingNode(
                             SlicingType   type,
                             CenteringType c, 
                             float         tolerance, 
                             float         x, 
                             float         y, 
                             float         w, 
                             float         h
                            ):SlicingNode(type,NULL,c,x,y,w,h),
                              _tolerance(tolerance){}
HVSlicingNode::~HVSlicingNode(){}

void HVSlicingNode::createPushBackNode(
                                       SlicingType   type, 
                                       CenteringType c,
                                       float         tolerance,
                                       float         x, 
                                       float         y, 
                                       float         w, 
                                       float         h
                                      ) 
{ 
  if (type == Horizontal)
    {
      this->pushBackNode(HSlicingNode::create(c,tolerance,x,y,w,h));
      
    }
  else if (type == Vertical)
    {
      this->pushBackNode(VSlicingNode::create(c,tolerance,x,y,w,h));
    }
  else
    {
      cerr << " Error(void HSlicingNode::createPushBack(SlicingType type, CenteringType c, float x, float y, float w, float h)): Unknown or Device type." << endl;
    }
}
void HVSlicingNode::createPushBackDevice(
                                         map<float,float>* mapHW,  
                                         CenteringType     c,
                                         float             x, 
                                         float             y, 
                                         float             w, 
                                         float             h
                                        )
{ 
  this->pushBackNode(DSlicingNode::create(mapHW,c,x,y,w,h)); }


int                         HVSlicingNode::getNbChild()        const { return _children.size(); }
SlicingNode*                HVSlicingNode::getChild(int index) const { return _children[index]; }
const vector<SlicingNode*>& HVSlicingNode::getChildren()       const { return _children; }

void HVSlicingNode::printChildren()
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      if ((*it)->getType() == DeviceNode){ (*it)->print(); }
      else
        {
          (*it)->print();
          (*it)->printChildren();
        }
    }
}

void HVSlicingNode::addNode       (SlicingNode* node, int index){ _children[index]=node; }
void HVSlicingNode::pushBackNode  (SlicingNode* node)           { _children.push_back(node); }
void HVSlicingNode::removeAllNodes()                            { _children.clear(); }

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
  if (this->getType() == DeviceNode){ height = _h; }
  else if (this->getType() == Horizontal)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        {
          height += (*it)->updateHeight();
        }
    }  
  else if (this->getType() == Vertical)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        {
          if (height < (*it)->updateHeight()){ height = (*it)->getHeight(); }
        }
    }
  else
    {  cerr << " Error(HVSlicingNode::updateHeight()): Unknown type in SlicingTree." << endl; }
  _h = height;
  return height;
}

float HVSlicingNode::updateWidth()
{
  float width = 0;
  if (this->getType() == DeviceNode){ width = _w; }
  else if (this->getType() == Vertical)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        {
          width += (*it)->updateWidth();
        }
    }  
  else if (this->getType() == Horizontal)
    {
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
        {
          if (width < (*it)->updateWidth()){ width = (*it)->getWidth(); }
        }
    }
  else
    {  cerr << " Error(HVSlicingNode::updateWidth()): Unknown type in SlicingTree." << endl; }
  _w = width;
  return width;
}

CenteringType HVSlicingNode::getCenteringType() const{ return _c; }

void HVSlicingNode::place(float x, float y)
{
  updateHeight();
  updateWidth();
  this->_place(x,y);
}
void HVSlicingNode::_place(float x, float y)
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

          if      ((*it)->getCenteringType() == LB)     { (*it)->_place(xref                                 , yref); }
          else if ((*it)->getCenteringType() == Middle) { (*it)->_place(xref + (_w/2) - ((*it)->getWidth()/2), yref); }
          else if ((*it)->getCenteringType() == RT)     { (*it)->_place(xref + _w     - (*it)->getWidth()    , yref); }
          else { cerr << " Error(place(float x, float y)): Unknown CenteringType in SlicingTree." << endl; }

          xref =  x;
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

          if      ((*it)->getCenteringType() == LB)     { (*it)->_place(xref, yref); }
          else if ((*it)->getCenteringType() == Middle) { (*it)->_place(xref, yref + (_h/2) - ((*it)->getHeight()/2)); }
          else if ((*it)->getCenteringType() == RT)     { (*it)->_place(xref, yref + _h     - (*it)->getHeight()); }
          else { cerr << " Error(place(float x, float y)): Unknown CenteringType in SlicingTree." << endl; }

          xref += (*it)->getWidth();
          yref = y;
        }
    }
  else { cerr << " Error(place(float x, float y)): Unknown Slicingtype in SlicingTree." << endl; }
}

void  HVSlicingNode::setTolerance(float tolerance){ _tolerance = tolerance; }
void  HVSlicingNode::setAllTolerance(float tolerance)
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      (*it)->setAllTolerance(tolerance);
    }
  _tolerance = tolerance; 
}
float HVSlicingNode::getTolerance() const         { return _tolerance; }

void HVSlicingNode::updateGlobalSize()
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      (*it)->updateGlobalSize();
    }

  if (this->getNbChild() == 1)
    {
      _mapHW = (*_children.begin())->getmapHW();
    }
  else if (this->emptyChildren() != true)
    {        
      if (this->getType() == Vertical)
        {
        // Clear the content of the map
          _mapHW->clear(); 

        // childrenHW contains the map from each children.
          vector<map<float,float>*> childrenmapHW;
          for (vector<SlicingNode*>::iterator itSN = _children.begin(); itSN != _children.end(); itSN++)
            {
              childrenmapHW.push_back( (*itSN)->getmapHW() );
            }
        // childrenpair represents 1 state of the combinations
          vector< pair<float,float> > childrenpair;
          for (vector< map<float,float>* >::iterator it = childrenmapHW.begin(); it != childrenmapHW.end(); it++)
            {
              childrenpair.push_back(pair<float,float>((*it)->begin()->first,(*it)->begin()->second));
            }
          
          int   index = 0; // index used to modify childrenpair content
          float hmin  = (*childrenmapHW.begin())->upper_bound(index)->first; // min height from the current combinations
          float hmax  = (*childrenmapHW.begin())->upper_bound(index)->first; // max height from the current combinations
          
          list< pair<float,float> >             currentHs  = list< pair<float,float> >(); // heights from the current combination
          vector <int>                          modulos    = vector<int>();               // vectors of the modulos
          int                                   modulo     = 1;                           // to calculate modulos
          int                                   counter    = 0;                           
          int                                   endCounter = 1;
          float                                 currentW   = 0;                           // total width of the current combination
          vector< pair<float,float> >::iterator itpair     = childrenpair.begin();        // iterator to go through childrenpair

        // Set the modulos
          modulos.push_back(0);
          for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
            {
              if (itmap != childrenmapHW.begin()){ modulos.push_back(modulo); }
              modulo *= (*itmap)->size();
              endCounter *= (*itmap)->size();
            }

          while( counter != endCounter )
            {
            //cout << "----------- Start -----------" << endl;
            //cout << "counter = " << counter << endl;

            // Need to be reset at each loop
              index     = 0;
              itpair    = childrenpair.begin();
              currentHs = list< pair<float,float> >();
              currentW  = 0;

            /* We go through all the possible combinations (childrenmap). childrenpair represent 1 combinations.
               For each combinations, we find the max height and its corresponding width.
               Once found, we check if it's already in the map, if no, we add this pair
               Otherwise we check if the pair <max heigh, width> has a higher width than the previous one, if yes, we add it.
             */

              for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
                {
                /*cout << "Element: " << index << endl;
                  cout << "h = " << (*itpair).first << endl;
                  cout << "w = " << (*itpair).second << endl;
                */

                  currentHs.push_back(pair<float,float>((*itpair).first,(*itpair).second));
                  currentW += (*itpair).second;
                  if (itmap == childrenmapHW.begin())
                    {
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        {
                          childrenpair[index] = pair<float,float>(
                                                                  (*itmap)->upper_bound((*itpair).first)->first,
                                                                  (*itmap)->upper_bound((*itpair).first)->second
                                                                 );
                        }
                      else
                        {
                          childrenpair[index] = pair<float,float>(
                                                                  (*itmap)->begin()->first,
                                                                  (*itmap)->begin()->second
                                                                 );
                        }
                    } 
                  else
                    {
                      if (( counter%modulos[index] == modulos[index]-1 ) && ( counter != 0 ))
                        {
                          if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                            {
                              childrenpair[index] = pair<float,float>(
                                                                      (*itmap)->upper_bound((*itpair).first)->first,
                                                                      (*itmap)->upper_bound((*itpair).first)->second
                                                                     );
                            }
                          else
                            {
                              childrenpair[index] = pair<float,float>(
                                                                      (*itmap)->begin()->first,
                                                                      (*itmap)->begin()->second
                                                                     );
                                
                            }
                        }
                    }

                  index++;
                  itpair++;
                }
              counter++;
              currentHs.sort();
              hmin = currentHs.front().first;
              hmax = currentHs.back().first;

            /*cout << "----------- Result -----------" << endl;
              cout << "hmax = " << hmax << endl;
              cout << "hmin = " << hmin << endl;
            */

              if ((hmax-hmin) <= _tolerance)
                {
                //cout << "Add-or-not" << endl;

                  if ( _mapHW->find(currentHs.back().first) != _mapHW->end() )
                    {
                      if ( (*_mapHW->find(currentHs.back().first)).second < currentW )
                        { 
                        /*cout << "We add a new pair" << endl;
                          cout << "Previous pair: h = " <<(*_mapHW->find(currentHs.back().first)).first << ", w = " << (*_mapHW->find(currentHs.back().first)).second << endl;
                          cout << "New pair: h = " << currentHs.back().first << ", w = " << currentW << endl;
                        */
                          _mapHW->insert(pair<float,float> ( currentHs.back().first, currentW) ); 
                        }
                    }
                  else 
                    { 
                    //cout << "New pair: h = " << currentHs.back().first << ", w = " << currentW << endl;
                      _mapHW->insert(pair<float,float> ( currentHs.back().first, currentW) ); 
                    }
                }
            }
        }
      else if (this->getType() == Horizontal)
        {
        // Similar to Vertical type but instead, we pay attention to the width instead of the height

          _mapHW->clear(); 

          vector<map<float,float>*> childrenmapHW;
          for (vector<SlicingNode*>::iterator itSN = _children.begin(); itSN != _children.end(); itSN++)
            {
              childrenmapHW.push_back( (*itSN)->getmapHW() );
            }
          
          vector< pair<float,float> > childrenpair;
          for (vector< map<float,float>* >::iterator it = childrenmapHW.begin(); it != childrenmapHW.end(); it++)
            {
              childrenpair.push_back(pair<float,float>((*it)->begin()->first,(*it)->begin()->second));
            }
         
          int   index = 0;
          float wmin  = (*childrenmapHW.begin())->upper_bound(index)->second; 
          float wmax  = (*childrenmapHW.begin())->upper_bound(index)->second;
          
          list< pair<float,float> >             currentWs  = list< pair<float,float> >();
          vector <int>                          modulos    = vector<int>();
          int                                   modulo     = 1;
          int                                   counter    = 0;
          int                                   endCounter = 1;
          float                                 currentH   = 0;
          vector< pair<float,float> >::iterator itpair     = childrenpair.begin();

          modulos.push_back(0);
          for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
            {
              if (itmap != childrenmapHW.begin()){ modulos.push_back(modulo);}
              modulo *= (*itmap)->size();
              endCounter *= (*itmap)->size();
            }

          while( counter != endCounter )
            {
            //cout << "----------- Start -----------" << endl;
            //cout << "counter = " << counter << endl;

              index     = 0;
              itpair    = childrenpair.begin();
              currentWs = list< pair<float,float> >();
              currentH  = 0;

              for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
                {
                /*cout << "Element: " << index << endl;
                  cout << "h = " << (*itpair).first << endl;
                  cout << "w = " << (*itpair).second << endl;
                */

                  currentWs.push_back(pair<float,float>((*itpair).second,(*itpair).first));
                  currentH += (*itpair).first;
                  if (itmap == childrenmapHW.begin())
                    {
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        {
                          childrenpair[index] = pair<float,float>(
                                                                  (*itmap)->upper_bound((*itpair).first)->first,
                                                                  (*itmap)->upper_bound((*itpair).first)->second
                                                                 );
                        }
                      else
                        {
                          childrenpair[index] = pair<float,float>(
                                                                  (*itmap)->begin()->first,
                                                                  (*itmap)->begin()->second
                                                                 );
                        }
                    } 
                  else
                    {
                      if (( counter%modulos[index] == modulos[index]-1 ) && ( counter != 0 ))
                        {
                          if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                            {
                              childrenpair[index] = pair<float,float>(
                                                                      (*itmap)->upper_bound((*itpair).first)->first,
                                                                      (*itmap)->upper_bound((*itpair).first)->second
                                                                     );
                            }
                          else
                            {
                              childrenpair[index] = pair<float,float>(
                                                                      (*itmap)->begin()->first,
                                                                      (*itmap)->begin()->second
                                                                     );
                                
                            }
                        }
                    }
                  index++;
                  itpair++;
                }
              counter++;
              currentWs.sort();
              wmin = currentWs.front().first;
              wmax = currentWs.back().first;

            /*cout << "----------- Result -----------" << endl;
              cout << "wmax = " << wmax << endl;
              cout << "wmin = " << wmin << endl;
            */

              if ((wmax-wmin) <= _tolerance)
                {
                //cout << "Add-or-not" << endl;

                  if ( _mapHW->find(currentH) != _mapHW->end() )
                    {
                      if ( (*_mapHW->find(currentH)).second < currentWs.back().second )
                        {  
                        /*cout << "We add a new pair" << endl;
                          cout << "Previous pair: h = " << currentH << ", w = " << (*_mapHW->find(currentH)).second << endl;
                          cout << "New pair: h = " <<  currentH << ", w = " <<  currentWs.back().second << endl;
                        */
                          _mapHW->insert(pair<float,float> ( currentH, currentWs.back().second) ); 
                        }
                    }
                  else 
                    { 
                    //cout << "New pair: h = " <<  currentH << ", w = " <<  currentWs.back().second << endl;
                      
                      _mapHW->insert(pair<float,float> ( currentH, currentWs.back().second) ); 
                    }
                }
            }
        }
    }
}

bool HVSlicingNode::emptyChildren() const
{
  bool flag = false;
  for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
    {
      if ((*it)->getmapHW()->empty() == true) {flag = true;}
    }
  return flag;
}

// Error Message Methods

// class HSlicingNode
HSlicingNode* HSlicingNode::create(
                                   CenteringType c,
                                   float         tolerance,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new HSlicingNode(Horizontal,c,tolerance,x,y,w,h); }

HSlicingNode::HSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         tolerance,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,tolerance,x,y,w,h){}
HSlicingNode::~HSlicingNode(){}

// class VSlicingNode
VSlicingNode* VSlicingNode::create(
                                   CenteringType c,
                                   float         tolerance,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new VSlicingNode(Vertical,c,tolerance,x,y,w,h); }

VSlicingNode::VSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         tolerance,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,tolerance,x,y,w,h){}
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
  this->_place(x,y);
}

void DSlicingNode::_place(float x, float y)
{
  _x = x;
  _y = y;
}

// Error Message Methods
void DSlicingNode::createPushBackNode(
                                      SlicingType   type, 
                                      CenteringType c, 
                                      float         tolerance,
                                      float         x, 
                                      float         y, 
                                      float         w, 
                                      float         h
                                     )
{
  cerr << " Error(createPushBackNode(SlicingType type, CenteringType c, float tolerance, float x, float y, float w, float h)): Device do not have child." << endl;
}

void DSlicingNode::createPushBackDevice(
                                        map<float,float>* mapHW, 
                                        CenteringType     c, 
                                        float             x, 
                                        float             y, 
                                        float             w, 
                                        float             h
                                       )
{
  cerr << " Error(createPushBackNode(map<float,float>* mapHW, CenteringType c, float x, float y, float w, float h)): Device do not have child." << endl;
}

int DSlicingNode::getNbChild() const
{
  cerr << " Error(int DSlicingNode::getNbChild()): Device do not have child." << endl;
  return 0;
}

SlicingNode* DSlicingNode::getChild(int index) const
{
  cerr << " Error(SlicingNode* DSlicingNode::getChild(int index)): Device do not have child." << endl;
  return NULL;
}

const vector<SlicingNode*>& DSlicingNode::getChildren() const
{
  cerr << " Error(vector<SlicingNode*> DSlicingNode::getChildren()): Device do not have child." << endl;
  static vector<SlicingNode*> dummyVectorSlicingNode;
  return dummyVectorSlicingNode;
}

void DSlicingNode::printChildren()
{
  cerr << " Error(void DSlicingNode::printChildren()): Device do not have child." << endl;
}
void DSlicingNode::addNode(SlicingNode* node, int index)
{
  cerr << " Error(void DSlicingNode::addNode(SlicingNode* node, int index)): Device do not have child." << endl;
}

void DSlicingNode::pushBackNode(SlicingNode* node)
{
  cerr << " Error(void DSlicingNode::pushBackNode(SlicingNode* node)): Device do not have child." << endl;
}

void DSlicingNode::removeAllNodes()
{
  cerr << " Error(void DSlicingNode::removeAllNodes()): Device do not have child." << endl;
}

void DSlicingNode::removeNode(SlicingNode* node)
{
 cerr << " Error(void DSlicingNode::removeNode(SlicingNode* node)): Device do not have child." << endl;
}

float DSlicingNode::updateHeight(){ return _h; }

float DSlicingNode::updateWidth(){ return _w; }

void DSlicingNode::setTolerance(float tolerance)
{
 cerr << " Error(void DSlicingNode::setTolerance(float tolerance)): Device do not have tolerance parameter." << endl;
}

void DSlicingNode::setAllTolerance(float tolerance)
{
 cerr << " Error(void DSlicingNode::setTolerance(float tolerance)): Device do not have tolerance parameter." << endl;
}

float DSlicingNode::getTolerance() const
{
 cerr << " Error(DSlicingNode::getTolerance()): Device do not have tolerance parameter." << endl;
 return 0;
}

void DSlicingNode::updateGlobalSize(){} // just do nothing

bool DSlicingNode::emptyChildren() const
{
 cerr << " Error(DSlicingNode::emptyChildren()): Device do not have child." << endl;
return true;
} 
