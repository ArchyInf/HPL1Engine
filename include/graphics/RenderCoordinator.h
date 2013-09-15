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
#ifndef HPL_RENDERCOORDINATOR_H
#define HPL_RENDERCOORDINATOR_H

namespace hpl {
	
	class cWorld2D;
	class cWorld3D;
	class iCamera;
	class cCamera3D;
	class cRenderList;
	class cGraphics;
	class cUpdater;

	class cRenderCoordinator
	{
	public:
		cRenderCoordinator( cGraphics* apGraphics );
		~cRenderCoordinator( );

		void UpdateRenderList(float afFrameTime);
		void Render(cUpdater* apUpdater, float afFrameTime);

		void ClearRenderList( );
		void FetchOcclusionQueries();
		
		void SetSceneInfo( iCamera* apCamera, cWorld2D* apWorld2D, cWorld3D* apWorld3D );
		void SetDrawScene( bool abX );
		bool GetDrawScene();

	private:
		void UpdateRenderList(cRenderList* apRenderList, cWorld3D* apWorld, cCamera3D* apCamera, float afFrameTime);

		cGraphics* mpGraphics;
		cRenderList* mpRenderList;
		bool mbDrawScene;

		iCamera* mpActiveCamera;
		cWorld2D* mpCurrentWorld2D;
		cWorld3D* mpCurrentWorld3D;
	};

};
#endif // HPL_RENDERCOORDINATOR_H
