#include <iostream>
#include <vector>
#include <string>
#include <memory>

class ShapeNode;
class TransformNode;

class INodeVisitor
{
public:
    virtual ~INodeVisitor() {}
    virtual void Visit(ShapeNode& node) = 0;
    virtual void Visit(TransformNode& node) = 0;
};

class BaseNode
{
public:
    explicit BaseNode(const std::string& name) : mName(name) {}
    virtual ~BaseNode() {}
    virtual void Accept(INodeVisitor& visitor) = 0;
private:
    std::string mName;
};

class ShapeNode : public BaseNode
{
private:
public:
    explicit ShapeNode(const std::string& name) : BaseNode(name) {}
    void Accept(INodeVisitor& visitor)
    {
        visitor.Visit(*this);
    }
    int GetPolygonCount() const {return 4;}
};

class TransformNode : public BaseNode
{
private:
public:
    explicit TransformNode(const std::string& name) : BaseNode(name) {}
    void Accept(INodeVisitor& visitor)
    {
        visitor.Visit(*this);
    }
};

class SceneGraph
{
private:
    std::vector<BaseNode*> tree;
public:
    SceneGraph() = default;
    ~SceneGraph() = default;
    SceneGraph(const SceneGraph&) = delete;
    const SceneGraph& operator=(const SceneGraph&) = delete;
    void addScene(BaseNode* baseNode)
    {
        tree.push_back(baseNode);
    }
    void Traverse(INodeVisitor& visitor)
    {
        for(const auto& x : tree)
        {
            //MyVisitorクラスに個数カウントメソッドをまとめて、明記した
            x->Accept(visitor);
        }
    }
};

class MyVisitor : public INodeVisitor
{
private:
    int mNumShapes;
    int mNumPolygons;
    int mNumTransforms;
public:
    MyVisitor() : mNumShapes(), mNumPolygons(), mNumTransforms() {}
    void Visit(ShapeNode& node)
    {
        mNumPolygons += node.GetPolygonCount();
        ++mNumShapes;
    }
    
    void Visit(TransformNode&)
    {
        ++mNumTransforms;
    }
    int getNumShapes() {return mNumShapes; }
    int getNumPolygons() {return mNumPolygons; }
    int getNumTransforms() {return mNumTransforms; }
};

void print(MyVisitor& v)
{
    std::cout << "Shapes : " << v.getNumShapes() << std::endl;
    std::cout << "Polygons : " << v.getNumPolygons() << std::endl;
    std::cout << "Transforms : " << v.getNumTransforms() << std::endl;
}

int main(void)
{
    SceneGraph s;
    std::unique_ptr<BaseNode> n1(new ShapeNode("test1"));
    std::unique_ptr<BaseNode> n2(new TransformNode("test2"));
    s.addScene(n1.get());
    s.addScene(n2.get());
    
    MyVisitor visitor;
    s.Traverse(visitor);
    print(visitor);
    return 0;
}

