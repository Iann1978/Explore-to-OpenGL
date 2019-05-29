//
// Created by Iann on 2019/5/29.
//

#ifndef OPENGLBYNDK_IRENDERABLE_H
#define OPENGLBYNDK_IRENDERABLE_H

class  IRenderable
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~IRenderable() { }
};

#endif //OPENGLBYNDK_IRENDERABLE_H
