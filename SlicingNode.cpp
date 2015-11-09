#include "SlicingNode.h"

using namespace std;

namespace SlicingTree{


// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  SlicingNode::SlicingNode( SlicingType type
                          , MapHW       mapHW
                          , Alignment   alignment 
                          , float       w        
                          , float       h
                          ):_type(type)
                           ,_alignment(alignment)
                           ,_x(0),_y(0)
                           ,_w(w),_h(h)
  {
    _mapHW = mapHW; 

    if ( (w != 0)&&(h != 0) ){ _preset = true ; }
    else                     { _preset = false; }
  } 


  SlicingNode::~SlicingNode(){}


  void SlicingNode::setPairH(float h)
  {
    pair<float,float> hw = this->getPairH(h);
    _h                   = hw.first;
    _w                   = hw.second;
    }


  void SlicingNode::print() const
  {
    if   (_preset == true){ cout << "preset = True"  << endl; }
    else                  { cout << "preset = False" << endl; }
    cout << "Height = " << _h << endl;
    cout << "Width  = " << _w << endl;
    cout << "X      = " << _x << endl;
    cout << "Y      = " << _y << endl;
    cout << endl;

    if (_type != RoutingNode ){
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
  
// Error Methods
  void SlicingNode::createChild ( SlicingType type     
                                , Alignment   alignment  
                                , float       toleranceH 
                                , float       toleranceW 
                                , float       w          
                                , float       h          
                                )
  {
    cerr << " Error(createChild( SlicingType type, Alignment alignment = UnknownAlignment, float toleranceH = 0, float toleranceW = 0, float w = 0, float h = 0)): DeviceNode and RoutingNode do not have child." << endl; 
  }


  void SlicingNode::createChild( MapHW     mapHW
                               , Alignment alignment
                               , float     w
                               , float     h 
                               )
  {
    cerr << " Error(createChild(MapHW mapHW, Alignment alignment, float w, float h)): DeviceNode and RoutingNode do not have child." << endl; 
  }


  void SlicingNode::createChild(float hw)
  {
    std::cerr << " Error(createChild(float hw): DeviceNode and RoutingNode do not have child." << endl; 
  }


  void SlicingNode::createChild( int childIndex, int copyIndex, Transformation tr)
  {
    std::cerr << " Error(createChild( int childIndex, int copyIndex, Transformation tr)): DeviceNode and RoutingNode do not have child." << endl; 
  }


  int SlicingNode::getNbChild() const
  {
    cerr << " Error(int SlicingNode::getNbChild()): Devices do not have child." << endl;
    return 0;
  }


  SlicingNode* SlicingNode::getChild(int index) const
  {
    cerr << " Error(SlicingNode* SlicingNode::getChild(int index)): Devices do not have child." << endl;
    return NULL;
  }


  const vector<SlicingNode*>& SlicingNode::getChildren() const
  {
    cerr << " Error(vector<SlicingNode*> SlicingNode::getChildren()): Devices do not have child." << endl;
    static vector<SlicingNode*> dummyVectorSlicingNode;
    return dummyVectorSlicingNode;
  }


  void SlicingNode::printChildren()
  {
    cerr << " Error(void DSlicingNode::printChildren()): Devices do not have child." << endl; 
  }


  void SlicingNode::insertNode(SlicingNode* node, int index)
  {
    cerr << " Error(void SlicingNode::insertNode(SlicingNode* node, int index)): Devices do not have child." << endl; 
  }


  void SlicingNode::pushBackNode(SlicingNode* node)
  {
    cerr << " Error(void SlicingNode::pushBackNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::pushFrontNode(SlicingNode* node)
  {
    cerr << " Error(void SlicingNode::pushFrontNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::removeAllNodes()
  {
    cerr << " Error(void SlicingNode::removeAllNodes()): Devices do not have child." << endl; 
  }


  void SlicingNode::removeNode(SlicingNode* node)
  {
    cerr << " Error(void SlicingNode::removeNode(SlicingNode* node)): Devices do not have child." << endl; 
  }


  void SlicingNode::setToleranceH(float tolerance)
  {
    cerr << " Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceH(float tolerance)
  {
    cerr << " Error(void SlicingNode::setToleranceH(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  float SlicingNode::getToleranceH() const
  {
   cerr << " Error(SlicingNode::getToleranceH()): Devices do not have tolerance parameter." << endl;
   return 0;
  }


  void SlicingNode::setToleranceW(float tolerance)
  {
    cerr << " Error(void SlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  void SlicingNode::recursiveSetToleranceW(float tolerance)
  {
    cerr << " Error(void SlicingNode::setToleranceW(float tolerance)): Devices do not have tolerance parameter." << endl; 
  }


  float SlicingNode::getToleranceW() const
  {
   cerr << " Error(SlicingNode::getToleranceW()): Devices do not have tolerance parameter." << endl;
   return 0;
  }


  bool SlicingNode::hasEmptyChildrenMap() const
  {
   cerr << " Error(SlicingNode::hasEmptyChildrenMap()): Devices do not have child." << endl;
   return true;
  } 


  pair<float, float> SlicingNode::setGlobalSize(float height, float width)
  {
    if ( _preset != true      ) { this->setPairH(height); }
    if ( (_h != 0)&&(_w != 0) ) { _preset = true        ; }

    return pair<float, float> (_h,_w); 
  }


  void SlicingNode::setSymmetry(int childIndex, int copyIndex)
  {
    cerr << "SlicingNode::setSymmetry(int childIndex, int copyIndex) : RoutingNodes do not have symmetries." << endl; 
  }


  list<pair<int,int> > SlicingNode::getSymmetries() const
  {
    cerr << "SlicingNode::getSymmetries() const : RoutingNodes do not have symmetries." << endl; 
    return list<pair<int,int> >();
  }


  void SlicingNode::normalizeSymmetries() 
  {
    cerr << "SlicingNode::normalizeSymmetries() const : RoutingNodes do not have symmetries." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  HVSlicingNode::HVSlicingNode( SlicingType type
                              , Alignment   alignment 
                              , float       toleranceH 
                              , float       toleranceW
                              , float       w 
                              , float       h
                              ):SlicingNode(type, MapHW::create(), alignment, w, h)
                               ,_toleranceH(toleranceH)
                               ,_toleranceW(toleranceW){}


  HVSlicingNode::~HVSlicingNode(){}


  void HVSlicingNode::createChild(int childIndex, int copyIndex, Transformation tr)
  {
    if (childIndex != copyIndex){
      
      this->insertNode(this->getChild(childIndex)->clone(tr), copyIndex); 
      _symmetries.push_back(pair<int,int>(min(childIndex, copyIndex),max(childIndex, copyIndex)));
      this->updateGlobalSize();
    }
    else { cerr << "Error(HVSlicingNode::createChild(int childIndex, int copyIndex, Transformation tr)): Indexes cannot be the same." << endl; }
  }


  void HVSlicingNode::printChildren()
  {
    int count = 1;
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (((*it)->getType() == DeviceNode)||((*it)->getType() == RoutingNode)){
        cout << "-- Children: " << count << "/" << _children.size() << " --" << endl;
        (*it)->print(); 
      }
      else {
        cout << "-- Children: " << count << "/" << _children.size() << " --" << endl;
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

      if (((*it)->getType() != DeviceNode)&&((*it)->getType() != RoutingNode))
        { (*it)->recursiveSetToleranceH(tolerance); }
    }
    _toleranceH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceW(float tolerance)
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if (((*it)->getType() != DeviceNode)&&((*it)->getType() != RoutingNode))
        { (*it)->recursiveSetToleranceW(tolerance); }
    }
    _toleranceW = tolerance; 
  }


  bool HVSlicingNode::hasEmptyChildrenMap() const
  {
    bool flag = false;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){

      if (((*it)->getMapHW().empty() != true)&&((*it)->getType() != RoutingNode))
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


  vector< pair<float,float> > HVSlicingNode::initSet()
  {
    vector< pair<float,float> > nextSet;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
        
      if ( (*it)->getType() != RoutingNode ) 
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
    int           endCounter    = 1;
    pair<int,int> symmetry      = pair<int,int>(); // created only for isSymmetry(...) method
    
    modulos.push_back(1);
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
        
      if ( it               != _children.begin() ){ modulos.push_back(modulo); }
      if ( (*it)->getType() != RoutingNode       ){
      // Check if the current child is a symmetry or not

        if ( (!this->isSymmetry(index, symmetry)) && ((*it)->getPreset() != true) ){
          modulo     *= (*it)->getMapHW().size();
          endCounter *= (*it)->getMapHW().size();
        }
      }
      index++;
    }
    modulos.push_back(endCounter);
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
  

// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  VSlicingNode* VSlicingNode::create( Alignment alignment
                                    , float     toleranceH
                                    , float     toleranceW
                                    , float     w
                                    , float     h
                                    )
  {
    return new VSlicingNode(Vertical, alignment, toleranceH, toleranceW, w, h); 
  }
 

  void VSlicingNode::createChild( SlicingType type
                                , Alignment   alignment
                                , float       toleranceH
                                , float       toleranceW
                                , float       w         
                                , float       h
                                )
  {
    if (type == Horizontal)
      { this->pushBackNode(HSlicingNode::create(alignment, toleranceH, toleranceW, w, h)); }

    else if (type == Vertical  )
      { this->pushBackNode(VSlicingNode::create(alignment, toleranceH, toleranceW, w, h)); }

    else 
      { cerr << " Error(void VSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }
  
   
  void VSlicingNode::createChild( MapHW     mapHW
                                , Alignment alignment
                                , float     w        
                                , float     h
                                )
  {
    this->pushBackNode(DSlicingNode::create(mapHW, alignment, w, h)); 
  }


  void VSlicingNode::createChild(float hw)
  {
    this->pushBackNode(RVSlicingNode::create(hw)); 
  } 


  void VSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Vertical"  << endl; 
    if      (_alignment == AlignBottom){ cout << "Alignment  : Bot"     << endl; }
    else if (_alignment == AlignCenter){ cout << "Alignment  : Middle"  << endl; }
    else if (_alignment == AlignTop   ){ cout << "Alignment  : Top"     << endl; }
    else                               { cout << "Alignment  : Unknown" << endl; }
    HVSlicingNode::print();
  }

  
  void VSlicingNode::place(float x, float y)
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
    // Set X,Y Node
      if (((*it)->getType() == Horizontal)||((*it)->getType() == Vertical)){ 
        if ((*it)->getAlignment() == AlignBottom){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        
        else if ((*it)->getAlignment() == AlignCenter){
          (*it)->setX(xref);
          (*it)->setY(yref + (_h/2) - ((*it)->getHeight()/2));
        }
        
        else if ((*it)->getAlignment() == AlignTop){
          (*it)->setX(xref);
          (*it)->setY(yref + _h - (*it)->getHeight());
        }
      }
      
    // Place Node
      if ((*it)->getAlignment() == AlignBottom)
        { (*it)->place(xref, yref); }
      
      else if ((*it)->getAlignment() == AlignCenter) 
        { (*it)->place(xref, yref + (_h/2) - ((*it)->getHeight()/2)); }
      
      else if ((*it)->getAlignment() == AlignTop)
        { (*it)->place(xref, yref +  _h    -  (*it)->getHeight())   ; }
      
      else if ((*it)->getType() == RoutingNode){ (*it)->place(xref, yref); }
      
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
      
    // nextSet represents 1 state of the combinations
      vector< pair<float,float> > nextSet = this->initSet();

      float hmin  = (*_children.begin())->getMapHW().upper_bound(0)->first; // min height from the current combinations
      float hmax  = (*_children.begin())->getMapHW().upper_bound(0)->first; // max height from the current combinations
      
      float                      currentW   = 0;                            // total width of the current combination
      list<pair<float,float> >   currentHs  = list<pair<float,float> >();   // heights from the current combination
      vector<int>                modulos    = this->setModulos();           // vectors of the modulos
      int                        counter    = 1;                            // counter
      int                        endCounter = modulos.back();               // end counter-1
      vector<pair<float,float> > currentSet = vector<pair<float,float> >(); // Current combination
      
      
      while( counter != endCounter+1 ){
        
      // Need to be reset at each loop
        currentW  = 0;
        currentHs.clear();
        
        this->setNextSet( currentW
                        , currentHs
                        , counter
                        , modulos
                        , nextSet
                        , currentSet
                        );
        
      // Set number, determining height max of the combination
        counter++;
        currentHs.sort();
        hmin = currentHs.front().first;
        hmax = currentHs.back().first;

      /* If the difference betwen the highest and the lowest height is allowed:
         1) Check if it's already in the map, yes: next step, no: add combination
         2) Compare previous width and the current width and keep the highest width.
      */
        if ((hmax-hmin) <= _toleranceH){ _mapHW.insertWorst(hmax, currentW); }
      }
    }
    if (_mapHW.empty()) { cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set a larger toleranceH or toleranceW." << endl; }
  }
  

  pair<float, float> VSlicingNode::setGlobalSize(float height, float width)
  {
    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;

  // nextSet represents 1 state of the combinations, make sure that we take into account if the HVSlicingNode is preset.
    vector< pair<float,float> > nextSet = this->initSet();

  /* Best Height [height-toleranceH;height] means: 
     1) Respect the toleranceH 
     2) Closest to the desired Height if not inside of the interval

     Best Width  [width-tolerance> ;Width ] means: 
     1) Respect the toleranceW and have a acceptable height 
     2) Less and closest to Width but higher width are accepted if no lower width but still closest to Width.
  */

    float hmin  = (*_children.begin())->getMapHW().upper_bound(0)->first; // min height from the current combinations
    float hmax  = (*_children.begin())->getMapHW().upper_bound(0)->first; // max height from the current combinations

    float                      bestHeight = 0;                            // Current best Height 
    float                      bestWidth  = 0;                            // Current best Width
    vector<pair<float,float> > bestSet    = vector<pair<float,float> >(); // Current bestPair
    vector<pair<float,float> > currentSet = vector<pair<float,float> >(); // Current combination
      
    list<pair<float,float> >   currentHs  = list<pair<float,float> >();   // heights from the current combination
    vector<int>                modulos    = this->setModulos();           // vectors of the modulos
    int                        counter    = 1;                            // counter
    int                        endCounter = modulos.back();               // end counter-1
    float                      currentW   = 0;                            // total width of the current combination

      
    while( counter != (endCounter+1) ){

    // Need to be reset at each loop
      currentW = 0; 
      currentHs.clear(); 
      currentSet.clear();

      this->setNextSet( currentW
                      , currentHs
                      , counter
                      , modulos
                      , nextSet
                      , currentSet
                      );

    // Set number, determining height max of the combination
      currentHs.sort();
      hmin = currentHs.front().first;
      hmax = currentHs.back().first;

    // Determine the best Height and the best Width
      if ((hmax-hmin) <= _toleranceH){
        this->updateBestSet( currentW , hmax
                           , width    , height
                           , bestWidth, bestHeight
                           , bestSet  , currentSet
                           );
      }
      counter++;
    }
  // If a valid pair is found, propate required sizes to lower hierarchy
    this->recursiveSetGlobalSize( bestSet, finalWidth, finalHeight, height );
  
    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ _preset = true; }

    return pair<float,float>(_h,_w);
  }


  VSlicingNode* VSlicingNode::clone(Transformation tr)
  {
    VSlicingNode* node = VSlicingNode::create( this->getAlignment()
                                             , this->getToleranceH()
                                             , this->getToleranceW()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setMapHW(_mapHW.clone());
    node->setPreset(_preset);
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MX){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
    return node;
  }


  VSlicingNode::VSlicingNode( SlicingType type
                            , Alignment   alignment
                            , float       toleranceH
                            , float       toleranceW
                            , float       w
                            , float       h
                            ):HVSlicingNode(type, alignment, toleranceH, toleranceW, w, h){}


  VSlicingNode::~VSlicingNode(){}


  void VSlicingNode::setNextSet ( float&                       currentW
                                , list  < pair<float,float> >& currentHs
                                , int&                         counter
                                , vector<int>&                 modulos
                                , vector< pair<float,float> >& nextSet
                                , vector< pair<float,float> >& currentSet
                                )
  {
    int           index = 0;
    pair<int,int> symmetry = pair<int,int>();

    vector< pair<float,float> >::iterator itpair  = nextSet.begin();

    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
          
      if ( this->isSymmetry(index, symmetry) ){
        itpair - (symmetry.second - symmetry.first);
        
        if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
        currentSet.push_back((*itpair));
        currentW           += (*itpair).second;
        nextSet[index] = nextSet[symmetry.first];
        
        itpair + (symmetry.second - symmetry.first);
      }
      
      else {
      // Collect the pair<float,float> in vector (size order) and list (sort height) of the combination in order sort them. Calculate the width of the combination.
        if ((*it)->getType() != RoutingNode ) { currentHs.push_back((*itpair)); }
        currentSet.push_back((*itpair));
        currentW += (*itpair).second;
        
      // Go through the different combinations
        if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ((*it)->getPreset() != true)){
          
          if ( (*it)->getMapHW().upper_bound((*itpair).first) != (*it)->getMapHW().end() )
            { nextSet[index] = (*(*it)->getMapHW().upper_bound((*itpair).first)); }
          else
            { nextSet[index] = (*(*it)->getMapHW().begin()); }
        }
      }
      itpair++;
      index++;
    }
  }


  void VSlicingNode::recursiveSetGlobalSize( vector< pair<float,float> >& bestSet
                                           , float&                       finalWidth
                                           , float&                       finalHeight
                                           , float&                       height
                                           )
  {
    if (bestSet.empty() != true){

      pair<float,float> pairreal                = pair<float,float> (0,0);
      vector< pair<float,float> >::iterator it2 = bestSet.begin();

      for (vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++){

        if ((*it3)->getPreset() != true){ pairreal = (*it3)->setGlobalSize(height,(*it2).second)               ; }
        else                            { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth()); }

        finalWidth += pairreal.second;
        if (finalHeight < pairreal.first) { finalHeight = pairreal.first; }
        it2++;
      }
    }
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  HSlicingNode* HSlicingNode::create( Alignment alignment
                                    , float     toleranceH
                                    , float     toleranceW
                                    , float     w
                                    , float     h
                                    )
  {
    return new HSlicingNode(Horizontal, alignment, toleranceH, toleranceW, w, h);
  }


  void HSlicingNode::createChild( SlicingType type
                                , Alignment   alignment
                                , float       toleranceH
                                , float       toleranceW
                                , float       w         
                                , float       h
                                ) 
  {
    if (type == Horizontal)
      { this->pushBackNode(HSlicingNode::create(alignment, toleranceH, toleranceW, w, h)); }

    else if (type == Vertical  )
      { this->pushBackNode(VSlicingNode::create(alignment, toleranceH, toleranceW, w, h)); }

    else 
      { cerr << " Error(void HSlicingNode::createChild(SlicingType type, Alignment alignment, float w, float h)): Unknown type." << endl; }
  }


  void HSlicingNode::createChild( MapHW     mapHW
                                , Alignment alignment
                                , float     w
                                , float     h
                                )
  {
    this->pushBackNode(DSlicingNode::create(mapHW, alignment, w, h));
  }


  void HSlicingNode::createChild(float hw)
  {
    this->pushBackNode(RHSlicingNode::create(hw));
  } 


  void HSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Horizontal" << endl; 
    if      (_alignment == AlignLeft  ){ cout << "Alignment  : Left"    << endl; }
    else if (_alignment == AlignCenter){ cout << "Alignment  : Middle"  << endl; }
    else if (_alignment == AlignRight ){ cout << "Alignment  : Right"   << endl; }
    else                               { cout << "Alignment  : Unknown" << endl; }
    HVSlicingNode::print();
  }


  void HSlicingNode::place(float x, float y)
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 

    // Set X,Y Node
      if (((*it)->getType() == Horizontal)||((*it)->getType() == Vertical)){ 
        if ((*it)->getAlignment() == AlignLeft){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        
        else if ((*it)->getAlignment() == AlignCenter){
          (*it)->setX(xref + (_w/2) - ((*it)->getWidth()/2));
          (*it)->setY(yref);
        }
        
        else if ((*it)->getAlignment() == AlignRight){
          (*it)->setX(xref + _w - (*it)->getWidth());
          (*it)->setY(yref);
        }
      }
      
    // Place Node
      if ((*it)->getAlignment() == AlignLeft)
        { (*it)->place(xref                                 , yref); }
      
      else if ((*it)->getAlignment() == AlignCenter) 
        { (*it)->place(xref + (_w/2) - ((*it)->getWidth()/2), yref); }
      
      else if ((*it)->getAlignment() == AlignRight)
        { (*it)->place(xref + _w     -  (*it)->getWidth()   , yref); }

      else if ((*it)->getType() == RoutingNode){ (*it)->place(xref, yref); }
      
      else { cerr << " Error(place(float x, float y)): Unknown Alignment in SlicingTree." << endl; }
      
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

      vector< pair<float,float> > nextSet = this->initSet();
      this->normalizeSymmetries();
      
      float wmin  = (*_children.begin())->getMapHW().upper_bound(0)->second; 
      float wmax  = (*_children.begin())->getMapHW().upper_bound(0)->second; 
      
      float                      currentH   = 0;
      list<pair<float,float> >   currentWs  = list<pair<float,float> >();
      vector<int>                modulos    = this->setModulos();
      int                        counter    = 1;
      int                        endCounter = modulos.back();
      vector<pair<float,float> > currentSet = vector<pair<float,float> >();
      
      
      while( counter != endCounter+1 ){

        currentH  = 0;
        currentWs.clear();

        this->setNextSet( currentWs
                        , currentH
                        , counter
                        , modulos
                        , nextSet
                        , currentSet
                        );
        currentWs.sort();
        wmin = currentWs.front().first;
        wmax = currentWs.back().first;
        if ((wmax-wmin) <= _toleranceW){ _mapHW.insertWorst(currentH, wmax); }

        counter++;
      }
    }

    if (_mapHW.empty()){ cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set a larger toleranceH or toleranceW." << endl; }

  }

  
  pair<float, float> HSlicingNode::setGlobalSize(float height, float width) 
  {
    this->normalizeSymmetries();
    float finalHeight = 0;
    float finalWidth  = 0;

    vector< pair<float,float> > nextSet = this->initSet();
    
    float wmin = (*_children.begin())->getMapHW().upper_bound(0)->second; 
    float wmax = (*_children.begin())->getMapHW().upper_bound(0)->second; 
    
    float                      bestHeight = 0;
    float                      bestWidth  = 0;
    vector<pair<float,float> > bestSet    = vector<pair<float,float> >();
    vector<pair<float,float> > currentSet = vector<pair<float,float> >();
    
    list<pair<float,float> >   currentWs  = list<pair<float,float> >();
    vector<int>                modulos    = this->setModulos();       
    int                        counter    = 1; 
    int                        endCounter = modulos.back();
    float                      currentH   = 0; 
    
    
    while( counter != (endCounter+1) ){
      
      currentH = 0; 
      currentWs.clear(); 
      currentSet.clear();
      
      this->setNextSet( currentWs
                      , currentH
                      , counter
                      , modulos
                      , nextSet
                      , currentSet
                      );
      currentWs.sort();
      wmin = currentWs.front().first;
      wmax = currentWs.back().first;
      
    // Checkin wmax and wmin difference first. Then check the height and then the most appropriate width.
      if ((wmax-wmin) <= _toleranceW){
        this->updateBestSet( wmax     , currentH
                           , width    , height
                           , bestWidth, bestHeight
                           , bestSet  , currentSet
                           );
      }
      counter++;
    }
    
    this->recursiveSetGlobalSize(bestSet, finalWidth, finalHeight, width);

    _h = finalHeight;
    _w = finalWidth;
    
    if ( (_h == 0)||(_w == 0) ){ cerr << "No solution found. Required height = " << height << " and width = " << width << endl; }
    if ( (_h != 0)&&(_w != 0) ){ _preset = true; }
  
    return pair<float,float>(_h,_w);
  }


  HSlicingNode* HSlicingNode::clone(Transformation tr)
  {
    HSlicingNode* node = HSlicingNode::create( this->getAlignment()
                                             , this->getToleranceH()
                                             , this->getToleranceW()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setMapHW(_mapHW.clone());
    node->setPreset(_preset);
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MY){ node->pushFrontNode((*it)->clone(tr)); }
      else         { node->pushBackNode ((*it)->clone(tr)); }
    }
    return node;
  }


  HSlicingNode::HSlicingNode( SlicingType type
                            , Alignment   alignment
                            , float       toleranceH
                            , float       toleranceW
                            , float       w
                            , float       h
                            ):HVSlicingNode(type, alignment, toleranceH, toleranceW, w, h){}


  HSlicingNode::~HSlicingNode(){}


  void HSlicingNode::setNextSet ( list  < pair<float,float> >& currentWs
                                , float&                       currentH
                                , int&                         counter
                                , vector<int>&                 modulos
                                , vector< pair<float,float> >& nextSet
                                , vector< pair<float,float> >& currentSet
                                )
  {
    int           index = 0;
    pair<int,int> symmetry = pair<int,int>();

    vector< pair<float,float> >::iterator itpair  = nextSet.begin();

    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
              
      if ( this->isSymmetry(index, symmetry) ){
        itpair - (symmetry.second - symmetry.first);
        
        currentSet.push_back((*itpair));
        if ((*it)->getType() != RoutingNode ){ currentWs.push_back(pair<float,float>((*itpair).second, (*itpair).first)); }
        currentH += (*itpair).first;
        nextSet[index] = nextSet[symmetry.first];
        
        itpair + (symmetry.second - symmetry.first);
      }
      
      else {
        currentSet.push_back(pair<float,float>((*itpair).first,(*itpair).second));
        if ((*it)->getType() != RoutingNode ){ currentWs.push_back(pair<float,float>((*itpair).second,(*itpair).first)); }
        currentH += (*itpair).first;
        
        if (( (counter-1)%modulos[index] == modulos[index]-1 ) && ((*it)->getPreset() != true)){
          
          if ( (*it)->getMapHW().upper_bound((*itpair).first) != (*it)->getMapHW().end() )
            { nextSet[index] = (*(*it)->getMapHW().upper_bound((*itpair).first)); }
          else
            { nextSet[index] = (*(*it)->getMapHW().begin()); }
        }
      }
      index++;
      itpair++;
    }
  }


  void HSlicingNode::recursiveSetGlobalSize( vector< pair<float,float> >& bestSet
                                           , float&                       finalWidth
                                           , float&                       finalHeight
                                           , float&                       width
                                           )
  {
    if (bestSet.empty() != true){
      
      pair<float,float> pairreal = pair<float,float> (0,0);
      vector< pair<float,float> >::iterator it2 = bestSet.begin();
      
      for(vector<SlicingNode*>::iterator it3 = _children.begin(); it3 != _children.end(); it3++){
        
        if ((*it3)->getPreset() != true){ pairreal = (*it3)->setGlobalSize((*it2).first,width)                 ; }
        else                            { pairreal = pair<float,float> ((*it3)->getHeight(),(*it3)->getWidth()); }
        
        finalHeight += pairreal.first;
        if (finalWidth < pairreal.second){ finalWidth = pairreal.second; }
        it2++;
      }
    }
  }


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  DSlicingNode* DSlicingNode::create( MapHW     mapHW
                                    , Alignment alignment
                                    , float     w
                                    , float     h
                                    )
  { return new DSlicingNode(DeviceNode, mapHW, alignment, w, h); }


  DSlicingNode::DSlicingNode( SlicingType type
                            , MapHW       mapHW
                            , Alignment   alignment
                            , float       w
                            , float       h
                            ):SlicingNode(type, mapHW, alignment, w, h)
  {
    if ( (w == 0)&&(h == 0) ){
      _h = _mapHW.begin()->first;
      _w = _mapHW.begin()->second;
    }
  }


  DSlicingNode::~DSlicingNode(){}
  

  void DSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Device" << endl; 
    if      (_alignment == AlignLeft  ){ cout << "Alignment  : Left"    << endl; }
    else if (_alignment == AlignCenter){ cout << "Alignment  : Middle"  << endl; }
    else if (_alignment == AlignRight ){ cout << "Alignment  : Right"   << endl; }
    else if (_alignment == AlignTop   ){ cout << "Alignment  : Top"     << endl; }
    else if (_alignment == AlignBottom){ cout << "Alignment  : Bottom"  << endl; }
    else                               { cout << "Alignment  : Unknown" << endl; }
    SlicingNode::print();
  }


  DSlicingNode* DSlicingNode::clone(Transformation tr)
  {
    DSlicingNode* node = DSlicingNode::create( _mapHW.clone() 
                                             , this->getAlignment()
                                             , this->getWidth()
                                             , this->getHeight()
                                             );
    node->setPreset(_preset);
    return node;
  }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHVSlicingNode::RHVSlicingNode( float w
                                , float h
                                ):SlicingNode(RoutingNode, MapHW::create(), UnknownAlignment, w, h)
  {
    _preset = true; 
  }


  RHVSlicingNode::~RHVSlicingNode(){}


  void RHVSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Routing space" << endl;
    SlicingNode::print();
  }


  // Error Message Methods
  Alignment RHVSlicingNode::getAlignment() const
  {
    cerr << " Error(getAlignment () const): RoutingNodes do not have centering type." << endl;
    return UnknownAlignment;
  }


  MapHW RHVSlicingNode::getMapHW() const
  {
    cerr << " Error(getMapHW () const): RoutingNodes do not have mapHW." << endl;
    return MapHW::create();
  }


  void RHVSlicingNode::setPreset(bool preset)
  {
    cerr << " Error(setPreset(bool preset)): RoutingNodes preset is always true." << endl; 
  }


  pair<float,float> RHVSlicingNode::getPairH(float h) const
  {
    cerr << " Error(getPairH (float h) const): RoutingNodes do not have mapHW." << endl;
    return pair<float, float> (_h,_w);
  }


  pair<float,float> RHVSlicingNode::getPairW(float w) const
  {
    cerr << " Error(getPairW (float w) const): RoutingNodes do not have mapHW." << endl;
    return pair<float, float> (_h,_w);
  }


  void RHVSlicingNode::setPairH (float h)
  {
    cerr << " Error(setPairH (float h)): RoutingNodes do not have mapHW." << endl;
  } 


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHSlicingNode::RHSlicingNode(float h):RHVSlicingNode(0,h){}


  RHSlicingNode* RHSlicingNode::clone(Transformation tr)
  {
    RHSlicingNode* node = RHSlicingNode::create(this->getHeight());
    return node; 
  }


  RHSlicingNode::~RHSlicingNode(){};


  // Error Methods
  RHSlicingNode* RHSlicingNode::create(float h){ return new RHSlicingNode(h); }


  void RHSlicingNode::setWidth(float w)
  {
    cerr << " Error(RHVSlicingNode::setHeight(float w)): RoutingNodes do not have width." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  RVSlicingNode::RVSlicingNode(float w):RHVSlicingNode(w,0){}


  RVSlicingNode* RVSlicingNode::clone(Transformation tr)
  {
    RVSlicingNode* node = RVSlicingNode::create(this->getWidth());
    return node; 
  }


  RVSlicingNode::~RVSlicingNode(){};


  // Error Methods
  RVSlicingNode* RVSlicingNode::create(float w)
  {
    return new RVSlicingNode(w);
  }


  void RVSlicingNode::setHeight(float h)
  {
    cerr << " Error(RHVSlicingNode::setHeight(float h)): RoutingNodes do not have height." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : MapHW
// -----------------------------------------------------------------------------------------------//


  MapHW::MapHW( map <float,float>* map1 ):_mapHW(map1){}


  MapHW::~ MapHW(){}


  MapHW MapHW::create( map <float,float>* map1 )
  { 
    if (map1 == NULL) { return MapHW ( new std::map<float,float> () ); }
    else              { return MapHW ( map1                         ); }
  }


  MapHW MapHW::clone ()
  {
    map <float,float>* mapHW = new map <float,float>();
    for (map<float,float>::const_iterator it = _mapHW->begin(); it != _mapHW->end(); it++)
      { mapHW->insert(pair<float,float>((*it).first, (*it).second)); }
    return mapHW;
  }


  bool MapHW::compare ( MapHW map2 )
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


}

