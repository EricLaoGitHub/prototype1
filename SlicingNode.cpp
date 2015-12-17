#include "SlicingNode.h"

using namespace std;

namespace SlicingTree{

  void printPair(pair<float,float> paire){ cout << "H: " << paire.first << ", W: " << paire.second << endl; }  
  void printVectorPair(vector<pair<float, float> > vectorpaire)
  {
    for (vector<pair<float, float> >::iterator it = vectorpaire.begin(); it != vectorpaire.end(); it++)
      { cout << "H: " << it->first << ", W: " << it->second << endl; }
  }
  void printV( vector<size_t> vect )
  {
    cout << "start printV" << endl;
    for (vector<size_t>::iterator it = vect.begin(); it != vect.end(); it++){ 
      cout << "index: " << (*it) << endl;
    }
    cout << "end printV" << endl;
  }


// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  SlicingNode::SlicingNode( unsigned int type
                          , NodeSets     nodeSets
                          , unsigned int alignment 
                          , float        w        
                          , float        h
                          ):_nodeSets(nodeSets)
                           ,_x(0),_y(0)
                           ,_w(w),_h(h)
  {
    _flags = 0;
    this->setType(type);
    this->setAlignment(alignment);

    if ( (w != 0)&&(h != 0) ){ this->setPreset(Preset); }
  } 


  SlicingNode::~SlicingNode(){}


  void SlicingNode::print() const
  {
    if   ( this->isPreset() ){ cout << "preset = True"   << endl; }
    else                     { cout << "preset = False " << endl; }
    cout << "Height = " << _h << endl;
    cout << "Width  = " << _w << endl;
    cout << "X      = " << _x << endl;
    cout << "Y      = " << _y << endl;
    cout << endl;

    cout << "Print - NodeSets:" << endl;
    int index = 0;
    NodeSets node = _nodeSets;
    if ( node.size() == 0){cout << "--- EMPTY ---" << endl;}
    else {
      for (vector <SingleNodeSet*>::const_iterator itPrint = node.begin(); itPrint != node.end(); itPrint++)
        { 
          cout << index << ": \t area: " << (*itPrint)->getOccupationArea() << setprecision(4) <<"%, \t" << " cpt: " << (*itPrint)->getCount() << ", \t H: " << (*itPrint)->getHeight() << ", W: " << (*itPrint)->getWidth() << endl; 
          index++;
        } 
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


// Error Methods
  void SlicingNode::createChild( unsigned int type, unsigned int alignment )
  {
    cerr << "Error(createChild( SlicingType type, Alignment alignment = UnknownAlignment)): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createChild( NodeSets     nodeSets
                               , unsigned int alignment
                               , float        w
                               , float        h 
                               )
  {
    cerr << "Error(createChild(NodeSets nodeSets, Alignment alignment, float w, float h)): Device and Routing do not have child." << endl; 
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


  void SlicingNode::setToleranceRatioH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::setToleranceRatioW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  float SlicingNode::getToleranceRatioH() const
  {
    cerr << "Error(SlicingNode::getToleranceH()): Devices do not have tolerance parameter." << endl;
    return 0;
  }


  float SlicingNode::getToleranceRatioW() const
  {
    cerr << "Error(SlicingNode::getToleranceW()): Devices do not have tolerance parameter." << endl;
    return 0;
  }


  void SlicingNode::recursiveSetToleranceRatioH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceRatioW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceRatioW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  bool SlicingNode::hasEmptyChildrenNodeSets() const
  {
    cerr << "Error(SlicingNode::hasEmptyChildrenNodeSets()): Devices do not have child." << endl;
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


  float SlicingNode::getOccupationArea() const
  {
    cerr << "Error(SlicingNode::getOccupationArea() const) : Occupied Area not possible for Routing and Devices." << endl; 
    return 100;
  }


  void SlicingNode::setToleranceBandH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceBandH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::setToleranceBandW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceBandW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  float SlicingNode::getToleranceBandH() const
  {
    cerr << "Error(SlicingNode::getToleranceBandH()): Devices do not have tolerance parameter." << endl;
    return 0;
  }


  float SlicingNode::getToleranceBandW() const
  {
    cerr << "Error(SlicingNode::getToleranceBandW()): Devices do not have tolerance parameter." << endl;
    return 0;
  }


  void SlicingNode::setTolerances(float trh, float trw, float tbh, float tbw)
  {
    cerr << "Error(void SlicingNode::setTolerances(float trh, float trw, float tbh, float tbw)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceBandH(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceBandH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceBandW(float tolerance)
  {
    cerr << "Error(void SlicingNode::setToleranceBandW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  HVSlicingNode::HVSlicingNode( unsigned int type, unsigned int alignment ):SlicingNode(type, NodeSets(), alignment, 0, 0)
  {
    _toleranceRatioH = 0;
    _toleranceRatioW = 0;
    _toleranceBandH = 0;
    _toleranceBandW = 0;
  }


  HVSlicingNode::~HVSlicingNode(){}


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


  void  HVSlicingNode::recursiveSetToleranceRatioH(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceRatioH(tolerance); }
    }
    _toleranceRatioH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceRatioW(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceRatioW(tolerance); }
    }
    _toleranceRatioW = tolerance; 
  }


  bool HVSlicingNode::hasEmptyChildrenNodeSets() const
  {
    bool flag = false;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      if ( (node.empty() != true) && (!(*it)->isRouting()) )
        { if (node.empty() == true) {flag = true;} }
    }
    return flag;
  }


  void HVSlicingNode::setSymmetry(int childIndex, int copyIndex)
  {
    if (childIndex != copyIndex){
      NodeSets node = this->getChild(childIndex)->getNodeSets();
      if (node.compare( this->getChild(copyIndex)->getNodeSets() ) == true)
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


  void HVSlicingNode::setTolerances(float trh, float trw, float tbh, float tbw)
  {
    _toleranceRatioH = trh;
    _toleranceRatioW = trw;
    _toleranceBandH = tbh;
    _toleranceBandW = tbw;
  }



  void  HVSlicingNode::recursiveSetToleranceBandH(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceBandH(tolerance); }
    }
    _toleranceBandH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceBandW(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceBandW(tolerance); }
    }
    _toleranceBandW = tolerance; 
  }


  void SlicingNode::setGlobalSize2 ( float height, float width )
  {
    if ( !this->isPreset() ) { 
      _h = height;
      _w = width;
    }
    if ( (_h != 0) && (_w != 0) ) { this->setPreset(Preset) ; }
  }


  void SlicingNode::_setGlobalSize2 ( float height, float width )
  {
    if ( !this->isPreset() ) { 
      _h = height;
      _w = width;
    }
    if ( (_h != 0) && (_w != 0) ) { this->setPreset(Preset) ; }
  }


  void HVSlicingNode::_setGlobalSize2 ( float height, float width )
  {
    _h = height;
    _w = width;
    if ( (_h != 0) && (_w != 0) ) { this->setPreset(Preset) ; }
    
    int index = 0;
    print();
    vector<SingleNodeSet*>::const_iterator itSet1  = _nodeSets.find(height, width);
    vector<SingleNodeSet*>                 vecSet1 =  (*itSet1)->getSet();
    vector<SingleNodeSet*>::const_iterator itSet   = vecSet1.begin();

    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
      (*it)->_setGlobalSize2((*itSet)->getHeight(), (*itSet)->getWidth());
      itSet++;
    }
  }


  void HVSlicingNode::setGlobalSize2 ( float height, float width )
  {
    if ( _nodeSets.empty() != true ){
      vector<SingleNodeSet*>::const_iterator it     = _nodeSets.begin();
      vector<SingleNodeSet*>::const_iterator itBest = _nodeSets.begin();
      float bestH = (*it)->getHeight();
      float bestW = (*it)->getWidth();
      float currentH = 0;
      float currentW = 0;

      while (it != _nodeSets.end()){
        currentH = (*it)->getHeight();
        currentW = (*it)->getWidth();
      
        if ((currentH <= height)&&(currentW <= width)){
          if ( ((height-currentH) <= _toleranceRatioH) && ((height-bestH) <= _toleranceRatioH) ) {
            if (currentW > bestW){ 
              itBest = it;
              bestH = currentH;
              bestW = currentW;
            }
          } else if (currentH > bestH) {
            itBest = it;
            bestH = currentH;
            bestW = currentW;
          }
        }
        it++;
      } 

      int index = 0;
      cout << "START: On fait des TESTS " << endl;
      (*itBest)->print();
      cout << "END: On fait des TESTS " << endl;
      index = 0;


      vector<SingleNodeSet*>::const_iterator itSet = (*itBest)->getSet().begin();
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
        (*it)->_setGlobalSize2((*itSet)->getHeight(), (*itSet)->getWidth());
        itSet++;
        index++;
      }

      _h = bestH;
      _w = bestW;
      if ( (_h == 0)||(_w == 0) ){ cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
      if ( (_h != 0)&&(_w != 0) ){ this->setPreset(Preset); }

    } else  { cerr << "NodeSets empty. UpdateGlobalSize needs to be used first or with higher tolerances." << endl; }
  }

// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//

  
  VSlicingNode::VSlicingNode( unsigned int type, unsigned int alignment ):HVSlicingNode(type, alignment){}


  VSlicingNode::~VSlicingNode(){}


  VSlicingNode* VSlicingNode::create( unsigned int alignment )
  {
    return new VSlicingNode(Vertical, alignment); 
  }
 

  void VSlicingNode::createChild( unsigned int type, unsigned int alignment )
  {
    if (type == Horizontal) {
      HSlicingNode* hsn = HSlicingNode::create(alignment);
      hsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      this->pushBackNode(hsn);
    }

    else if (type == Vertical) { 
      VSlicingNode* vsn = VSlicingNode::create(alignment);
      vsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      this->pushBackNode(vsn); 
    }

    else 
      { cerr << " Error(void HVSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }

   
  void VSlicingNode::createChild( NodeSets     nodeSets
                                , unsigned int alignment
                                , float        w        
                                , float        h
                                )
  {
    this->pushBackNode(DSlicingNode::create(nodeSets, alignment, w, h)); 
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
    else                           { cout << "Alignment  : Unknown" << endl; }
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
      _nodeSets = (*_children.begin())->getNodeSets();
      cerr << "Error(void HVSlicingNode::updateGlobalSize()): You have a HVSlicingNode with only 1 child. This is an incorrect way to use HVSlicingNodes." << endl; 
    }
    else if (this->hasEmptyChildrenNodeSets() != true){  
      _nodeSets.clear();
      this->normalizeSymmetries();
      
      VSetState state = VSetState(this);
      while( !state.end() ){ state.next(); }

      _nodeSets = state.getNodeSets();
    }
    if (_nodeSets.empty()) { cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set larger tolerances." << endl; }
  }


  VSlicingNode* VSlicingNode::clone(Flags tr)
  {
    VSlicingNode* node = VSlicingNode::create( this->getAlignment() );
    node->setTolerances( getToleranceRatioH()
                       , getToleranceRatioW()
                       , getToleranceBandH()
                       , getToleranceBandW()
                       );
    node->setWidth(getWidth());
    node->setHeight(getHeight());
    node->setNodeSets(_nodeSets.clone());
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


  HSlicingNode::HSlicingNode( unsigned int type, unsigned int alignment ):HVSlicingNode(type, alignment){}


  HSlicingNode::~HSlicingNode(){}


  HSlicingNode* HSlicingNode::create( unsigned int alignment )
  {
    return new HSlicingNode(Horizontal, alignment);
  }


  void HSlicingNode::createChild( unsigned int type, unsigned int alignment )
  {
    if (type == Horizontal) {
      HSlicingNode* hsn = HSlicingNode::create(alignment);
      hsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      this->pushBackNode(hsn);
    }

    else if (type == Vertical) { 
      VSlicingNode* vsn = VSlicingNode::create(alignment);
      vsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      this->pushBackNode(vsn); 
    }

    else 
      { cerr << " Error(void HVSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }

  void HSlicingNode::createChild( NodeSets     nodeSets
                                , unsigned int alignment
                                , float        w
                                , float        h
                                )
  {
    this->pushBackNode(DSlicingNode::create(nodeSets, alignment, w, h));
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
    
    if (x == 0) { }
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
      _nodeSets = (*_children.begin())->getNodeSets();
      cerr << "Error(void HVSlicingNode::updateGlobalSize()): You have a HVSlicingNode with only 1 child. This is an incorrect way to use HVSlicingNodes." << endl; 
    }

    else if (this->hasEmptyChildrenNodeSets() != true){     
    // Similar to Vertical type but instead, we pay attention to the width instead of the height
      _nodeSets.clear();
      this->normalizeSymmetries();
      
      HSetState state = HSetState(this);
      while( !state.end() ){ state.next(); }

      _nodeSets = state.getNodeSets();
    }

    if (_nodeSets.empty()){ cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set larger tolerances." << endl; }

  }


  HSlicingNode* HSlicingNode::clone(Flags tr)
  {
    HSlicingNode* node = HSlicingNode::create( this->getAlignment() );
    node->setTolerances( getToleranceRatioH()
                       , getToleranceRatioW()
                       , getToleranceBandH()
                       , getToleranceBandW()
                       );
    node->setWidth(getWidth());
    node->setHeight(getHeight());
    node->setNodeSets(_nodeSets.clone());
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
                            , NodeSets     nodeSets
                            , unsigned int alignment
                            , float        w
                            , float        h
                            ):SlicingNode(type, nodeSets, alignment, w, h)
  {}


  DSlicingNode::~DSlicingNode(){}
  

  DSlicingNode* DSlicingNode::create( NodeSets     nodeSets
                                    , unsigned int alignment
                                    , float        w
                                    , float        h
                                    )
  { return new DSlicingNode(Device, nodeSets, alignment, w, h); }


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
    DSlicingNode* node = DSlicingNode::create( _nodeSets.clone() 
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


  RHVSlicingNode::RHVSlicingNode( float h
                                , float w
                                ):SlicingNode(Routing, NodeSets(), UnknownAlignment, w, h)
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


  void RHVSlicingNode::_setGlobalSize2 ( float height, float width ){}


// Error Message Methods
  unsigned int RHVSlicingNode::getAlignment() const
  {
    cerr << " Error(getAlignment () const): Routings do not have centering type." << endl;
    return UnknownAlignment;
  }


  NodeSets RHVSlicingNode::getNodeSets() const
  {
    cerr << " Error(getNodeSets() const): Routings do not have different dimensions." << endl;
    return NodeSets();
  }


  pair<float,float> RHVSlicingNode::getPairH(float h) const
  {
    cerr << " Error(getPairH (float h) const): Routings do not have different dimensions." << endl;
    return pair<float, float> (_h,_w);
  }


  pair<float,float> RHVSlicingNode::getPairW(float w) const
  {
    cerr << " Error(getPairW (float w) const): Routings do not have different dimensions." << endl;
    return pair<float, float> (_h,_w);
  }


  void RHVSlicingNode::setPairH(float h)
  {
    cerr << " Error(setPairH (float h)): Routings do not have different dimensions." << endl;
  } 


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHSlicingNode::RHSlicingNode(float h):RHVSlicingNode(h,0)
  {
    _nodeSets.push_back(RHSingleNodeSet::create(h));
  }


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


  RVSlicingNode::RVSlicingNode(float w):RHVSlicingNode(0,w)
  {
    _nodeSets.push_back(RVSingleNodeSet::create(w));
  }


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


// -----------------------------------------------------------------------------------------------//
// Class : HVSetState
// -----------------------------------------------------------------------------------------------//
  

  HVSetState::HVSetState( HVSlicingNode* node ):_children(node->getChildren())
                                               ,_symmetries(node->getSymmetries())
                                               ,_toleranceRatioH(node->getToleranceRatioH())
                                               ,_toleranceRatioW(node->getToleranceRatioW())
                                               ,_toleranceBandH(node->getToleranceBandH())
                                               ,_toleranceBandW(node->getToleranceBandW())
  {
    _hminWmin   = pair<float,float>(0,0);
    _hminWmax   = pair<float,float>(0,0);
    _hmaxWmin   = pair<float,float>(0,0);
    _hmaxWmax   = pair<float,float>(0,0);
    _wminHmin   = pair<float,float>(0,0);
    _wminHmax   = pair<float,float>(0,0);
    _wmaxHmin   = pair<float,float>(0,0);
    _wmaxHmax   = pair<float,float>(0,0);
    _currentSet = vector<size_t> ();
    _nextSet    = vector<size_t> ();
    _nodeSets   = NodeSets();
    _counter    = 1;

    initSet();
    initModulos();
  }


  HVSetState::~HVSetState(){}


  void HVSetState::initSet()
  {
     _nextSet.clear();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 
      if ( (*it)->isPreset() ) { 
        _nextSet.push_back((*it)->getNodeSets().findIndex((*it)->getHeight(), (*it)->getWidth())); 
      }
      else { 
        _nextSet.push_back(0); 
      }
    }
    _currentSet = _nextSet;

  }


  void HVSetState::initModulos()
  {
    int modulo = 1;
    int index  = 0;
    
    _modulos.clear();
    _modulos.push_back(1);
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        
      if ( it != _children.begin() ){ _modulos.push_back(modulo); }
      if ( (!isSymmetry(index)) && (!(*it)->isPreset()) ){
        NodeSets node = (*it)->getNodeSets();
        modulo *= node.size();
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
    vector<size_t>::iterator it2 = _currentSet.begin();
    int index = 0;
    cout << "--------------------------------currentSet:" << endl;
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      cout << index << ": H = " << node[(*it2)]->getHeight();
      cout << ", W = " << node[(*it2)]->getWidth() << endl;
      it2++;
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
    
    _nodeSets.print();
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


  const NodeSets HVSetState::getNodeSets()
  {
    _nodeSets.sort();
    return _nodeSets.clone();
  }


  void HVSetState::next()
  {
    int           index    = 0;
    pair<int,int> symmetry = pair<int,int>();
    vector<size_t>::iterator itpair = _nextSet.begin();

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( this->isSymmetry(index, symmetry) ){ (*itpair) = _nextSet[symmetry.first]; }
      else {
        if ( (((_counter-1)%_modulos[index]) == _modulos[index]-1) && (!(*it)->isPreset()) ) {
          NodeSets node = (*it)->getNodeSets();
          if ( (*itpair)+1 != node.size() ) { (*itpair)++  ; }
          else                              { (*itpair) = 0; }
        }
      }
      index++;
      itpair++;
    }
    _counter += 1;
    _currentSet = _nextSet;
  }


// -----------------------------------------------------------------------------------------------//
// Class : VSetState
// -----------------------------------------------------------------------------------------------//
  

  VSetState::VSetState( VSlicingNode* node ):HVSetState(node) {}


  VSetState::~VSetState(){}


  void VSetState::next()
  {
    push_back(); 
    HVSetState::next();
  }


  float VSetState::getMinH ()
  {
    float hmin = 0;
    if (!_currentSet.empty()) {
      vector< size_t >::const_iterator it2 = _currentSet.begin();
      vector<SlicingNode*>::iterator it = _children.begin();

      while( (hmin == 0) && (it != _children.end()) ){
        NodeSets node1 = (*it)->getNodeSets();
        if ( node1[(*it2)]->getHeight() != 0 )
          { hmin = node1[(*it2)]->getHeight(); }
        it++;
        it2++;
      }

      it2 = _currentSet.begin();
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        NodeSets node2 = (*it)->getNodeSets();
        if ( (node2[(*it2)]->getHeight() < hmin)&&(node2[(*it2)]->getHeight() != 0) )
          { hmin = node2[(*it2)]->getHeight(); }
          it2++;
      }
    }
    return hmin;  
  }


  float VSetState::getCurrentH()
  {
    float currentH = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      if (node[(*it2)]->getHeight() > currentH)
        { currentH = node[(*it2)]->getHeight(); }
      it2++;
    }

    return currentH;
  }


  float VSetState::getCurrentW()
  {
    float currentW = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      currentW += node[(*it2)]->getWidth(); 
      it2++;
    }
    return currentW;
  }


  void VSetState::print()
  {
    HVSetState::print();
    cout << "currentH = " << getCurrentH() << endl;
    cout << "currentW = " << getCurrentW() << endl;
    cout << endl;
  }



  void VSetState::push_back()
  {
    if ( checkToleranceBandH() ) {
      vector<SingleNodeSet*> vect = vector<SingleNodeSet*>();
      vector<size_t>::iterator it2 = _currentSet.begin();
    
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        NodeSets node = (*it)->getNodeSets();
        vect.push_back(node[(*it2)]);
        it2++;
      }
      _nodeSets.push_back(VSingleNodeSet::create(vect));
    }
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//
  

  HSetState::HSetState( HSlicingNode* node ):HVSetState(node) {}


  HSetState::~HSetState(){}

  
  void HSetState::next()
  {
    push_back(); 
    updateLimits(); 
    HVSetState::next();
  }


  float HSetState::getMinW()
  {
    float wmin = 0;
    if (!_currentSet.empty()) { 
      vector< size_t >::const_iterator it2 = _currentSet.begin();
      vector<SlicingNode*>::iterator it = _children.begin();
      
      while( (wmin == 0) && (it != _children.end()) ){
        NodeSets node = (*it)->getNodeSets();
        if ( node[(*it2)]->getWidth() != 0 )
          { wmin = node[(*it2)]->getWidth(); }
        it++;
        it2++;
      }

      it2 = _currentSet.begin();
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        NodeSets node = (*it)->getNodeSets();
        if ( (node[(*it2)]->getWidth() < wmin)&&(node[(*it2)]->getWidth() != 0) )
          { wmin = node[(*it2)]->getWidth(); }
          it2++;
      }
    }
    return wmin;  
  }


  float HSetState::getCurrentW()
  {
    float currentW = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      if (node[(*it2)]->getWidth() > currentW)
        { currentW = node[(*it2)]->getWidth(); }
      it2++;
    }
    return currentW;
  }


  float HSetState::getCurrentH()
  {
    float currentH = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      NodeSets node = (*it)->getNodeSets();
      currentH += node[(*it2)]->getHeight(); 
      it2++;
    }

    return currentH;
  }


  void HSetState::print()
  {
    HVSetState::print();
    cout << "currentH = " << getCurrentH() << endl;
    cout << "currentW = " << getCurrentW() << endl;
    cout << endl;
  }


  void HSetState::push_back()
  {
    if ( checkToleranceBandW() ) {
      vector<SingleNodeSet*> vect = vector<SingleNodeSet*>();
      vector<size_t>::iterator it2 = _currentSet.begin();
    
      for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
        NodeSets node = (*it)->getNodeSets();
        vect.push_back(node[(*it2)]);
        it2++;
      }
      _nodeSets.push_back(HSingleNodeSet::create(vect));
    }
  }


// -----------------------------------------------------------------------------------------------//
// Class : NodeSets
// -----------------------------------------------------------------------------------------------//
  
  NodeSets::NodeSets()
  {
    _nodeSets.clear();
  }
  

  NodeSets::NodeSets(const NodeSets& other)
  {
    _nodeSets = other.getNodeSets();
  }


  NodeSets::~NodeSets(){}


  void NodeSets::push_back(SingleNodeSet* singleSet)
  { 
    if( this->find(singleSet) == _nodeSets.end() ){ _nodeSets.push_back(singleSet); }
    else { (*find(singleSet))->incrementCount(); }
    
  }


  std::pair<float,float> NodeSets::getPairH(float h) const 
  {
    float w        = 0;
    float hclosest = 0;

    for (vector<SingleNodeSet*>::const_iterator itHW = _nodeSets.begin(); itHW != _nodeSets.end(); itHW++){ 
      if ( ((*itHW)->getHeight() > hclosest) && (h >= (*itHW)->getHeight()) ){
        hclosest = (*itHW)->getHeight();
        w        = (*itHW)->getWidth();
      }
    }
    
    if ( (w == 0) && (hclosest == 0) ){ cerr << "No solution for h = " << h << " has been found." << endl; }
    return pair<float,float>(hclosest,w);
  }
  
  pair<float,float> NodeSets::getPairHW(float height, float width) const 
  {
    vector<SingleNodeSet*>::const_iterator it = _nodeSets.begin();
    float bestH = (*it)->getHeight();
    float bestW = (*it)->getWidth();
    float currentH = 0;
    float currentW = 0;

    while (it != _nodeSets.end()){
      currentH = (*it)->getHeight();
      currentW = (*it)->getWidth();

      if (currentH <= height){
        if ( currentH > bestH ){
          bestH = currentH;
          bestW = currentW;
        } else if (currentH == bestH){
          if ( (currentW > bestW) && (currentW <= width) ){ 
            bestH = currentH;
            bestW = currentW;
          }
          else if ( (currentW < bestW) && (bestW > width) ){ 
            bestH = currentH;
            bestW = currentW;
          }
        }
        it++;
      } else {
        it = _nodeSets.end();
      }
    }
    return pair<float,float>(bestH, bestW);
  }

  void NodeSets::print() const 
  {
    cout << "Print - NodeSets:" << endl;
    int index = 0;
    if (_nodeSets.size() == 0){cout << "--- EMPTY ---" << endl;}
    else {
      for (vector <SingleNodeSet*>::const_iterator itPrint = _nodeSets.begin(); itPrint != _nodeSets.end(); itPrint++)
        { 
          cout << index << ": cpt: " << (*itPrint)->getCount() << ", H: " << (*itPrint)->getHeight() << ", W: " << (*itPrint)->getWidth() << endl; 
          index++;
        } 
      cout << endl;
    }
  }


  NodeSets NodeSets::clone() 
  {
    NodeSets nodesets = NodeSets();
    for (vector<SingleNodeSet*>::iterator it = _nodeSets.begin(); it != _nodeSets.end(); it++)
      { nodesets.push_back((*it)); }
    return nodesets;
  }


  bool NodeSets::compare( NodeSets nodeSets2 ) 
  {
    bool comp = true;
    if (_nodeSets.size() != nodeSets2.size()) { comp = false; }

    if (comp == true) {
      vector<SingleNodeSet*>::iterator it2 = nodeSets2.begin();
      for (vector<SingleNodeSet*>::iterator it1 = _nodeSets.begin(); it1 != _nodeSets.end(); it1++){

        if ( ((*it1)->getHeight() != (*it2)->getHeight())||((*it1)->getWidth() != (*it2)->getWidth()) ){ comp = false; }
        if (it2 != nodeSets2.end()){ it2++; }
      }
    }
    return comp;
  }


  int NodeSets::findIndex(float height, float width) const
  {
    bool end = false;
    int indextbd = 0;
    int index    = 0;
    vector<SingleNodeSet* >::const_iterator it = _nodeSets.begin();
    while(end == false){
      if ( ((*it)->getHeight() == height) && ((*it)->getWidth() == width) ){
        indextbd = index;
        end = true;
      }
      index++;
      it++;
      if (it == _nodeSets.end()){ end = true; }
    }
    return indextbd;
  }


  SingleNodeSet* NodeSets::operator[](size_t i) 
  {
    vector<SingleNodeSet* >::iterator it = _nodeSets.begin();
    it += i;
    return (*it); 
  }
  

  vector<SingleNodeSet* >::iterator NodeSets::find ( SingleNodeSet* singleSet )
  {
    vector<SingleNodeSet* >::iterator it = _nodeSets.begin();
    vector<SingleNodeSet* >::iterator itFind = _nodeSets.end();
    if ( (_nodeSets.empty() != true)&&(singleSet != NULL) ){

      while(it != _nodeSets.end()){
        if ( ((*it)->getHeight() == singleSet->getHeight())&&((*it)->getWidth() == singleSet->getWidth()) ){ 
          itFind = it;
          it = _nodeSets.end(); 
        }
        else { it++; }
      }
    } else {
      it = _nodeSets.end();
    }

    return itFind;
  }


  vector<SingleNodeSet* >::iterator NodeSets::find ( float height, float width )
  { 
    vector<SingleNodeSet* >::iterator it = _nodeSets.begin();
    vector<SingleNodeSet* >::iterator itFind = _nodeSets.end();
    
    if (_nodeSets.empty() != true){

      while(it != _nodeSets.end()){
        if ( ((*it)->getHeight() == height)&&((*it)->getWidth() == width) ){ 
          itFind = it;
          it     = _nodeSets.end(); 
        }
        else { it++; }
        if ( it == _nodeSets.end() ){ it = _nodeSets.end(); }
      }
    } else {
      it = _nodeSets.end();
    }

    return itFind;
  }


// -----------------------------------------------------------------------------------------------//
// Class : SingleNodeSet
// -----------------------------------------------------------------------------------------------//


  SingleNodeSet::SingleNodeSet( float height, float width ):_height(height), _width(width),_cpt(1){}


  SingleNodeSet::SingleNodeSet( SingleNodeSet* singleSet ):_height(singleSet->getHeight()), _width(singleSet->getWidth()),_cpt(singleSet->getCount()){}


  SingleNodeSet::~SingleNodeSet(){}


  void SingleNodeSet::print() const 
  {
    cout << "Print - SingleNodeSet" << endl;
    cout << "cpt: " << _cpt << ", H: " << _height << ", W: " << _width << endl;
  }


  const vector< SingleNodeSet*>& SingleNodeSet::getSet () const
  {
    cerr << "Error(vector< SingleNodeSet*> getSet () const): DSingleNodeSet and RHVSingleNodeSet do not have vector of sets." << endl;
    static const vector< SingleNodeSet*> test = vector< SingleNodeSet*> ();
    return test;
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSingleNodeSet
// -----------------------------------------------------------------------------------------------//
                                       

  HVSingleNodeSet::HVSingleNodeSet(vector< SingleNodeSet*> dimensionSet):SingleNodeSet(),_dimensionSet(dimensionSet)
  {}
                                       

  HVSingleNodeSet::HVSingleNodeSet(HVSingleNodeSet* singleSet):SingleNodeSet(singleSet),_dimensionSet(singleSet->getSet()){}


  HVSingleNodeSet::~HVSingleNodeSet(){}


  void HVSingleNodeSet::print() const 
  {
    int index = 0;
    cout << "start Print - HVSingleNodeSet, ";
    cout << "Total Height: " << getHeight() << " and Total Width: " << getWidth() << endl;
    for (vector< SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){ 
    //cout << index << ": H: " << (*it)->getHeight() << ", W: " << (*it)->getWidth() << endl;
      (*it)->print();
      index++;
    }
    cout << "end Print - HVSingleNodeSet, ";
    cout << "Total Height: " << getHeight() << " and Total Width: " << getWidth() << endl;
  }


  float HVSingleNodeSet::getDevicesArea() const
  {
    float area = 0;
    for (vector<SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){ 
      area += (*it)->getDevicesArea();
    }
    return area;
  }

  
// -----------------------------------------------------------------------------------------------//
// Class : VSingleNodeSet
// -----------------------------------------------------------------------------------------------//

  VSingleNodeSet::VSingleNodeSet(vector<SingleNodeSet*> dimensionSet):HVSingleNodeSet(dimensionSet)
  {
    calculateHeight();
    calculateWidth();
  }


  VSingleNodeSet::VSingleNodeSet(VSingleNodeSet* singleSet):HVSingleNodeSet(singleSet){}


  VSingleNodeSet::~VSingleNodeSet(){}


  VSingleNodeSet* VSingleNodeSet::create(vector<SingleNodeSet*> dimensionSet)
  { 
    return new VSingleNodeSet(dimensionSet); 
  }


  void VSingleNodeSet::calculateHeight()
  {
    float currentH = 0;
    for (vector< SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      if (currentH < (*it)->getHeight()){ currentH = (*it)->getHeight(); }
    }
    _height = currentH;
  }


  void VSingleNodeSet::calculateWidth()
  {
    float currentW = 0;
    for (vector< SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      currentW += (*it)->getWidth();
    }
    _width = currentW;
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  HSingleNodeSet::HSingleNodeSet(vector< SingleNodeSet*> dimensionSet):HVSingleNodeSet(dimensionSet)
  {
    calculateHeight();
    calculateWidth();
  }


  HSingleNodeSet::HSingleNodeSet(HSingleNodeSet* singleSet):HVSingleNodeSet(singleSet){}
  

  HSingleNodeSet::~HSingleNodeSet(){}


  HSingleNodeSet* HSingleNodeSet::create(vector< SingleNodeSet*> dimensionSet)
  { 
    return new HSingleNodeSet(dimensionSet); 
  }


  void HSingleNodeSet::calculateHeight() 
  {
    float currentH = 0;
    for (vector< SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      currentH += (*it)->getHeight();
    }
    _height = currentH;
  }


  void HSingleNodeSet::calculateWidth()
  {
    float currentW = 0;
    for (vector< SingleNodeSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      if (currentW < (*it)->getWidth()){ currentW = (*it)->getWidth(); }
    }
    _width = currentW;
  }


// -----------------------------------------------------------------------------------------------//
// Class : DSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  DSingleNodeSet::DSingleNodeSet(float height, float width):SingleNodeSet( height, width ){}


  DSingleNodeSet::DSingleNodeSet(DSingleNodeSet* singleSet):SingleNodeSet(singleSet){}


  DSingleNodeSet::~DSingleNodeSet(){}


  DSingleNodeSet* DSingleNodeSet::create(float height, float width)
  { 
    return new DSingleNodeSet(height, width); 
  }
  

// -----------------------------------------------------------------------------------------------//
// Class : RHVSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  RHVSingleNodeSet::RHVSingleNodeSet(float height, float width):SingleNodeSet(height, width){}


  RHVSingleNodeSet::RHVSingleNodeSet(RHVSingleNodeSet* singleSet):SingleNodeSet(singleSet){}


  RHVSingleNodeSet::~RHVSingleNodeSet(){}


// -----------------------------------------------------------------------------------------------//
// Class : RHSingleNodeSet
// -----------------------------------------------------------------------------------------------//
  
  
  RHSingleNodeSet::RHSingleNodeSet(float height):RHVSingleNodeSet(height, 0){}


  RHSingleNodeSet::RHSingleNodeSet(RHSingleNodeSet* singleSet):RHVSingleNodeSet(singleSet){}

  
  RHSingleNodeSet::~RHSingleNodeSet(){}


  RHSingleNodeSet* RHSingleNodeSet::create(float height)
  {
    return new RHSingleNodeSet ( height );
  }


// -----------------------------------------------------------------------------------------------//
// Class : RVSingleNodeSet
// -----------------------------------------------------------------------------------------------//
  
  
  RVSingleNodeSet::RVSingleNodeSet(float width):RHVSingleNodeSet(0, width){}


  RVSingleNodeSet::RVSingleNodeSet(RVSingleNodeSet* singleSet):RHVSingleNodeSet(singleSet){}

  
  RVSingleNodeSet::~RVSingleNodeSet(){}


  RVSingleNodeSet* RVSingleNodeSet::create(float width)
  {
    return new RVSingleNodeSet ( width );
  }

}
