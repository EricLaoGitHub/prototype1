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
  
// Flags = ( Transformation - SlicingType (3bits) - Alignment (3bits) - Preset (1bit) )
  const unsigned int presetMask      = 0x1;
  const unsigned int alignmentMask   = 0x7E;
  const unsigned int slicingTypeMask = 0xF80;

  enum Flags { Preset           = 1 << 0
             , UnknownAlignment = 1 << 1
             , AlignLeft        = 1 << 2
             , AlignRight       = 1 << 3
             , AlignCenter      = 1 << 4
             , AlignTop         = 1 << 5
             , AlignBottom      = 1 << 6
             , UnknownType      = 1 << 7
             , Horizontal       = 1 << 8
             , Vertical         = 1 << 9
             , Device           = 1 << 10
             , Routing          = 1 << 11
             , None             = 1 << 12
             , MX               = 1 << 13
             , MY               = 1 << 14
             };


// -----------------------------------------------------------------------------------------------//
// Class : SingleNodeSet
// -----------------------------------------------------------------------------------------------//

  
  class SingleNodeSet
  {
    public:
      SingleNodeSet ( float height = 0, float width = 0 );
      SingleNodeSet ( SingleNodeSet* singleSet );
      ~SingleNodeSet ();
      
      virtual const std::vector< SingleNodeSet*>& getSet () const;
      friend bool operator == (SingleNodeSet const& lhs, SingleNodeSet const& rhs) 
      { 
        return ( (lhs.getHeight()==rhs.getHeight())&&(lhs.getWidth()==rhs.getWidth()) ); 
      }
      inline  unsigned int getCount          () const;
      inline  void         incrementCount    ();
      inline  float        getHeight         () const;
      inline  float        getWidth          () const; 
      virtual void         print             () const;
      virtual inline unsigned int getType    () const;
      virtual float        getDevicesArea    () const = 0;
      virtual inline float getOccupationArea () const;

    protected:
      float        _height;
      float        _width;
      unsigned int _cpt;

  };

  inline unsigned int SingleNodeSet::getCount          () const { return _cpt;        }
  inline void         SingleNodeSet::incrementCount    ()       { _cpt++;             }
  inline float        SingleNodeSet::getHeight         () const { return _height;     }
  inline float        SingleNodeSet::getWidth          () const { return _width ;     }
  inline unsigned int SingleNodeSet::getType           () const { return UnknownType; }
  inline float        SingleNodeSet::getOccupationArea () const { return 100;         }

// -----------------------------------------------------------------------------------------------//
// Class : HVSingleNodeSet
// -----------------------------------------------------------------------------------------------//

  
  class HVSingleNodeSet: public SingleNodeSet
  {   protected:
      HVSingleNodeSet  ( std::vector< SingleNodeSet*> dimensionSet);
      HVSingleNodeSet  ( HVSingleNodeSet* singleSet );
      ~HVSingleNodeSet ();

      inline const std::vector< SingleNodeSet*>& getSet () const;
             virtual void  print             () const;
      inline virtual void  calculateHeight   ();
      inline virtual void  calculateWidth    ();
                     float getDevicesArea    () const;
      inline         float getOccupationArea () const;
    protected:
      std::vector< SingleNodeSet*> _dimensionSet;
  };

  inline const std::vector< SingleNodeSet*>& HVSingleNodeSet::getSet() const { return _dimensionSet; }
  inline void  HVSingleNodeSet::calculateHeight () {}
  inline void  HVSingleNodeSet::calculateWidth  () {}
  inline float HVSingleNodeSet::getOccupationArea() const{ return getDevicesArea()/(_height * _width)*100; }

// -----------------------------------------------------------------------------------------------//
// Class : VSingleNodeSet
// -----------------------------------------------------------------------------------------------//

  
  class VSingleNodeSet: public HVSingleNodeSet
  {
    protected:
      VSingleNodeSet  ( std::vector< SingleNodeSet*> dimensionSet );
      VSingleNodeSet  ( VSingleNodeSet* singleSet );
      ~VSingleNodeSet ();

    public:
      static VSingleNodeSet* create          ( std::vector< SingleNodeSet*> dimensionSet );
      inline unsigned int    getType         () const;
      void                   calculateHeight ();
      void                   calculateWidth  ();
  };

  inline unsigned int VSingleNodeSet::getType () const { return Vertical; }


// -----------------------------------------------------------------------------------------------//
// Class : HSingleNodeSet
// -----------------------------------------------------------------------------------------------//

  
  class HSingleNodeSet: public HVSingleNodeSet
  {
    protected:
      HSingleNodeSet  ( std::vector< SingleNodeSet*> dimensionSet );
      HSingleNodeSet  ( HSingleNodeSet* singleSet );
      ~HSingleNodeSet ();
      
    public:
      static HSingleNodeSet* create          ( std::vector< SingleNodeSet*> dimensionSet );
      inline unsigned int    getType         () const;
      void                   calculateHeight ();
      void                   calculateWidth  ();
  };

  inline unsigned int HSingleNodeSet::getType () const { return Horizontal; }

// -----------------------------------------------------------------------------------------------//
// Class : DSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  class DSingleNodeSet: public SingleNodeSet
  {
    protected:
      DSingleNodeSet  ( float height, float width );
      DSingleNodeSet  ( DSingleNodeSet* singleSet );
      ~DSingleNodeSet ();

    public:
      static DSingleNodeSet* create  (float height, float width);
      inline unsigned int getType        () const;
      inline float        getDevicesArea () const;

  };

  inline unsigned int DSingleNodeSet::getType        () const { return Device; }
  inline float        DSingleNodeSet::getDevicesArea () const { return _height*_width; }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  class RHVSingleNodeSet: public SingleNodeSet
  {
    public:
      RHVSingleNodeSet  ( float height = 0, float width = 0);
      RHVSingleNodeSet  ( RHVSingleNodeSet* singleSet );
      ~RHVSingleNodeSet ();

      inline float        getHeight      () const;
      inline float        getWidth       () const;
      inline unsigned int getType        () const;
      inline float        getDevicesArea () const;

    private:
      float _height;
      float _width;
  };

 
  inline float        RHVSingleNodeSet::getHeight      () const { return _height; } 
  inline float        RHVSingleNodeSet::getWidth       () const { return _width;  }
  inline unsigned int RHVSingleNodeSet::getType        () const { return Routing; }
  inline float        RHVSingleNodeSet::getDevicesArea () const { return 0;       }


// -----------------------------------------------------------------------------------------------//
// Class : RHSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  class RHSingleNodeSet: public RHVSingleNodeSet
  {
      
    protected:
      RHSingleNodeSet  ( float height = 0 );
      RHSingleNodeSet  ( RHSingleNodeSet* singleSet);
      ~RHSingleNodeSet ();

    public:
      static RHSingleNodeSet* create ( float height );
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVSingleNodeSet
// -----------------------------------------------------------------------------------------------//


  class RVSingleNodeSet: public RHVSingleNodeSet
  {
    protected:
      RVSingleNodeSet  ( float width = 0 );
      RVSingleNodeSet  ( RVSingleNodeSet* singleSet);
      ~RVSingleNodeSet ();

    public:
      static RVSingleNodeSet* create ( float width );
  };

// -----------------------------------------------------------------------------------------------//
// Class : NodeSets
// -----------------------------------------------------------------------------------------------//
  
// To compare SingleNodeSets
  class compSingleNodeSet{
    public:
      bool operator() ( const  SingleNodeSet* lhs, const  SingleNodeSet* rhs) {
        return ( (lhs->getHeight() < rhs->getHeight()) || 
               ( (lhs->getHeight() == rhs->getHeight()) && (lhs->getWidth() < rhs->getWidth()))
               ); 
      }
  };

  class NodeSets 
  {
    public:
      NodeSets  ();
      NodeSets  (const NodeSets& other);
      ~NodeSets ();

      SingleNodeSet* operator[] (size_t i);

      inline void            clear     ();
      inline void            sort      ();
      inline size_t          size      ();
      inline bool            empty     ();
      inline std::vector<SingleNodeSet* > getNodeSets() const;
      inline std::vector<SingleNodeSet* >::iterator begin ();
      inline std::vector<SingleNodeSet* >::iterator end   ();
      std::vector<SingleNodeSet* >::iterator find  ( SingleNodeSet* singleNodeSet );
      std::vector<SingleNodeSet* >::iterator find  ( float height, float width    );

      void                   push_back ( SingleNodeSet* singleSet );
      std::pair<float,float> getPairH  ( float h ) const;
      void                   print     () const;
      NodeSets               clone     ();
      bool                   compare   ( NodeSets nodeSets2 );
      int                    findIndex ( float height, float width ) const;
      std::pair<float,float> getPairHW ( float height, float width ) const;

    private:
      std::vector<SingleNodeSet* > _nodeSets;
  };

  inline void   NodeSets::clear () { _nodeSets.clear(); }
  inline void   NodeSets::sort  () { std::sort(_nodeSets.begin(),_nodeSets.end(), compSingleNodeSet() ); }
  inline size_t NodeSets::size  () { return _nodeSets.size() ; }
  inline bool   NodeSets::empty () { return _nodeSets.empty(); }

  inline std::vector<SingleNodeSet* >           NodeSets::getNodeSets () const { return _nodeSets; }
  inline std::vector<SingleNodeSet* >::iterator NodeSets::begin       () { return _nodeSets.begin(); }
  inline std::vector<SingleNodeSet* >::iterator NodeSets::end         () { return _nodeSets.end  (); }

// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  class SlicingNode
  {
    protected:
    // Constructor & destructor
      SlicingNode ( unsigned int type       
                  , NodeSets     nodeSets  = NodeSets()
                  , unsigned int alignment = UnknownAlignment
                  , float        w         = 0
                  , float        h         = 0
                  );
      virtual ~SlicingNode ();

    public:
      // Accessors and Mutators
      inline unsigned int getType       () const;
      inline unsigned int getAlignment  () const;
      inline unsigned int getPreset     () const;
      inline float        getWidth      () const;
      inline float        getHeight     () const;
      inline float        getX          () const;
      inline float        getY          () const;
      inline const NodeSets& getNodeSets() const;

      inline bool isPreset      () const;
      inline bool isAlignLeft   () const;
      inline bool isAlignRight  () const;
      inline bool isAlignCenter () const;
      inline bool isAlignTop    () const;
      inline bool isAlignBottom () const;
      inline bool isHorizontal  () const;
      inline bool isVertical    () const;
      inline bool isDevice      () const;
      inline bool isRouting     () const;

      inline void setWidth     ( float        w         );
      inline void setHeight    ( float        h         );
      inline void setX         ( float        x         );
      inline void setY         ( float        y         );
      inline void setType      ( unsigned int type      );
      inline void setAlignment ( unsigned int alignment );
      inline void setPreset    ( unsigned int preset    );
      inline void setNodeSets  ( NodeSets     nodeSets  );

      inline std::pair<float,float> getPairH  ( float h ) const; 
      inline std::pair<float,float> getPairHW ( float height, float width ) const;
      virtual inline void updateGlobalSize ();

      friend inline std::ostream& operator << ( std::ostream& o, const SlicingNode* node ){ node->print(); return o; } 
      friend inline std::ostream& operator << ( std::ostream& o, const SlicingNode& node ){ node.print() ; return o; }

      // Common Virtual
      virtual void print    () const;
      virtual void place    ( float x = 0, float y = 0 ); 
      void         setPairH ( float h );       
      virtual void setGlobalSize2 ( float height, float width );
      virtual void _setGlobalSize2 ( float height, float width );

      // HVSlicingNode Virtual (see HVSlicingNode) or Errors Methods
      virtual void createChild ( unsigned int type, unsigned int alignment );
      virtual void createChild ( NodeSets     nodeSets  
                               , unsigned int alignment = UnknownAlignment
                               , float        w         = 0
                               , float        h         = 0
                               );
      virtual void createChild   ( int childIndex, int copyIndex, Flags tr = None ); 
      virtual void createRouting ( float hw );

      virtual int                              getNbChild             ()            const;
      virtual SlicingNode*                     getChild               ( int index ) const;
      virtual const std::vector<SlicingNode*>& getChildren            ()            const;
      virtual void                             printChildren          ()                 ;

      virtual void                             pushBackNode           ( SlicingNode* node )           ; 
      virtual void                             pushFrontNode          ( SlicingNode* node )           ; 
      virtual void                             removeAllNodes         ()                              ;
      virtual void                             insertNode             ( SlicingNode* node, int index ); 
      virtual void                             removeNode             ( SlicingNode* node )           ;

      virtual void                             setToleranceRatioH          ( float tolerance );
      virtual void                             setToleranceRatioW          ( float tolerance );
      virtual float                            getToleranceRatioH          () const           ;
      virtual float                            getToleranceRatioW          () const           ;
      virtual void                             recursiveSetToleranceRatioH ( float tolerance );
      virtual void                             recursiveSetToleranceRatioW ( float tolerance );

      virtual bool                             hasEmptyChildrenNodeSets    () const;

      virtual SlicingNode*                     clone                  ( Flags tr = None ) = 0;
      virtual void                             setSymmetry            ( int childIndex, int copyIndex );
      virtual int                              getLeafNumber          () const = 0;
      virtual void                             normalizeSymmetries    ();
      virtual std::list<std::pair< int,int> >  getSymmetries          () const;
      virtual bool                             recursiveCheckPreset   () const = 0;
      virtual float                            getDevicesArea         () const = 0;
      virtual float                            getOccupationArea      () const;

      virtual void                             setToleranceBandH      ( float tolerance );
      virtual void                             setToleranceBandW      ( float tolerance );
      virtual float                            getToleranceBandH      () const           ;
      virtual float                            getToleranceBandW      () const           ;
      virtual void                             setTolerances          (float trh, float trw, float tbh, float tbw);
      virtual void                             recursiveSetToleranceBandH ( float tolerance );
      virtual void                             recursiveSetToleranceBandW ( float tolerance );

    protected:
      unsigned int _flags;
      NodeSets     _nodeSets;    
      float        _x;         
      float        _y;         
      float        _w;         
      float        _h;         
  };

  inline unsigned int SlicingNode::getType      () const { return (_flags & slicingTypeMask); }
  inline unsigned int SlicingNode::getAlignment () const { return (_flags & alignmentMask  ); }
  inline unsigned int SlicingNode::getPreset    () const { return (_flags & presetMask     ); }
  inline float        SlicingNode::getWidth     () const { return _w    ; }
  inline float        SlicingNode::getHeight    () const { return _h    ; }
  inline float        SlicingNode::getX         () const { return _x    ; }
  inline float        SlicingNode::getY         () const { return _y    ; }
  inline const NodeSets& SlicingNode::getNodeSets () const { return _nodeSets; }

  inline bool SlicingNode::isPreset      () const { return (_flags & Preset)     ; }
  inline bool SlicingNode::isAlignLeft   () const { return (_flags & AlignLeft)  ; }
  inline bool SlicingNode::isAlignRight  () const { return (_flags & AlignRight) ; }
  inline bool SlicingNode::isAlignCenter () const { return (_flags & AlignCenter); }
  inline bool SlicingNode::isAlignTop    () const { return (_flags & AlignTop)   ; }
  inline bool SlicingNode::isAlignBottom () const { return (_flags & AlignBottom); }
  inline bool SlicingNode::isHorizontal  () const { return (_flags & Horizontal) ; }
  inline bool SlicingNode::isVertical    () const { return (_flags & Vertical)   ; }
  inline bool SlicingNode::isDevice      () const { return (_flags & Device)     ; }
  inline bool SlicingNode::isRouting     () const { return (_flags & Routing)    ; }

  inline void SlicingNode::setWidth     ( float        w         ) { _w = w         ; }
  inline void SlicingNode::setHeight    ( float        h         ) { _h = h         ; }
  inline void SlicingNode::setX         ( float        x         ) { _x = x         ; }
  inline void SlicingNode::setY         ( float        y         ) { _y = y         ; }
  inline void SlicingNode::setType      ( unsigned int type      ) { _flags = ((_flags & ~(slicingTypeMask) ) | type     ); }
  inline void SlicingNode::setAlignment ( unsigned int alignment ) { _flags = ((_flags & ~(alignmentMask)   ) | alignment); }
  inline void SlicingNode::setPreset    ( unsigned int preset    ) { _flags = ((_flags & ~(presetMask)      ) | preset   ); } 
  inline void SlicingNode::setNodeSets  ( NodeSets     nodeSets  ) { _nodeSets = nodeSets; }  
    
  inline std::pair<float,float> SlicingNode::getPairH ( float h ) const { return _nodeSets.getPairH(h); }  
  inline std::pair<float,float> SlicingNode::getPairHW ( float height, float width ) const { return _nodeSets.getPairHW(height, width); }     
  inline void SlicingNode::updateGlobalSize () {}    


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HVSlicingNode: public SlicingNode
  {
    protected:
      HVSlicingNode ( unsigned int type, unsigned int alignment  = AlignLeft );
      virtual ~HVSlicingNode ();

      bool                                  isSymmetry ( int index, std::pair<int,int>& symmetry );
      bool                                  isSymmetry ( int index );
    
    public:
      inline int                              getNbChild     ()            const;
      inline SlicingNode*                     getChild       ( int index ) const;
      inline const std::vector<SlicingNode*>& getChildren    ()            const;
      inline void                             pushBackNode   ( SlicingNode* node );  
      inline void                             pushFrontNode  ( SlicingNode* node ); 
      inline void                             removeAllNodes ();
      inline void                             setToleranceRatioH  ( float tolerance );
      inline void                             setToleranceRatioW  ( float tolerance );
      inline float                            getToleranceRatioH  () const;
      inline float                            getToleranceRatioW  () const;
      inline std::list<std::pair< int,int> >  getSymmetries  () const;
      inline void                             cpSymmetries   (std::list<std::pair< int,int> > sym);

    //void  createChild   ( unsigned int type, unsigned int alignment );
      void  createChild   ( int childIndex, int copyIndex, Flags tr = None); 
      void  printChildren ();
      void  insertNode    ( SlicingNode* node, int index ); 
      void  removeNode    ( SlicingNode* node ); 
      
      void  recursiveSetToleranceRatioH ( float tolerance );
      void  recursiveSetToleranceRatioW ( float tolerance );
      
      bool  hasEmptyChildrenNodeSets () const;
      
      void  setSymmetry          ( int childIndex, int copyIndex );
      int   getLeafNumber        () const;
      void  print                () const;
      void  normalizeSymmetries  ();

      bool  recursiveCheckPreset () const;
      float getDevicesArea       () const;
      float getOccupationArea    () const;

      inline void  setToleranceBandH ( float tolerance );
      inline void  setToleranceBandW ( float tolerance );
      inline float getToleranceBandH () const;
      inline float getToleranceBandW () const;
      void setTolerances(float trh, float trw, float tbh, float tbw);

      void  recursiveSetToleranceBandH ( float tolerance );
      void  recursiveSetToleranceBandW ( float tolerance );

      void  setGlobalSize2  ( float height, float width = 0 );
      void  _setGlobalSize2 ( float height, float width = 0 );

    protected:
      std::vector<SlicingNode*>       _children;
      float                           _toleranceRatioH;
      float                           _toleranceRatioW;
      float                           _toleranceBandH;
      float                           _toleranceBandW;
      std::list<std::pair <int,int> > _symmetries;
  };

  inline int                              HVSlicingNode::getNbChild  ()            const { return _children.size(); }
  inline SlicingNode*                     HVSlicingNode::getChild    ( int index ) const { return _children[index]; }
  inline const std::vector<SlicingNode*>& HVSlicingNode::getChildren ()            const { return _children;        }

  inline void HVSlicingNode::pushBackNode   ( SlicingNode* node ) { _children.push_back(node);                 }
  inline void HVSlicingNode::pushFrontNode  ( SlicingNode* node ) { _children.insert(_children.begin(), node); }
  inline void HVSlicingNode::removeAllNodes ()                    { _children.clear();                         }

  inline void  HVSlicingNode::setToleranceRatioH ( float tolerance ) { _toleranceRatioH = tolerance; }
  inline void  HVSlicingNode::setToleranceRatioW ( float tolerance ) { _toleranceRatioW = tolerance; }
  inline float HVSlicingNode::getToleranceRatioH ()            const { return _toleranceRatioH;      }
  inline float HVSlicingNode::getToleranceRatioW ()            const { return _toleranceRatioW;      }

  inline std::list<std::pair<int,int> > HVSlicingNode::getSymmetries() const { return _symmetries; }
  inline void HVSlicingNode::cpSymmetries(std::list<std::pair<int,int> > sym) { _symmetries = sym; }

  inline void  HVSlicingNode::setToleranceBandH ( float tolerance ) { _toleranceBandH = tolerance; }
  inline void  HVSlicingNode::setToleranceBandW ( float tolerance ) { _toleranceBandW = tolerance; }
  inline float HVSlicingNode::getToleranceBandH ()            const { return _toleranceBandH;      }
  inline float HVSlicingNode::getToleranceBandW ()            const { return _toleranceBandW;      }


// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  class VSlicingNode: public HVSlicingNode
  {
    private:
      VSlicingNode ( unsigned int type, unsigned int alignment  = UnknownAlignment);
      ~VSlicingNode ();    public:

    public:
      static VSlicingNode* create ( unsigned int alignment = AlignBottom );

      void          createChild ( unsigned int type, unsigned int alignment );
      void          createChild ( NodeSets     nodeSets  
                                , unsigned int alignment = AlignBottom
                                , float        w         = 0
                                , float        h         = 0
                                );

      void          createRouting ( float hw );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      VSlicingNode*          clone            ( Flags tr = None );
  };


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HSlicingNode: public HVSlicingNode
  {
    private:
      HSlicingNode ( unsigned int type, unsigned int alignment = UnknownAlignment );
      ~HSlicingNode ();

    public:
      static HSlicingNode* create ( unsigned int alignment  = AlignLeft );

      void          createChild ( unsigned int type, unsigned int alignment );
      void          createChild ( NodeSets     nodeSets  
                                , unsigned int alignment = AlignLeft
                                , float        w         = 0
                                , float        h         = 0
                                );
      void          createRouting ( float hw );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      HSlicingNode*          clone            ( Flags tr = None );
  };


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  class DSlicingNode: public SlicingNode
  {
    private:
      DSlicingNode ( unsigned int type
                   , NodeSets     nodeSets  
                   , unsigned int alignment = UnknownAlignment
                   , float        w         = 0
                   , float        h         = 0
                   );
      ~DSlicingNode ();

    public:
      inline int           getLeafNumber        () const;
      inline float         getDevicesArea       () const;
      inline bool          recursiveCheckPreset () const;
       
      static DSlicingNode* create ( NodeSets     nodeSets  
                                  , unsigned int alignment = UnknownAlignment
                                  , float        w         = 0
                                  , float        h         = 0
                                  );
      void                 print  () const;
      DSlicingNode*        clone  ( Flags tr = None );
  };

  inline int   DSlicingNode::getLeafNumber        () const { return 1  ; }
  inline float DSlicingNode::getDevicesArea       () const { return _h*_w; }
  inline bool  DSlicingNode::recursiveCheckPreset () const { return isPreset(); }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHVSlicingNode: public SlicingNode
  {
    protected:
      RHVSlicingNode  ( float h = 0, float w = 0 );
      ~RHVSlicingNode ();

    public:
      inline int             getLeafNumber        () const;
      inline float           getDevicesArea       () const;
      inline bool            recursiveCheckPreset () const;
      void                   print                () const;
      void                   _setGlobalSize2 ( float height, float width = 0 );

      // Error Message Methods
      unsigned int           getAlignment ()          const      ;
      NodeSets               getNodeSets  ()          const      ;
      std::pair<float,float> getPairH     ( float h ) const      ; 
      std::pair<float,float> getPairW     ( float w ) const      ; 
      void                   setPairH     ( float h )            ;      
  };

  inline int   RHVSlicingNode::getLeafNumber        () const { return 1; }
  inline float RHVSlicingNode::getDevicesArea       () const { return 0; }
  inline bool  RHVSlicingNode::recursiveCheckPreset () const { return isPreset(); }


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHSlicingNode: public RHVSlicingNode
  {
    private:
      RHSlicingNode  ( float h = 0 );
      ~RHSlicingNode ();

    public:
      static RHSlicingNode* create ( float h = 0 );
             RHSlicingNode* clone  ( Flags tr = None );

      // Error Message Methods
      void  setWidth ( float w );
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RVSlicingNode: public RHVSlicingNode
  {
    public:
      static RVSlicingNode* create ( float w = 0 );
      RVSlicingNode* clone  ( Flags tr = None );

      // Error Message Methods
      void  setHeight ( float h );

    private:
      RVSlicingNode  ( float w = 0 );
      ~RVSlicingNode ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : HVSetState
// -----------------------------------------------------------------------------------------------//

  class HVSetState
  {
    public:
      inline  std::vector<size_t> getBestSet  ();
      inline  bool   end           ();
      inline  int    getEndCounter ();
      virtual void   print         ();
      virtual void   next ();
      virtual float  getCurrentH () = 0;
      virtual float  getCurrentW () = 0;

      void           initSet      ();
      void           initModulos  ();
      bool           isSymmetry   ( int index, std::pair<int,int>& symmetry );
      bool           isSymmetry   ( int index );
      void           updateLimits ();      
      const NodeSets getNodeSets  (); 
      
    protected:
      HVSetState  ( HVSlicingNode* node );
      ~HVSetState ();

    protected:
      float                          _height;
      float                          _width;
      bool                           _isTop;
      std::vector<SlicingNode*>      _children;
      std::list<std::pair<int,int> > _symmetries;
      float                          _toleranceRatioH;
      float                          _toleranceRatioW;
      float                          _toleranceBandH;
      float                          _toleranceBandW;
      NodeSets                       _nodeSets;
      
      std::vector<int>               _modulos;
      int                            _counter;

      std::vector<size_t> _currentSet ;
      std::vector<size_t> _nextSet    ;

      std::pair<float,float> _hminWmin;
      std::pair<float,float> _hminWmax;
      std::pair<float,float> _hmaxWmin;
      std::pair<float,float> _hmaxWmax;

      std::pair<float,float> _wminHmin;
      std::pair<float,float> _wminHmax;
      std::pair<float,float> _wmaxHmin;
      std::pair<float,float> _wmaxHmax;
      
  };

  inline bool HVSetState::end           () { return (_counter == _modulos.back()+1); }
  inline int  HVSetState::getEndCounter () { return _modulos.back()+1              ; }


// -----------------------------------------------------------------------------------------------//
// Class : VSetState
// -----------------------------------------------------------------------------------------------//


  class VSetState: public HVSetState
  {
    public:
      VSetState  ( VSlicingNode* node );
      ~VSetState ();
      
      inline bool checkToleranceBandH ();
      void  next             ();
      float getMinH          ();
      float getCurrentH      ();
      float getCurrentW      ();
      void  print            ();
      void  push_back        ();
  };

  inline bool VSetState::checkToleranceBandH () { return (getCurrentH() - getMinH() <= _toleranceBandH); }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//


  class HSetState: public HVSetState
  {
    public:
      HSetState  ( HSlicingNode* node );
      ~HSetState ();

      inline bool checkToleranceBandW ();
      void  next             ();
      float getMinW          ();
      float getCurrentH      ();
      float getCurrentW      ();
      void  print            ();
      void  push_back        ();
  };

  inline bool HSetState::checkToleranceBandW () { return (getCurrentW() - getMinW() <= _toleranceBandW); }
  
}
#endif

