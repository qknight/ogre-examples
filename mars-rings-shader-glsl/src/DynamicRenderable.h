/*
This source file is part of Rigs of Rods
Copyright 2005,2006,2007,2008,2009 Pierre-Michel Ricordel
Copyright 2007,2008,2009 Thomas Fischer

For more information, see http://www.rigsofrods.com/

Rigs of Rods is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3, as 
published by the Free Software Foundation.

Rigs of Rods is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Rigs of Rods.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DYNAMIC_RENDERABLE_H
#define DYNAMIC_RENDERABLE_H

#include <OgreSimpleRenderable.h>

class DynamicRenderable : public Ogre::SimpleRenderable
{
public:
  DynamicRenderable();
  virtual ~DynamicRenderable();

  void initialize(Ogre::RenderOperation::OperationType operationType,
                  bool useIndices);

  virtual Ogre::Real getBoundingRadius(void) const;
  virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;

protected:
  size_t mVertexBufferCapacity;
  size_t mIndexBufferCapacity;

  virtual void createVertexDeclaration() = 0;

  void prepareHardwareBuffers(size_t vertexCount, size_t indexCount);

  virtual void fillHardwareBuffers() = 0;
};

#endif // DYNAMIC_RENDERABLE_H

