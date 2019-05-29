//
// Created by Iann on 2019/5/29.
//

#ifndef OPENGLBYNDK_RENDERABLE_H
#define OPENGLBYNDK_RENDERABLE_H
class  IRenderable
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~IRenderable() { }
};
#endif //OPENGLBYNDK_RENDERABLE_H
