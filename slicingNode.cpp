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

void HVSlicingNode::updateBandSize()
{
  for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
      (*it)->updateBandSize();
    }

  if (this->getNbChild() == 1)
    {
      _mapHW = (*_children.begin())->getmapHW();
    }
  else if (this->emptyChildren() != true)
    {
      if (this->getType() == Vertical)
        {
        //cout << "1) On commence le test" << endl;
        // childrenmapHW: On recupère les maps de chacun des fils dans un vector 
          vector<map<float,float>*> childrenmapHW;
          for (vector<SlicingNode*>::iterator itSN = _children.begin(); itSN != _children.end(); itSN++)
            {
              childrenmapHW.push_back( (*itSN)->getmapHW() );
            }
          
        //cout << "2) On a recupéré les maps " << endl;
          
          vector< pair<float,float> > childrenpair;
          for (vector< map<float,float>* >::iterator it = childrenmapHW.begin(); it != childrenmapHW.end(); it++)
            {
              childrenpair.push_back(pair<float,float>((*it)->begin()->first,(*it)->begin()->second));
            }
          
        //cout << "3) On a recupéré les premieres paires de chaque map " << endl;
          
          bool  incrementation = 1;
          int   index     = 0;
          int   indexNext = 0;
          pair<float,float> nextPair = pair<float,float>((*childrenmapHW.begin())->upper_bound(index)->first,(*childrenmapHW.begin())->upper_bound(index)->second);
          float nextPairMin          = nextPair.first;
          float hmin                 = (*childrenmapHW.begin())->upper_bound(index)->first; // H from the first map
          float hmax                 = (*childrenmapHW.begin())->upper_bound(index)->first;
          list<float> feasibleH      = list<float>();
          
          while(incrementation != 0)
            {
            //cout << "4)------------- Première étape de boucle while ------------- " << endl;
              incrementation = 0;
              index = 0;
              vector< pair<float,float> >::iterator itpair = childrenpair.begin();
              for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
                {
                //cout << "Debut boucle for des maps" << endl;
                  if (itmap == childrenmapHW.begin())
                    {
                      hmin     = childrenpair.begin()->first;
                      hmax     = childrenpair.begin()->first;
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        {
                          indexNext      = index;
                          incrementation = 1;
                          nextPairMin    = (*itpair).first;
                          nextPair       = pair<float,float>(
                                                             (*itmap)->upper_bound((*itpair).first)->first,
                                                             (*itmap)->upper_bound((*itpair).first)->second
                                                            );
                        }
                    //cout << "4.1) Premier tour de boucle, initialisation de hmin et hmax " << endl;
                    //cout << "hmin          : " << hmin << endl;
                    //cout << "hmax          : " << hmax << endl;
                    //cout << "incrementation: " << incrementation << endl;
                    }
                  else 
                    {
                    //cout << "4.2) 2nd+ tour de boucle" << endl;
                    //cout << "hactuel: " << (*itpair).first << endl;
                    //cout << "hmin   : " << hmin << endl;
                    //cout << "hmax   : " << hmax << endl;
                      
                      if (hmin > (*itpair).first){ hmin = (*itpair).first; }
                      if (hmax < (*itpair).first){ hmax = (*itpair).first; }
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        if ((incrementation == 0) || (nextPairMin > (*itpair).first) )
                          {
                            indexNext      = index;
                            incrementation = 1;
                            nextPairMin    = (*itpair).first;
                            nextPair       = pair<float,float>(
                                                               (*itmap)->upper_bound((*itpair).first)->first,
                                                               (*itmap)->upper_bound((*itpair).first)->second
                                                              );
                          }
                    }
                  index++;
                  itpair++;
                //cout << "Fin de la boucle for, index: " << index << endl;
                }
              
            //cout << "5) On a calculé le min et max de la serie de pair en cours " << endl;
            //cout << "hmin: " << hmin << endl;
            //cout << "hmax: " << hmax << endl;
              
            // Mis a jour du vecteur de pair
            //cout << "5.1) On met a jour le vector de pair " << endl;
            //cout << "indexNext: " << indexNext << endl;
            //cout << "h: " << nextPair.first << ", w: " << nextPair.second << endl;
              childrenpair[indexNext] = nextPair; 
              
              if ((hmax-hmin) <= _tolerance)
                {
                  feasibleH.push_back(hmax);
                }
            //cout << "6) On a une valeur de pour H viable qui est: " << hmax << endl;
            //cout << "7) incrementation vaux: " << incrementation << endl;
            }
          
        //cout << "8) Fin du while. Creation de la map avec les feasibles H" << endl;
          map <float,float>* mapHW = new map <float,float>();
          float w = 0; 
          for (list<float>::iterator it1 = feasibleH.begin(); it1 != feasibleH.end(); it1++)
            {
              w = 0;
              for (vector<SlicingNode*>::iterator it2 = _children.begin(); it2 != _children.end(); it2++)
                {
                  w += (*it2)->getPairH((*it1)).second;
                }
              mapHW->insert(pair<float,float>((*it1),w));
            }
          _mapHW = mapHW;
          _h = mapHW->begin()->first;
          _w = mapHW->begin()->second;
        }
      if (this->getType() == Horizontal)
        {
          
          cout << "1) On commence le test" << endl;
        // childrenmapHW: On recupère les maps de chacun des fils dans un vector 
          vector<map<float,float>*> childrenmapHW;
          for (vector<SlicingNode*>::iterator itSN = _children.begin(); itSN != _children.end(); itSN++)
            {
              childrenmapHW.push_back( (*itSN)->getmapHW() );
            }
          
          cout << "2) On a recupéré les maps " << endl;
          
          vector< pair<float,float> > childrenpair;
          for (vector< map<float,float>* >::iterator it = childrenmapHW.begin(); it != childrenmapHW.end(); it++)
            {
              childrenpair.push_back(pair<float,float>((*it)->begin()->first,(*it)->begin()->second));
            }
          
          cout << "3) On a recupéré les premieres paires de chaque map " << endl;
          
          bool  incrementation = 1;
          int   index     = 0;
          int   indexNext = 0;
          pair<float,float> nextPair = pair<float,float>((*childrenmapHW.begin())->upper_bound(index)->first,(*childrenmapHW.begin())->upper_bound(index)->second);
          float nextPairMax          = nextPair.second;
          float wmin                 = (*childrenmapHW.begin())->upper_bound(index)->second; // H from the first map
          float wmax                 = (*childrenmapHW.begin())->upper_bound(index)->second;
          list<float> feasibleW      = list<float>();
          
          while(incrementation != 0)
            {
              cout << "4)------------- Première étape de boucle while ------------- " << endl;
              incrementation = 0;
              index = 0;
              vector< pair<float,float> >::iterator itpair = childrenpair.begin();
              for (vector<map<float,float>*>::iterator itmap = childrenmapHW.begin(); itmap != childrenmapHW.end(); itmap++)
                {
                  cout << "Debut boucle for des maps" << endl;
                  if (itmap == childrenmapHW.begin())
                    {
                      wmin     = childrenpair.begin()->second;
                      wmax     = childrenpair.begin()->second;
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        {
                          indexNext      = index;
                          incrementation = 1;
                          nextPairMax    = (*itpair).second;
                          nextPair       = pair<float,float>(
                                                             (*itmap)->upper_bound((*itpair).first)->first,
                                                             (*itmap)->upper_bound((*itpair).first)->second
                                                            );
                        }
                      cout << "4.1) Premier tour de boucle, initialisation de wmin et wmax " << endl;
                      cout << "wmin          : " << wmin << endl;
                      cout << "wmax          : " << wmax << endl;
                      cout << "incrementation: " << incrementation << endl;
                    }
                  else 
                    {
                      cout << "4.2) 2nd+ tour de boucle" << endl;
                      cout << "hactuel: " << (*itpair).second << endl;
                      cout << "wmin   : " << wmin << endl;
                      cout << "wmax   : " << wmax << endl;
                      
                      if (wmin > (*itpair).second){ wmin = (*itpair).second; }
                      if (wmax < (*itpair).second){ wmax = (*itpair).second; }
                      if ( (*itmap)->upper_bound((*itpair).first) != (*itmap)->end() )
                        if ((incrementation == 0) || (nextPairMax < (*itpair).second) )
                          {
                            indexNext      = index;
                            incrementation = 1;
                            nextPairMax    = (*itpair).second;
                            nextPair       = pair<float,float>(
                                                               (*itmap)->upper_bound((*itpair).first)->first,
                                                               (*itmap)->upper_bound((*itpair).first)->second
                                                              );
                          }
                    }
                  index++;
                  itpair++;
                  cout << "Fin de la boucle for, index: " << index << endl;
                }
              
              cout << "5) On a calculé le min et max de la serie de pair en cours " << endl;
              cout << "wmin: " << wmin << endl;
              cout << "wmax: " << wmax << endl;
              
            // Mis a jour du vecteur de pair
              cout << "5.1) On met a jour le vector de pair " << endl;
              cout << "indexNext: " << indexNext << endl;
              cout << "h: " << nextPair.first << ", w: " << nextPair.second << endl;
              childrenpair[indexNext] = nextPair; 
              
              
              if ((wmax-wmin) <= _tolerance)
                {
                  feasibleW.push_back(wmax);
                  cout << "6) On a une valeur de pour W viable qui est: " << wmax << endl;
                }
                


              cout << "7) incrementation vaux: " << incrementation << endl;
            }
          
          cout << "8) Fin du while. Creation de la map avec les feasibles W" << endl;
          map <float,float>* mapHW = new map <float,float>();
          float h = 0; 
          for (list<float>::iterator it1 = feasibleW.begin(); it1 != feasibleW.end(); it1++)
            {
              cout << "wActual is: " << (*it1) << endl;
              h = 0;
              for (vector<SlicingNode*>::iterator it2 = _children.begin(); it2 != _children.end(); it2++)
                {
                  h += (*it2)->getPairW((*it1)).first;
                }
              mapHW->insert(pair<float,float>(h,(*it1)));
            }
          _mapHW = mapHW;
          _h = mapHW->begin()->first;
          _w = mapHW->begin()->second;
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


void DSlicingNode::updateBandSize(){} // just do nothing

bool DSlicingNode::emptyChildren() const
{
 cerr << " Error(DSlicingNode::emptyChildren()): Device do not have child." << endl;
return true;
} 
