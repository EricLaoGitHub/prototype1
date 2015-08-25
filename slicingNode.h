#ifndef DEF_SLICINGNODE
#define DEF_SLICINGNODE

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum HCenteringType { Left = 1, HMiddle = 2, Right = 3 };
enum VCenteringType { Bot  = 1, VMiddle = 2, Top   = 3 };
enum SlicingType    { Unknown = 0, Horizontal = 1, Vertical = 2, DeviceNode = 3 };

class SlicingNode
{
  public:
    // Accessors & Mutators
    SlicingType getType  () const;
    float       getWidth () const;
    float       getHeight() const;
    float       getX     () const;
    float       getY     () const;

    void  setWidth (float w);
    void  setHeight(float h);
    void  setX     (float x);
    void  setY     (float y);

    // Common Virtual
    virtual void print() const;
    virtual void place(float x, float y) = 0;

    // HVSlicingNode Virtual
    virtual void                        createPushBackNode(
                                                           SlicingType type, 
                                                           map<float,float>* mapH = NULL, 
                                                           map<float,float>* mapW = NULL,
                                                           float x = 0, 
                                                           float y = 0, 
                                                           float w = 0, 
                                                           float h = 0,
                                                           HCenteringType hc = Left,
                                                           VCenteringType vc = Bot
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
                SlicingType type, 
                float x = 0, 
                float y = 0, 
                float w = 0, 
                float h = 0
               );
    virtual ~SlicingNode();

  protected:
    SlicingType _type;
    float       _x;
    float       _y;
    float       _w;
    float       _h;
};

class HVSlicingNode: public SlicingNode
{
  public:
    void                        createPushBackNode(
                                                   SlicingType type, 
                                                   map<float,float>* mapH = NULL,
                                                   map<float,float>* mapW = NULL,
                                                   float x = 0, 
                                                   float y = 0, 
                                                   float w = 0, 
                                                   float h = 0,
                                                   HCenteringType hc = Left,
                                                   VCenteringType vc = Bot
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
    void                        place             (float x, float y);

    // Error Message Methods

  protected:
    HVSlicingNode(
                  SlicingType type, 
                  float x = 0, 
                  float y = 0, 
                  float w = 0, 
                  float h = 0
                 );
    virtual ~HVSlicingNode();

  protected:
    vector<SlicingNode*> _children;
};

class VSlicingNode: public HVSlicingNode
{
  public:
    static VSlicingNode* create(float x = 0, float y = 0, float w = 0, float h = 0, VCenteringType c = Bot);

  private:
    VSlicingNode(SlicingType type, float x = 0, float y = 0, float w = 0, float h = 0, VCenteringType c = Bot);
    ~VSlicingNode();

  private:
    VCenteringType _c;
};

class HSlicingNode: public HVSlicingNode
{
  public:
    static HSlicingNode* create(float x = 0, float y = 0, float w = 0, float h = 0, HCenteringType c = Left);

  private:
    HSlicingNode(SlicingType type, float x = 0, float y = 0, float w = 0, float h = 0, HCenteringType c = Left);
    ~HSlicingNode();

  private:
    HCenteringType _c;
};

class DSlicingNode: public SlicingNode
{
  public:
    static DSlicingNode* create   (
                                   map<float,float>* mapH = NULL,
                                   map<float,float>* mapW = NULL,
                                   float x = 0, 
                                   float y = 0,
                                   float w = 0, 
                                   float h = 0
                                  );
    void                 print    () const;
    void                 place    (float x, float y);

    // Error Message Methods
    void                        createPushBackNode(
                                                   SlicingType type, 
                                                   map<float,float>* mapH = NULL,
                                                   map<float,float>* mapW = NULL,
                                                   float x = 0, 
                                                   float y = 0, 
                                                   float w = 0, 
                                                   float h = 0,
                                                   HCenteringType hc = Left,
                                                   VCenteringType vc = Bot
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

  private:
    DSlicingNode(
                 SlicingType type, 
                 map<float,float>* mapH = NULL,
                 map<float,float>* mapW = NULL,
                 float x = 0, 
                 float y = 0, 
                 float w = 0, 
                 float h = 0
                );
    ~DSlicingNode();

  private:
    map<float,float>* _mapH;
    map<float,float>* _mapW;

};
#endif
