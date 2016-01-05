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
// Class : BoxSet
// -----------------------------------------------------------------------------------------------//


  BoxSet::BoxSet( float height, float width ): _height( height )
                                             , _width ( width  )
                                             , _cpt   ( 1      ){}


  BoxSet::BoxSet( BoxSet* boxSet ): _height( boxSet->getHeight() )
                                  , _width ( boxSet->getWidth()  )
                                  ,_cpt    ( boxSet->getCpt()  ){}


  BoxSet::~BoxSet(){}


  void BoxSet::print() const 
  {
    cout << "Print - BoxSet" << endl;
    cout << "cpt: " << _cpt << ", H: " << _height << ", W: " << _width << endl;
  }


  const vector<BoxSet*>& BoxSet::getSet() const
  {
    cerr << "Error(vector< BoxSet*> getSet () const): DBoxSet and RHVBoxSet do not have vector of BoxSets." << endl;
    static const vector<BoxSet*> boxSet = vector<BoxSet*> ();
    return boxSet;
  }


  void BoxSet::destroy()
  {
    delete(this);
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVBoxSet
// -----------------------------------------------------------------------------------------------//
                                       

  HVBoxSet::HVBoxSet( vector<BoxSet*> dimensionSet, float height, float width ): BoxSet       ( height, width )
                                                                               ,_dimensionSet ( dimensionSet  ){}
                                       

  HVBoxSet::HVBoxSet( HVBoxSet* boxSet ): BoxSet        ( boxSet           )
                                        , _dimensionSet ( boxSet->getSet() ){}


  HVBoxSet::~HVBoxSet(){}


  void HVBoxSet::print() const 
  {
    int index = 0;
    cout << "Print - HVBoxSet, ";
    cout << "Total Height: " << getHeight() << " and Total Width: " << getWidth() << endl;

    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){ 
      cout << index << ": H: " << (*it)->getHeight() << ", W: " << (*it)->getWidth() << endl;
      index++;
    }
  }


  float HVBoxSet::getDevicesArea() const
  {
    float area = 0;
    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){ 
      area += (*it)->getDevicesArea();
    }
    return area;
  }

  
// -----------------------------------------------------------------------------------------------//
// Class : VBoxSet
// -----------------------------------------------------------------------------------------------//

  int VBoxSet::_count    = 0;
  int VBoxSet::_countAll = 0;


  VBoxSet::VBoxSet( vector<BoxSet*> dimensionSet, float height, float width ): HVBoxSet( dimensionSet, height, width )
  {
    if ( (_height == 0) && (_width == 0) ){
      calculateHeight();
      calculateWidth ();
    }
  }


  VBoxSet::VBoxSet( VBoxSet* boxSet ): HVBoxSet( boxSet ){}


  VBoxSet::~VBoxSet(){}


  VBoxSet* VBoxSet::create( vector<BoxSet*> dimensionSet, float height, float width  )
  {
    _count++;
    _countAll++;
    return new VBoxSet( dimensionSet, height, width ); 
  }


  VBoxSet* VBoxSet::clone()
  {
    return VBoxSet::create( getSet(), getHeight(), getWidth() );
  }


  void VBoxSet::calculateHeight()
  {
    float currentH = 0;
    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      if (currentH < (*it)->getHeight()){ currentH = (*it)->getHeight(); }
    }
    _height = currentH;
  }


  void VBoxSet::calculateWidth()
  {
    float currentW = 0;
    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      currentW += (*it)->getWidth();
    }
    _width = currentW;
  }


  void VBoxSet::destroy()
  {
    _count--;
    BoxSet::destroy();
  }


// -----------------------------------------------------------------------------------------------//
// Class : HBoxSet
// -----------------------------------------------------------------------------------------------//


  int HBoxSet::_count    = 0;
  int HBoxSet::_countAll = 0;


  HBoxSet::HBoxSet( vector< BoxSet*> dimensionSet, float height, float width  ): HVBoxSet( dimensionSet, height, width )
  {
    if ( (_height == 0) && (_width == 0) ){
      calculateHeight();
      calculateWidth();
    }
  }


  HBoxSet::HBoxSet( HBoxSet* boxSet ): HVBoxSet( boxSet ){}
  

  HBoxSet::~HBoxSet(){}


  HBoxSet* HBoxSet::create( vector< BoxSet*> dimensionSet, float height, float width  )
  {
    _count++;
    _countAll++;
    return new HBoxSet( dimensionSet, height, width ); 
  }


  HBoxSet* HBoxSet::clone()
  {
    return HBoxSet::create( getSet(), getHeight(), getWidth() );
  }


  void HBoxSet::calculateHeight() 
  {
    float currentH = 0;
    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      currentH += (*it)->getHeight();
    }
    _height = currentH;
  }


  void HBoxSet::calculateWidth()
  {
    float currentW = 0;
    for (vector<BoxSet*>::const_iterator it = _dimensionSet.begin(); it != _dimensionSet.end(); it++){
      if (currentW < (*it)->getWidth()){ currentW = (*it)->getWidth(); }
    }
    _width = currentW;
  }


  void HBoxSet::destroy()
  {
    _count--;
    BoxSet::destroy();
  }


// -----------------------------------------------------------------------------------------------//
// Class : DBoxSet
// -----------------------------------------------------------------------------------------------//


  int DBoxSet::_count    = 0;
  int DBoxSet::_countAll = 0;


  DBoxSet::DBoxSet( float height, float width ): BoxSet( height, width ){}


  DBoxSet::DBoxSet( DBoxSet* boxSet ): BoxSet( boxSet ){}


  DBoxSet::~DBoxSet(){}


  DBoxSet* DBoxSet::create( float height, float width )
  {
    _count++;
    _countAll++;
    return new DBoxSet( height, width ); 
  }


  DBoxSet* DBoxSet::clone()
  {
    return DBoxSet::create( getHeight(), getWidth() ); 
  }


  void DBoxSet::destroy()
  {
    _count--;
    BoxSet::destroy();
  }
  

// -----------------------------------------------------------------------------------------------//
// Class : RHVBoxSet
// -----------------------------------------------------------------------------------------------//


  int RHVBoxSet::_count    = 0;
  int RHVBoxSet::_countAll = 0;


  RHVBoxSet::RHVBoxSet( float height, float width ): BoxSet( height, width ){}


  RHVBoxSet::RHVBoxSet( RHVBoxSet* boxSet ): BoxSet( boxSet ){}


  RHVBoxSet::~RHVBoxSet(){}


  void RHVBoxSet::destroy()
  {
    _count--;
    delete(this);
  }


// -----------------------------------------------------------------------------------------------//
// Class : RVBoxSet
// -----------------------------------------------------------------------------------------------//
  
  
  RVBoxSet::RVBoxSet( float width ): RHVBoxSet( 0, width ){}


  RVBoxSet::RVBoxSet( RVBoxSet* boxSet ): RHVBoxSet( boxSet ){}

  
  RVBoxSet::~RVBoxSet(){}


  RVBoxSet* RVBoxSet::create( float width )
  {
    _count++;
    _countAll++;
    return new RVBoxSet( width );
  }


  RVBoxSet* RVBoxSet::clone()
  {
    return RVBoxSet::create( getWidth() ); 
  }


// -----------------------------------------------------------------------------------------------//
// Class : RHBoxSet
// -----------------------------------------------------------------------------------------------//
  
  
  RHBoxSet::RHBoxSet( float height ): RHVBoxSet( height, 0 ){}


  RHBoxSet::RHBoxSet( RHBoxSet* boxSet ): RHVBoxSet( boxSet ){}

  
  RHBoxSet::~RHBoxSet(){}


  RHBoxSet* RHBoxSet::create( float height )
  {
    _count++;
    _countAll++;
    return new RHBoxSet ( height );
  }


  RHBoxSet* RHBoxSet::clone()
  {
    return RHBoxSet::create( getHeight() ); 
  }


// -----------------------------------------------------------------------------------------------//
// Class : NodeSets
// -----------------------------------------------------------------------------------------------//


  NodeSets::NodeSets()
  {
    _nodeSets.clear();
  }
  

  NodeSets::NodeSets( const NodeSets& other )
  {
    _nodeSets = other.getNodeSets();
  }


  NodeSets::~NodeSets(){}


  BoxSet* NodeSets::operator[]( size_t i ) 
  {
    vector<BoxSet*>::iterator it = _nodeSets.begin();
    it += i;
    return (*it); 
  }


  void NodeSets::clear() 
  {
    if ( _nodeSets.empty() != true ){
      for (vector<BoxSet*>::iterator it = _nodeSets.begin(); it != _nodeSets.end(); it++){
        (*it)->destroy();
      }
      _nodeSets.clear();
    }
  }


  pair<float,float> NodeSets::getPairH( float height ) const 
  {
    float w        = 0;
    float hclosest = 0;

    for (vector<BoxSet*>::const_iterator itHW = _nodeSets.begin(); itHW != _nodeSets.end(); itHW++){ 

      if ( ((*itHW)->getHeight() > hclosest) && (height >= (*itHW)->getHeight()) ){
        hclosest = (*itHW)->getHeight();
        w        = (*itHW)->getWidth();
      }
    }
    
    if ( (w == 0) && (hclosest == 0) )
      { cerr << "Error(pair<float,float> NodeSets::getPairH(float height) const): No solution for h = " << height << " has been found." << endl; }

    return pair<float,float>(hclosest, w);
  }
 

  pair<float,float> NodeSets::getPairHW( float height, float width ) const 
  {
    vector<BoxSet*>::const_iterator it = _nodeSets.begin();
    float bestH    = (*it)->getHeight();
    float bestW    = (*it)->getWidth();
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


  int NodeSets::findIndex( float height, float width ) const
  {
    bool end     = false;
    int indextbd = 0;
    int index    = 0;
    vector<BoxSet*>::const_iterator it = _nodeSets.begin();

    while(end == false){
      if ( ((*it)->getHeight() == height) && ((*it)->getWidth() == width) ){
        indextbd = index;
        end      = true;
      }
      index++;
      it++;
      if (it == _nodeSets.end()){ end = true; }
    }

    return indextbd;
  }


  vector<BoxSet* >::iterator NodeSets::find( float height, float width )
  {
    vector<BoxSet* >::iterator it     = _nodeSets.begin();
    vector<BoxSet* >::iterator itFind = _nodeSets.end();
    
    if (_nodeSets.empty() != true){

      while(it != _nodeSets.end()){
        if ( ((*it)->getHeight() == height) && ((*it)->getWidth() == width) ){ 
          itFind = it;
          it     = _nodeSets.end(); 
        }
        else { it++; }
        if ( it == _nodeSets.end() ){ it = _nodeSets.end(); }
      }
    } else { it = _nodeSets.end(); }

    return itFind;
  }


  vector<BoxSet* >::iterator NodeSets::find( BoxSet* boxSet )
  {
    vector<BoxSet* >::iterator it     = _nodeSets.begin();
    vector<BoxSet* >::iterator itFind = _nodeSets.end();

    if ( (_nodeSets.empty() != true) && (boxSet != NULL) ){

      while(it != _nodeSets.end()){
        if ( ((*it)->getHeight() == boxSet->getHeight()) && ((*it)->getWidth() == boxSet->getWidth()) ){ 
          itFind = it;
          it     = _nodeSets.end(); 
        }
        else { it++; }
      }
    } else { it = _nodeSets.end(); }

    return itFind;
  }


  void NodeSets::print() const 
  {
    cout << "Print - NodeSets:" << endl;
    int index = 0;
    if (_nodeSets.size() == 0){ cout << "--- EMPTY ---" << endl; }
    else {
      for (vector <BoxSet*>::const_iterator itPrint = _nodeSets.begin(); itPrint != _nodeSets.end(); itPrint++){ 
        cout << index << ": cpt: " << (*itPrint)->getCpt() << ", H: " << (*itPrint)->getHeight() << ", W: " << (*itPrint)->getWidth() << endl; 
        index++;
      } 
      cout << endl;
    }
  }


  bool NodeSets::compare( NodeSets nodeSets2 ) const
  {
    bool comp = true;
    if (_nodeSets.size() != nodeSets2.size()) { comp = false; }

    if (comp == true) {
      vector<BoxSet*>::const_iterator it2 = nodeSets2.begin();
      for (vector<BoxSet*>::const_iterator it1 = _nodeSets.begin(); it1 != _nodeSets.end(); it1++){

        if ( ((*it1)->getHeight() != (*it2)->getHeight()) || ((*it1)->getWidth() != (*it2)->getWidth()) )
          { comp = false; }
        if (it2 != nodeSets2.end())                          
          { it2++; }
      }
    }

    return comp;
  }


  void NodeSets::push_back( BoxSet* boxSet )
  {
    if( this->find(boxSet) == _nodeSets.end() ){ _nodeSets.push_back(boxSet);       }
    else { 
      (*find(boxSet))->incrementCpt(); 
      boxSet->destroy();
    }
  }


  void NodeSets::push_back( vector<BoxSet*> vect, float height, float width, unsigned int type )
  {
    if( this->find(height, width) == _nodeSets.end() ){ 
      if (type == Horizontal){
        _nodeSets.push_back(HBoxSet::create(vect, height, width));     
      } 
      else if (type == Vertical){
        _nodeSets.push_back(VBoxSet::create(vect, height, width));   
      }    
    }
    else { 
      (*find(height, width))->incrementCpt(); 
    }
  }


  NodeSets NodeSets::clone() 
  {
    NodeSets nodesets = NodeSets();
    for (vector<BoxSet*>::iterator it = _nodeSets.begin(); it != _nodeSets.end(); it++)
      { 
        nodesets.push_back((*it)->clone()); 
      }
    return nodesets;
  }


// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  SlicingNode::SlicingNode( unsigned int type
                          , NodeSets     nodeSets
                          , unsigned int alignment    
                          , float        height
                          , float        width   
                          ):_nodeSets(nodeSets)
                           ,_x(0)          , _y(0)
                           ,_height(height), _width(width)
  {
    _flags = 0;
    _parent = NULL;
    this->setType(type);
    this->setAlignment(alignment);

    if ( (_width != 0) && (_height != 0) ){ 
      this->setPreset(Preset); 
      this->setSet(Set);
    }
  } 


  SlicingNode::~SlicingNode(){}
  

  SlicingNode* SlicingNode::getRoot() 
  { 
    SlicingNode* parent = this;
    if (_parent != NULL){ parent = _parent->getRoot(); }
    return parent; 
  }


  void SlicingNode::setPairH( float height )
  {
    pair<float,float> hw = this->getPairH(height);
    _height              = hw.first;
    _width               = hw.second;
  }

  
  void SlicingNode::clearParentsNodeSets()
  {
    if ( _parent != NULL ){ _parent->clearParentsNodeSets(); }
    _nodeSets.clear();
  }


  void SlicingNode::resetSlicingTree()
  {
    clearParentsNodeSets();
    getRoot()->_resetSlicingTree();
  }


  void SlicingNode::_resetSlicingTree()
  {
    _x = 0;
    _y = 0;
    setPlaced(false);
    
    if ( isPreset() == false ){
      _height = 0;
      _width  = 0;
      setSet(false);
    }
  }


  void SlicingNode::print() const
  {
    printParent();
    if   ( this->isPreset() ){ cout << "Preset     : True"   << endl; }
    else                     { cout << "Preset     : False " << endl; }
    if   ( this->isSet() )   { cout << "Set        : True"   << endl; }
    else                     { cout << "Set        : False " << endl; }
    if   ( this->isPlaced() ){ cout << "Placed     : True"   << endl; }
    else                     { cout << "Placed     : False " << endl; }
    cout << "Height     : " << _height << endl;
    cout << "Width      : " << _width << endl;
    cout << "X          : " << _x << endl;
    cout << "Y          : " << _y << endl;

    cout << "Print - NodeSets:" << endl;
    int index = 0;
    NodeSets node = _nodeSets;
    if ( node.size() == 0){cout << "--- EMPTY ---" << endl;}
    else {
      for (vector<BoxSet*>::const_iterator itPrint = node.begin(); itPrint != node.end(); itPrint++)
        { 
          cout << index << ": \t area: " << setprecision(4) << (*itPrint)->getOccupationArea() <<"%, \t" << " cpt: " << (*itPrint)->getCpt() << ", \t H: " << (*itPrint)->getHeight() << ", W: " << (*itPrint)->getWidth() << endl; 
          index++;
        } 
      cout << endl;
    }
  }

  void SlicingNode::printParent() const 
  {
    if (_parent != NULL){
      unsigned int type = _parent->getType();
      if      ( type == Horizontal ){ cout << "Parent     : Type: Horizontal" ; }
      else if ( type == Vertical   ){ cout << "Parent     : Type: Vertical"   ; }
      else                          { cout << "Parent     : Type: UnknownType"; }
      cout << ", H: " << _parent->getHeight();
      cout << ", W: " << _parent->getWidth();
      cout << ", X: " << _parent->getX();
      cout << ", Y: " << _parent->getY() <<  endl;
    } else {
      cout << "Parent     : None " << endl;
    }
  }


  void SlicingNode::place( float x, float y )
  {
    _x = x;
    _y = y;
    setPlaced(Placed);
  }


  void SlicingNode::_place( float x, float y )
  {
    SlicingNode::place(x,y);
  }


  void SlicingNode::setGlobalSize( float height, float width )
  {
    if ( !this->isPreset() ) {
      _height = height;
      _width  = width;
    }
    if ( (_height != 0) && (_width != 0) ) { this->setSet(Set) ; }
  }


  void SlicingNode::_setGlobalSize( float height, float width )
  {
    SlicingNode::setGlobalSize(height, width);
  }


  void SlicingNode::preDestroy()
  {
    if ( _parent != NULL ){
      _parent->removeNode(this);
    }
    _nodeSets.clear();
  }


  void SlicingNode::destroy()
  {
    SlicingNode::preDestroy();
    delete(this);
  }


  void SlicingNode::preRecursiveDestroy()
  {
    SlicingNode::preDestroy();
  }


  void SlicingNode::recursiveDestroy()
  {
    SlicingNode::preRecursiveDestroy();
    delete(this);
  }


// Error Methods
  float SlicingNode::getToleranceRatioH() const
  {
    cerr << "Error(SlicingNode::getToleranceH()): Device and Routing do not have tolerance parameters." << endl;
    return 0;
  }


  float SlicingNode::getToleranceRatioW() const
  {
    cerr << "Error(SlicingNode::getToleranceW()): Device and Routing do not have tolerance parameters." << endl;
    return 0;
  }


  void SlicingNode::setToleranceRatioH( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceH( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::setToleranceRatioW( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceW( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  float SlicingNode::getToleranceBandH() const
  {
    cerr << "Error(SlicingNode::getToleranceBandH()): Device and Routing do not have tolerance parameters." << endl;
    return 0;
  }


  float SlicingNode::getToleranceBandW() const
  {
    cerr << "Error(SlicingNode::getToleranceBandW()): Device and Routing do not have tolerance parameters." << endl;
    return 0;
  }


  void SlicingNode::setToleranceBandH( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceBandH( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::setToleranceBandW( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceBandW(float tolerance)): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::recursiveSetToleranceRatioH( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceH( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::recursiveSetToleranceRatioW( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceRatioW( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::recursiveSetToleranceBandH( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceBandH( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::recursiveSetToleranceBandW( float tolerance )
  {
    cerr << "Error(void SlicingNode::setToleranceBandW( float tolerance )): Device and Routing do not have tolerance parameters." << endl; 
  }


  void SlicingNode::setTolerances( float trh, float trw, float tbh, float tbw )
  {
    cerr << "Error(void SlicingNode::setTolerances( float trh, float trw, float tbh, float tbw )): Device and Routing do not have tolerance parameters." << endl; 
  }


  bool SlicingNode::hasEmptyChildrenNodeSets() const
  {
    cerr << "Error(bool SlicingNode::hasEmptyChildrenNodeSets()): Device and routing do not have child." << endl;
    return true;
  } 


  const vector<SlicingNode*>& SlicingNode::getChildren() const
  {
    cerr << "Error(vector<SlicingNode*> SlicingNode::getChildren()): Device and Routing do not have child." << endl;
    static vector<SlicingNode*> dummyVectorSlicingNode;
    return dummyVectorSlicingNode;
  }


  SlicingNode* SlicingNode::getChild( int index ) const
  {
    cerr << "Error(SlicingNode* SlicingNode::getChild(int index)): Device and Routing do not have child." << endl;
    return NULL;
  }


  int SlicingNode::getChildIndex( SlicingNode* node ) const
  {
    cerr << "Error(int SlicingNode::getChildIndex( SlicingNode* node )): Device and Routing do not have child." << endl;
    return 0;
  }


  int SlicingNode::getNbChild() const
  {
    cerr << "Error(int SlicingNode::getNbChild()): Device and Routing do not have child." << endl;
    return 0;
  }


  void SlicingNode::createChild( unsigned int type, unsigned int alignment )
  {
    cerr << "Error(void createChild( SlicingType type, Alignment alignment = UnknownAlignment)): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createChild( NodeSets     nodeSets
                               , unsigned int alignment
                               , float        height 
                               , float        width
                               )
  {
    cerr << "Error(void createChild( NodeSets nodeSets, Alignment alignment, float height, float width )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createChild( int childIndex, int copyIndex, unsigned int tr )
  {
    std::cerr << "Error(createChild( int childIndex, int copyIndex, unsigned int tr )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::createRouting( float space )
  {
    std::cerr << "Error(void createChild( float space )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::insertNode( SlicingNode* node, int index )
  {
    cerr << "Error(void SlicingNode::insertNode( SlicingNode* node, int index )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::push_back( SlicingNode* node )
  {
    cerr << "Error(void SlicingNode::push_back( SlicingNode* node )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::push_front( SlicingNode* node )
  {
    cerr << "Error(void SlicingNode::push_front( SlicingNode* node )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::removeNode( SlicingNode* node )
  {
    cerr << "Error(void SlicingNode::removeNode( SlicingNode* node )): Device and Routing do not have child." << endl; 
  }


  void SlicingNode::removeAllNodes()
  {
    cerr << "Error(void SlicingNode::removeAllNodes()): Device and Routing do not have child." << endl; 
  }


  list<pair<int,int> > SlicingNode::getSymmetries() const
  {
    cerr << "Error(list<pair<int,int> > SlicingNode::getSymmetries() const) : Device and Routing do not have symmetries." << endl; 
    return list<pair<int,int> >();
  }


  void SlicingNode::setSymmetries( list<pair<int,int> > sym )
  {
    cerr << "Error(void SlicingNode::setSymmetries( list<pair<int,int> > sym )) : Device and Routing do not have symmetries." << endl; 
  }


  bool SlicingNode::isSymmetry( int index, std::pair<int,int>& symmetry )
  {
    cerr << "Error(bool SlicingNode::isSymmetry( int index, std::pair<int,int>& symmetry )) : Device and Routing do not have symmetries." << endl; 
    return false;
  }


  bool SlicingNode::isSymmetry( int index )
  {
    cerr << "Error(bool SlicingNode::isSymmetry( int index )) : Device and Routing do not have symmetries." << endl; 
    return false;
  }


  void SlicingNode::addSymmetry( int childIndex, int copyIndex )
  {
    cerr << "Error(void SlicingNode::addSymmetry( int childIndex, int copyIndex )) : Device and Routing do not have symmetries." << endl; 
  }


  void SlicingNode::removeSymmetry( int index )
  {
    cerr << "Error(void SlicingNode::removeSymmetry( int index )) : Device and Routing do not have symmetries." << endl; 
  }


  void SlicingNode::normalizeSymmetries() 
  {
    cerr << "Error(void SlicingNode::normalizeSymmetries() const) : Device and Routing do not have symmetries." << endl; 
  }


  void SlicingNode::printChildren() const
  {
    cerr << "Error(void SlicingNode::printChildren() const): Device and Routing do not have child." << endl; 
  }


  float SlicingNode::getOccupationArea() const
  {
    cerr << "Error(float SlicingNode::getOccupationArea() const) : Occupied Area is not relevant for Routing and Devices." << endl; 
    return 100;
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  HVSlicingNode::HVSlicingNode( unsigned int type, unsigned int alignment ): SlicingNode( type, NodeSets(), alignment, 0, 0 )
  {
    _toleranceRatioH = 0;
    _toleranceRatioW = 0;
    _toleranceBandH  = 0;
    _toleranceBandW  = 0;
  }


  HVSlicingNode::~HVSlicingNode(){}


  void  HVSlicingNode::recursiveSetToleranceRatioH( float tolerance )
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceRatioH(tolerance); }
    }
    _toleranceRatioH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceRatioW( float tolerance )
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceRatioW(tolerance); }
    }
    _toleranceRatioW = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceBandH( float tolerance )
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceBandH(tolerance); }
    }
    _toleranceBandH = tolerance; 
  }


  void  HVSlicingNode::recursiveSetToleranceBandW( float tolerance )
  {
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){

      if ( (!(*it)->isDevice()) && (!(*it)->isRouting()) )
        { (*it)->recursiveSetToleranceBandW(tolerance); }
    }
    _toleranceBandW = tolerance; 
  }


  void HVSlicingNode::setTolerances( float trh, float trw, float tbh, float tbw )
  {
    _toleranceRatioH = trh;
    _toleranceRatioW = trw;
    _toleranceBandH  = tbh;
    _toleranceBandW  = tbw;
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


  int HVSlicingNode::getChildIndex( SlicingNode* node ) const
  {
    int i = 0;
    vector<SlicingNode*>::const_iterator it = _children.begin();
    while (it != _children.end()){
      if (  ((*it)->getType()   == node->getType()  )
         && ((*it)->getHeight() == node->getHeight()) 
         && ((*it)->getWidth () == node->getWidth ()) 
         && ((*it)->getX()      == node->getX()     ) 
         && ((*it)->getY()      == node->getY()     ) 
         )
        { it = _children.end(); }
      else { 
        i++;
        it++;
      }
    }
    return i;
  }

  void HVSlicingNode::createChild( unsigned int type, unsigned int alignment )
  {
    if (type == Horizontal) {
      HSlicingNode* hsn = HSlicingNode::create(alignment);
      hsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      push_back(hsn);
      resetSlicingTree();
    }

    else if (type == Vertical) { 
      VSlicingNode* vsn = VSlicingNode::create(alignment);
      vsn->setTolerances( getToleranceRatioH()
                        , getToleranceRatioW()
                        , getToleranceBandH()
                        , getToleranceBandW()
                        );
      push_back(vsn); 
      resetSlicingTree();
    }
    else 
      { cerr << " Error(void HVSlicingNode::createChild(SlicingType type, Alignment alignment)): Unknown type." << endl; }
  }   


  void HVSlicingNode::createChild( NodeSets     nodeSets
                                 , unsigned int alignment
                                 , float        height
                                 , float        width      
                                 )
  {
    DSlicingNode* node = DSlicingNode::create( nodeSets, alignment, height, width );
    node->setParent(this);
    this->push_back(node); 
    resetSlicingTree();
  }
  

  void HVSlicingNode::createChild( int childIndex, int copyIndex, unsigned int tr )
  {
    if (childIndex != copyIndex){
      
      SlicingNode* node = this->getChild(childIndex)->clone(tr);
      this->insertNode( node, copyIndex ); 
      _symmetries.push_back( pair<int,int>(min(childIndex, copyIndex), max(childIndex, copyIndex)) );
      resetSlicingTree();
    }
    else { cerr << "Error(void HVSlicingNode::createChild( int childIndex, int copyIndex, unsigned int tr )): Indexes cannot be the same." << endl; }
  }  


  void HVSlicingNode::insertNode( SlicingNode* node, int index )
  {
    vector<SlicingNode*>::iterator it = _children.begin();
    for (int i = 0; i < index; i++){ if (it != _children.end()){ it++; } }
    _children.insert(it,node);
    node->setParent(this);
    resetSlicingTree();
  }


  void HVSlicingNode::push_back( SlicingNode* node ) 
  {
    node->setParent(this);
    _children.push_back(node); 
    resetSlicingTree();
  }


  void HVSlicingNode::push_front( SlicingNode* node ) 
  {
    node->setParent(this);
    _children.insert(_children.begin(), node); 
    resetSlicingTree();
  }


  void HVSlicingNode::removeNode( SlicingNode* node ) 
  {
    int index = 0;
    bool found = false;
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 
      if (  ((*it)->getType()   == node->getType()  )
         && ((*it)->getHeight() == node->getHeight()) 
         && ((*it)->getWidth () == node->getWidth ()) 
         && ((*it)->getX()      == node->getX()     ) 
         && ((*it)->getY()      == node->getY()     ) 
         )
        {  
          _children.erase(it); 
          found = true;
        } 
      else { index++; }
    }
    if (found == true){
      removeSymmetry(index);
      resetSlicingTree();
      node->removeParent();
      node->setX(0);
      node->setY(0);
      node->setPlaced(false);
    }
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


  void HVSlicingNode::addSymmetry( int childIndex, int copyIndex )
  {
    if (childIndex != copyIndex){
      NodeSets node = this->getChild(childIndex)->getNodeSets();
      if (node.compare( this->getChild(copyIndex)->getNodeSets() ) == true )
        { 
          _symmetries.push_back( pair<int,int>(min(childIndex, copyIndex), max(childIndex, copyIndex)) ); 
          resetSlicingTree();
        }
      else
        { cerr << "Error(void HVSlicingNode::addSymmetry( int childIndex, int copyIndex )): Child are not the same, symmetry cannot be set." << endl; }
    }
    else { cerr << "Error(void HVSlicingNode::addSymmetry( int childIndex, int copyIndex )): Indexes cannot be the same." << endl; }
  }

  
  void HVSlicingNode::removeSymmetry( int index )
  {
    list<pair<int,int> >::iterator it = _symmetries.begin();

    while( it != _symmetries.end() ){
      if (((*it).first == index) || ((*it).second == index) ){
        list<pair<int,int> >::iterator itToerase = it;
        it++;
        _symmetries.erase(itToerase);
        resetSlicingTree();
      } 
      else { 
        if   ((*it).first > index) { it = _symmetries.end(); }
        else                       { it++;                   }
      }
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


  void HVSlicingNode::_resetSlicingTree()
  {
    _x = 0;
    _y = 0;
    setPlaced(false);
    
    if ( isPreset() == false ){
      _height = 0;
      _width  = 0;
      setSet(false);
      
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
        (*it)->_resetSlicingTree();
      }
    }
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


  void HVSlicingNode::printChildren() const
  {
    int count = 0;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
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


  bool HVSlicingNode::recursiveCheckSet() const
  {
    bool isSet = this->isSet();   
    if (isSet){
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
        isSet = (*it)->recursiveCheckSet(); 
      }
    }
    return isSet;
  }


  bool HVSlicingNode::recursiveCheckPlaced() const
  {
    bool isPlaced = this->isPlaced();
    if (isPlaced){
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){ 
        isPlaced = (*it)->recursiveCheckPlaced(); 
      }
    }
    return isPlaced;
  }


  int HVSlicingNode::getLeafNumber() const
  {
    int cpt = 0;
    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++)
      { cpt += (*it)->getLeafNumber(); }
    return cpt;  
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
    if(recursiveCheckPlaced())
      {
        estimation = getDevicesArea()/(getHeight() * getWidth())*100;
      }
    else { cerr << "Error(float HVSlicingNode::getSpaceEstimation()): SlicingNodes dimensions need to be set first before being estimated." << endl; }
    return estimation;
  }


  void HVSlicingNode::setGlobalSize ( float height, float width )
  {
    if ( _nodeSets.empty() != true ){
      vector<BoxSet*>::const_iterator it     = _nodeSets.begin();
      vector<BoxSet*>::const_iterator itBest = _nodeSets.begin();
      float bestH    = (*it)->getHeight();
      float bestW    = (*it)->getWidth();
      float currentH = 0;
      float currentW = 0;

      while (it != _nodeSets.end()){
        currentH = (*it)->getHeight();
        currentW = (*it)->getWidth();
      
        if ( (currentH <= height) && (currentW <= width) ){
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
      vector<BoxSet*>::const_iterator itSet = (*itBest)->getSet().begin();
      for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
        (*it)->_setGlobalSize( (*itSet)->getHeight(), (*itSet)->getWidth() );
        itSet++;
        index++;
      }
      _height = bestH;
      _width  = bestW;
      this->setSet(Set); 

    } else  { cerr << "NodeSets empty. UpdateGlobalSize needs to be used first or with higher tolerances." << endl; }
  }


  void HVSlicingNode::_setGlobalSize ( float height, float width )
  {
    _height = height;
    _width  = width;
    if ( (_height != 0) && (_width != 0) ) { this->setSet(Set) ; }
    
    vector<BoxSet*>::const_iterator itSet1  = _nodeSets.find(height, width);
    vector<BoxSet*>                 vecSet1 =  (*itSet1)->getSet();
    vector<BoxSet*>::const_iterator itSet   = vecSet1.begin();

    for (vector<SlicingNode*>::const_iterator it = _children.begin(); it != _children.end(); it++){
      (*it)->_setGlobalSize((*itSet)->getHeight(), (*itSet)->getWidth());
      itSet++;
    }
  }


  void HVSlicingNode::preDestroy()
  {
    SlicingNode::preDestroy();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      (*it)->removeParent();
    }
  }


  void HVSlicingNode::destroy()
  {
    HVSlicingNode::preDestroy();
    delete(this);
  }


  void HVSlicingNode::preRecursiveDestroy()
  {
    SlicingNode::preRecursiveDestroy();
    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if ( ((*it)->getType() == Horizontal) || ((*it)->getType() == Vertical) ){
        (*it)->removeParent();
        (*it)->recursiveDestroy();
      } else {
        (*it)->removeParent();
        (*it)->destroy();
      }
    }
  }


  void HVSlicingNode::recursiveDestroy()
  {
    HVSlicingNode::preRecursiveDestroy();
    delete(this);
  }



// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  int VSlicingNode::_count    = 0;
  int VSlicingNode::_countAll = 0;

  
  VSlicingNode::VSlicingNode( unsigned int type, unsigned int alignment ): HVSlicingNode( type, alignment ){}


  VSlicingNode::~VSlicingNode(){}


  VSlicingNode* VSlicingNode::create( unsigned int alignment )
  {
    _count++;
    _countAll++;
    return new VSlicingNode( Vertical, alignment ); 
  }


  void VSlicingNode::createRouting( float space )
  {
    this->push_back(RVSlicingNode::create( space )); 
    resetSlicingTree();
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


  VSlicingNode* VSlicingNode::clone( unsigned int tr )
  {
    VSlicingNode* node = VSlicingNode::create( this->getAlignment() );
    node->setTolerances( getToleranceRatioH()
                       , getToleranceRatioW()
                       , getToleranceBandH()
                       , getToleranceBandW()
                       );
    node->setHeight    ( getHeight()           );
    node->setWidth     ( getWidth()            );
    node->setNodeSets  ( _nodeSets.clone()     );
    node->setPreset    ( this->getPreset()     );
    node->setSet       ( this->getSet()        );
    node->setPlaced    ( this->getPlaced()     );
    node->setSymmetries( this->getSymmetries() );

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MX){ node->push_front((*it)->clone(tr)); }
      else         { node->push_back ((*it)->clone(tr)); }
    }
    return node;
  }

  
  void VSlicingNode::place( float x, float y )
  {
    if (recursiveCheckSet()){ this->_place(x,y); }
  }

  
  void VSlicingNode::_place( float x, float y )
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if ( ( (*it)->isHorizontal()) || ((*it)->isVertical()) ){ 
        if ( (*it)->isAlignBottom() ){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        else if ( (*it)->isAlignCenter() ){
          (*it)->setX(xref);
          (*it)->setY(yref + (_height/2) - ((*it)->getHeight()/2));
        }
        else if ( (*it)->isAlignTop() ){
          (*it)->setX(xref);
          (*it)->setY(yref + _height - (*it)->getHeight());
        }
      }
      
      if      ( (*it)->isAlignBottom() ) { (*it)->_place(xref, yref); }
      else if ( (*it)->isAlignCenter() ) { (*it)->_place(xref, yref + (_height/2) - ((*it)->getHeight()/2))  ; }
      else if ( (*it)->isAlignTop()    ) { (*it)->_place(xref, yref +  _height    -  (*it)->getHeight())     ; }
      else if ( (*it)->isRouting()     ) { (*it)->_place(xref, yref)                                         ; }
      else    { cerr << " Error(void place( float x, float y )): Unknown Alignment in SlicingTree." << endl ; }
    
      xref += (*it)->getWidth();
      yref = y;
    }
    setPlaced(Placed);
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


  void VSlicingNode::preDestroy()
  {
    _count--;
    HVSlicingNode::preDestroy();
  }


  void VSlicingNode::destroy()
  {
    VSlicingNode::preDestroy();
    delete(this);
  }


  void VSlicingNode::preRecursiveDestroy()
  {
    _count--;
    HVSlicingNode::preRecursiveDestroy();
  }


  void VSlicingNode::recursiveDestroy()
  {
    VSlicingNode::preRecursiveDestroy();
    delete(this);
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  int HSlicingNode::_count    = 0;
  int HSlicingNode::_countAll = 0;


  HSlicingNode::HSlicingNode( unsigned int type, unsigned int alignment ): HVSlicingNode( type, alignment ){}


  HSlicingNode::~HSlicingNode(){}


  HSlicingNode* HSlicingNode::create( unsigned int alignment )
  {
    _count++;
    _countAll++;
    return new HSlicingNode( Horizontal, alignment );
  }


  void HSlicingNode::createRouting( float space )
  {
    this->push_back(RHSlicingNode::create( space )); 
    resetSlicingTree();
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


  HSlicingNode* HSlicingNode::clone( unsigned int tr )
  {
    HSlicingNode* node = HSlicingNode::create( this->getAlignment() );
    node->setTolerances( getToleranceRatioH()
                       , getToleranceRatioW()
                       , getToleranceBandH()
                       , getToleranceBandW()
                       );
    node->setHeight    ( getHeight()           );
    node->setWidth     ( getWidth()            );
    node->setNodeSets  ( _nodeSets.clone()     );
    node->setPreset    ( this->getPreset()     );
    node->setSet       ( this->getSet()        );
    node->setPlaced    ( this->getPlaced()     );
    node->setSymmetries( this->getSymmetries() );

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){
      if (tr == MY){ node->push_front((*it)->clone(tr)); }
      else         { node->push_back ((*it)->clone(tr)); }
    }
    return node;
  }


  void HSlicingNode::place( float x, float y )
  {
    if( recursiveCheckSet() ){ this->_place(x,y); } 
  }


  void HSlicingNode::_place( float x, float y )
  {
    float xref = x;
    float yref = y;

    for (vector<SlicingNode*>::iterator it = _children.begin(); it != _children.end(); it++){ 
      if ( ((*it)->isHorizontal()) || ((*it)->isVertical()) ){ 
        if ( (*it)->isAlignLeft() ){
          (*it)->setX(xref);
          (*it)->setY(yref);
        }
        else if ( (*it)->isAlignCenter() ){
          (*it)->setX(xref + (_width/2) - ((*it)->getWidth()/2));
          (*it)->setY(yref);
        }
        else if ( (*it)->isAlignRight()  ){
          (*it)->setX(xref + _width - (*it)->getWidth());
          (*it)->setY(yref);
        }
      }

      if      ( (*it)->isAlignLeft()   ) { (*it)->_place(xref                                     , yref); }
      else if ( (*it)->isAlignCenter() ) { (*it)->_place(xref + (_width/2) - ((*it)->getWidth()/2), yref); }
      else if ( (*it)->isAlignRight()  ) { (*it)->_place(xref + _width     -  (*it)->getWidth()   , yref); }
      else if ( (*it)->isRouting()     ) { (*it)->_place(xref                                     , yref); }
      else    { cerr << "Error(_place( float x, float y )): Unknown Alignment in SlicingTree." << endl   ; }
      
      xref = x;
      yref += (*it)->getHeight();
    }
    setPlaced(Placed);
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
      _nodeSets.clear();
      this->normalizeSymmetries();
      
      HSetState state = HSetState(this);
      while( !state.end() ){ state.next(); }

      _nodeSets = state.getNodeSets();
    }
    if (_nodeSets.empty()){ cerr << "Error(void HVSlicingNode::updateGlobalSize()): No solution has been found. Try to set larger tolerances." << endl; }
  }


  void HSlicingNode::preDestroy()
  {
    _count--;
    HVSlicingNode::preDestroy();
  }


  void HSlicingNode::destroy()
  {
    HSlicingNode::preDestroy();
    delete(this);
  }


  void HSlicingNode::preRecursiveDestroy()
  {
    _count--;
    HVSlicingNode::preRecursiveDestroy();
  }


  void HSlicingNode::recursiveDestroy()
  {
    HSlicingNode::preRecursiveDestroy();
    delete(this);
  }


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  int DSlicingNode::_count    = 0;
  int DSlicingNode::_countAll = 0;


  DSlicingNode::DSlicingNode( unsigned int type
                            , NodeSets     nodeSets
                            , unsigned int alignment
                            , float        height
                            , float        width
                            ): SlicingNode( type, nodeSets, alignment, height, width ){}


  DSlicingNode::~DSlicingNode(){}
  

  DSlicingNode* DSlicingNode::create( NodeSets     nodeSets
                                    , unsigned int alignment
                                    , float        height
                                    , float        width
                                    )
  {
    _count++;
    _countAll++;
    return new DSlicingNode( Device, nodeSets, alignment, height, width ); 
  }


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


  DSlicingNode* DSlicingNode::clone( unsigned int tr )
  {
    DSlicingNode* node = DSlicingNode::create( _nodeSets.clone() 
                                             , this->getAlignment()
                                             , this->getHeight()
                                             , this->getWidth()
                                             );
    node->setPreset(this->getPreset());
    node->setSet   (this->getSet()   );
    node->setPlaced(this->getPlaced());
    return node;
  }


  void DSlicingNode::preDestroy()
  {
    _count--;
    SlicingNode::preDestroy();
  }


  void DSlicingNode::destroy()
  {
    DSlicingNode::preDestroy();
    delete(this);
  }


  void DSlicingNode::preRecursiveDestroy()
  {
    _count--;
    SlicingNode::preRecursiveDestroy();
  }


  void DSlicingNode::recursiveDestroy()
  {
    DSlicingNode::preRecursiveDestroy();
    delete(this);
  }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  int RHVSlicingNode::_count    = 0;
  int RHVSlicingNode::_countAll = 0;


  RHVSlicingNode::RHVSlicingNode( float height, float width ): SlicingNode( Routing, NodeSets(), UnknownAlignment, height, width )
  {
    this->setPreset(Preset); 
    this->setSet   (Set   ); 
  }


  RHVSlicingNode::~RHVSlicingNode(){}


  void RHVSlicingNode::print() const
  {
    cout << "- Print from Slicing Node - " << endl;
    cout << "SlicingType: Routing space" << endl;
    SlicingNode::print();
  }


  void RHVSlicingNode::_setGlobalSize ( float height, float width ){}


  void RHVSlicingNode::preDestroy()
  {
    _count--;
    SlicingNode::preDestroy();
  }


  void RHVSlicingNode::destroy()
  {
    RHVSlicingNode::preDestroy();
    delete(this);
  }


  void RHVSlicingNode::preRecursiveDestroy()
  {
    _count--;
    SlicingNode::preRecursiveDestroy();
  }


  void RHVSlicingNode::recursiveDestroy()
  {
    RHVSlicingNode::preRecursiveDestroy();
    delete(this);
  }


// Error Message Methods
  unsigned int RHVSlicingNode::getAlignment() const
  {
    cerr << " Error(unsigned int getAlignment () const): Routings do not have centering type." << endl;
    return UnknownAlignment;
  }


  NodeSets RHVSlicingNode::getNodeSets() const
  {
    cerr << " Error(NodeSets getNodeSets() const): Routings do not have different dimensions." << endl;
    return NodeSets();
  }


  pair<float,float> RHVSlicingNode::getPairH( float height ) const
  {
    cerr << " Error(pair<float,float> getPairH ( float height ) const): Routings do not have different dimensions." << endl;
    return pair<float, float> (_height, _width);
  }


  pair<float,float> RHVSlicingNode::getPairW( float width ) const
  {
    cerr << " Error(pair<float,float> getPairW ( float width ) const): Routings do not have different dimensions." << endl;
    return pair<float, float> (_height, _width);
  }


  void RHVSlicingNode::setPairH( float height )
  {
    cerr << " Error(void setPairH ( float height )): Routings do not have different dimensions." << endl;
  } 


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  RVSlicingNode::RVSlicingNode( float width ): RHVSlicingNode( 0, width )
  {
    _nodeSets.push_back(RVBoxSet::create(width));
  }


  RVSlicingNode::~RVSlicingNode(){};


  RVSlicingNode* RVSlicingNode::create( float width )
  {
    _count++;
    _countAll++;
    return new RVSlicingNode(width);
  }

  RVSlicingNode* RVSlicingNode::clone( unsigned int tr )
  {
    RVSlicingNode* node = RVSlicingNode::create(this->getWidth());
    return node; 
  }


// Error Methods
  void RVSlicingNode::setHeight( float height )
  {
    cerr << "Error(void RVSlicingNode::setHeight( float height )): Routings do not have height." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  RHSlicingNode::RHSlicingNode( float height ): RHVSlicingNode( height, 0 )
  {
    _nodeSets.push_back(RHBoxSet::create(height));
  }


  RHSlicingNode::~RHSlicingNode(){};


  RHSlicingNode* RHSlicingNode::create( float height )
  {
    _count++;
    _countAll++;
    return new RHSlicingNode(height); 
  }


  RHSlicingNode* RHSlicingNode::clone( unsigned int tr )
  {
    RHSlicingNode* node = RHSlicingNode::create(this->getHeight());
    return node; 
  }


// Error Methods
  void RHSlicingNode::setWidth( float width )
  {
    cerr << " Error(void RHSlicingNode::setWidth( float width )): Routings do not have width." << endl; 
  }


// -----------------------------------------------------------------------------------------------//
// Class : HVSetState
// -----------------------------------------------------------------------------------------------//
  

  HVSetState::HVSetState( HVSlicingNode* node ): _HVSnode( node )
  {
    _currentSet = vector<size_t> ();
    _nextSet    = vector<size_t> ();
    _nodeSets   = NodeSets();
    _counter    = 1;
    initSet();
    initModulos();
  }


  HVSetState::~HVSetState(){}


  const NodeSets HVSetState::getNodeSets()
  {
    _nodeSets.sort();
    return _nodeSets; 
  }


  void HVSetState::print()
  {
    int index = 0;
    cout << "currentSet:" << endl;
    vector<size_t>::iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
      NodeSets node = (*it)->getNodeSets();
      cout << index << ": H = " << node[(*it2)]->getHeight() << ", W = " << node[(*it2)]->getWidth() << endl;
      it2++;
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
    _nodeSets.print();
  }


  void HVSetState::initSet()
  {
     _nextSet.clear();
     for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){ 
      if ( (*it)->isPreset() ) 
        { _nextSet.push_back((*it)->getNodeSets().findIndex((*it)->getHeight(), (*it)->getWidth())); }
      else 
        { _nextSet.push_back(0); }
    }
    _currentSet = _nextSet;
  }


  void HVSetState::initModulos()
  {
    int modulo = 1;
    int index  = 0;
    
    _modulos.clear();
    _modulos.push_back(1);
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
        
      if ( it != _HVSnode->getChildren().begin() )       { _modulos.push_back(modulo); }
      if ( (!isSymmetry(index)) && (!(*it)->isPreset()) ){ modulo *= (*it)->getNodeSets().size(); }
      index++;
    }
    _modulos.push_back(modulo);
  }


  void HVSetState::next()
  {
    int                      index    = 0;
    pair<int,int>            symmetry = pair<int,int>();
    vector<size_t>::iterator itpair   = _nextSet.begin();

    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){

      if ( this->isSymmetry(index, symmetry) )
        { (*itpair) = _nextSet[symmetry.first]; }
      else {
        if ( (((_counter-1)%_modulos[index]) == _modulos[index]-1) && (!(*it)->isPreset()) ) {
          if ( (*itpair)+1 != (*it)->getNodeSets().size() ) { (*itpair)++  ; }
          else                                              { (*itpair) = 0; }
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


  pair<float,float> VSetState::getCurrentHs ()
  {
    float hmin = 0;
    float hmax = 0;
    if (!_currentSet.empty()) {
      vector<size_t>::const_iterator      it2 = _currentSet.begin();
      vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin();

      while( (hmin == 0) && (it != _HVSnode->getChildren().end()) ){
        NodeSets node = (*it)->getNodeSets();
        if ( node[(*it2)]->getHeight() != 0 )
          { hmin = node[(*it2)]->getHeight(); }
        it++;
        it2++;
      }

      it2 = _currentSet.begin();
      for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
        NodeSets node = (*it)->getNodeSets();
        if ( (node[(*it2)]->getHeight() < hmin)&&(node[(*it2)]->getHeight() != 0) )
          { hmin = node[(*it2)]->getHeight(); }

        if (node[(*it2)]->getHeight() > hmax)
          { hmax = node[(*it2)]->getHeight(); }
          it2++;
      }
    }
    return pair<float,float> (hmin, hmax);  
  }


  float VSetState::getCurrentH()
  {
    float currentH = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
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
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
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


  void VSetState::next()
  {
    push_back(); 
    HVSetState::next();
  }


  void VSetState::push_back()
  {
    pair<float,float> paireHeights = getCurrentHs();
    float             height       = paireHeights.second;
    float             hmin         = paireHeights.first;
    float             width        = 0;

    if (height - hmin <= _HVSnode->getToleranceBandH()){
      vector<BoxSet*> vect = vector<BoxSet*>();
      vector<size_t>::iterator it2 = _currentSet.begin();
    
      for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
        NodeSets node = (*it)->getNodeSets();
        vect.push_back(node[(*it2)]);
        width += node[(*it2)]->getWidth(); 
        it2++;
      }
      _nodeSets.push_back(vect, height, width, Vertical);
    }
  }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//
  

  HSetState::HSetState( HSlicingNode* node ):HVSetState(node) {}


  HSetState::~HSetState(){}


  pair<float,float> HSetState::getCurrentWs()
  {
    float wmin = 0;
    float wmax = 0;
    if (!_currentSet.empty()) { 
      vector< size_t >::const_iterator it2 = _currentSet.begin();
      vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin();
      
      while( (wmin == 0) && (it != _HVSnode->getChildren().end()) ){
        NodeSets node = (*it)->getNodeSets();
        if ( node[(*it2)]->getWidth() != 0 )
          { wmin = node[(*it2)]->getWidth(); }
        it++;
        it2++;
      }

      it2 = _currentSet.begin();
      for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
        NodeSets node = (*it)->getNodeSets();
        if ( (node[(*it2)]->getWidth() < wmin)&&(node[(*it2)]->getWidth() != 0) )
          { wmin = node[(*it2)]->getWidth(); }
        if (node[(*it2)]->getWidth() > wmax)
          { wmax = node[(*it2)]->getWidth(); }
        it2++;
      }
    }
    return pair<float,float> (wmin, wmax);  
  }


  float HSetState::getCurrentH()
  {
    float currentH = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
      NodeSets node = (*it)->getNodeSets();
      currentH += node[(*it2)]->getHeight(); 
      it2++;
    }

    return currentH;
  }


  float HSetState::getCurrentW()
  {
    float currentW = 0;
    vector< size_t >::const_iterator it2 = _currentSet.begin();
    for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
      NodeSets node = (*it)->getNodeSets();
      if (node[(*it2)]->getWidth() > currentW)
        { currentW = node[(*it2)]->getWidth(); }
      it2++;
    }
    return currentW;
  }
  

  void HSetState::print()
  {
    HVSetState::print();
    cout << "currentH = " << getCurrentH() << endl;
    cout << "currentW = " << getCurrentW() << endl;
    cout << endl;
  }

  
  void HSetState::next()
  {
    push_back(); 
    HVSetState::next();
  }


  void HSetState::push_back()
  {
    pair<float,float> paireWidths = getCurrentWs();
    float             width       = paireWidths.second;
    float             wmin        = paireWidths.first;
    float             height      = 0;
    if ( width - wmin <= _HVSnode->getToleranceBandW() ){
      vector<BoxSet*> vect = vector<BoxSet*>();
      vector<size_t>::iterator it2 = _currentSet.begin();
    
      for (vector<SlicingNode*>::const_iterator it = _HVSnode->getChildren().begin(); it != _HVSnode->getChildren().end(); it++){
        NodeSets node = (*it)->getNodeSets();
        vect.push_back(node[(*it2)]);
        height += node[(*it2)]->getHeight(); 
        it2++;
      }

      _nodeSets.push_back(vect, height, width, Horizontal);
    }
  }

}
