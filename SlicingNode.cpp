#include "SlicingNode.h"

using namespace std;

namespace SlicingTree{

  void printPair(pair<float,float> paire){ cout << "H: " << paire.first << ", W: " << paire.second << endl; }  
  void printVectorPair(vector<pair<float, float> > vectorpaire)
  {
    for (vector<pair<float, float> >::iterator it = vectorpaire.begin(); it != vectorpaire.end(); it++)
      { cout << "H: " << it->first << ", W: " << it->second << endl; }
  }


// -----------------------------------------------------------------------------------------------//
// Class : MapHW
// -----------------------------------------------------------------------------------------------//


  MapHW::MapHW(map <float,float>* map1)
  {
    if (map1 == NULL) { _mapHW = new std::map<float,float> (); }
    else              { _mapHW = map1; }
  }


  MapHW::~ MapHW(){}


  MapHW MapHW::clone ()
  {
    map <float,float>* mapHW = new map <float,float>();
    for (map<float,float>::const_iterator it = _mapHW->begin(); it != _mapHW->end(); it++)
      { mapHW->insert(pair<float,float>((*it).first, (*it).second)); }
    return mapHW;
  }


  bool MapHW::compare(MapHW map2)
  {
    bool comp = true;
    map <float,float>::const_iterator it2 = map2.begin();
    if (_mapHW->size() != map2.size()) { comp = false; }

    if (comp == true) {
      for (map<float,float>::const_iterator it1 = _mapHW->begin(); it1 != _mapHW->end(); it1++){

        if ( ((*it1).first != (*it2).first)||((*it1).second != (*it2).second) ){ comp = false; }
        if (it2 != map2.end()){ it2++; }
      }
    }
    return comp;
  }

  
  void MapHW::print()
  {
    cout << "PrintMap - MapHW:" << endl;
    for (map <float,float>::iterator itPrint = _mapHW->begin(); itPrint != _mapHW->end(); itPrint++)
      { cout << "H = " << itPrint->first << ", W = " << itPrint->second << endl; } 
    cout << endl;
  }


  pair<float,float> MapHW::getPairH(float h) const 
  {
    float w        = 0;
    float hclosest = 0;

    for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++){ 
      if ( (itHW->first > hclosest) && (h >= itHW->first) ){
        hclosest = itHW->first;
        w        = itHW->second;
      }
    }

    if ( (w == 0) && (hclosest == 0) ){ cerr << "No solution for h = " << h << " has been found." << endl; }
    return pair<float,float>(hclosest,w);
  }


  pair<float,float> MapHW::getPairW(float w) const 
  {
    float wclosest = 0;
    float h        = 0;

    for (map <float,float>::const_iterator itHW = _mapHW->begin(); itHW != _mapHW->end(); itHW++){ 
      if ( (itHW->second > wclosest) && (w >= itHW->second) ){
        h        = itHW->first;
        wclosest = itHW->second;
      }
    }

    if ( (h == 0) && (wclosest == 0) ){ cerr << "No solution for w = " << w << " has been found." << endl; }
    return pair<float,float>(h,wclosest);
  }


  void MapHW::insertWorst(float h, float w)
  {
    if ( _mapHW->find(h) != _mapHW->end() ){
      if ( (*_mapHW->find(h)).second < w ) 
        {( *_mapHW->find(h)).second = w; }
    }
    else 
      { _mapHW->insert(pair<float,float> ( h, w ) ); }
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSetState
// -----------------------------------------------------------------------------------------------//
  

  HVSetState::HVSetState( HVSlicingNode* node, float height, float width, bool  isTop
                        ):_height(height)
                         ,_width(width)
                         ,_isTop(isTop)
                         ,_children(node->getChildren())
                         ,_symmetries(node->getSymmetries())
                         ,_toleranceH(node->getToleranceH())
                         ,_toleranceW(node->getToleranceW())
                         ,_hminWmin(pair<float,float>(0,0))
                         ,_hminWmax(pair<float,float>(0,0))
                         ,_hmaxWmin(pair<float,float>(0,0))
                         ,_hmaxWmax(pair<float,float>(0,0))
                         ,_wminHmin(pair<float,float>(0,0))
                         ,_wminHmax(pair<float,float>(0,0))
                         ,_wmaxHmin(pair<float,float>(0,0))
                         ,_wmaxHmax(pair<float,float>(0,0))
  {
    _bestSet    = vector<pair<float,float> > ();
    _currentSet = vector<pair<float,float> > ();
    _nextSet    = vector<pair<float,float> > ();
    _mapHW      = MapHW();
    _counter    = 1;
    initSet();
    initModulos();
  }


  HVSetState::~HVSetState(){}


  void HVSetState::initSet()
  {
    _nextSet.clear();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 
        
      if ( (*it)->isPreset() ) { _nextSet.push_back(pair<float, float>((*it)->getHeight(), (*it)->getWidth())); }
      else                     { _nextSet.push_back((*(*it)->getMapHW().begin())); }
    }
    _currentSet = _nextSet;
  }


  void HVSetState::initModulos()
  {
    int  modulo        = 1;
    int  index         = 0;
    
    _modulos.clear();
    _modulos.push_back(1);
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        
      if ( it != _children.begin() ){ _modulos.push_back(modulo); }
      if ( (!isSymmetry(index)) && (!(*it)->isPreset()) ){
        modulo *= (*it)->getMapHW().size();
      }
      index++;
    }
    _modulos.push_back(modulo);
  }

  
  bool HVSetState::isSymmetry( int index, pair<int,int>& symmetry )
  {
    bool symmetryFound = false;
    
    if (_symmetries.empty() != true){
      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++){
        
        if ((*it2).second == index){ 
          symmetry = pair<int,int>((*it2).first,(*it2).second); 
          symmetryFound = true;
        }
      }
    }
    return symmetryFound;
  }


  bool HVSetState::isSymmetry( int index )
  {
    bool symmetryFound = false;
    
    if (_symmetries.empty() != true){
      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++){
        
        if ((*it2).second == index){ 
          symmetryFound = true;
        }
      }
    }
    return symmetryFound;
  }


  void HVSetState::print()
  {
    cout << "--------------------------------currentSet:" << endl;
    int index = 0;
    for (vector<pair<float,float> >::iterator it = _currentSet.begin(); it != _currentSet.end(); it++)
      { 
        cout << index << ": H = " << it->first << ", W = " << it->second << endl;
        index++;
      }
    cout << "--------------------------------bestSet:" << endl;
    index = 0;
    for (vector<pair<float,float> >::iterator it = _bestSet.begin(); it != _bestSet.end(); it++)
      { 
        cout << index << ": H = " << it->first << ", W = " << it->second << endl;
        index++;
      }
    cout << "counter     = " << _counter  << endl;
    cout << "end counter = " << _modulos.back()<< endl;
    cout << "modulos:" << endl;
    index = 0;
    for (vector<int>::iterator it = _modulos.begin(); it != _modulos.end(); it++)
      { 
        cout << index << ": modulo = " << (*it) << endl;
        index++;
        }
     
    _mapHW.print();
    cout << "hminwmin: H: " << _hminWmin.first << ", W: " << _hminWmin.second << endl;
    cout << "hminwmax: H: " << _hminWmax.first << ", W: " << _hminWmax.second << endl;
    cout << "hmaxwmin: H: " << _hmaxWmin.first << ", W: " << _hmaxWmin.second << endl;
    cout << "hmaxwmax: H: " << _hmaxWmax.first << ", W: " << _hmaxWmax.second << endl;

    cout << endl;

    cout << "wminhmin: H: " << _wminHmin.first << ", W: " << _wminHmin.second << endl;
    cout << "wminhmax: H: " << _wminHmax.first << ", W: " << _wminHmax.second << endl;
    cout << "wmaxhmin: H: " << _wmaxHmin.first << ", W: " << _wmaxHmin.second << endl;
    cout << "wmaxhmax: H: " << _wmaxHmax.first << ", W: " << _wmaxHmax.second << endl;
  }


  void HVSetState::updateLimits()
  {
    pair<float,float> currentPair = pair<float,float>(getCurrentH(),getCurrentW());
    if (  (_hminWmin == pair<float,float>(0,0)) 
       && (_hminWmax == pair<float,float>(0,0)) 
       && (_hmaxWmin == pair<float,float>(0,0)) 
       && (_hmaxWmax == pair<float,float>(0,0)) 
       && (_wminHmin == pair<float,float>(0,0))
       && (_wminHmax == pair<float,float>(0,0))
       && (_wmaxHmin == pair<float,float>(0,0))
       && (_wmaxHmax == pair<float,float>(0,0))
       ){
      _hminWmin = currentPair;
      _hminWmax = currentPair;
      _hmaxWmin = currentPair;
      _hmaxWmax = currentPair;
      _wminHmin = currentPair;
      _wminHmax = currentPair;
      _wmaxHmin = currentPair;
      _wmaxHmax = currentPair;
    } 
    else {
      if ( getCurrentH() < _hminWmin.first ) { 
        _hminWmin = currentPair;
        _hminWmax = currentPair;
      }
      else if (getCurrentH() == _hminWmin.first ) {
        if      (getCurrentW() < _hminWmin.second) { _hminWmin = currentPair; }
        else if (getCurrentW() > _hminWmax.second) { _hminWmax = currentPair; }
      }
      else if ( getCurrentH() > _hmaxWmin.first ){
        _hmaxWmin = currentPair;
        _hmaxWmax = currentPair;
      }
      else if (getCurrentH() == _hmaxWmin.first ) {
        if      (getCurrentW() < _hmaxWmin.second) { _hmaxWmin = currentPair; }
        else if (getCurrentW() > _hmaxWmax.second) { _hmaxWmax = currentPair; }
      }

      if ( getCurrentW() < _wminHmin.second ) { 
        _wminHmin = currentPair;
        _wminHmax = currentPair;
      }
      else if (getCurrentW() == _wminHmin.second ) {
        if      (getCurrentH() < _wminHmin.first) { _wminHmin = currentPair; }
        else if (getCurrentH() > _wminHmax.first) { _wminHmax = currentPair; }
      }
      else if ( getCurrentW() > _wmaxHmin.second ){
        _wmaxHmin = currentPair;
        _wmaxHmax = currentPair;
      }
      else if (getCurrentW() == _wmaxHmin.second ) {
        if      (getCurrentH() < _wmaxHmin.first) { _hmaxWmin = currentPair; }
        else if (getCurrentH() > _wmaxHmax.first) { _hmaxWmax = currentPair; }
      }
    }
  }


  void HVSetState::next()
  {
    int           index    = 0;
    pair<int,int> symmetry = pair<int,int>();
    int           maxIndex = _nextSet.size() ;
    vector< pair<float,float> >::iterator itpair = _nextSet.begin();

    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){

      if ( this->isSymmetry(index, symmetry) ){
        _nextSet.push_back(_nextSet[(maxIndex-index) + symmetry.first]);
      }
      else {
        if ( (((_counter-1)%_modulos[index]) == _modulos[index]-1) && (!(*it)->isPreset()) ) {
          
          if ( (*it)->getMapHW().upper_bound((*itpair).first) != (*it)->getMapHW().end() ) 
            { _nextSet.push_back(*(*it)->getMapHW().upper_bound((*itpair).first)); }

          else {_nextSet.push_back(*(*it)->getMapHW().begin()); }
        }
        else { _nextSet.push_back((*itpair)); }
      }
      _nextSet.erase(_nextSet.begin());
      index++;
    }
    _counter += 1;
    _currentSet = _nextSet;
  }


// -----------------------------------------------------------------------------------------------//
// Class : VSetState
// -----------------------------------------------------------------------------------------------//
  

  VSetState::VSetState( VSlicingNode* node, float height, float width, bool isTop):HVSetState(node, height, width, isTop) {}


  VSetState::~VSetState(){}


  void VSetState::next()
  {
    if      ( (_height == 0)&&(_width == 0) ) { insertWorst()     ; }
    else if (_isTop)                          { updateBestSetTop(); }
    else                                      {  updateBestSet()  ; }
    HVSetState::next();
  }

  float VSetState::getMinH ()
  {
    float hmin = 0;
    if (!_currentSet.empty()) {
      vector<pair<float, float> >::const_iterator it = _currentSet.begin();
      while( (hmin == 0) && (it != _currentSet.end()) ){
        if ( (*it).first != 0 ){ hmin = (*it).first; }
        it++;
      }

      for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
        if ( (hmin > (*it).first) && ((*it).first != 0) ) { hmin = (*it).first; }
      }
    }
    return hmin;  
  }


  float VSetState::getBestH()
  {
    float hBest = 0;
    for (vector<pair<float, float> >::const_iterator it = _bestSet.begin(); it != _bestSet.end(); it++){
      if (hBest < (*it).first){ hBest = (*it).first; }
    }
    return hBest;
  }


  float VSetState::getBestW()
  {
    float wBest = 0;
    for (vector<pair<float, float> >::const_iterator it = _bestSet.begin(); it != _bestSet.end(); it++){
      wBest += (*it).second;
    }
    return wBest;
  }


  float VSetState::getCurrentH()
  {
    float currentH = 0;
    for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
      if (currentH < (*it).first){ currentH = (*it).first; }
    }
    return currentH;
  }


  float VSetState::getCurrentW()
  {
    float currentW = 0;
    for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
      currentW += (*it).second;
    }
    return currentW;
  }


  void VSetState::updateBestSet ()
  {
    float currentH = getCurrentH();
    float currentW = getCurrentW();
    
    if ((currentH == _height)&&(currentW == _width)){ _bestSet = _currentSet; }
  }


  void VSetState::updateBestSetTop ()
  {
    float currentH = getCurrentH();
    float currentW = getCurrentW();
    if ( checkToleranceH() ){
      float bestH = getBestH();
      float bestW = getBestW();
      
      if (currentH <= _height){
        if ( (bestH == 0) || (bestW == 0) ){ _bestSet = _currentSet; }
        else { 
          if ( (_height-currentH) <= _toleranceH ){
            if ( _height-bestH <= _toleranceH ){
              if      ( (currentW > bestW)&&(currentW <= _width) ){ _bestSet = _currentSet; }
              else if ( (currentW < bestW)&&(bestW     > _width) ){ _bestSet = _currentSet; }
            }
            else { _bestSet = _currentSet; }
          }
          else if (currentH > bestH){ _bestSet = _currentSet; }
        }
      }
    }
  }


  void VSetState::print()
  {
    HVSetState::print();
    cout << "currentH = " << getCurrentH() << endl;
    cout << "currentW = " << getCurrentW() << endl;
    cout << "bestH    = " << getBestH() << endl;
    cout << "bestW    = " << getBestW() << endl;
    cout << endl;
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//
  

HSetState::HSetState( HSlicingNode* node, float height, float width, bool isTop):HVSetState(node, height, width, isTop) {}


  HSetState::~HSetState(){}

  
  void HSetState::next()
  {
    if ( (_height == 0)&&(_width == 0) ) { 
      insertWorst(); 
      updateLimits();      
    }
    else if (_isTop) { updateBestSetTop() ; }
    else             { updateBestSet()    ; }
    HVSetState::next();
  }


  float HSetState::getMinW()
  {
    float wmin = 0;
    if (!_currentSet.empty()) { 
      vector<pair<float, float> >::const_iterator it = _currentSet.begin();
      while( (wmin == 0) && (it != _currentSet.end()) ){
        if ( (*it).second != 0 ){ wmin = (*it).second; }
        it++;
      }
      for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
        if (wmin > (*it).second){ wmin = (*it).second; }
      }
    }
    return wmin;  
  }


  float HSetState::getBestH()
  {
    float hBest = 0;
    for (vector<pair<float, float> >::const_iterator it = _bestSet.begin(); it != _bestSet.end(); it++){
      hBest += (*it).first;
    }
    return hBest;
  }


  float HSetState::getBestW()
  {
    float wBest = 0;
    for (vector<pair<float, float> >::const_iterator it = _bestSet.begin(); it != _bestSet.end(); it++){
      if (wBest < (*it).second){ wBest = (*it).second; }
    }
    return wBest;
  }


  float HSetState::getCurrentW()
  {
    float currentW = 0;
    for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
      if (currentW < (*it).second){ currentW = (*it).second; }
    }
    return currentW;
  }


  float HSetState::getCurrentH()
  {
    float currentH = 0;
    for (vector<pair<float, float> >::const_iterator it = _currentSet.begin(); it != _currentSet.end(); it++){
      currentH += (*it).first;
    }
    return currentH;
  }


  void HSetState::updateBestSet()
  {
    float currentH = getCurrentH();
    float currentW = getCurrentW();
    
    if ((currentH == _height)&&(currentW == _width)){ _bestSet = _currentSet; }
  }



  void HSetState::updateBestSetTop()
  {
    float currentH = getCurrentH();
    float currentW = getCurrentW();

    if ( checkToleranceW() ){
      float bestH = getBestH();
      float bestW = getBestW();
      
      if (currentH <= _height){
        if (( bestH == 0 )||( bestW == 0 )){ _bestSet = _currentSet; }
        else { 
          if ( (_height-currentH) <= _toleranceH ){
            if ( _height-bestH    <= _toleranceH ){
              if      ( (currentW > bestW)&&( currentW <= _width) ){ _bestSet = _currentSet; }
              else if ( (currentW < bestW)&&( bestW     > _width) ){ _bestSet = _currentSet; }
            }
            else { _bestSet = _currentSet; }
          }
          else if (currentH > bestH){ _bestSet = _currentSet; }
        }
      }
    }
  }


  void HSetState::print()
  {
    HVSetState::print();
    cout << "currentH = " << getCurrentH() << endl;
    cout << "currentW = " << getCurrentW() << endl;
    cout << "bestH    = " << getBestH() << endl;
    cout << "bestW    = " << getBestW() << endl;
    cout << endl;
  }

// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  SlicingNode::SlicingNode( unsigned int type
                          , MapHW        mapHW
                          , unsigned int alignment 
                          , float        w        
                          , float        h
                          ):_x(0),_y(0)
                           ,_w(w),_h(h)
  {
    _flags = 0;
    this->setType(type);
    this->setAlignment(alignment);
    _mapHW = mapHW; 

    if ( (w != 0)&&(h != 0) ){ this->setPreset(Preset); }
  } 


  SlicingNode::~SlicingNode(){}


  void SlicingNode::print() const
  {
    if   ( this->isPreset() ){ cout << "preset = True"  << endl; }
    else                     { cout << "preset = False " << endl; }
    cout << "Height = " << _h << endl;
    cout << "Width  = " << _w << endl;
    cout << "X      = " << _x << endl;
    cout << "Y      = " << _y << endl;
    cout << endl;

    if ( !this->isRouting() ){
      cout << "MapHW:" << endl;
      for (map <float,float>::const_iterator itHW = _mapHW.begin(); itHW != _mapHW.end(); itHW++)
        { cout << "H = " << itHW->first << ", W = " << itHW->second << endl; }
      cout << endl;
    }
  }


  void SlicingNode::place(float x, float y)
  {
    _x = x;
    _y = y;
  }  


  void SlicingNode::setPairH(float h)
  {
    pair<float,float> hw = this->getPairH(h);
    _h                   = hw.first;
    _w                   = hw.second;
  }
  

  pair<float, float> SlicingNode::_setGlobalSize(float height, float width)
  {
    if ( !this->isPreset() )      { this->setPairH(height)  ; }
    if ( (_h != 0) && (_w != 0) ) { this->setPreset(Preset) ; }

    return pair<float, float> (_h,_w); 
  }


// Error Methods
  void SlicingNode::createChild ( unsigned int type     
                                , unsigned int alignment  
                                , float        toleranceH 
                                , float        toleranceW 
                                , float        w          
                                , float        h          
                                )
  {
    cerr << "Error(createChild( SlicingType type, Alignment alignment = UnknownAlignment, float toleranceH = 0, float toleranceW = 0, float w = 0, float h = 0)): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createChild( MapHW        mapHW
                               , unsigned int alignment
                               , float        w
                               , float        h 
                               )
  {
    cerr << "Error(createChild(MapHW mapHW, Alignment alignment, float w, float h)): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createChild( int childIndex, int copyIndex, Flags tr)
  {
    std::cerr << "Error(createChild( int childIndex, int copyIndex, Flags tr)): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createRouting(float hw)
  {
    std::cerr << "Error(createChild(float hw): Device and Routing do not have child." << endl; 
  }

  int SlicingNode::getNbChild() const
  {
    cerr << "Error(int SlicingNode::getNbChild()): Devices do not have child." << endl;
    return 0;
  }


  SlicingNode* SlicingNode::getChild(int index) const
  {
    cerr << "Error(SlicingNode* SlicingNode::getChild(int index)): Devices do not have child." << endl;
    return NULL;
  }


  const vector<SlicingNode*>& SlicingNode::getChildren() const
  {
    cerr << "Error(vector<SlicingNode*> SlicingNode::getChildren()): Devices do not have child." << endl;
    static vector<SlicingNode*> dummyVectorSlicingNode;
    return dummyVectorSlicingNode;
  }


  void SlicingNode::printChildren()
  {
    cerr << "Error(void DSlicingNode::printChildren()): Devices do not have child." << endl; 
  }


  void SlicingNode::pushBackNode(SlicingNode* node)
  {
    cerr << "Error(void SlicingNode::pushBackNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::pushFrontNode(SlicingNode* node)
  {
    cerr << "Error(void SlicingNode::pushFrontNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::removeAllNodes()
  {
    cerr << "Error(void SlicingNode::removeAllNodes()): Devices do not have child." << endl; 
  }


  void SlicingNode::insertNode(SlicingNode* node, int index)
  {
    cerr << "Error(void SlicingNode::insertNode(SlicingNode* node, int index)): Devices do not have child." << endl; 
  }


  void SlicingNode::removeNode(SlicingNode* node)
  {
    cerr << "Error(void SlicingNode::removeNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::setToleranceH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::setToleranceW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  float SlicingNode::getToleranceH() const
  {
   cerr << "Error(SlicingNode::getToleranceH()): Devices do not have tolerance parameter." << endl;
   return 0;
  }


  float SlicingNode::getToleranceW() const
  {
   cerr << "Error(SlicingNode::getToleranceW()): Devices do not have tolerance parameter." << endl;
   return 0;
  }


  void SlicingNode::recursiveSetToleranceH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  bool SlicingNode::hasEmptyChildrenMap() const
  {
   cerr << "Error(SlicingNode::hasEmptyChildrenMap()): Devices do not have child." << endl;
   return true;
  } 


  void SlicingNode::setSymmetry(int childIndex, int copyIndex)
  {
    cerr << "Error(SlicingNode::setSymmetry(int childIndex, int copyIndex)) : Routings do not have symmetries." << endl; 
  }


  void SlicingNode::normalizeSymmetries() 
  {
    cerr << "Error(SlicingNode::normalizeSymmetries() const) : Routings do not have symmetries." << endl; 
  }


  list<pair<int,int> > SlicingNode::getSymmetries() const
  {
    cerr << "Error(SlicingNode::getSymmetries() const) : Routings do not have symmetries." << endl; 
    return list<pair<int,int> >();
  }


  float SlicingNode::getOccupationArea () const
  {
    cerr << "Error(SlicingNode::getOccupationArea() const) : Occupied Area not possible for Routing and Devices." << endl; 
    return 0;
  }

// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  HVSlicingNode::HVSlicingNode( unsigned int type
                              , unsigned int alignment 
                              , float        toleranceH 
                              , float        toleranceW
                              , float        w 
                              , float        h
                              ):SlicingNode(type, MapHW(), alignment, w, h)
                               ,_toleranceH(toleranceH)
                               ,_toleranceW(toleranceW){}


  HVSlicingNode::~HVSlicingNode(){}


  vector< pair<float,float> > HVSlicingNode::initSet()
  {
    vector< pair<float,float> > nextSet;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
        
      if ( !(*it)->isRouting() ) 
        { nextSet.push_back((*(*it)->getMapHW().begin())); }
      else 
        { nextSet.push_back(pair<float,float>((*it)->getHeight(),(*it)->getWidth())); }
    }
    return nextSet;
  }


  std::vector<int> HVSlicingNode::setModulos()
  {
    vector<int>   modulos       = vector<int>();
    int           modulo        = 1;
    int           index         = 0;
    pair<int,int> symmetry      = pair<int,int>(); // created only for isSymmetry(...) method
    
    modulos.push_back(1);
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
        
      if ( it != _children.begin() ){ modulos.push_back(modulo); }
      if ( !(*it)->isRouting()     ){
      // Check if the current child is a symmetry or not

        if ( (!this->isSymmetry(index, symmetry)) && (!(*it)->isPreset()) ){
          modulo *= (*it)->getMapHW().size();
        }
      }
      index++;
    }
    modulos.push_back(modulo);
    return modulos;
  }
  
  
  bool HVSlicingNode::isSymmetry( int index, pair<int,int>& symmetry )
  {
    bool symmetryFound = false;
    
    if (_symmetries.empty() != true){
      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++){
        
        if ((*it2).second == index){ 
          symmetry = pair<int,int>((*it2).first,(*it2).second); 
          symmetryFound = true;
        }
      }
    }
    return symmetryFound;
  }


  bool HVSlicingNode::isSymmetry( int index )
  {
    bool symmetryFound = false;
    
    if (_symmetries.empty() != true){
      for (list<pair<int,int> >::const_iterator it2 = _symmetries.begin(); it2 != _symmetries.end(); it2++){
        
        if ((*it2).second == index){ 
          symmetryFound = true;
        }
      }
    }
    return symmetryFound;
  }

  
  void HVSlicingNode::updateBestSet( float& currentW
                                   , float& currentH
                                   , float& width
                                   , float& height
                                   , float& bestWidth
                                   , float& bestHeight
                                   , vector<pair<float,float> >& bestSet
                                   , vector<pair<float,float> >& currentSet
                                   )
  {
    if (currentH <= height){
      if (( bestHeight == 0 )||( bestWidth == 0 )){
        bestSet    = currentSet; 
        bestHeight = currentH;
        bestWidth  = currentW;
      }
      else { 
        if ( (height-currentH) <= _toleranceH ){
          if ( height-bestHeight <= _toleranceH ){
            if      ( (currentW > bestWidth)&&(currentW <= width) ){ 
              bestSet    = currentSet; 
              bestHeight = currentH;
              bestWidth  = currentW;
            }
            else if ( (currentW < bestWidth)&&(bestWidth > width) ){ 
              bestSet    = currentSet; 
              bestHeight = currentH;
              bestWidth  = currentW;
            }
          }
          else {
            bestSet    = currentSet; 
            bestHeight = currentH;
            bestWidth  = currentW;
          }
        }
        else if (currentH > bestHeight){ 
          bestSet    = currentSet; 
          bestHeight = currentH;
          bestWidth  = currentW;
        }
      }
    }
  }
  

  void HVSlicingNode::createChild(int childIndex, int copyIndex, Flags tr)
  {
    if (childIndex != copyIndex){
      
      this->insertNode(this->getChild(childIndex)->clone(tr), copyIndex); 
      _symmetries.push_back(pair<int,int>(min(childIndex, copyIndex),max(childIndex, copyIndex)));
    }
    else { cerr << "Error(HVSlicingNode::createChild(int childIndex, int copyIndex, Flags tr)): Indexes cannot be the same." << endl; }
  }


  void HVSlicingNode::printChildren()
  {
    int count = 0;
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if ( ((*it)->isDevice()) || ((*it)->isRouting()) ){
        cout << "-- Children: " << count << "/" << _children.size()-1 << " --" << endl;
        (*it)->print(); 
      }
      else {
        cout << "-- Children: " << count << "/" << _children.size()-1 << " --" << endl;
        (*it)->print();
        (*it)->printChildren();
      }
      count++;
    }
  }


  void HVSlicingNode::insertNode(SlicingNode* node, int index)
  {
    vector<SlicingNode*>::iterator it = _children.begin();
    for (int i = 0; i < index; i++){ if (it != _children.end()){ it++; } }
    _children.insert(it,node);
  }


  void HVSlicingNode::removeNode(SlicingNode* node) 
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
      { if (*it == node){  _children.erase(it); } }
  }


  void  HVSlicingNode::recursiveSetToleranceH(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceH(tolerance); }
    }
    _toleranceH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceW(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceW(tolerance); }
    }
    _toleranceW = tolerance; 
  }


  bool HVSlicingNode::hasEmptyChildrenMap() const
  {
    bool flag = false;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){

      if ( ((*it)->getMapHW().empty() != true) && (!(*it)->isRouting()) )
        { if ((*it)->getMapHW().empty() == true) {flag = true;} }
    }
    return flag;
  }


  void HVSlicingNode::setSymmetry(int childIndex, int copyIndex)
  {
    if (childIndex != copyIndex){
      if (this->getChild(childIndex)->getMapHW().compare( this->getChild(copyIndex)->getMapHW() ) == true)
        { _symmetries.push_back(pair<int,int>(min(childIndex, copyIndex), max(childIndex, copyIndex))); }
      else
        { cerr << "Error(HVSlicingNode::setSymmetry(int childIndex, int copyIndex)): Child are not the same, symmetry cannot be set." << endl; }
    }
    else { cerr << "Error(HVSlicingNode::setSymmetry(int childIndex, int copyIndex)): Indexes cannot be the same." << endl; }
  }


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
    if (_symmetries.empty() == false){
        cout << "Symmetries: " << endl;
        for (list<pair<int,int> >::const_iterator it = _symmetries.begin(); it != _symmetries.end(); it++)
          { cout << "Children: " << (*it).first << " and " << (*it).second << endl;  }
        cout << endl;
      }
  }


  void HVSlicingNode::normalizeSymmetries()
  {
    list<pair<int,int> > adjustedSymmetries = list<pair<int,int> >();
    for (list<pair<int,int> >::const_iterator it = _symmetries.begin(); it != _symmetries.end(); it++){ 

      if ((*it).first > (*it).second ){ adjustedSymmetries.push_back(pair<int,int >((*it).second,(*it).first)); } 
      else { adjustedSymmetries.push_back(pair<int,int >((*it).first,(*it).second)); } 
    }
    adjustedSymmetries.sort();

    bool next = false;
    list<pair<int,int> >::iterator it2 = adjustedSymmetries.begin();
    it2++;

    for (list<pair<int,int> >::iterator it = adjustedSymmetries.begin(); it != adjustedSymmetries.end(); it++){
      it2 = it;
      it2++;

      while(next != true){
        if ( (*it).second == (*it2).first ){ (*it2).first = (*it).first; }
        if ( (*it).second <  (*it2).first ){ next = true; }
        it2++;
        if ( it2 == adjustedSymmetries.end() ) { next = true; }
      }
      next = false;
    }
    _symmetries = adjustedSymmetries;
  }


  bool HVSlicingNode::recursiveCheckPreset() const
  {
    bool isPreset = this->isPreset();
    if (isPreset){
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
        isPreset = (*it)->recursiveCheckPreset(); 
      }
    }
    return isPreset;
  }


  float HVSlicingNode::getDevicesArea() const
  {
    float area = 0;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
      area += (*it)->getDevicesArea();
      }
    return area;
  }


  float HVSlicingNode::getOccupationArea() const
  {
    float estimation = 0;
    if( recursiveCheckPreset() )
      {
        estimation = getDevicesArea()/(getHeight() * getWidth())*100;
      }
    else { cerr << "Error(HVSlicingNode::getSpaceEstimation()): SlicingNodes dimensions need to be set first before being estimated." << endl; }
    return estimation;
  }
// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//

  
  VSlicingNode::VSlicingNode( unsigned int type
                            , unsigned int alignment
                            , float        toleranceH
                            , float        toleranceW
                            , float        w
                            , float        h
                            ):HVSlicingNode(type, alignment, toleranceH, toleranceW, w, h){}


  VSlicingNode::~VSlicingNode(){}


  void VSlicingNode::recursiveSetGlobalSize( vector< pair<float,float> >  bestSet
                                           , float&                       finalWidth
                                           , float&                       finalHeight
                                           , float&                       height
                                           )
  {
    if (bestSet.empty() != true){
      pair<float,float> pairreal = pair<float,float> (0,0);
      vector< pair<float,float> >::iterator it2 = bestSet.begin();

      for (vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++){

        if ( !(*it3)->isPreset() ){ pairreal = (*it3)->_setGlobalSize((*it2).first,(*it2).second)        ; }
        else                      { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth()); }
        
        finalWidth += pairreal.second;
        if (finalHeight < pairreal.first) { finalHeight = pairreal.first; }
        it2++;
       
      }
    }
  }


  VSlicingNode* VSlicingNode::create( unsigned int alignment
                                    , float        toleranceH
                                    , float        toleranceW
                                    , float        w
                                    , float        h
                                    )
  {
    return new VSlicingNode(Vertical, alignment, toleranceH, toleranceW, w, h); 
  }
 

  void VSlicingNode::createChild( unsigned int type
                                , unsigned int alignment
                                , float        toleranceH
                                , float        toleranceW
                                , float        w         
                                , float        h
                                )
  {
    float th = toleranceH;
    float tw = toleranceW;
    if ( (toleranceH == 0)&&(toleranceW == 0) ){
      th = getToleranceH();
      tw = getToleranceW();
      }

    if (type == Horizontal)
      { this->pushBackNode(HSlicingNode::create(alignment, th, tw, w, h)); }

    else if (type == Vertical)
      { this->pushBackNode(VSlicingNode::create(alignment, th, tw, w, h)); }

    else 
      { cerr << " Error(void VSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }
  
   
  void VSlicingNode::createChild( MapHW        mapHW
                                , unsigned int alignment
                                , float        w        
                                , float        h
                                )
  {
    this->pushBackNode(DSlicingNode::create(mapHW, alignment, w, h)); 
  }


  void VSlicingNode::createRouting(float hw)
  {
    this->pushBackNode(RVSlicingNode::create(hw)); 
  } 


  void VSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Vertical"  << endl; 
    if      (this->isAlignBottom()){ cout << "Alignment  : Bot"     << endl; }
    else if (this->isAlignCenter()){ cout << "Alignment  : Middle"  << endl; }
    else if (this->isAlignTop   ()){ cout << "Alignment  : Top"     << endl; }
    else                                         { cout << "Alignment  : Unknown" << endl; }
    HVSlicingNode::print();
  }

  
  void VSlicingNode::place(float x, float y)
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
    // Set X,Y Node
      if ( ( (*it)->isHorizontal()) || ((*it)->isVertical()) ){ 
        if ( (*it)->isAlignBottom() ){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        
        else if ( (*it)->isAlignCenter() ){
          (*it)->setX(xref);
          (*it)->setY(yref + (_h/2) - ((*it)->getHeight()/2));
        }
        
        else if ( (*it)->isAlignTop() ){
          (*it)->setX(xref);
          (*it)->setY(yref + _h - (*it)->getHeight());
        }
      }
      
    // Place Node
      if ( (*it)->isAlignBottom() )
        { (*it)->place(xref, yref); }
      
      else if ( (*it)->isAlignCenter() ) { (*it)->place(xref, yref + (_h/2) - ((*it)->getHeight()/2)); }
      
      else if ( (*it)->isAlignTop()    ) { (*it)->place(xref, yref +  _h    -  (*it)->getHeight())   ; }
      
      else if ( (*it)->isRouting()     ) { (*it)->place(xref, yref)                                  ; }
      
      else { cerr << " Error(place(float x, float y)): Unknown Alignment in SlicingTree." << endl; }
    
      xref += (*it)->getWidth();
      yref = y;
    }
  }


  void VSlicingNode::updateGlobalSize()
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
      { (*it)->updateGlobalSize(); }

    if (this->getNbChild() == 1){
      _mapHW = (*_children.begin())->getMapHW();
      cerr << "Error(void HVSlicingNode::updateGlobalSize()): You have a HVSlicingNode with only 1 child. This is an incorrect way to use HVSlicingNodes." << endl; 
    }
    else if (this->hasEmptyChildrenMap() != true){  
      _mapHW.clear();
      this->normalizeSymmetries();
      
      VSetState state = VSetState(this);
      while( !state.end() ){ state.next(); }

      _mapHW = state.getMapHW();
    }
    if (_mapHW.empty()) { cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set a larger toleranceH or toleranceW." << endl; }
  }


  pair<float, float> VSlicingNode::setGlobalSize(float height, float width)
  {
    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;
    
    VSetState state = VSetState(this, height, width, true);
    while ( !state.end() ){ state.next(); }

    this->recursiveSetGlobalSize( state.getBestSet(), finalWidth, finalHeight, height );
  
    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution foundV. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ this->setPreset(Preset); }

    return pair<float,float>( _h, _w );
  }


 pair<float, float> VSlicingNode::_setGlobalSize(float height, float width)
  {

    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;
    
    VSetState state = VSetState(this, height, width, false);
    while( !state.end() ){ state.next(); }

    this->recursiveSetGlobalSize( state.getBestSet(), finalWidth, finalHeight, height );
  
    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution foundV. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ this->setPreset(Preset); }

    return pair<float,float>( _h, _w );
  }


  VSlicingNode* VSlicingNode::clone(Flags tr)
  {
    VSlicingNode* node = VSlicingNode::create( this->getAlignment()
                                             , this->getToleranceH()
                                             , this->getToleranceW()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setMapHW(_mapHW.clone());
    node->setPreset(this->getPreset());
    node->cpSymmetries(this->getSymmetries());
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MX){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
    return node;
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  HSlicingNode::HSlicingNode( unsigned int type
                            , unsigned int alignment
                            , float        toleranceH
                            , float        toleranceW
                            , float        w
                            , float        h
                            ):HVSlicingNode(type, alignment, toleranceH, toleranceW, w, h){}


  HSlicingNode::~HSlicingNode(){}


  void HSlicingNode::recursiveSetGlobalSize( vector< pair<float,float> >  bestSet
                                           , float&                       finalWidth
                                           , float&                       finalHeight
                                           , float&                       width
                                           )
  {
    if (bestSet.empty() != true){
      
      pair<float,float> pairreal = pair<float,float> (0,0);
      vector< pair<float,float> >::iterator it2 = bestSet.begin();
      
      for(vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++){
        
        if ( !(*it3)->isPreset() ){ pairreal = (*it3)->_setGlobalSize((*it2).first,(*it2).second)        ; }
        else                      { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth()); }
        
        finalHeight += pairreal.first;
        if (finalWidth < pairreal.second){ finalWidth = pairreal.second; }
        it2++;
      }
    }
  }


  HSlicingNode* HSlicingNode::create( unsigned int alignment
                                    , float        toleranceH
                                    , float        toleranceW
                                    , float        w
                                    , float        h
                                    )
  {
    return new HSlicingNode(Horizontal, alignment, toleranceH, toleranceW, w, h);
  }


  void HSlicingNode::createChild( unsigned int type
                                , unsigned int alignment
                                , float        toleranceH
                                , float        toleranceW
                                , float        w         
                                , float        h
                                ) 
  {
    float th = toleranceH;
    float tw = toleranceW;
    if ( (toleranceH == 0)&&(toleranceW == 0) ){
      th = getToleranceH();
      tw = getToleranceW();
      }

    if (type == Horizontal)
      { this->pushBackNode(HSlicingNode::create(alignment, th, tw, w, h)); }

    else if (type == Vertical  )
      { this->pushBackNode(VSlicingNode::create(alignment, th, tw, w, h)); }

    else 
      { cerr << " Error(void HSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }


  void HSlicingNode::createChild( MapHW        mapHW
                                , unsigned int alignment
                                , float        w
                                , float        h
                                )
  {
    this->pushBackNode(DSlicingNode::create(mapHW, alignment, w, h));
  }


  void HSlicingNode::createRouting(float hw)
  {
    this->pushBackNode(RHSlicingNode::create(hw));
  } 


  void HSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Horizontal" << endl; 
    if      (this->isAlignLeft  ()){ cout << "Alignment  : Left"    << endl; }
    else if (this->isAlignCenter()){ cout << "Alignment  : Middle"  << endl; }
    else if (this->isAlignRight ()){ cout << "Alignment  : Right"   << endl; }
    else                           { cout << "Alignment  : Unknown" << endl; }
    HVSlicingNode::print();
  }


  void HSlicingNode::place(float x, float y)
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 

    // Set X,Y Node
      if ( ((*it)->isHorizontal()) || ((*it)->isVertical()) ){ 
        if ( (*it)->isAlignLeft() ){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        
        else if ( (*it)->isAlignCenter() ){
          (*it)->setX(xref + (_w/2) - ((*it)->getWidth()/2));
          (*it)->setY(yref);
        }
        
        else if ( (*it)->isAlignRight()  ){
          (*it)->setX(xref + _w - (*it)->getWidth());
          (*it)->setY(yref);
        }
      }
      
    // Place Node
      if ( (*it)->isAlignLeft()        ) { (*it)->place(xref                                 , yref); }
      
      else if ( (*it)->isAlignCenter() ) { (*it)->place(xref + (_w/2) - ((*it)->getWidth()/2), yref); }
      
      else if ( (*it)->isAlignRight()  ) { (*it)->place(xref + _w     -  (*it)->getWidth()   , yref); }

      else if ( (*it)->isRouting()     ) { (*it)->place(xref, yref)                                 ; }
      
      else { cerr << "Error(place(float x, float y)): Unknown Alignment in SlicingTree." << endl; }
      
      xref = x;
      yref += (*it)->getHeight();
    }
  }


  void HSlicingNode::updateGlobalSize()
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++)
      { (*it)->updateGlobalSize(); }

    if (this->getNbChild() == 1){
      _mapHW = (*_children.begin())->getMapHW();
      cerr << "Error(void HVSlicingNode::updateGlobalSize()): You have a HVSlicingNode with only 1 child. This is an incorrect way to use HVSlicingNodes." << endl; 
    }

    else if (this->hasEmptyChildrenMap() != true){     
    // Similar to Vertical type but instead, we pay attention to the width instead of the height
      _mapHW.clear();
      this->normalizeSymmetries();
      
      HSetState state = HSetState(this);
      while( !state.end() ){ state.next(); }
    //state.print();

      _mapHW = state.getMapHW();
    }

    if (_mapHW.empty()){ cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set a larger toleranceH or toleranceW." << endl; }

  }

  
  pair<float, float> HSlicingNode::setGlobalSize(float height, float width) 
  {
    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;

    HSetState state = HSetState(this, height, width, true);
    while( !state.end() ){ state.next(); }

    this->recursiveSetGlobalSize( state.getBestSet(), finalWidth, finalHeight, height );
  
    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ this->setPreset(Preset); }
  
    return pair<float,float>(_h,_w);
  }

 
  pair<float, float> HSlicingNode::_setGlobalSize(float height, float width) 
  {
    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;

    HSetState state = HSetState(this, height, width, false);
    while( !state.end() ){ state.next(); }

    this->recursiveSetGlobalSize( state.getBestSet(), finalWidth, finalHeight, height );
    
    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ this->setPreset(Preset); }
  
    return pair<float,float>(_h,_w);
  }


  HSlicingNode* HSlicingNode::clone(Flags tr)
  {
    HSlicingNode* node = HSlicingNode::create( this->getAlignment()
                                             , this->getToleranceH()
                                             , this->getToleranceW()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setMapHW(_mapHW.clone());
    node->setPreset(this->getPreset());
    node->cpSymmetries(this->getSymmetries());
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MY){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
    return node;
  }


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  DSlicingNode::DSlicingNode( unsigned int type
                            , MapHW        mapHW
                            , unsigned int alignment
                            , float        w
                            , float        h
                            ):SlicingNode(type, mapHW, alignment, w, h)
  {}


  DSlicingNode::~DSlicingNode(){}
  

  DSlicingNode* DSlicingNode::create( MapHW        mapHW
                                    , unsigned int alignment
                                    , float        w
                                    , float        h
                                    )
  { return new DSlicingNode(Device, mapHW, alignment, w, h); }


  void DSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Device" << endl; 
    if      (this->isAlignLeft  ()){ cout << "Alignment  : Left"    << endl; }
    else if (this->isAlignCenter()){ cout << "Alignment  : Middle"  << endl; }
    else if (this->isAlignRight ()){ cout << "Alignment  : Right"   << endl; }
    else if (this->isAlignTop   ()){ cout << "Alignment  : Top"     << endl; }
    else if (this->isAlignBottom()){ cout << "Alignment  : Bottom"  << endl; }
    else                           { cout << "Alignment  : Unknown" << endl; }
    SlicingNode::print();
  }


  DSlicingNode* DSlicingNode::clone(Flags tr)
  {
    DSlicingNode* node = DSlicingNode::create( _mapHW.clone() 
                                             , this->getAlignment()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setPreset(this->getPreset());
    return node;
  }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHVSlicingNode::RHVSlicingNode( float w
                                , float h
                                ):SlicingNode(Routing, MapHW(), UnknownAlignment, w, h)
  {
    this->setPreset(Preset);
  }


  RHVSlicingNode::~RHVSlicingNode(){}


  void RHVSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Routing space" << endl;
    SlicingNode::print();
  }


  // Error Message Methods
  unsigned int RHVSlicingNode::getAlignment() const
  {
    cerr << " Error(getAlignment () const): Routings do not have centering type." << endl;
    return UnknownAlignment;
  }


  MapHW RHVSlicingNode::getMapHW() const
  {
    cerr << " Error(getMapHW () const): Routings do not have mapHW." << endl;
    return MapHW();
  }


  pair<float,float> RHVSlicingNode::getPairH(float h) const
  {
    cerr << " Error(getPairH (float h) const): Routings do not have mapHW." << endl;
    return pair<float, float> (_h,_w);
  }


  pair<float,float> RHVSlicingNode::getPairW(float w) const
  {
    cerr << " Error(getPairW (float w) const): Routings do not have mapHW." << endl;
    return pair<float, float> (_h,_w);
  }


  void RHVSlicingNode::setPairH (float h)
  {
    cerr << " Error(setPairH (float h)): Routings do not have mapHW." << endl;
  } 


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHSlicingNode::RHSlicingNode(float h):RHVSlicingNode(0,h){}


  RHSlicingNode::~RHSlicingNode(){};


  RHSlicingNode* RHSlicingNode::create(float h)
  { 
    return new RHSlicingNode(h); 
  }


  RHSlicingNode* RHSlicingNode::clone(Flags tr)
  {
    RHSlicingNode* node = RHSlicingNode::create(this->getHeight());
    return node; 
  }


  // Error Methods
  void RHSlicingNode::setWidth(float w)
  {
    cerr << " Error(RHSlicingNode::setWidth(float w)): Routings do not have width." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  RVSlicingNode::RVSlicingNode(float w):RHVSlicingNode(w,0){}


  RVSlicingNode::~RVSlicingNode(){};


  RVSlicingNode* RVSlicingNode::create(float w)
  {
    return new RVSlicingNode(w);
  }

  RVSlicingNode* RVSlicingNode::clone(Flags tr)
  {
    RVSlicingNode* node = RVSlicingNode::create(this->getWidth());
    return node; 
  }


  // Error Methods
  void RVSlicingNode::setHeight(float h)
  {
    cerr << "Error(RVSlicingNode::setHeight(float h)): Routings do not have height." << endl; 
  }

}
