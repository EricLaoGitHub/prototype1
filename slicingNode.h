#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum CenteringType { LB = 1, Middle = 2, RT = 3, UnknownCentering = 4 }; // Left or Bot, Middle, Right or Top
enum SlicingType   { Unknown = 0, Horizontal = 1, Vertical = 2, DeviceNode = 3 };

class SlicingNode
{
  public:
    // Accessors & Mutators
    SlicingType   getType           () const;
    float         getWidth          () const;
    float         getHeight         () const;
    float         getX              () const;
    float         getY              () const;
    CenteringType getCenteringType  () const;

    void  setWidth        (float w);
    void  setHeight       (float h);
    void  setX            (float x);
    void  setY            (float y);
    void  setCenteringType(CenteringType type);

    // Common Virtual
    virtual void print() const;
    virtual void place(float x = 0, float y = 0) = 0;
    virtual void _place(float x = 0, float y = 0) = 0;

    // HVSlicingNode Virtual
    virtual void                        createPushBackNode(
                                                           SlicingType   type, 
                                                           CenteringType c = LB,
                                                           float         x = 0, 
                                                           float         y = 0, 
                                                           float         w = 0, 
                                                           float         h = 0
                                                           ) = 0;
    virtual void                        createPushBackDevice(
                                                             map<float,float>* mapH = NULL, 
                                                             map<float,float>* mapW = NULL,
                                                             CenteringType     c    = LB,
                                                             float             x    = 0, 
                                                             float             y    = 0, 
                                                             float             w    = 0, 
                                                             float             h    = 0
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

    // DSlicingNode Virtual

  protected:
    SlicingNode(
                SlicingType   type, 
                CenteringType c = LB,
                float         x = 0, 
                float         y = 0, 
                float         w = 0, 
                float         h = 0
               );
    virtual ~SlicingNode();


  protected:
    SlicingType   _type;
    CenteringType _c;
    float         _x;
    float         _y;
    float         _w;
    float         _h;
};

class HVSlicingNode: public SlicingNode
{
  public:
    void                        createPushBackNode(
                                                   SlicingType   type,      
                                                   CenteringType c = LB,
                                                   float         x = 0, 
                                                   float         y = 0, 
                                                   float         w = 0, 
                                                   float         h = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float,float>* mapH = NULL, 
                                                     map<float,float>* mapW = NULL,   
                                                     CenteringType     c    = LB,
                                                     float             x    = 0, 
                                                     float             y    = 0, 
                                                     float             w    = 0, 
                                                     float             h    = 0
                                                    );
    int                         getNbChild        ()          const;
    SlicingNode*                getChild          (int index) const;
    const vector<SlicingNode*>& getChildren       ()          const;
    void                        print             ()          const;
    void                        printChildren     ();

    void                        addNode           (SlicingNode* node, int index); 
    void                        pushBackNode      (SlicingNode* node); 
    void                        removeAllNodes    ();
    void                        removeNode        (SlicingNode* node);

    float                       updateHeight      (); 
    float                       updateWidth       ();

    CenteringType               getCenteringType  () const;
    void                        place             (float x = 0, float y = 0);
    void                        _place(float x = 0, float y = 0);
    // Error Message Methods

  protected:
    HVSlicingNode(
                  SlicingType   type,
                  CenteringType c = LB, 
                  float         x = 0, 
                  float         y = 0, 
                  float         w = 0, 
                  float         h = 0
                 );
    virtual ~HVSlicingNode();

  protected:
    vector<SlicingNode*> _children;
};

class VSlicingNode: public HVSlicingNode
{
  public:
    static VSlicingNode* create(CenteringType c = LB, float x = 0, float y = 0, float w = 0, float h = 0);

  private:
    VSlicingNode(SlicingType type, CenteringType c = LB, float x = 0, float y = 0, float w = 0, float h = 0);
    ~VSlicingNode();
};

class HSlicingNode: public HVSlicingNode
{
  public:
    static HSlicingNode* create(CenteringType c = LB, float x = 0, float y = 0, float w = 0, float h = 0);

  private:
    HSlicingNode(SlicingType type, CenteringType c = LB, float x = 0, float y = 0, float w = 0, float h = 0);
    ~HSlicingNode();
};

class DSlicingNode: public SlicingNode
{
  public:
    static DSlicingNode* create   (
                                   map<float,float>* mapH = NULL,
                                   map<float,float>* mapW = NULL,
                                   CenteringType     c    = LB,
                                   float             x    = 0, 
                                   float             y    = 0,
                                   float             w    = 0, 
                                   float             h    = 0
                                  );
    void                 print    () const;
    void                 place    (float x, float y);
    void                 _place   (float x = 0, float y = 0);

    // Error Message Methods
    void                        createPushBackNode(
                                                   SlicingType   type, 
                                                   CenteringType c = LB,
                                                   float         x = 0, 
                                                   float         y = 0, 
                                                   float         w = 0, 
                                                   float         h = 0
                                                  );
    void                        createPushBackDevice(
                                                     map<float,float>* mapH = NULL, 
                                                     map<float,float>* mapW = NULL,
                                                     CenteringType     c    = LB,
                                                     float             x    = 0, 
                                                     float             y    = 0, 
                                                     float             w    = 0, 
                                                     float             h    = 0
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

  private:
    DSlicingNode(
                 SlicingType       type, 
                 map<float,float>* mapH = NULL,
                 map<float,float>* mapW = NULL,
                 CenteringType     c    = LB,
                 float             x    = 0, 
                 float             y    = 0, 
                 float             w    = 0, 
                 float             h    = 0
                );
    ~DSlicingNode();

  private:
    map<float,float>* _mapH;
    map<float,float>* _mapW;

};
#endif
