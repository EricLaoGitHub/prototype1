#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

namespace SlicingTree{
  
// Flags = ( Alignment (3bits) - SlicingType (3bits) - Transformation (2bits) - Preset (1bit) )
  const unsigned short alignmentMask       = 0x1C;
  const unsigned short alignmentShift      = 6;
  const unsigned short alignmentClear      = 0xE3F;
  const unsigned short slicingTypeMask     = 0x38;
  const unsigned short slicingTypeShift    = 3;
  const unsigned short slicingTypeClear    = 0xC7;
  const unsigned short transformationMask  = 0x6;
  const unsigned short transformationShift = 1;
  const unsigned short transformationClear = 0x8;
  const unsigned short presetMask          = 0x1;
  const unsigned short presetShift         = 0;
 const unsigned short  presetClear         = 0xE;

  enum Alignment { UnknownAlignment = 0
                 , AlignLeft        = 1
                 , AlignRight       = 2
                 , AlignCenter      = 3
                 , AlignTop         = 4
                 , AlignBottom      = 5
                 }; 

  enum SlicingType { Unknown     = 0
                   , Horizontal  = 1
                   , Vertical    = 2
                   , DeviceNode  = 3
                   , RoutingNode = 4 
                   };

  enum Transformation { None = 0
                      , MX = 1
                      , MY = 2 
                      };


// -----------------------------------------------------------------------------------------------//
// Class : MapHW
// -----------------------------------------------------------------------------------------------//


  class MapHW
  {
    public:
      static MapHW create ( std::map<float,float>* map1 = NULL );

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
             MapHW                                  clone       ();
             bool                                   compare     ( MapHW map2 );
             void                                   print       ();

      std::pair<float,float> getPairH    (float h         ) const;
      std::pair<float,float> getPairW    (float w         ) const;
      void                   insertWorst (float h, float w);

    public:
      MapHW ( std::map<float,float>* map1 = NULL );
      ~MapHW();

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
    public:
      // Accessors & Mutators
      inline SlicingType getType      () const;
      inline float       getWidth     () const;
      inline float       getHeight    () const;
      inline float       getX         () const;
      inline float       getY         () const;
      inline Alignment   getAlignment () const;
      inline MapHW       getMapHW     () const;
      inline bool        getPreset    () const;

      inline void        setWidth     ( float     w      );
      inline void        setHeight    ( float     h      );
      inline void        setX         ( float     x      );
      inline void        setY         ( float     y      );
      inline void        setAlignment ( Alignment type   );
      inline void        setPreset    ( bool      preset );
      inline void        setMapHW     ( MapHW     mapHW  );

      // Common Virtual

    //inline std::ostream& operator<< ( std::ostream& o, const SlicingNode& node ){ node.print(); return o; } 
      
      virtual void           print    () const;
      virtual void           place    ( float x = 0, float y = 0 ); // Place the node in the plan at (x,y)

      inline std::pair<float,float> getPairH    ( float h ) const;   // Given a height, return width
      inline std::pair<float,float> getPairW    ( float w ) const;   // Given a width , return height
             void                   setPairH    ( float h );         // Given a height, set width
      inline void                   insertWorst ( float h, float w );

      // HVSlicingNode Virtual (see HVSlicingNode)
      virtual void createChild ( SlicingType type     
                               , Alignment   alignment  = UnknownAlignment
                               , float       toleranceH = 0
                               , float       toleranceW = 0
                               , float       w          = 0
                               , float       h          = 0
                               );
      virtual void createChild ( MapHW     mapHW     
                               , Alignment alignment = UnknownAlignment
                               , float     w         = 0
                               , float     h         = 0
                               );
      virtual void createChild ( float hw = 0 );
      virtual void createChild ( int childIndex, int copyIndex, Transformation tr = None); 
      
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

      virtual bool                             hasEmptyChildrenMap    () const                             ;
      virtual inline void                      updateGlobalSize       ()                                   ;
      virtual std::pair<float,float>           setGlobalSize          ( float height = 0, float width = 0 );

      virtual SlicingNode* clone               ( Transformation tr = None )  = 0;
      virtual void         setSymmetry         ( int childIndex, int copyIndex );
      virtual int          getLeafNumber       () const                      = 0;
      virtual void         normalizeSymmetries ()                               ;
      virtual std::list<std::pair< int,int> > getSymmetries () const           ;

    protected:
    // Constructor & destructor
      SlicingNode ( SlicingType type       
                  , MapHW       mapHW     = MapHW::create()
                  , Alignment   alignment = UnknownAlignment
                  , float       w         = 0
                  , float       h         = 0
                  );
      virtual ~SlicingNode ();


    protected:
      SlicingType _type;      
      MapHW       _mapHW;     
      Alignment   _alignment; 
      float       _x;         
      float       _y;         
      float       _w;         
      float       _h;         
      bool        _preset;    
  };

  inline SlicingType SlicingNode::getType      () const { return _type;      }
  inline float       SlicingNode::getWidth     () const { return _w;         }
  inline float       SlicingNode::getHeight    () const { return _h;         }
  inline float       SlicingNode::getX         () const { return _x;         }
  inline float       SlicingNode::getY         () const { return _y;         }
  inline Alignment   SlicingNode::getAlignment () const { return _alignment; }
  inline MapHW       SlicingNode::getMapHW     () const { return _mapHW;     }
  inline bool        SlicingNode::getPreset    () const { return _preset;    }

  inline void SlicingNode::setWidth         ( float w )             { _w = w                ; }
  inline void SlicingNode::setHeight        ( float h )             { _h = h                ; }
  inline void SlicingNode::setX             ( float x )             { _x = x                ; }
  inline void SlicingNode::setY             ( float y )             { _y = y                ; }
  inline void SlicingNode::setAlignment     ( Alignment alignment ) { _alignment = alignment; }
  inline void SlicingNode::setPreset        ( bool preset )         { _preset = preset      ; }
  inline void SlicingNode::setMapHW         ( MapHW mapHW )         { _mapHW  = mapHW       ; }
  inline void SlicingNode::updateGlobalSize ()                      {}      
    
  inline void                   SlicingNode::insertWorst ( float h, float w ) { _mapHW.insertWorst(h,w)  ; }
  inline std::pair<float,float> SlicingNode::getPairH    ( float h ) const    { return _mapHW.getPairH(h); }
  inline std::pair<float,float> SlicingNode::getPairW    ( float w ) const    { return _mapHW.getPairW(w); }

  inline std::ostream& operator << ( std::ostream& o, const SlicingNode* node ){ node->print(); return o; } 
  inline std::ostream& operator << ( std::ostream& o, const SlicingNode& node ){ node.print() ; return o; }

// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HVSlicingNode: public SlicingNode
  {
    public:
      void createChild ( int childIndex, int copyIndex, Transformation tr = None); 

      inline int                              getNbChild    ()            const;
      inline SlicingNode*                     getChild      ( int index ) const;
      inline const std::vector<SlicingNode*>& getChildren   ()            const;
             void                             printChildren ();

      inline void  pushBackNode           ( SlicingNode* node );  
      inline void  pushFrontNode          ( SlicingNode* node ); 
      inline void  removeAllNodes         ();
             void  insertNode             ( SlicingNode* node, int index ); 
             void  removeNode             ( SlicingNode* node ); 

      inline void  setToleranceH          ( float tolerance );
      inline void  setToleranceW          ( float tolerance );
      inline float getToleranceH          () const;
      inline float getToleranceW          () const;
             void  recursiveSetToleranceH ( float tolerance );
             void  recursiveSetToleranceW ( float tolerance );

             bool  hasEmptyChildrenMap    () const;

             void  setSymmetry            ( int childIndex, int copyIndex );
             int   getLeafNumber          () const;
             void  print                  () const;
             void  normalizeSymmetries    ();

      inline std::list<std::pair< int,int> > getSymmetries () const;

    protected:
      HVSlicingNode ( SlicingType type
                    , Alignment   alignment  = AlignLeft
                    , float       toleranceH = 0
                    , float       toleranceW = 0
                    , float       w          = 0
                    , float       h          = 0
                    );
      virtual ~HVSlicingNode ();

      std::vector< std::pair<float,float> > initSet    ();
      std::vector<int>                      setModulos ();
      bool                                  isSymmetry ( int index, std::pair<int,int>& symmetry);

      void updateBestSet( float& currentW
                        , float& currentH
                        , float& width
                        , float& height
                        , float& bestWidth
                        , float& bestHeight
                        , std::vector<std::pair<float,float> >& bestSet
                        , std::vector<std::pair<float,float> >& currentSet
                        );
      

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


// -----------------------------------------------------------------------------------------------//
// Class : VSlicingNode
// -----------------------------------------------------------------------------------------------//


  class VSlicingNode: public HVSlicingNode
  {
    public:
      static VSlicingNode* create ( Alignment alignment  = AlignBottom
                                  , float     toleranceH = 0
                                  , float     toleranceW = 0
                                  , float     w          = 0
                                  , float     h          = 0
                                  );

      void          createChild ( SlicingType type     
                                , Alignment   alignment  = AlignBottom
                                , float       toleranceH = 0
                                , float       toleranceW = 0
                                , float       w          = 0
                                , float       h          = 0
                                );
      void          createChild ( MapHW     mapHW     
                                , Alignment alignment = AlignBottom
                                , float     w         = 0
                                , float     h         = 0
                                );
      void          createChild ( float hw = 0 );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      std::pair<float,float> setGlobalSize    ( float height = 0, float width = 0 );

      VSlicingNode*          clone            ( Transformation tr = None );

    private:
      VSlicingNode ( SlicingType type
                   , Alignment   alignment  = UnknownAlignment
                   , float       toleranceH = 0
                   , float       toleranceW = 0
                   , float       w          = 0
                   , float       h          = 0
                   );
      ~VSlicingNode ();    public:

      void setNextSet ( float&                                 currentW
                      , std::list  < std::pair<float,float> >& currentHs
                      , int&                                   counter
                      , std::vector<int>&                      modulos
                      , std::vector<std:: pair<float,float> >& nextSet
                      , std::vector< std::pair<float,float> >& currentSet
                      );
      void recursiveSetGlobalSize( std::vector<std::pair<float,float> >& bestSet
                                 , float&                                finalWidth
                                 , float&                                finalHeight
                                 , float&                                height
                                 );

  };


// -----------------------------------------------------------------------------------------------//
// Class : HSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HSlicingNode: public HVSlicingNode
  {
    public:
      static HSlicingNode* create ( Alignment alignment  = UnknownAlignment
                                  , float     toleranceH = 0
                                  , float     toleranceW = 0
                                  , float     w          = 0
                                  , float     h          = 0
                                  );

      void          createChild ( SlicingType type     
                                , Alignment   alignment  = AlignLeft
                                , float       toleranceH = 0
                                , float       toleranceW = 0
                                , float       w          = 0
                                , float       h          = 0
                                );
      void          createChild ( MapHW     mapHW     
                                , Alignment alignment = AlignLeft
                                , float     w         = 0
                                , float     h         = 0
                                );
      void          createChild ( float hw = 0 );

      void          print       () const;
      void          place       ( float x = 0, float y = 0 );

      void                   updateGlobalSize ();
      std::pair<float,float> setGlobalSize    ( float height = 0, float width = 0 );

      HSlicingNode*          clone            ( Transformation tr = None );

    private:
      HSlicingNode ( SlicingType type
                   , Alignment   alignment  = UnknownAlignment
                   , float       toleranceH = 0
                   , float       toleranceW = 0
                   , float       w          = 0
                   , float       h          = 0
                   );
      ~HSlicingNode ();

      void setNextSet ( std::list   <std::pair<float,float> >& currentWs
                      , float&                                 currentH
                      , int&                                   counter
                      , std::vector<int>&                      modulos
                      , std::vector<std:: pair<float,float> >& nextSet
                      , std::vector< std::pair<float,float> >& currentSet
                      );
      void recursiveSetGlobalSize( std::vector<std::pair<float,float> >& bestSet
                                 , float&                                finalWidth
                                 , float&                                finalHeight
                                 , float&                                width
                                 );
  };


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  class DSlicingNode: public SlicingNode
  {
    public:
      static DSlicingNode* create ( MapHW     mapHW     
                                  , Alignment alignment = UnknownAlignment
                                  , float     w         = 0
                                  , float     h         = 0
                                  );
      void                 print         () const;
      inline int           getLeafNumber () const;
      DSlicingNode*        clone         ( Transformation tr = None );

    private:
      DSlicingNode ( SlicingType type
                   , MapHW       mapHW     
                   , Alignment   alignment = UnknownAlignment
                   , float       w         = 0
                   , float       h         = 0
                   );
      ~DSlicingNode ();
  };

  inline int   DSlicingNode::getLeafNumber () const { return 1 ; }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHVSlicingNode: public SlicingNode
  {
    public:
      void                   print         () const;
      inline int             getLeafNumber () const;

      // Error Message Methods
      Alignment              getAlignment ()              const;
      MapHW                  getMapHW     ()              const;
      void                   setPreset    ( bool preset )      ;
      std::pair<float,float> getPairH     ( float h )     const; 
      std::pair<float,float> getPairW     ( float w )     const; 
      void                   setPairH     ( float h )          ;      

    protected:
      RHVSlicingNode  ( float w = 0, float h = 0 );
      ~RHVSlicingNode ();
  };

  inline int  RHVSlicingNode::getLeafNumber () const { return 1; }


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHSlicingNode: public RHVSlicingNode
  {
    public:
      static RHSlicingNode* create ( float h = 0 );
             RHSlicingNode* clone  ( Transformation tr = None );

      // Error Message Methods
      float getWidth () const;
      void  setWidth ( float w );

    private:
      RHSlicingNode  ( float h = 0 );
      ~RHSlicingNode ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//

  class RVSlicingNode: public RHVSlicingNode
  {
    public:
      static RVSlicingNode* create ( float w = 0 );
             RVSlicingNode* clone  ( Transformation tr = None );

      // Error Message Methods
      float getHeight () const;
      void  setHeight ( float h );

    private:
      RVSlicingNode  ( float w = 0 );
      ~RVSlicingNode ();
  };


}

#endif

