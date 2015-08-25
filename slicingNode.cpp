#include "slicingNode.h"

using namespace std;

// class Node
SlicingNode::SlicingNode(
                         SlicingType type, 
                         CenteringType c, 
                         float x, 
                         float y, 
                         float w, 
                         float h
                        ):_type(type),
                          _c(c),
                          _x(x),
                          _y(y),
                          _w(w),
                          _h(h){} 
SlicingNode::~SlicingNode(){}

SlicingType   SlicingNode::getType         () const { return _type; }
float         SlicingNode::getWidth        () const { return _w; }
float         SlicingNode::getHeight       () const { return _h; }
float         SlicingNode::getX            () const { return _x; }
float         SlicingNode::getY            () const { return _y; }
CenteringType SlicingNode::getCenteringType() const { return _c; }

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
}


// class HVSlicingNode
HVSlicingNode::HVSlicingNode(
                             SlicingType   type,
                             CenteringType c, 
                             float         x, 
                             float         y, 
                             float         w, 
                             float         h
                            ):SlicingNode(type,c,x,y,w,h){}
HVSlicingNode::~HVSlicingNode(){}

void HVSlicingNode::createPushBackNode(
                                       SlicingType   type, 
                                       CenteringType c,
                                       float         x, 
                                       float         y, 
                                       float         w, 
                                       float         h
                                      ) 
{ 
  if (type == Horizontal)
    {
      this->pushBackNode(HSlicingNode::create(c,x,y,w,h));
      
    }
  else if (type == Vertical)
    {
      this->pushBackNode(VSlicingNode::create(c,x,y,w,h));
    }
  else
    {
      cerr << " Error(void HSlicingNode::createPushBack(SlicingType type, CenteringType c, float x, float y, float w, float h)): Unknown or Device type." << endl;
    }
}
void HVSlicingNode::createPushBackDevice(
                                         map<float,float>* mapH, 
                                         map<float,float>* mapW,  
                                         CenteringType     c,
                                         float             x, 
                                         float             y, 
                                         float             w, 
                                         float             h
                                        )
{ this->pushBackNode(DSlicingNode::create(mapH,mapW,c,x,y,w,h)); }


int                         HVSlicingNode::getNbChild()        const { return _children.size(); }
SlicingNode*                HVSlicingNode::getChild(int index) const { return _children[index]; }
const vector<SlicingNode*>& HVSlicingNode::getChildren()       const { return _children; }

void HVSlicingNode::print() const {SlicingNode::print();}
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

// Error Message Methods

// class HSlicingNode
HSlicingNode* HSlicingNode::create(
                                   CenteringType c,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new HSlicingNode(Horizontal,c,x,y,w,h); }

HSlicingNode::HSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,x,y,w,h){}
HSlicingNode::~HSlicingNode(){}

// class VSlicingNode
VSlicingNode* VSlicingNode::create(
                                   CenteringType c,
                                   float         x, 
                                   float         y, 
                                   float         w, 
                                   float         h
                                  ){ return new VSlicingNode(Vertical,c,x,y,w,h); }

VSlicingNode::VSlicingNode(
                           SlicingType   type, 
                           CenteringType c,
                           float         x, 
                           float         y, 
                           float         w, 
                           float         h
                          ):HVSlicingNode(type,c,x,y,w,h){}
VSlicingNode::~VSlicingNode(){}

// class DSlicingNode
DSlicingNode* DSlicingNode::create(
                                   map<float,float>* mapH, 
                                   map<float,float>* mapW, 
                                   CenteringType     c, 
                                   float             x, 
                                   float             y, 
                                   float             w, 
                                   float             h
                                  ){ return new DSlicingNode(DeviceNode,mapH,mapW,c,x,y,w,h); }

DSlicingNode::DSlicingNode(
                           SlicingType       type, 
                           map<float,float>* mapH, 
                           map<float,float>* mapW, 
                           CenteringType     c,
                           float             x, 
                           float             y, 
                           float             w, 
                           float             h
                          ):SlicingNode(type,c,x,y,w,h),
                            _mapH(mapH),
                            _mapW(mapW)
{
  if ((w == 0)&&(h == 0))
    {
      _h = _mapH->begin()->first;
      _w = _mapH->begin()->second;
    }
}
DSlicingNode::~DSlicingNode(){}

void DSlicingNode::print() const
{
  SlicingNode::print();

  map <float,float>::const_iterator itL = _mapH->begin();
  cout << "MapH:" << endl;
  for (; itL != _mapH->end(); itL++){ cout << "H = " << itL->first << ", W = " << itL->second << endl;}
  cout << endl;
  cout << endl;
}

void DSlicingNode::place(float x, float y)
{
  _x = x;
  _y = y;
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
                                      float         x, 
                                      float         y, 
                                      float         w, 
                                      float         h
                                     )
{
  cerr << " Error(createPushBackNode(SlicingType type, CenteringType c, float x, float y, float w, float h)): Device do not have child." << endl;
}

void DSlicingNode::createPushBackDevice(
                                        map<float,float>* mapH, 
                                        map<float,float>* mapW,
                                        CenteringType     c, 
                                        float             x, 
                                        float             y, 
                                        float             w, 
                                        float             h
                                       )
{
  cerr << " Error(createPushBackNode(map<float,float>* mapH, map<float,float>* mapW, CenteringType c, float x, float y, float w, float h)): Device do not have child." << endl;
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


