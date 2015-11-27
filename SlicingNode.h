#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

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
// Class : MapHW
// -----------------------------------------------------------------------------------------------//


  class MapHW
  {
    public:
      MapHW ( std::map<float,float>* map1 = NULL );
      ~MapHW();

      inline std::map <float,float>::const_iterator begin       () const;
      inline std::map <float,float>::const_iterator end         () const;
      inline std::map <float,float>::iterator       find        ( float key );
      inline std::map <float,float>::const_iterator upper_bound ( float key ) const;
      inline bool                                   empty       ();
      inline void                                   clear       ();
      inline size_t                                 size        ();
      inline std::map<float,float>*                 get         ();
      inline void                                   set         ( std::map<float,float>* map2 );
      inline void                                   insert      ( std::pair<float,float> pair );

      MapHW                  clone       ();
      bool                   compare     ( MapHW map2 );
      void                   print       ();
      std::pair<float,float> getPairH    (float h         ) const;
      std::pair<float,float> getPairW    (float w         ) const;
      void                   insertWorst (float h, float w);

    private:
      std::map<float,float>* _mapHW;
  };

  inline std::map <float,float>::const_iterator MapHW::begin       ()            const { return _mapHW->begin()          ; }
  inline std::map <float,float>::const_iterator MapHW::end         ()            const { return _mapHW->end()            ; }
  inline std::map <float,float>::iterator       MapHW::find        ( float key )       { return _mapHW->find(key)        ; }
  inline std::map <float,float>::const_iterator MapHW::upper_bound ( float key ) const { return _mapHW->upper_bound(key) ; }
  inline bool                                   MapHW::empty       ()                  { return _mapHW->empty()          ; }
  inline void                                   MapHW::clear       ()                  { return _mapHW->clear()          ; }
  inline size_t                                 MapHW::size        ()                  { return _mapHW->size()           ; }
  inline std::map<float,float>*                 MapHW::get         ()                  { return _mapHW                   ; }
  inline void                                   MapHW::set         ( std::map<float,float>* map2 ) { _mapHW = map2       ; }
  inline void                                   MapHW::insert      ( std::pair<float,float> pair ) { _mapHW->insert(pair); }


// -----------------------------------------------------------------------------------------------//
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  class SlicingNode
  {
    protected:
    // Constructor & destructor
      SlicingNode ( unsigned int type       
                  , MapHW        mapHW     = MapHW()
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
      inline MapHW        getMapHW      () const;

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
      inline void setMapHW     ( MapHW        mapHW     );
      inline void setType      ( unsigned int type      );
      inline void setAlignment ( unsigned int alignment );
      inline void setPreset    ( unsigned int preset    );

      inline void                   insertWorst ( float h, float w );
      inline std::pair<float,float> getPairH    ( float h ) const;   
      inline std::pair<float,float> getPairW    ( float w ) const;  

      virtual inline void updateGlobalSize ();

      // Common Virtual
      virtual void                   print          () const;
      virtual void                   place          ( float x = 0, float y = 0 ); 
              void                   setPairH       ( float h );       
      virtual std::pair<float,float> _setGlobalSize ( float height = 0, float width = 0 );   

      // HVSlicingNode Virtual (see HVSlicingNode) or Errors Methods
      virtual void createChild ( unsigned int type     
                               , unsigned int alignment  
                               , float        toleranceH = 0
                               , float        toleranceW = 0
                               , float        w          = 0
                               , float        h          = 0
                               );
      virtual void createChild ( MapHW        mapHW     
                               , unsigned int alignment = UnknownAlignment
                               , float        w         = 0
                               , float        h         = 0
                               );
      virtual void createChild   ( int childIndex, int copyIndex, Flags tr = None); 
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

      virtual void                             setToleranceH          ( float tolerance );
      virtual void                             setToleranceW          ( float tolerance );
      virtual float                            getToleranceH          () const           ;
      virtual float                            getToleranceW          () const           ;
      virtual void                             recursiveSetToleranceH ( float tolerance );
      virtual void                             recursiveSetToleranceW ( float tolerance );

      virtual bool                             hasEmptyChildrenMap    () const;

      virtual SlicingNode*                     clone                  ( Flags tr = None ) = 0;
      virtual void                             setSymmetry            ( int childIndex, int copyIndex );
      virtual int                              getLeafNumber          () const = 0;
      virtual void                             normalizeSymmetries    ();
      virtual std::list<std::pair< int,int> >  getSymmetries          () const;
      virtual bool                             recursiveCheckPreset   () const = 0;
      virtual float                            getDevicesArea         () const = 0;
      virtual float                            getOccupationArea      () const;
    protected:
      unsigned int _flags;
      MapHW        _mapHW;     
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
  inline MapHW        SlicingNode::getMapHW     () const { return _mapHW; }

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

  inline void SlicingNode::setWidth         ( float        w         ) { _w = w         ; }
  inline void SlicingNode::setHeight        ( float        h         ) { _h = h         ; }
  inline void SlicingNode::setX             ( float        x         ) { _x = x         ; }
  inline void SlicingNode::setY             ( float        y         ) { _y = y         ; }
  inline void SlicingNode::setMapHW         ( MapHW        mapHW     ) { _mapHW  = mapHW; }
  inline void SlicingNode::setType          ( unsigned int type      ) { _flags = ((_flags & ~(slicingTypeMask) ) | type     ); }
  inline void SlicingNode::setAlignment     ( unsigned int alignment ) { _flags = ((_flags & ~(alignmentMask)   ) | alignment); }
  inline void SlicingNode::setPreset        ( unsigned int preset    ) { _flags = ((_flags & ~(presetMask)      ) | preset   ); }   
    
  inline void                   SlicingNode::insertWorst ( float h, float w ) { _mapHW.insertWorst(h,w)  ; }
  inline std::pair<float,float> SlicingNode::getPairH    ( float h ) const    { return _mapHW.getPairH(h); }
  inline std::pair<float,float> SlicingNode::getPairW    ( float w ) const    { return _mapHW.getPairW(w); }

  inline void SlicingNode::updateGlobalSize ()                         {}    

  inline std::ostream& operator << ( std::ostream& o, const SlicingNode* node ){ node->print(); return o; } 
  inline std::ostream& operator << ( std::ostream& o, const SlicingNode& node ){ node.print() ; return o; }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HVSlicingNode: public SlicingNode
  {
    protected:
      HVSlicingNode ( unsigned int type
                    , unsigned int alignment  = AlignLeft
                    , float        toleranceH = 0
                    , float        toleranceW = 0
                    , float        w          = 0
                    , float        h          = 0
                    );
      virtual ~HVSlicingNode ();

      std::vector< std::pair<float,float> > initSet    ();
      std::vector<int>                      setModulos ();
      bool                                  isSymmetry ( int index, std::pair<int,int>& symmetry );
      bool                                  isSymmetry ( int index );

      void updateBestSet( float& currentW
                        , float& currentH
                        , float& width
                        , float& height
                        , float& bestWidth
                        , float& bestHeight
                        , std::vector<std::pair<float,float> >& bestSet
                        , std::vector<std::pair<float,float> >& currentSet
                        );
      
    public:
      inline int                              getNbChild     ()            const;
      inline SlicingNode*                     getChild       ( int index ) const;
      inline const std::vector<SlicingNode*>& getChildren    ()            const;
      inline void                             pushBackNode   ( SlicingNode* node );  
      inline void                             pushFrontNode  ( SlicingNode* node ); 
      inline void                             removeAllNodes ();
      inline void                             setToleranceH  ( float tolerance );
      inline void                             setToleranceW  ( float tolerance );
      inline float                            getToleranceH  () const;
      inline float                            getToleranceW  () const;
      inline std::list<std::pair< int,int> >  getSymmetries  () const;
      inline void                             cpSymmetries   (std::list<std::pair< int,int> > sym);

      void  createChild            ( int childIndex, int copyIndex, Flags tr = None); 
      void  printChildren          ();
      void  insertNode             ( SlicingNode* node, int index ); 
      void  removeNode             ( SlicingNode* node ); 
      
      void  recursiveSetToleranceH ( float tolerance );
      void  recursiveSetToleranceW ( float tolerance );
      
      bool  hasEmptyChildrenMap    () const;
      
      void  setSymmetry            ( int childIndex, int copyIndex );
      int   getLeafNumber          () const;
      void  print                  () const;
      void  normalizeSymmetries    ();

      bool  recursiveCheckPreset () const;
      float getDevicesArea       () const;
      float getOccupationArea    () const;


    protected:
      std::vector<SlicingNode*>       _children;
      float                           _toleranceH;
      float                           _toleranceW;
      std::list<std::pair <int,int> > _symmetries;
  };

  inline int                              HVSlicingNode::getNbChild  ()            const { return _children.size(); }
  inline SlicingNode*                     HVSlicingNode::getChild    ( int index ) const { return _children[index]; }
  inline const std::vector<SlicingNode*>& HVSlicingNode::getChildren ()            const { return _children;        }

  inline void HVSlicingNode::pushBackNode   ( SlicingNode* node ) { _children.push_back(node);                 }
  inline void HVSlicingNode::pushFrontNode  ( SlicingNode* node ) { _children.insert(_children.begin(), node); }
  inline void HVSlicingNode::removeAllNodes ()                    { _children.clear();                         }

  inline void  HVSlicingNode::setToleranceH ( float tolerance )     { _toleranceH = tolerance; }
  inline void  HVSlicingNode::setToleranceW ( float tolerance )     { _toleranceW = tolerance; }
  inline float HVSlicingNode::getToleranceH ()                const { return _toleranceH;      }
  inline float HVSlicingNode::getToleranceW ()                const { return _toleranceW;      }

  inline std::list<std::pair<int,int> > HVSlicingNode::getSymmetries() const { return _symmetries; }
  inline void HVSlicingNode::cpSymmetries(std::list<std::pair<int,int> > sym) { _symmetries = sym; }


// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  class VSlicingNode: public HVSlicingNode
  {
    private:
      VSlicingNode ( unsigned int type
                   , unsigned int alignment  = UnknownAlignment
                   , float        toleranceH = 0
                   , float        toleranceW = 0
                   , float        w          = 0
                   , float        h          = 0
                   );
      ~VSlicingNode ();    public:

    /*void setNextSet ( float&                                 currentW
                      , std::list  < std::pair<float,float> >& currentHs
                      , int&                                   counter
                      , std::vector<int>&                      modulos
                      , std::vector<std:: pair<float,float> >& nextSet
                      , std::vector< std::pair<float,float> >& currentSet
                      );*/
      void recursiveSetGlobalSize( std::vector<std::pair<float,float> >  bestSet
                                 , float&                                finalWidth
                                 , float&                                finalHeight
                                 , float&                                height
                                 );

    public:
      static VSlicingNode* create ( unsigned int alignment  = AlignBottom
                                  , float        toleranceH = 0
                                  , float        toleranceW = 0
                                  , float        w          = 0
                                  , float        h          = 0
                                  );

      void          createChild ( unsigned int type     
                                , unsigned int alignment  = AlignBottom
                                , float        toleranceH = 0
                                , float        toleranceW = 0
                                , float        w          = 0
                                , float        h          = 0
                                );
      void          createChild ( MapHW        mapHW     
                                , unsigned int alignment = AlignBottom
                                , float        w         = 0
                                , float        h         = 0
                                );

      void          createRouting ( float hw );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      std::pair<float,float> setGlobalSize    ( float height = 0, float width = 0 );
      std::pair<float,float> _setGlobalSize   ( float height = 0, float width = 0 );

      VSlicingNode*          clone            ( Flags tr = None );
  };


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HSlicingNode: public HVSlicingNode
  {
    private:
      HSlicingNode ( unsigned int type
                   , unsigned int alignment  = UnknownAlignment
                   , float        toleranceH = 0
                   , float        toleranceW = 0
                   , float        w          = 0
                   , float        h          = 0
                   );
      ~HSlicingNode ();

    /*void setNextSet ( std::list   <std::pair<float,float> >& currentWs
                      , float&                                 currentH
                      , int&                                   counter
                      , std::vector<int>&                      modulos
                      , std::vector<std:: pair<float,float> >& nextSet
                      , std::vector< std::pair<float,float> >& currentSet
                      );*/
      void recursiveSetGlobalSize( std::vector<std::pair<float,float> >  bestSet
                                 , float&                                finalWidth
                                 , float&                                finalHeight
                                 , float&                                width
                                 );

    public:
      static HSlicingNode* create ( unsigned int alignment  = AlignLeft
                                  , float        toleranceH = 0
                                  , float        toleranceW = 0
                                  , float        w          = 0
                                  , float        h          = 0
                                  );

      void          createChild ( unsigned int type     
                                , unsigned int alignment  = AlignLeft
                                , float        toleranceH = 0
                                , float        toleranceW = 0
                                , float        w          = 0
                                , float        h          = 0
                                );
      void          createChild ( MapHW        mapHW     
                                , unsigned int alignment = AlignLeft
                                , float        w         = 0
                                , float        h         = 0
                                );
      void          createRouting ( float hw );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      std::pair<float,float> setGlobalSize    ( float height = 0, float width = 0 );
      std::pair<float,float> _setGlobalSize   ( float height = 0, float width = 0 );

      HSlicingNode*          clone            ( Flags tr = None );
  };


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  class DSlicingNode: public SlicingNode
  {
    private:
      DSlicingNode ( unsigned int type
                   , MapHW        mapHW     
                   , unsigned int alignment = UnknownAlignment
                   , float        w         = 0
                   , float        h         = 0
                   );
      ~DSlicingNode ();

    public:
      inline int           getLeafNumber        () const;
      inline float         getDevicesArea       () const;
      inline bool          recursiveCheckPreset () const;
       
      static DSlicingNode* create ( MapHW        mapHW     
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
      RHVSlicingNode  ( float w = 0, float h = 0 );
      ~RHVSlicingNode ();

    public:
      inline int             getLeafNumber        () const;
      inline float           getDevicesArea       () const;
      inline bool            recursiveCheckPreset () const;
      void                   print                () const;

      // Error Message Methods
      unsigned int           getAlignment ()          const      ;
      MapHW                  getMapHW     ()          const      ;
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
      inline std::vector<std::pair<float,float> > getBestSet  ();
      inline bool   end         ();
      inline MapHW  getMapHW    ();
             void   initSet     ();
             void   initModulos ();
             bool   isSymmetry  ( int index, std::pair<int,int>& symmetry );
             bool   isSymmetry  ( int index );
      virtual void  print       ();
      virtual void  next ();
      virtual float getBestH    () = 0;
      virtual float getBestW    () = 0;
      virtual float getCurrentH () = 0;
      virtual float getCurrentW () = 0;
      
    protected:
      HVSetState  ( HVSlicingNode* node, float height = 0, float width = 0, bool isTop = true );
      ~HVSetState ();

    protected:
      float                                 _height    ;
      float                                 _width     ;
      bool                                  _isTop     ;
      std::vector<SlicingNode*>             _children  ;
      std::list<std::pair <int,int> >       _symmetries;
      float                                 _toleranceH;
      float                                 _toleranceW;
      MapHW                                 _mapHW     ;
      
      std::vector<int>                      _modulos   ;
      int                                   _counter   ;

      std::vector<std::pair<float,float> >  _bestSet   ;
      std::vector<std::pair<float,float> >  _currentSet;
      std::vector<std::pair<float,float> >  _nextSet   ;
  };
  inline std::vector<std::pair<float,float> > HVSetState::getBestSet (){ return _bestSet; }
  inline bool  HVSetState::end     (){ return (_counter == _modulos.back()+1); }
  inline MapHW HVSetState::getMapHW(){ return _mapHW; }


// -----------------------------------------------------------------------------------------------//
// Class : VSetState
// -----------------------------------------------------------------------------------------------//


  class VSetState: public HVSetState
  {
    public:
      VSetState  ( VSlicingNode* node, float height = 0, float width = 0, bool isTop = false );
      ~VSetState ();

      inline void insertWorst ();
      inline bool checkToleranceH ();
      void  next             ();
      float getMinH          ();
      float getBestH         ();
      float getBestW         ();
      float getCurrentH      ();
      float getCurrentW      ();
      void  updateBestSetTop (); 
      void  updateBestSet    (); 
      void  print            ();
  };
  
  inline void VSetState::insertWorst()
  { if ( checkToleranceH() ) { _mapHW.insertWorst( getCurrentH(), getCurrentW() ); } }
  inline bool VSetState::checkToleranceH()
  { return (getCurrentH() - getMinH() <= _toleranceH); }


// -----------------------------------------------------------------------------------------------//
// Class : HSetState
// -----------------------------------------------------------------------------------------------//


  class HSetState: public HVSetState
  {
    public:
      HSetState  ( HSlicingNode* node, float height = 0, float width = 0, bool isTop = false);
      ~HSetState ();

      inline void insertWorst ();
      inline bool checkToleranceW ();
      void  next             ();
      float getMinW          ();
      float getBestH         ();
      float getBestW         ();
      float getCurrentH      ();
      float getCurrentW      ();
      void  updateBestSetTop (); 
      void  updateBestSet    (); 
      void  print            ();
  };

  inline void HSetState::insertWorst()
  { if ( checkToleranceW() ) { _mapHW.insertWorst( getCurrentH(), getCurrentW() ); } }

  inline bool HSetState::checkToleranceW()
  { return (getCurrentW() - getMinW() <= _toleranceW); }
}

#endif

