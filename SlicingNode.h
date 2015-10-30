#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

namespace SlicingTree{

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
// Class : SlicingNode
// -----------------------------------------------------------------------------------------------//


  class SlicingNode
  {
    public:
      // Accessors & Mutators
      inline SlicingType            getType      () const;
      inline float                  getWidth     () const;
      inline float                  getHeight    () const;
      inline float                  getX         () const;
      inline float                  getY         () const;
      inline Alignment              getAlignment () const;
      inline std::map<float,float>* getMapHW     () const;
      inline bool                   getPreset    () const;

      inline void setWidth     (float w);
      inline void setHeight    (float h);
      inline void setX         (float x);
      inline void setY         (float y);
      inline void setAlignment (Alignment type);
      inline void setPreset    (bool preset);
      inline void setMapHW     (std::map<float,float>* mapHW);

      // Common Virtual
      virtual void print () const;
      virtual void place (float x = 0, float y = 0) = 0; // Place the node in the plan at (x,y)

      std::pair<float,float> getPairH (float h) const;   // Given a height, return width
      std::pair<float,float> getPairW (float w) const;   // Given a width , return height
      void                   setPairH (float h);         // Given a height, set width

      // HVSlicingNode Virtual (see HVSlicingNode)
      virtual void createPushBackNode ( SlicingType type
                                      , Alignment   alignment  = UnknownAlignment
                                      , float       toleranceH = 0
                                      , float       toleranceW = 0
                                      , float       x          = 0
                                      , float       y          = 0
                                      , float       w          = 0
                                      , float       h          = 0
                                      ) = 0;
      
      virtual void createPushBackDevice ( std::map<float,float>* mapHW     = NULL
                                        , Alignment              alignment = UnknownAlignment
                                        , float                  x         = 0
                                        , float                  y         = 0
                                        , float                  w         = 0
                                        , float                  h         = 0
                                        ) = 0;

      virtual void createPushBackRouting ( float hw = 0
                                         , float x  = 0
                                         , float y  = 0 
                                         ) = 0;
      
      virtual int                              getNbChild       ()          const = 0;
      virtual SlicingNode*                     getChild         (int index) const = 0;
      virtual const std::vector<SlicingNode*>& getChildren      ()          const = 0;
      virtual void                             printChildren    ()                = 0;

      virtual void  pushBackNode   (SlicingNode* node)            = 0; 
      virtual void  pushFrontNode  (SlicingNode* node)            = 0; 
      virtual void  removeAllNodes ()                             = 0;
      virtual void  insertNode     (SlicingNode* node, int index) = 0; 
      virtual void  removeNode     (SlicingNode* node)            = 0;

      virtual void  setToleranceH    (float tolerance) = 0;
      virtual void  setToleranceW    (float tolerance) = 0;
      virtual float getToleranceH    () const          = 0;
      virtual float getToleranceW    () const          = 0;
      virtual void  setAllToleranceH (float tolerance) = 0;
      virtual void  setAllToleranceW (float tolerance) = 0;

      virtual bool                   emptyChildrenMap () const                            = 0;
      virtual void                   updateGlobalSize ()                                  = 0;
      virtual std::pair<float,float> setGlobalSize    (float height = 0, float width = 0) = 0;

      virtual SlicingNode* clone          (Transformation tr = None)   = 0;
      virtual void         createSymmetry ( int childIndex
                                          , int copyIndex
                                          , Transformation tr = None
                                          )                            = 0;
      virtual void setSymmetry         (int childIndex, int copyIndex) = 0;
      virtual int  getLeafNumber       () const                        = 0;
      virtual void normalizeSymmetries ()                              = 0;
      virtual std::list<std::pair< int,int> > getSymmetries () const   = 0;

    protected:
    // Constructor & destructor
      SlicingNode ( SlicingType            type       
                  , std::map<float,float>* mapHW     = NULL
                  , Alignment              alignment = UnknownAlignment
                  , float                  x         = 0
                  , float                  y         = 0
                  , float                  w         = 0
                  , float                  h         = 0
                  );
      virtual ~SlicingNode ();


    protected:
      SlicingType            _type;      // Node type (see enum)
      std::map<float,float>* _mapHW;     // std::map containing node sizes
      Alignment              _alignment; // Centering (see enum)
      float                  _x;         // position x
      float                  _y;         // position y
      float                  _w;         // width
      float                  _h;         // height
      bool                   _preset;    // preset
  };

  inline SlicingType            SlicingNode::getType      () const { return _type;      }
  inline float                  SlicingNode::getWidth     () const { return _w;         }
  inline float                  SlicingNode::getHeight    () const { return _h;         }
  inline float                  SlicingNode::getX         () const { return _x;         }
  inline float                  SlicingNode::getY         () const { return _y;         }
  inline Alignment              SlicingNode::getAlignment () const { return _alignment; }
  inline std::map<float,float>* SlicingNode::getMapHW     () const { return _mapHW;     }
  inline bool                   SlicingNode::getPreset    () const { return _preset;    }

  inline void SlicingNode::setWidth     (float w)                      { _w = w; }
  inline void SlicingNode::setHeight    (float h)                      { _h = h; }
  inline void SlicingNode::setX         (float x)                      { _x = x; }
  inline void SlicingNode::setY         (float y)                      { _y = y; }
  inline void SlicingNode::setAlignment (Alignment alignment)          { _alignment = alignment; }
  inline void SlicingNode::setPreset    (bool preset)                  { _preset = preset; }
  inline void SlicingNode::setMapHW     (std::map<float,float>* mapHW) { _mapHW  = mapHW; }


// -----------------------------------------------------------------------------------------------//
// Class : HVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class HVSlicingNode: public SlicingNode
  {
    public:
    // Add a SlicingNode
      void  createPushBackNode ( SlicingType type     
                               , Alignment   alignment  = UnknownAlignment
                               , float       toleranceH = 0
                               , float       toleranceW = 0
                               , float       x          = 0
                               , float       y          = 0
                               , float       w          = 0
                               , float       h          = 0
                               );
    // Create and add a SlicingNode
      void  createPushBackDevice ( std::map<float,float>* mapHW     = NULL
                                 , Alignment              alignment = UnknownAlignment
                                 , float                  x         = 0
                                 , float                  y         = 0
                                 , float                  w         = 0
                                 , float                  h         = 0
                                 );
      void createPushBackRouting ( float hw = 0
                                 , float x  = 0
                                 , float y  = 0
                                 );

      inline int                              getNbChild    ()          const;
      inline SlicingNode*                     getChild      (int index) const;
      inline const std::vector<SlicingNode*>& getChildren   ()          const;
             void                             printChildren ();

      inline void pushBackNode   (SlicingNode* node);  
      inline void pushFrontNode  (SlicingNode* node); 
      inline void removeAllNodes ();
             void insertNode     (SlicingNode* node, int index); 
             void removeNode     (SlicingNode* node);

      void  place (float x = 0, float y = 0);

      inline void  setToleranceH    (float tolerance);
      inline void  setToleranceW    (float tolerance);
      inline float getToleranceH    () const;
      inline float getToleranceW    () const;
             void  setAllToleranceH (float tolerance);
             void  setAllToleranceW (float tolerance);

      bool                   emptyChildrenMap () const;
      void                   updateGlobalSize ();
      std::pair<float,float> setGlobalSize    (float height = 0, float width = 0);

      void createSymmetry      (int childIndex, int copyIndex, Transformation tr = None);
      void setSymmetry         (int childIndex, int copyIndex);
      int  getLeafNumber       () const;
      void print               () const;
      void normalizeSymmetries ();

      inline std::list<std::pair< int,int> > getSymmetries () const;

    protected:
      HVSlicingNode ( SlicingType type
                    , Alignment   alignment  = AlignLeft
                    , float       toleranceH = 0
                    , float       toleranceW = 0
                    , float       x          = 0
                    , float       y          = 0
                    , float       w          = 0
                    , float       h          = 0
                    );
      virtual ~HVSlicingNode ();

    protected:
      std::vector<SlicingNode*>       _children;
      float                           _toleranceH;
      float                           _toleranceW;
      std::list<std::pair <int,int> > _symmetries;
  };

  inline int                              HVSlicingNode::getNbChild  ()          const { return _children.size(); }
  inline SlicingNode*                     HVSlicingNode::getChild    (int index) const { return _children[index]; }
  inline const std::vector<SlicingNode*>& HVSlicingNode::getChildren ()          const { return _children;        }

  inline void HVSlicingNode::pushBackNode   (SlicingNode* node) { _children.push_back(node);                 }
  inline void HVSlicingNode::pushFrontNode  (SlicingNode* node) { _children.insert(_children.begin(), node); }
  inline void HVSlicingNode::removeAllNodes ()                  { _children.clear();                         }

  inline void  HVSlicingNode::setToleranceH (float tolerance)       { _toleranceH = tolerance; }
  inline void  HVSlicingNode::setToleranceW (float tolerance)       { _toleranceW = tolerance; }
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
                                  , float     x          = 0
                                  , float     y          = 0
                                  , float     w          = 0
                                  , float     h          = 0
                                  );
      VSlicingNode* clone (Transformation tr = None);

    private:
      VSlicingNode ( SlicingType type
                   , Alignment   alignment  = UnknownAlignment
                   , float       toleranceH = 0
                   , float       toleranceW = 0
                   , float       x          = 0
                   , float       y          = 0
                   , float       w          = 0
                   , float       h          = 0
                   );
      ~VSlicingNode ();
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
                                  , float     x          = 0
                                  , float     y          = 0
                                  , float     w          = 0
                                  , float     h          = 0
                                  );
      HSlicingNode* clone (Transformation tr = None);

    private:
      HSlicingNode ( SlicingType type
                   , Alignment   alignment  = UnknownAlignment
                   , float       toleranceH = 0
                   , float       toleranceW = 0
                   , float       x          = 0
                   , float       y          = 0
                   , float       w          = 0
                   , float       h          = 0
                   );
      ~HSlicingNode ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : DSlicingNode
// -----------------------------------------------------------------------------------------------//


  class DSlicingNode: public SlicingNode
  {
    public:
      static DSlicingNode* create ( std::map<float,float>* mapHW     = NULL
                                  , Alignment              alignment = UnknownAlignment
                                  , float                  x         = 0
                                  , float                  y         = 0
                                  , float                  w         = 0
                                  , float                  h         = 0
                                  );

      void                   place            (float x = 0, float y = 0);
      inline void            updateGlobalSize ();
      std::pair<float,float> setGlobalSize    (float height = 0, float width = 0);

      inline int             getLeafNumber () const;
      DSlicingNode*          clone         (Transformation tr = None);

      // Error Message Methods
      void createPushBackNode ( SlicingType type
                              , Alignment   alignment  = UnknownAlignment
                              , float       toleranceH = 0
                              , float       toleranceW = 0
                              , float       x          = 0
                              , float       y          = 0
                              , float       w          = 0
                              , float       h          = 0
                                                     );
      void createPushBackDevice ( std::map<float,float>* mapHW     = NULL
                                , Alignment              alignment = UnknownAlignment
                                , float                  x         = 0
                                , float                  y         = 0
                                , float                  w         = 0
                                , float                  h         = 0
                                                       );

      void  createPushBackRouting ( float hw = 0
                                  , float x  = 0
                                  , float y  = 0
                                  );

      int                              getNbChild       ()          const;
      SlicingNode*                     getChild         (int index) const;
      const std::vector<SlicingNode*>& getChildren      ()          const;
      void                             printChildren    ();

      void insertNode     (SlicingNode* node, int index); 
      void pushBackNode   (SlicingNode* node); 
      void pushFrontNode  (SlicingNode* node); 
      void removeAllNodes ();
      void removeNode     (SlicingNode* node);

      void  setToleranceH    (float tolerance);
      void  setAllToleranceH (float tolerance);
      void  setToleranceW    (float tolerance);
      void  setAllToleranceW (float tolerance);
      float getToleranceH    () const;
      float getToleranceW    () const;

      bool  emptyChildrenMap () const;

      void createSymmetry      (int childIndex, int copyIndex, Transformation tr = None);
      void setSymmetry         (int childIndex, int copyIndex);
      void normalizeSymmetries ();
      std::list<std::pair< int,int> > getSymmetries () const;

    private:
      DSlicingNode( SlicingType            type
                  , std::map<float,float>* mapHW     = NULL
                  , Alignment              alignment = UnknownAlignment
                  , float                  x         = 0
                  , float                  y         = 0
                  , float                  w         = 0
                  , float                  h         = 0
                  );
      ~DSlicingNode();

  };

  inline void  DSlicingNode::updateGlobalSize()       {}
  inline int   DSlicingNode::getLeafNumber   () const { return 1 ; }


// -----------------------------------------------------------------------------------------------//
// Class : RHVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHVSlicingNode: public SlicingNode
  {
    public:
      void place            (float x = 0, float y = 0);

      inline void updateGlobalSize ();
      inline int  getLeafNumber    () const;

      // Error Message Methods
      Alignment              getAlignment ()            const;
      std::map<float,float>* getMapHW     ()            const;
      void                   setPreset    (bool preset)      ;
      std::pair<float,float> getPairH     (float h)     const; 
      std::pair<float,float> getPairW     (float w)     const; 
      void                   setPairH     (float h)          ;      

      void createPushBackNode ( SlicingType type
                              , Alignment   alignment  = UnknownAlignment
                              , float       toleranceH = 0
                              , float       toleranceW = 0
                              , float       x          = 0 
                              , float       y          = 0 
                              , float       w          = 0 
                              , float       h          = 0
                              );
      void createPushBackDevice ( std::map<float,float>* mapHW     = NULL
                                , Alignment              alignment = UnknownAlignment
                                , float                  x         = 0
                                , float                  y         = 0
                                , float                  w         = 0
                                , float                  h         = 0
                                );
      void createPushBackRouting ( float hw = 0
                                 , float x  = 0
                                 , float y  = 0 
                                 );

      int                              getNbChild    ()          const;
      SlicingNode*                     getChild      (int index) const;
      const std::vector<SlicingNode*>& getChildren   ()          const;
      void                             printChildren ();

      void insertNode     (SlicingNode* node, int index); 
      void pushBackNode   (SlicingNode* node); 
      void pushFrontNode  (SlicingNode* node); 
      void removeAllNodes ();
      void removeNode     (SlicingNode* node);

      void  setToleranceH    (float tolerance);
      void  setToleranceW    (float tolerance);
      float getToleranceH    () const;
      float getToleranceW    () const;
      void  setAllToleranceH (float tolerance);
      void  setAllToleranceW (float tolerance);

      bool                   emptyChildrenMap () const;
      std::pair<float,float> setGlobalSize    (float height = 0, float width = 0);

      void  createSymmetry      (int childIndex, int copyIndex, Transformation tr = None);
      void  setSymmetry         (int childIndex, int copyIndex);
      void  normalizeSymmetries ();
      std::list<std::pair< int,int> > getSymmetries       () const;

    protected:
      RHVSlicingNode( float x = 0
                    , float y = 0
                    , float w = 0
                    , float h = 0
                  );
      ~RHVSlicingNode();
  };

  inline int  RHVSlicingNode::getLeafNumber    () const { return 1; }
  inline void RHVSlicingNode::updateGlobalSize ()       {} 


// -----------------------------------------------------------------------------------------------//
// Class : RHSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RHSlicingNode: public RHVSlicingNode
  {
    public:
      static RHSlicingNode* create ( float h = 0, float x = 0, float y = 0 );
             RHSlicingNode* clone  (Transformation tr = None);

      // Error Message Methods
      float getWidth () const;
      void  setWidth ( float w );

    private:
      RHSlicingNode  (float h = 0, float x = 0, float y = 0 );
      ~RHSlicingNode ();
  };


// -----------------------------------------------------------------------------------------------//
// Class : RVSlicingNode
// -----------------------------------------------------------------------------------------------//


  class RVSlicingNode: public RHVSlicingNode
  {
    public:
      static RVSlicingNode* create ( float w = 0, float x = 0, float y = 0 );
             RVSlicingNode* clone  (Transformation tr = None);

      // Error Message Methods
      float getHeight () const;
      void  setHeight ( float h );

    private:
      RVSlicingNode  ( float w = 0, float x = 0, float y = 0 );
      ~RVSlicingNode ();
  };
}
#endif
