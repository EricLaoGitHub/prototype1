#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iterator>     
#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

// Left or Bot, Middle, Right or Top
enum CenteringType { UnknownCentering = 0, LB         = 1, Middle   = 2, RT         = 3 }; 
enum SlicingType   { UnknownSlicing   = 0, Horizontal = 1, Vertical = 2, DeviceNode = 3 };

class SlicingNode
{
  public:
    // Accessors & Mutators
    SlicingType                           getType          () const;
    float                                 getWidth         () const;
    float                                 getHeight        () const;
    float                                 getX             () const;
    float                                 getY             () const;
    CenteringType                         getCenteringType () const;
    map<float, vector< vector<float> > >* getmapHW         () const;

    void  setWidth        (float w);
    void  setHeight       (float h);
    void  setX            (float x);
    void  setY            (float y);
    void  setCenteringType(CenteringType type);

    // Common Virtual
    virtual void print () const;
    virtual void place (float x = 0, float y = 0) = 0;

    pair<float, vector< vector<float> > > getPairH          (float h) const;
    pair<float, vector< vector<float> > > getPairW          (float w) const;
    void                    setPairH          (float h);
    void                    setPairW          (float w);

    // HVSlicingNode Virtual
    virtual void                        createPushBackNode(
                                                           SlicingType   type, 
                                                           CenteringType c         = LB,
                                                           float         tolerance = 0,
                                                           float         x         = 0, 
                                                           float         y         = 0, 
                                                           float         w         = 0, 
                                                           float         h         = 0
                                                           ) = 0;
    virtual void                        createPushBackDevice(
                                                             map<float, vector< vector<float> > > mapHW = NULL, 
                                                             CenteringType                        c     = LB,
                                                             float                                x     = 0, 
                                                             float                                y     = 0, 
                                                             float                                w     = 0, 
                                                             float                                h     = 0
                                                            ) = 0;
    virtual int                         getNbChild        ()          const              = 0;
    virtual SlicingNode*                getChild          (int index) const              = 0;
    virtual const vector<SlicingNode*>& getChildren       ()          const              = 0;
    virtual void                        printChildren     ()                             = 0;

    virtual void                        addNode           (SlicingNode* node, int index) = 0; 
    virtual void                        pushBackNode      (SlicingNode* node)            = 0; 
    virtual void                        removeAllNodes    ()                             = 0;
    virtual void                        removeNode        (SlicingNode* node)            = 0;

    virtual float                       updateHeight      ()                             = 0; 
    virtual float                       updateWidth       ()                             = 0;

    virtual void                        setTolerance      (float tolerance)              = 0;
    virtual void                        setAllTolerance   (float tolerance)              = 0;
    virtual float                       getTolerance      () const                       = 0;

    virtual void                        updateBandSize    ()                             = 0;
    virtual bool                        emptyChildren     () const                       = 0;
    // DSlicingNode Virtual

  protected:
    SlicingNode(
                SlicingType       type, 
                map<float, vector< vector<float> > >* mapHW = NULL,
                CenteringType                         c     = LB,
                float                                 x     = 0, 
                float                                 y     = 0, 
                float                                 w     = 0, 
                float                                 h     = 0
               );
    virtual ~SlicingNode();
    virtual void _place(float x = 0, float y = 0) = 0; // Not to be used


  protected:
    SlicingType                           _type;
    map<float, vector< vector<float> > >* _mapHW;
    CenteringType                         _c;
    float                                 _x;
    float                                 _y;
    float                                 _w;
    float                                 _h;
};

class HVSlicingNode: public SlicingNode
{
  public:
    void                        createPushBackNode(
                                                   SlicingType   type,      
                                                   CenteringType c         = LB,
                                                   float         tolerance = 0,
                                                   float         x         = 0, 
                                                   float         y         = 0, 
                                                   float         w         = 0, 
                                                   float         h         = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float, vector< vector<float> > >* mapHW = NULL, 
                                                     CenteringType                         c     = LB,
                                                     float                                 x     = 0, 
                                                     float                                 y     = 0, 
                                                     float                                 w     = 0, 
                                                     float                                 h     = 0
                                                    );
    int                         getNbChild        ()          const;
    SlicingNode*                getChild          (int index) const;
    const vector<SlicingNode*>& getChildren       ()          const;
    void                        printChildren     ();

    void                        addNode           (SlicingNode* node, int index); 
    void                        pushBackNode      (SlicingNode* node); 
    void                        removeAllNodes    ();
    void                        removeNode        (SlicingNode* node);

    float                       updateHeight      (); 
    float                       updateWidth       ();

    CenteringType               getCenteringType  () const;
    void                        place             (float x = 0, float y = 0);
    void                        _place            (float x = 0, float y = 0); // Not to be used

    void                        setTolerance      (float tolerance);
    void                        setAllTolerance   (float tolerance);
    float                       getTolerance      () const;

    void                        updateBandSize    ();
    bool                        emptyChildren     () const;
    // Error Message Methods

  protected:
    HVSlicingNode(
                  SlicingType   type,
                  CenteringType c         = LB, 
                  float         tolerance = 0,
                  float         x         = 0, 
                  float         y         = 0, 
                  float         w         = 0, 
                  float         h         = 0
                 );
    virtual ~HVSlicingNode();

  protected:
    vector<SlicingNode*> _children;
    float                _tolerance;
};

class VSlicingNode: public HVSlicingNode
{
  public:
    static VSlicingNode* create(
                                CenteringType c         = LB, 
                                float         tolerance = 0,
                                float         x         = 0, 
                                float         y         = 0, 
                                float         w         = 0, 
                                float         h         = 0
                               );

  private:
    VSlicingNode(
                 SlicingType   type, 
                 CenteringType c         = LB, 
                 float         tolerance = 0,
                 float         x         = 0, 
                 float         y         = 0, 
                 float         w         = 0, 
                 float         h         = 0
                );
    ~VSlicingNode();
};

class HSlicingNode: public HVSlicingNode
{
  public:
    static HSlicingNode* create(
                                CenteringType c         = LB, 
                                float         tolerance = 0,
                                float         x         = 0, 
                                float         y         = 0, 
                                float         w         = 0, 
                                float         h         = 0
                               );

  private:
    HSlicingNode(
                 SlicingType   type, 
                 CenteringType c         = LB, 
                 float         tolerance = 0,
                 float         x         = 0, 
                 float         y         = 0, 
                 float         w         = 0, 
                 float         h         = 0
                );
    ~HSlicingNode();
};

class DSlicingNode: public SlicingNode
{
  public:
    static DSlicingNode* create          (
                                          map<float, vector< vector<float> > >* mapHW = NULL,
                                          CenteringType                         c     = LB,
                                          float                                 x     = 0, 
                                          float                                 y     = 0,
                                          float                                 w     = 0, 
                                          float                                 h     = 0
                                         );
    void                 place           (float x = 0, float y = 0);
    void                 _place          (float x = 0, float y = 0); // Not to be used
    CenteringType        getCenteringType() const;

    // Error Message Methods
    void                        createPushBackNode(
                                                   SlicingType   type, 
                                                   CenteringType c         = LB,
                                                   float         tolerance = 0,
                                                   float         x         = 0, 
                                                   float         y         = 0, 
                                                   float         w         = 0, 
                                                   float         h         = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float, vector< vector<float> > >* mapHW = NULL, 
                                                     CenteringType                         c     = LB,
                                                     float                                 x     = 0, 
                                                     float                                 y     = 0, 
                                                     float                                 w     = 0, 
                                                     float                                 h     = 0
                                                    );
    int                         getNbChild        ()          const;
    SlicingNode*                getChild          (int index) const;
    const vector<SlicingNode*>& getChildren       ()          const;
    void                        printChildren     ();

    void                        addNode           (SlicingNode* node, int index); 
    void                        pushBackNode      (SlicingNode* node); 
    void                        removeAllNodes    ();
    void                        removeNode        (SlicingNode* node);

    float                       updateHeight      (); 
    float                       updateWidth       ();

    void                        setTolerance      (float tolerance);
    void                        setAllTolerance   (float tolerance);
    float                       getTolerance      () const;

    void                        updateBandSize    ();
    bool                        emptyChildren     () const;

  private:
    DSlicingNode(
                 SlicingType                           type, 
                 map<float, vector< vector<float> > >* mapHW = NULL,
                 CenteringType                         c      = LB,
                 float                                 x      = 0, 
                 float                                 y      = 0, 
                 float                                 w      = 0, 
                 float                                 h      = 0
                );
    ~DSlicingNode();

  private:

};
#endif
