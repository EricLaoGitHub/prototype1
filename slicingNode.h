#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

enum CenteringType { LB = 1, Middle = 2, RT = 3, UnknownCentering = 4 }; // Left or Bot, Middle, Right or Top
enum SlicingType   { Unknown = 0, Horizontal = 1, Vertical = 2, DeviceNode = 3, RoutingNode = 4 };

class SlicingNode
{
  public:
    // Accessors & Mutators
    SlicingType       getType          () const;
    float             getWidth         () const;
    float             getHeight        () const;
    float             getX             () const;
    float             getY             () const;
    CenteringType     getCenteringType () const;
    map<float,float>* getMapHW         () const;
    bool              getPreset        () const;

    void  setWidth        (float w);
    void  setHeight       (float h);
    void  setX            (float x);
    void  setY            (float y);
    void  setCenteringType(CenteringType type);
    void  setPreset       (bool preset);

    // Common Virtual
    virtual void print () const;
    virtual void place (float x = 0, float y = 0) = 0;   // Place the node in the plan at (x,y)
    pair<float,float> getPairH          (float h) const; // Given a height, return width
    pair<float,float> getPairW          (float w) const; // Given a width , return height
    void              setPairH          (float h);       // Given a height, set width
    void              setPairW          (float w);       // Given a width , set height


    // HVSlicingNode Virtual (see HVSlicingNode)
    virtual void                        createPushBackNode(
                                                           SlicingType   type, 
                                                           CenteringType c          = LB,
                                                           float         toleranceH = 0,
                                                           float         toleranceW = 0,
                                                           float         x          = 0, 
                                                           float         y          = 0, 
                                                           float         w          = 0, 
                                                           float         h          = 0
                                                           ) = 0;
    virtual void                        createPushBackDevice(
                                                             map<float,float>* mapHW = NULL, 
                                                             CenteringType     c     = LB,
                                                             float             x     = 0, 
                                                             float             y     = 0, 
                                                             float             w     = 0, 
                                                             float             h     = 0
                                                            ) = 0;
    virtual void                        createPushBackRouting( 
                                                              float hw = 0,
                                                              float x  = 0, 
                                                              float y  = 0 
                                                            ) = 0;
    virtual int                         getNbChild       ()          const              = 0;
    virtual SlicingNode*                getChild         (int index) const              = 0;
    virtual const vector<SlicingNode*>& getChildren      ()          const              = 0;
    virtual void                        printChildren    ()                             = 0;

    virtual void                        addNode          (SlicingNode* node, int index)      = 0; 
    virtual void                        pushBackNode     (SlicingNode* node)                 = 0; 
    virtual void                        removeAllNodes   ()                                  = 0;
    virtual void                        removeNode       (SlicingNode* node)                 = 0;

    virtual float                       updateHeight     ()                                  = 0; 
    virtual float                       updateWidth      ()                                  = 0;

    virtual void                        setToleranceH    (float tolerance)                   = 0;
    virtual void                        setAllToleranceH (float tolerance)                   = 0;
    virtual void                        setToleranceW    (float tolerance)                   = 0;
    virtual void                        setAllToleranceW (float tolerance)                   = 0;
    virtual float                       getToleranceH    () const                            = 0;
    virtual float                       getToleranceW    () const                            = 0;

    virtual bool                        emptyChildrenMap () const                            = 0;
    virtual void                        updateGlobalSize ()                                  = 0;
    virtual pair<float, float>          setGlobalSize    (float height = 0, float width = 0) = 0;
    // DSlicingNode Virtual

  protected:
  // Constructor & destructor
    SlicingNode(
                SlicingType       type,         
                map<float,float>* mapHW = NULL,
                CenteringType     c     = LB,
                float             x     = 0,
                float             y     = 0,
                float             w     = 0,
                float             h     = 0
               );
    virtual ~SlicingNode();


  protected:
    SlicingType       _type;  // Node type (see enum)
    map<float,float>* _mapHW; // map containing node sizes
    CenteringType     _c;     // Centering (see enum)
    float             _x;     // position x
    float             _y;     // position y
    float             _w;     // width
    float             _h;     // height
    bool              _preset;// preset
};

class HVSlicingNode: public SlicingNode
{
  public:
  // Add a SlicingNode
    void                        createPushBackNode(
                                                   SlicingType   type,      
                                                   CenteringType c          = LB,
                                                   float         toleranceH = 0,
                                                   float         toleranceW = 0,
                                                   float         x          = 0, 
                                                   float         y          = 0, 
                                                   float         w          = 0, 
                                                   float         h          = 0
                                                  );
  // Create and add a SlicingNode
    void                        createPushBackDevice(
                                                     map<float,float>* mapHW = NULL, 
                                                     CenteringType     c     = LB,
                                                     float             x     = 0, 
                                                     float             y     = 0, 
                                                     float             w     = 0, 
                                                     float             h     = 0
                                                    );
    void                        createPushBackRouting(
                                                      float hw = 0,
                                                      float x  = 0, 
                                                      float y  = 0
                                                     );
    int                         getNbChild       ()          const;
    SlicingNode*                getChild         (int index) const;
    const vector<SlicingNode*>& getChildren      ()          const;
    void                        printChildren    ();

    void                        addNode          (SlicingNode* node, int index); 
    void                        pushBackNode     (SlicingNode* node); 
    void                        removeAllNodes   ();
    void                        removeNode       (SlicingNode* node);

    float                       updateHeight     (); 
    float                       updateWidth      ();

    CenteringType               getCenteringType () const;
    void                        place            (float x = 0, float y = 0);

    void                        setToleranceH    (float tolerance);
    void                        setAllToleranceH (float tolerance);
    void                        setToleranceW    (float tolerance);
    void                        setAllToleranceW (float tolerance);
    float                       getToleranceH    () const;
    float                       getToleranceW    () const;

    bool                        emptyChildrenMap () const;
    void                        updateGlobalSize ();
    pair<float, float>          setGlobalSize (float height = 0, float width = 0);
    // Error Message Methods

  protected:
    HVSlicingNode(
                  SlicingType   type,
                  CenteringType c          = LB, 
                  float         toleranceH = 0,
                  float         toleranceW = 0,
                  float         x          = 0, 
                  float         y          = 0, 
                  float         w          = 0, 
                  float         h          = 0
                 );
    virtual ~HVSlicingNode();

  protected:
    vector<SlicingNode*> _children;
    float                _toleranceH;
    float                _toleranceW;
};

class VSlicingNode: public HVSlicingNode
{
  public:
    static VSlicingNode* create(
                                CenteringType c          = LB, 
                                float         toleranceH = 0,
                                float         toleranceW = 0,
                                float         x          = 0, 
                                float         y          = 0, 
                                float         w          = 0, 
                                float         h          = 0
                               );

  private:
    VSlicingNode(
                 SlicingType   type, 
                 CenteringType c          = LB, 
                 float         toleranceH = 0,
                 float         toleranceW = 0,
                 float         x          = 0, 
                 float         y          = 0, 
                 float         w          = 0, 
                 float         h          = 0
                );
    ~VSlicingNode();
};

class HSlicingNode: public HVSlicingNode
{
  public:
    static HSlicingNode* create(
                                CenteringType c          = LB, 
                                float         toleranceH = 0,
                                float         toleranceW = 0,
                                float         x          = 0, 
                                float         y          = 0, 
                                float         w          = 0, 
                                float         h          = 0
                               );

  private:
    HSlicingNode(
                 SlicingType   type, 
                 CenteringType c          = LB, 
                 float         toleranceH = 0,
                 float         toleranceW = 0,
                 float         x          = 0, 
                 float         y          = 0, 
                 float         w          = 0, 
                 float         h          = 0
                );
    ~HSlicingNode();
};

class DSlicingNode: public SlicingNode
{
  public:
    static DSlicingNode* create          (
                                          map<float,float>* mapHW = NULL,
                                          CenteringType     c     = LB,
                                          float             x     = 0, 
                                          float             y     = 0,
                                          float             w     = 0, 
                                          float             h     = 0
                                         );
    void                 place           (float x = 0, float y = 0);
    CenteringType        getCenteringType() const;
    pair<float, float>   setGlobalSize   (float height = 0, float width = 0);

    float                updateHeight    (); 
    float                updateWidth     ();
    // Error Message Methods
    void                        createPushBackNode(
                                                   SlicingType   type, 
                                                   CenteringType c          = LB,
                                                   float         toleranceH = 0,
                                                   float         toleranceW = 0,
                                                   float         x          = 0, 
                                                   float         y          = 0, 
                                                   float         w          = 0, 
                                                   float         h          = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float,float>* mapHW = NULL, 
                                                     CenteringType     c     = LB,
                                                     float             x     = 0, 
                                                     float             y     = 0, 
                                                     float             w     = 0, 
                                                     float             h     = 0
                                                    );

    void                        createPushBackRouting(
                                                      float hw = 0,
                                                      float x  = 0, 
                                                      float y  = 0
                                                     );

    int                         getNbChild       ()          const;
    SlicingNode*                getChild         (int index) const;
    const vector<SlicingNode*>& getChildren      ()          const;
    void                        printChildren    ();

    void                        addNode          (SlicingNode* node, int index); 
    void                        pushBackNode     (SlicingNode* node); 
    void                        removeAllNodes   ();
    void                        removeNode       (SlicingNode* node);

    void                        setToleranceH    (float tolerance);
    void                        setAllToleranceH (float tolerance);
    void                        setToleranceW    (float tolerance);
    void                        setAllToleranceW (float tolerance);
    float                       getToleranceH    () const;
    float                       getToleranceW    () const;

    bool                        emptyChildrenMap () const;
    void                        updateGlobalSize ();

  private:
    DSlicingNode(
                 SlicingType       type, 
                 map<float,float>* mapHW = NULL,
                 CenteringType     c     = LB,
                 float             x     = 0, 
                 float             y     = 0, 
                 float             w     = 0, 
                 float             h    =  0
                );
    ~DSlicingNode();

};

class RHVSlicingNode: public SlicingNode
{
  public:
    static RHVSlicingNode* create          (
                                          float             x     = 0, 
                                          float             y     = 0,
                                          float             w     = 0, 
                                          float             h     = 0
                                         );
    void                 place           (float x = 0, float y = 0);

    // Error Message Methods
    CenteringType     getCenteringType () const;
    map<float,float>* getMapHW         () const;
    void              setPreset        (bool preset);
    pair<float,float> getPairH         (float h) const; 
    pair<float,float> getPairW         (float w) const; 
    void              setPairH         (float h);       
    void              setPairW         (float w);       

    void                        createPushBackNode(
                                                   SlicingType   type, 
                                                   CenteringType c          = LB,
                                                   float         toleranceH = 0,
                                                   float         toleranceW = 0,
                                                   float         x          = 0, 
                                                   float         y          = 0, 
                                                   float         w          = 0, 
                                                   float         h          = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float,float>* mapHW = NULL, 
                                                     CenteringType     c     = LB,
                                                     float             x     = 0, 
                                                     float             y     = 0, 
                                                     float             w     = 0, 
                                                     float             h     = 0
                                                    );
    void                        createPushBackRouting(
                                                      float hw = 0,
                                                      float x  = 0, 
                                                      float y  = 0 
                                                     );
    int                         getNbChild       ()          const;
    SlicingNode*                getChild         (int index) const;
    const vector<SlicingNode*>& getChildren      ()          const;
    void                        printChildren    ();

    void                        addNode          (SlicingNode* node, int index); 
    void                        pushBackNode     (SlicingNode* node); 
    void                        removeAllNodes   ();
    void                        removeNode       (SlicingNode* node);

    float                       updateHeight     (); 
    float                       updateWidth      ();

    void                        setToleranceH    (float tolerance);
    void                        setAllToleranceH (float tolerance);
    void                        setToleranceW    (float tolerance);
    void                        setAllToleranceW (float tolerance);
    float                       getToleranceH    () const;
    float                       getToleranceW    () const;

    bool                        emptyChildrenMap () const;
    void                        updateGlobalSize ();
    pair<float, float>          setGlobalSize (float height = 0, float width = 0);

  protected:
    RHVSlicingNode(
                 float x = 0, 
                 float y = 0, 
                 float w = 0, 
                 float h = 0
                );
    ~RHVSlicingNode();


};


class RHSlicingNode: public RHVSlicingNode
{
  public:
    static RHSlicingNode* create ( float h = 0, float x = 0, float y = 0 );

    // Error Message Methods
    float getWidth () const;
    void  setWidth ( float w );

  private:
    RHSlicingNode(float h = 0, float x = 0, float y = 0 );
    ~RHSlicingNode();
};

class RVSlicingNode: public RHVSlicingNode
{
  public:
    static RVSlicingNode* create  ( float w = 0, float x = 0, float y = 0 );

    // Error Message Methods
    float getHeight () const;
    void  setHeight ( float h );

  private:
    RVSlicingNode( float w = 0, float x = 0, float y = 0 );
    ~RVSlicingNode();
};

#endif
