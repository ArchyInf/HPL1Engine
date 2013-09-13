/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 *
 * HPL1 Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HPL1 Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HPL1 Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "graphics/Renderer3DStereo.h"

#include "math/Math.h"
#include "graphics/Texture.h"
#include "system/LowLevelSystem.h"
#include "graphics/LowLevelGraphics.h"
#include "resources/Resources.h"
#include "resources/LowLevelResources.h"
#include "resources/TextureManager.h"
#include "graphics/VertexBuffer.h"
#include "graphics/MeshCreator.h"
#include "scene/Camera3D.h"
#include "scene/Entity3D.h"
#include "graphics/RenderList.h"
#include "graphics/Renderable.h"
#include "scene/World3D.h"
#include "scene/RenderableContainer.h"
#include "scene/Light3D.h"
#include "math/BoundingVolume.h"
#include "resources/GpuProgramManager.h"
#include "graphics/GPUProgram.h"
#include "graphics/RendererPostEffects.h"

namespace hpl {

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cRenderer3DStereo::cRenderer3DStereo(iLowLevelGraphics *apLowLevelGraphics,cResources* apResources,
										 cMeshCreator* apMeshCreator, cRenderList *apRenderList) 
		: cRenderer3D( apLowLevelGraphics, apResources, apMeshCreator, apRenderList )
	{
		Log("  Renderer3DStereo created\n");
	}

	//-----------------------------------------------------------------------

	cRenderer3DStereo::~cRenderer3DStereo()
	{
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void cRenderer3DStereo::RenderWorld(cWorld3D* apWorld, cCamera3D* apCamera, float afFrameTime)
	{
		cRenderer3D::RenderWorld( apWorld, apCamera, afFrameTime );
	}


	//-----------------------------------------------------------------------

}
