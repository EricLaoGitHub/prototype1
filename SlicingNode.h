#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <typeinfo>
#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <iomanip>

namespace SlicingTree{
  
  const unsigned int presetMask      = 0x1;
  const unsigned int setMask         = 0x2;
  const unsigned int placedMask      = 0x4;
  const unsigned int alignmentMask   = 0x1F1;
  const unsigned int slicingTypeMask = 0x3E00;

  enum Flags { Preset           = 1 << 0
             , Set              = 1 << 1
             , Placed           = 1 << 2
             , UnknownAlignment = 1 << 3
             , AlignLeft        = 1 << 4
             , AlignRight       = 1 << 5
             , AlignCenter      = 1 << 6
             , AlignTop         = 1 << 7
             , AlignBottom      = 1 << 8
             , UnknownType      = 1 << 9
             , Horizontal       = 1 << 10
             , Vertical         = 1 << 11
             , Device           = 1 << 12
             , Routing          = 1 << 13
             , None             = 1 << 14
             , MX               = 1 << 15
             , MY               = 1 << 16
             };


// -----------------------------------------------------------------------------------------------//
// Class : BoxSet
// -----------------------------------------------------------------------------------------------//

  
  class BoxSet
  {
    public:
      BoxSet  ( float height = 0, float width = 0 );
      BoxSet  ( BoxSet* boxSet );
      virtual ~BoxSet ();
  
      inline         float                 getHeight         () const;
      inline         float                 getWidth          () const; 
      inline         unsigned int          getCpt            () const;
      inline         void                  incrementCpt      ();
      virtual        BoxSet*               clone             () = 0;
                     void                  preDestroy        () {}
      virtual        void                  destroy           ();

      virtual inline unsigned int          getType           () const;
      virtual inline float                 getOccupationArea () const;
      virtual const  std::vector<BoxSet*>& getSet            () const;
      virtual        int                   getNFing          () const;
      virtual        void                  print             () const;
      virtual        float                 getDevicesArea    () const = 0;

    protected:
      float        _height;
      float        _width;
      unsigned int _cpt;

  };

  inline float        BoxSet::getHeight         () const { return _height;     }
  inline float        BoxSet::getWidth          () const { return _width ;     }
  inline unsigned int BoxSet::getCpt            () const { return _cpt;        }
  inline void         BoxSet::incrementCpt      ()       { _cpt++;             }

  inline unsigned int BoxSet::getType           () const { return UnknownType; }
  inline float        BoxSet::getOccupationArea () const { return 100;         }


// -----------------------------------------------------------------------------------------------//
// Class : HVBoxSet
// -----------------------------------------------------------------------------------------------//

  
  class HVBoxSet: public BoxSet
  {
    protected:
      HVBoxSet  ( std::vector<BoxSet*> dimensionSet, float height = 0, float width = 0 );
      HVBoxSet  ( HVBoxSet* boxSet );
      virtual ~HVBoxSet ();

      inline const   std::vector<BoxSet*>& getSet            () const;
      inline         float                 getOccupationArea () const;
                     float                 getDevicesArea    () const;

      virtual inline void                  calculateHeight   () = 0;
      virtual inline void                  calculateWidth    () = 0;
      virtual        void                  print             () const;

    protected:
      std::vector<BoxSet*> _dimensionSet;
  };

  inline const std::vector<BoxSet*>& HVBoxSet::getSet            () const { return _dimensionSet; }
  inline       float                 HVBoxSet::getOccupationArea () const { return getDevicesArea()/(_height * _width)*100; }


// -----------------------------------------------------------------------------------------------//
// Class : HBoxSet
// -----------------------------------------------------------------------------------------------//

  
  class HBoxSet: public HVBoxSet
  {
    protected:
      HBoxSet  ( std::vector<BoxSet*> dimensionSet, float height = 0, float width = 0 );
      HBoxSet  ( HBoxSet* boxSet );
      ~HBoxSet ();
      
    public:
      static HBoxSet*     create          ( std::vector<BoxSet*> dimensionSet, float height = 0, float width = 0  );
             HBoxSet*     clone           ();
      inline unsigned int getType         () const;
             void         calculateHeight ();
             void         calculateWidth  ();

      static inline int   getCount        ();
      static inline void  printCount      ();
      static inline void  printCountAll   ();
             void         destroy         ();

    private:
      static int _count;
      static int _countAll;
  };

  inline unsigned int HBoxSet::getType       () const { return Horizontal; }
  inline int          HBoxSet::getCount      () { return _count    ; }
  inline void         HBoxSet::printCount    () { std::cout << "HBoxSet::Count           = " << _count << std::endl; }
  inline void         HBoxSet::printCountAll () { std::cout << "HBoxSet::CountAll        = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : VBoxSet
// -----------------------------------------------------------------------------------------------//

  
  class VBoxSet: public HVBoxSet
  {
    protected:
      VBoxSet  ( std::vector<BoxSet*> dimensionSet, float height = 0, float width = 0 );
      VBoxSet  ( VBoxSet* boxSet );
      ~VBoxSet ();

    public:
      static VBoxSet*     create          ( std::vector<BoxSet*> dimensionSet, float height = 0, float width = 0  );
             VBoxSet*     clone           ();
      inline unsigned int getType         () const;
             void         calculateHeight ();
             void         calculateWidth  ();

      static inline int   getCount        ();
      static inline void  printCount      ();
      static inline void  printCountAll   ();
             void         destroy         ();

    private:
      static int _count;
      static int _countAll;
  };

  inline unsigned int VBoxSet::getType       () const { return Vertical; }
  inline int          VBoxSet::getCount      () { return _count  ; }
  inline void         VBoxSet::printCount    () { std::cout << "VBoxSet::Count           = " << _count << std::endl; }
  inline void         VBoxSet::printCountAll () { std::cout << "VBoxSet::CountAll        = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : DBoxSet
// -----------------------------------------------------------------------------------------------//


  class DBoxSet: public BoxSet
  {
    protected:
      DBoxSet  ( float height, float width, int nfing = 1 );
      DBoxSet  ( DBoxSet* boxSet );
      ~DBoxSet ();

    public:
      static DBoxSet*     create         ( float height, float width, int nfing = 1 );
             DBoxSet*     clone          ();
      inline unsigned int getType        () const;
      inline float        getDevicesArea () const;

             inline int   getNFing       () const;
      static inline int   getCount       ();
      static inline void  printCount     ();
      static inline void  printCountAll  ();
                    void  destroy        ();
                    void  print          () const;

    private:
             int _nfing;    
      static int _count;
      static int _countAll;
  };

  inline unsigned int DBoxSet::getType        () const { return Device; }
  inline float        DBoxSet::getDevicesArea () const { return _height*_width; }
  inline int          DBoxSet::getNFing       () const { return _nfing; }
  inline int          DBoxSet::getCount       () { return _count; }
  inline void         DBoxSet::printCount     () { std::cout << "DBoxSet::Count           = " << _count << std::endl; }
  inline void         DBoxSet::printCountAll  () { std::cout << "DBoxSet::CountAll        = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : RHVBoxSet
// -----------------------------------------------------------------------------------------------//


  class RHVBoxSet: public BoxSet
  {
    public:
      RHVBoxSet  ( float height = 0, float width = 0);
      RHVBoxSet  ( RHVBoxSet* boxSet );
      ~RHVBoxSet ();

      inline float        getHeight      () const;
      inline float        getWidth       () const;
      inline unsigned int getType        () const;
      inline float        getDevicesArea () const;
      
      static inline int   getCount       ();
      static inline void  printCount     ();
      static inline void  printCountAll  ();
             void         destroy        ();

    protected:
      static int _count;
      static int _countAll;
  };
 
  inline float        RHVBoxSet::getHeight      () const { return _height; } 
  inline float        RHVBoxSet::getWidth       () const { return _width;  }
  inline unsigned int RHVBoxSet::getType        () const { return Routing; }
  inline float        RHVBoxSet::getDevicesArea () const { return 0;       }
  inline int          RHVBoxSet::getCount       () { return _count;  }
  inline void         RHVBoxSet::printCount     () { std::cout << "RHVBoxSet::Count         = " << _count << std::endl; }
  inline void         RHVBoxSet::printCountAll  () { std::cout << "RHVBoxSet::CountAll      = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : RHBoxSet
// -----------------------------------------------------------------------------------------------//


  class RHBoxSet: public RHVBoxSet
  {
    protected:
      RHBoxSet  ( float     height = 0 );
      RHBoxSet  ( RHBoxSet* boxSet     );
      ~RHBoxSet ();

    public:
      static RHBoxSet* create ( float height );
             RHBoxSet* clone  ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVBoxSet
// -----------------------------------------------------------------------------------------------//


  class RVBoxSet: public RHVBoxSet
  {
    protected:
      RVBoxSet  ( float     width = 0 );
      RVBoxSet  ( RVBoxSet* boxSet );
      ~RVBoxSet ();

    public:
      static RVBoxSet* create ( float width );
             RVBoxSet* clone  ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : NodeSets
// -----------------------------------------------------------------------------------------------//
  
// To compare BoxSets
  class compBoxSet
  {
    public:
      bool operator() ( const  BoxSet* lhs, const  BoxSet* rhs) {
        return ( (lhs->getHeight() < rhs->getHeight()) || 
               ( (lhs->getHeight() == rhs->getHeight()) && (lhs->getWidth() < rhs->getWidth()))
               ); 
      }
  };


  class NodeSets 
  {
    public:
      NodeSets  ();
      NodeSets  ( const NodeSets& other );
      ~NodeSets ();

      BoxSet* operator[] (size_t i);

      inline std::vector<BoxSet*>::iterator begin       ();
      inline std::vector<BoxSet*>::iterator end         ();
      inline std::vector<BoxSet*>           getNodeSets () const;
      inline size_t                         size        () const;
      inline bool                           empty       () const;
             void                           clear       ();
      inline void                           sort        ();

             BoxSet*                        getPairH    ( float height ) const;
             BoxSet*                        getPairHW   ( float height, float width ) const;
             int                            findIndex   ( float height, float width ) const;
             std::vector<BoxSet*>::iterator find        ( float height, float width );
             std::vector<BoxSet*>::iterator find        ( BoxSet* boxSet );

             void                           print       () const;
             bool                           compare     ( NodeSets nodeSets2 ) const;
             void                           push_back   ( BoxSet* boxSet );
             void                           push_back   ( std::vector<BoxSet*> vect, float height, float width, unsigned int type );
             void                           push_back   ( float height, float width );
             NodeSets                       clone       ();

    private:
      std::vector<BoxSet*> _nodeSets;
  };

  inline std::vector<BoxSet*>::iterator NodeSets::begin       ()       { return _nodeSets.begin(); }
  inline std::vector<BoxSet*>::iterator NodeSets::end         ()       { return _nodeSets.end  (); }
  inline std::vector<BoxSet*>           NodeSets::getNodeSets () const { return _nodeSets;         }
  inline size_t                         NodeSets::size        () const { return _nodeSets.size() ; }
  inline bool                           NodeSets::empty       () const { return _nodeSets.empty(); }
  inline void                           NodeSets::sort        ()       { std::sort( _nodeSets.begin(),_nodeSets.end(), compBoxSet() ); }


// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  class SlicingNode
  {
    protected:
      SlicingNode ( unsigned int type       
                  , NodeSets     nodeSets  = NodeSets()
                  , unsigned int alignment = UnknownAlignment
                  , BoxSet*      boxSet    = NULL
                  );
      virtual ~SlicingNode ();

    public:
      inline bool                   isPreset             () const;
      inline bool                   isSet                () const;
      inline bool                   isPlaced             () const;
      inline bool                   isAlignLeft          () const;
      inline bool                   isAlignRight         () const;
      inline bool                   isAlignCenter        () const;
      inline bool                   isAlignTop           () const;
      inline bool                   isAlignBottom        () const;
      inline bool                   isHorizontal         () const;
      inline bool                   isVertical           () const;
      inline bool                   isDevice             () const;
      inline bool                   isRouting            () const;

      inline unsigned int           getPreset            () const;
      inline unsigned int           getSet               () const;
      inline unsigned int           getPlaced            () const;
      inline unsigned int           getAlignment         () const;
      inline unsigned int           getType              () const;
             float                  getHeight            () const;
             float                  getWidth             () const;
      inline BoxSet*                getBoxSet            () const;
      inline float                  getX                 () const;
      inline float                  getY                 () const;
      inline const NodeSets&        getNodeSets          () const;
      inline SlicingNode*           getParent            () const;
      inline BoxSet*                getPairH             ( float h ) const; 
      inline BoxSet*                getPairHW            ( float height, float width ) const;
             SlicingNode*           getRoot              ();

      inline void                   setPreset            ( unsigned int preset       );
      inline void                   setSet               ( unsigned int set          );
      inline void                   setPlaced            ( unsigned int placed       );
      inline void                   setAlignment         ( unsigned int alignment    );
      inline void                   setType              ( unsigned int type         );
             void                   setBoxSet            ( BoxSet*      boxSet       );
             void                   setBoxSet            ( float height, float width );
             void                   setBoxSet            ( size_t       index        );
             void                   _setBoxSet           ( BoxSet*      boxSet       );
      inline void                   setX                 ( float        x            );
      inline void                   setY                 ( float        y            );
      inline void                   setNodeSets          ( NodeSets     nodeSets     );
      inline void                   setParent            ( SlicingNode* parent       );
      inline void                   setPairH             ( float        height       );
      inline void                   setPairHW            ( float height, float width );
      
      inline  void                  clearNodeSets        ();
              void                  clearParentsNodeSets ();
      inline  void                  removeParent         ();
      virtual void                  resetSlicingTree     ();
      virtual void                  _resetSlicingTree    ();

      virtual void                  print                () const;
      virtual void                  printParent          () const;
      virtual void                  place                ( float x = 0 , float y = 0 ); 
      virtual void                  _place               ( float x = 0 , float y = 0 ); 
      virtual void                  updateGlobalSize     () {}; 
      virtual void                  setGlobalSize        ( float height, float width );
      virtual void                  setGlobalSize        ( size_t index );
      virtual void                 _setGlobalSize        ( BoxSet* boxSet );
      virtual inline bool           recursiveCheckPreset () const;
      virtual inline bool           recursiveCheckSet    () const;
      virtual inline bool           recursiveCheckPlaced () const;
      virtual inline int            getLeafNumber        () const;
      virtual void                  preDestroy           ();
      virtual void                  destroy              ();
      virtual void                  preRecursiveDestroy  ();
      virtual void                  recursiveDestroy     ();

    // Error Methods
      virtual float                            getToleranceRatioH          () const;
      virtual float                            getToleranceRatioW          () const;
      virtual void                             setToleranceRatioH          ( float tolerance );
      virtual void                             setToleranceRatioW          ( float tolerance );
      virtual float                            getToleranceBandH           () const;
      virtual float                            getToleranceBandW           () const;
      virtual void                             setToleranceBandH           ( float tolerance );
      virtual void                             setToleranceBandW           ( float tolerance );
      virtual void                             recursiveSetToleranceRatioH ( float tolerance );
      virtual void                             recursiveSetToleranceRatioW ( float tolerance );
      virtual void                             recursiveSetToleranceBandH  ( float tolerance );
      virtual void                             recursiveSetToleranceBandW  ( float tolerance );
      virtual void                             setTolerances               ( float trh, float trw, float tbh, float tbw );

      virtual bool                             hasEmptyChildrenNodeSets () const;
      virtual const std::vector<SlicingNode*>& getChildren              () const;
      virtual SlicingNode*                     getChild                 ( int index ) const;
      virtual int                              getChildIndex            ( SlicingNode* node ) const;
      virtual int                              getNbChild               () const;
      virtual void                             createChild              ( unsigned int type, unsigned int alignment );
      virtual void                             createChild              ( NodeSets     nodeSets  
                                                                        , unsigned int alignment = UnknownAlignment
                                                                        , BoxSet*      boxSet    = NULL
                                                                        );
      virtual void                             createChild              ( int childIndex, int copyIndex, unsigned int tr ); 
      virtual void                             createRouting            ( float space );
      virtual void                             insertNode               ( SlicingNode* node, int index ); 
      virtual void                             push_back                ( SlicingNode* node ); 
      virtual void                             push_front               ( SlicingNode* node ); 
      virtual void                             removeNode               ( SlicingNode* node );
      virtual void                             removeAllNodes           ();     

      virtual std::list<std::pair<int,int> >   getSymmetries            () const;
      virtual void                             setSymmetries            ( std::list<std::pair< int,int> > sym );
      virtual bool                             isSymmetry               ( int index, std::pair<int,int>& symmetry );
      virtual bool                             isSymmetry               ( int index );
      virtual void                             addSymmetry              ( int childIndex, int copyIndex );
      virtual void                             removeSymmetry           ( int index );
      virtual void                             normalizeSymmetries      ();

      virtual void                             printChildren            () const;
      virtual SlicingNode*                     clone                    ( unsigned int tr = None ) = 0;
      virtual float                            getDevicesArea           () const = 0;
      virtual float                            getOccupationArea        () const;

    protected:
      SlicingNode* _parent;
      unsigned int _flags;
      NodeSets     _nodeSets;    
      float        _x;         
      float        _y;       
      BoxSet*      _boxSet;
  };

  inline bool            SlicingNode::isPreset      () const { return (_flags & Preset)     ; }
  inline bool            SlicingNode::isSet         () const { return (_flags & Set)        ; }
  inline bool            SlicingNode::isPlaced      () const { return (_flags & Placed)     ; }
  inline bool            SlicingNode::isAlignLeft   () const { return (_flags & AlignLeft)  ; }
  inline bool            SlicingNode::isAlignRight  () const { return (_flags & AlignRight) ; }
  inline bool            SlicingNode::isAlignCenter () const { return (_flags & AlignCenter); }
  inline bool            SlicingNode::isAlignTop    () const { return (_flags & AlignTop)   ; }
  inline bool            SlicingNode::isAlignBottom () const { return (_flags & AlignBottom); }
  inline bool            SlicingNode::isHorizontal  () const { return (_flags & Horizontal) ; }
  inline bool            SlicingNode::isVertical    () const { return (_flags & Vertical)   ; }
  inline bool            SlicingNode::isDevice      () const { return (_flags & Device)     ; }
  inline bool            SlicingNode::isRouting     () const { return (_flags & Routing)    ; }

  inline unsigned int    SlicingNode::getPreset     () const { return (_flags & presetMask     ); }
  inline unsigned int    SlicingNode::getSet        () const { return (_flags & setMask        ); }
  inline unsigned int    SlicingNode::getPlaced     () const { return (_flags & placedMask     ); }
  inline unsigned int    SlicingNode::getAlignment  () const { return (_flags & alignmentMask  ); }
  inline unsigned int    SlicingNode::getType       () const { return (_flags & slicingTypeMask); }
  inline BoxSet*         SlicingNode::getBoxSet     () const { return _boxSet; }
  inline float           SlicingNode::getX          () const { return _x;      }
  inline float           SlicingNode::getY          () const { return _y;      }
  inline const NodeSets& SlicingNode::getNodeSets   () const { return _nodeSets; }
  inline SlicingNode*    SlicingNode::getParent     () const { return _parent; }

  inline BoxSet* SlicingNode::getPairH  ( float height )              const { return _nodeSets.getPairH(height); }  
  inline BoxSet* SlicingNode::getPairHW ( float height, float width ) const { return _nodeSets.getPairHW(height, width); }  

  inline void SlicingNode::setPreset     ( unsigned int preset    ) { _flags    = ((_flags & ~(presetMask)      ) | preset   ); } 
  inline void SlicingNode::setSet        ( unsigned int set       ) { _flags    = ((_flags & ~(setMask)         ) | set      ); } 
  inline void SlicingNode::setPlaced     ( unsigned int placed    ) { _flags    = ((_flags & ~(placedMask)      ) | placed   ); } 
  inline void SlicingNode::setAlignment  ( unsigned int alignment    ) { _flags    = ((_flags & ~(alignmentMask)   ) | alignment); }
  inline void SlicingNode::setType       ( unsigned int type         ) { _flags    = ((_flags & ~(slicingTypeMask) ) | type     ); }
  inline void SlicingNode::setX          ( float        x            ) { _x        = x;      }
  inline void SlicingNode::setY          ( float        y            ) { _y        = y;      }
  inline void SlicingNode::setNodeSets   ( NodeSets     nodeSets     ) { _nodeSets = nodeSets; }  
  inline void SlicingNode::setParent     ( SlicingNode* parent       ) { _parent   = parent;   }
  inline void SlicingNode::setPairH      ( float        height       ) { _boxSet   = this->getPairH(height);  }
  inline void SlicingNode::setPairHW     ( float height, float width ) { _boxSet   = this->getPairHW(height, width);  }

  inline void SlicingNode::clearNodeSets () { _nodeSets.clear(); }
  inline void SlicingNode::removeParent  () { _parent   = NULL;  }
    
  inline bool SlicingNode::recursiveCheckPreset () const { return isPreset(); }
  inline bool SlicingNode::recursiveCheckSet    () const { return isSet   (); }
  inline bool SlicingNode::recursiveCheckPlaced () const { return isPlaced(); }
  inline int  SlicingNode::getLeafNumber        () const { return 1  ; }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HVSlicingNode: public SlicingNode
  {
    protected:
      HVSlicingNode ( unsigned int type, unsigned int alignment = AlignLeft );
      virtual ~HVSlicingNode ();
    
    public:
      inline float                            getToleranceRatioH          () const;
      inline float                            getToleranceRatioW          () const;
      inline void                             setToleranceRatioH          ( float tolerance );
      inline void                             setToleranceRatioW          ( float tolerance );
      inline float                            getToleranceBandH           () const;
      inline float                            getToleranceBandW           () const;
      inline void                             setToleranceBandH           ( float tolerance );
      inline void                             setToleranceBandW           ( float tolerance );
             void                             recursiveSetToleranceRatioH ( float tolerance );
             void                             recursiveSetToleranceRatioW ( float tolerance );
             void                             recursiveSetToleranceBandH  ( float tolerance );
             void                             recursiveSetToleranceBandW  ( float tolerance );
             void                             setTolerances               ( float trh, float trw, float tbh, float tbw );

             bool                             hasEmptyChildrenNodeSets () const;
      inline const std::vector<SlicingNode*>& getChildren              () const;
      inline SlicingNode*                     getChild                 ( int index ) const;
             int                              getChildIndex            ( SlicingNode* node ) const;
      inline int                              getNbChild               () const;
             void                             createChild              ( unsigned int type, unsigned int alignment );
             void                             createChild              ( NodeSets     nodeSets  
                                                                       , unsigned int alignment = UnknownAlignment
                                                                       , BoxSet*      boxSet    = NULL
                                                                       );
             void                             createChild              ( int childIndex, int copyIndex, unsigned int tr );
             void                             insertNode               ( SlicingNode* node, int index );
             void                             push_back                ( SlicingNode* node );  
             void                             push_front               ( SlicingNode* node ); 
             void                             removeNode               ( SlicingNode* node ); 
      inline void                             removeAllNodes           ();

      inline std::list<std::pair< int,int> >  getSymmetries            () const;
      inline void                             setSymmetries            ( std::list<std::pair< int,int> > sym );
             bool                             isSymmetry               ( int index, std::pair<int,int>& symmetry );
             bool                             isSymmetry               ( int index );
             void                             addSymmetry              ( int childIndex, int copyIndex );
             void                             removeSymmetry           ( int index );
             void                             normalizeSymmetries      ();

             void                             preDestroy               ();
             void                             destroy                  ();
             void                             preRecursiveDestroy      ();
             void                             recursiveDestroy         ();

             void                             _resetSlicingTree        ();
             void                             print                    () const;
             void                             printChildren            () const;
             bool                             recursiveCheckPreset     () const;
             bool                             recursiveCheckSet        () const;
             bool                             recursiveCheckPlaced     () const;
             int                              getLeafNumber            () const;
             float                            getDevicesArea           () const;
             float                            getOccupationArea        () const;
             void                             setGlobalSize            ( float height, float width );
             void                             setGlobalSize            ( size_t index );
             void                             _setGlobalSize           ( BoxSet* boxSet );

    protected:
      std::vector<SlicingNode*>       _children;
      float                           _toleranceRatioH;
      float                           _toleranceRatioW;
      float                           _toleranceBandH;
      float                           _toleranceBandW;
      std::list<std::pair <int,int> > _symmetries;
  };

  inline float HVSlicingNode::getToleranceRatioH () const            { return _toleranceRatioH;      }
  inline float HVSlicingNode::getToleranceRatioW () const            { return _toleranceRatioW;      }
  inline void  HVSlicingNode::setToleranceRatioH ( float tolerance ) { _toleranceRatioH = tolerance; }
  inline void  HVSlicingNode::setToleranceRatioW ( float tolerance ) { _toleranceRatioW = tolerance; }
  inline float HVSlicingNode::getToleranceBandH  () const            { return _toleranceBandH;      }
  inline float HVSlicingNode::getToleranceBandW  () const            { return _toleranceBandW;      }
  inline void  HVSlicingNode::setToleranceBandH  ( float tolerance ) { _toleranceBandH = tolerance; }
  inline void  HVSlicingNode::setToleranceBandW  ( float tolerance ) { _toleranceBandW = tolerance; }

  inline const std::vector<SlicingNode*>& HVSlicingNode::getChildren    () const              { return _children; }
  inline SlicingNode*                     HVSlicingNode::getChild       ( int index ) const   { return _children[index]; }
  inline int                              HVSlicingNode::getNbChild     () const              { return _children.size(); }
  inline void                             HVSlicingNode::removeAllNodes ()                    { _children.clear(); }

  inline std::list<std::pair<int,int> >   HVSlicingNode::getSymmetries  () const                               { return _symmetries; }
  inline void                             HVSlicingNode::setSymmetries  ( std::list<std::pair<int,int> > sym ) { _symmetries = sym;  }


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HSlicingNode: public HVSlicingNode
  {
    private:
      HSlicingNode  ( unsigned int type, unsigned int alignment = UnknownAlignment );
      ~HSlicingNode ();

    public:
      static HSlicingNode* create              ( unsigned int alignment  = AlignLeft );
      void                 createRouting       ( float space );

      void                 print               () const;
      HSlicingNode*        clone               ( unsigned int tr = None );
      void                 place               ( float x = 0, float y = 0 );
      void                 _place              ( float x = 0, float y = 0 );
      void                 updateGlobalSize    ();

      static inline int    getCount            ();
      static inline void   printCount          ();
      static inline void   printCountAll       ();
      void                 preDestroy          ();
      void                 destroy             ();
      void                 preRecursiveDestroy ();
      void                 recursiveDestroy    ();

    private:
      static int _count;
      static int _countAll;
  };

  inline int  HSlicingNode::getCount      () { return _count; }
  inline void HSlicingNode::printCount    () { std::cout << "HSlicingNode::Count      = " << _count    << std::endl; }
  inline void HSlicingNode::printCountAll () { std::cout << "HSlicingNode::CountAll   = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  class VSlicingNode: public HVSlicingNode
  {
    private:
      VSlicingNode  ( unsigned int type, unsigned int alignment = UnknownAlignment);
      ~VSlicingNode (); 

    public:
      static VSlicingNode* create              ( unsigned int alignment = AlignBottom );
      void                 createRouting       ( float space );

      void                 print               () const;
      VSlicingNode*        clone               ( unsigned int tr = None );
      void                 place               ( float x = 0, float y = 0 );
      void                 _place              ( float x = 0, float y = 0 );
      void                 updateGlobalSize    ();

      static inline int    getCount            ();
      static inline void   printCount          ();
      static inline void   printCountAll       ();
      void                 preDestroy          ();
      void                 destroy             ();
      void                 preRecursiveDestroy ();
      void                 recursiveDestroy    ();

    private:
      static int _count;
      static int _countAll;
  };

  inline int  VSlicingNode::getCount      () { return _count; }
  inline void VSlicingNode::printCount    () { std::cout << "VSlicingNode::Count      = " << _count    << std::endl; }
  inline void VSlicingNode::printCountAll () { std::cout << "VSlicingNode::CountAll   = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  class DSlicingNode: public SlicingNode
  {
    private:
      DSlicingNode  ( unsigned int type
                    , NodeSets     nodeSets  
                    , unsigned int alignment = UnknownAlignment
                    , BoxSet*      boxSet    = NULL
                    );
      ~DSlicingNode ();

    public:
      static DSlicingNode* create              ( NodeSets     nodeSets  
                                               , unsigned int alignment = UnknownAlignment
                                               , BoxSet*      boxSet    = NULL
                                               );
      void                 print               () const;
      DSlicingNode*        clone               ( unsigned int tr = None );
      inline float         getDevicesArea      () const;
             int           getNFing            () const;
      
      static inline int    getCount            ();
      static inline void   printCount          ();
      static inline void   printCountAll       ();
      void                 preDestroy          ();
      void                 destroy             ();
      void                 preRecursiveDestroy ();
      void                 recursiveDestroy    ();

    private:
      static int _count;
      static int _countAll;
  };

  inline float DSlicingNode::getDevicesArea () const { return this->getHeight()*this->getWidth(); }
  inline int   DSlicingNode::getCount       () { return _count  ; }
  inline void  DSlicingNode::printCount     () { std::cout << "DSlicingNode::Count      = " << _count    << std::endl; }
  inline void  DSlicingNode::printCountAll  () { std::cout << "DSlicingNode::CountAll   = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHVSlicingNode: public SlicingNode
  {
    protected:
      RHVSlicingNode  ();
      ~RHVSlicingNode ();

    public:
      void                   print          () const;
      void                   _setGlobalSize ( float height, float width = 0 );
      inline float           getDevicesArea () const;

      // Error Message Methods
      unsigned int           getAlignment   () const;
      NodeSets               getNodeSets    () const;
      BoxSet*                getPairH       ( float height ) const; 
      BoxSet*                getPairHW      ( float height, float width ) const; 
      void                   setPairH       ( float height ); 
      void                   setPairHW      ( float height, float width ); 
  
      static inline int      getCount            ();
      static inline void     printCount          ();
      static inline void     printCountAll       ();
      void                   preDestroy          ();
      void                   destroy             ();
      void                   preRecursiveDestroy ();
      void                   recursiveDestroy    ();

    protected:
      static int _count;   
      static int _countAll;   
  };

  inline float RHVSlicingNode::getDevicesArea () const { return 0; }
  inline int   RHVSlicingNode::getCount       ()       { return _count; }
  inline void  RHVSlicingNode::printCount     ()       { std::cout << "RHVSlicingNode::Count    = " << _count    << std::endl; }
  inline void  RHVSlicingNode::printCountAll  ()       { std::cout << "RHVSlicingNode::CountAll = " << _countAll << std::endl; }


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHSlicingNode: public RHVSlicingNode
  {
    private:
      RHSlicingNode  ( float height = 0 );
      ~RHSlicingNode ();

    public:
      static RHSlicingNode* create ( float        height = 0    );
             RHSlicingNode* clone  ( unsigned int tr     = None );

      // Error Message Methods
      void  setWidth ( float width );
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RVSlicingNode: public RHVSlicingNode
  {
    private:
      RVSlicingNode  ( float width = 0 );
      ~RVSlicingNode ();

    public:
      static RVSlicingNode* create ( float        width = 0    );
             RVSlicingNode* clone  ( unsigned int tr    = None );

      // Error Message Methods
      void  setHeight ( float height );
  };


// -----------------------------------------------------------------------------------------------//
// Class : HVSetState
// -----------------------------------------------------------------------------------------------//

  class HVSetState
  {
    protected:
      HVSetState ( HVSlicingNode* node );
      virtual ~HVSetState ();

    public:
      virtual float    getCurrentH   () = 0;
      virtual float    getCurrentW   () = 0;
      inline  bool     end           ();
      inline  int      getEndCounter ();
      const   NodeSets getNodeSets   (); 
              bool     isSymmetry    ( int index, std::pair<int,int>& symmetry );
              bool     isSymmetry    ( int index );

      virtual void     print         ();
              void     initSet       ();
              void     initModulos   ();
              void     next          ();
      virtual void     push_back     () = 0;

    protected: 
      HVSlicingNode*      _HVSnode; 
      int                 _counter;
      std::vector<int>    _modulos;
      std::vector<size_t> _currentSet;
      std::vector<size_t> _nextSet;
      NodeSets            _nodeSets;
  };

  inline bool HVSetState::end           ()                                          { return (_counter == _modulos.back()+1); }
  inline int  HVSetState::getEndCounter ()                                          { return _modulos.back()+1; }
  inline bool HVSetState::isSymmetry    ( int index, std::pair<int,int>& symmetry ) { return _HVSnode->isSymmetry(index, symmetry); }
  inline bool HVSetState::isSymmetry    ( int index )                               { return _HVSnode->isSymmetry(index); }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//


  class HSetState: public HVSetState
  {
    public:
      HSetState  ( HSlicingNode* node );
      ~HSetState ();

      std::pair<float,float> getCurrentWs ();
      float                  getCurrentH  ();
      float                  getCurrentW  ();
      void                   print        ();
      void                   next         ();
      void                   push_back    ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : VSetState
// -----------------------------------------------------------------------------------------------//


  class VSetState: public HVSetState
  {
    public:
      VSetState  ( VSlicingNode* node );
      ~VSetState ();
      
      std::pair<float,float> getCurrentHs ();
      float                  getCurrentH  ();
      float                  getCurrentW  ();
      void                   print        ();
      void                   next         ();
      void                   push_back    ();
  };
  

}
#endif

