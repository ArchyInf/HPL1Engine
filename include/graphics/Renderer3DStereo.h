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

#ifndef HPL_RENDERER3DSTEREO_H
#define HPL_RENDERER3DSTEREO_H

#include "graphics/Renderer3D.h"

namespace hpl {

	//---------------------------------------------
	
	class cRenderer3DStereo : public cRenderer3D
	{
	public:
		cRenderer3DStereo(iLowLevelGraphics *apLowLevelGraphics,cResources* apResources,
							cMeshCreator* apMeshCreator, cRenderList *apRenderList);
		virtual ~cRenderer3DStereo();

		virtual void RenderWorld(cWorld3D* apWorld, cCamera3D* apCamera, float afFrameTime);
	};

};
#endif // HPL_RENDERER3DSTEREO_H
