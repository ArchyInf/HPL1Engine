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
#include "graphics/RenderCoordinator.h"

#include "graphics/RenderList.h"
#include "graphics/Graphics.h"
#include "graphics/GraphicsDrawer.h"
#include "graphics/Renderer2D.h"
#include "graphics/Renderer3D.h"
#include "graphics/RendererPostEffects.h"

#include "scene/RenderableContainer.h"
#include "scene/Camera2D.h"
#include "scene/Camera3D.h"
#include "scene/World2D.h"
#include "scene/World3D.h"

#include "game/Updater.h"

namespace hpl {

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cRenderCoordinator::cRenderCoordinator( cGraphics* apGraphics )
	{
		mpGraphics = apGraphics;

		mpRenderList = hplNew( cRenderList, (apGraphics) );
	}

	cRenderCoordinator::~cRenderCoordinator()
	{
		hplDelete( mpRenderList );
	}
	
	//-----------------------------------------------------------------------

	void cRenderCoordinator::ClearRenderList( )
	{
		mpRenderList->Clear();
	}

	//-----------------------------------------------------------------------
	
	void cRenderCoordinator::UpdateRenderList(float afFrameTime)
	{
		if(!mbDrawScene)
			return;

		if(mpActiveCamera->GetType() == eCameraType_3D)
		{
			cCamera3D* pCamera3D = static_cast<cCamera3D*>(mpActiveCamera);

			if(mpCurrentWorld3D)
				UpdateRenderList( mpRenderList, mpCurrentWorld3D, pCamera3D, afFrameTime );
		}
	}

	//-----------------------------------------------------------------------
	
	void cRenderCoordinator::SetDrawScene( bool abX )
	{
		mbDrawScene = abX;
		ClearRenderList();
	}

	//-----------------------------------------------------------------------

	bool cRenderCoordinator::GetDrawScene( )
	{
		return mbDrawScene;
	}

	//-----------------------------------------------------------------------
	
	void cRenderCoordinator::Render(cUpdater* apUpdater, float afFrameTime)
	{
		if(mbDrawScene && mpActiveCamera)
		{
			if(mpActiveCamera->GetType() == eCameraType_2D)
			{
				cCamera2D* pCamera2D = static_cast<cCamera2D*>(mpActiveCamera);

				//pCamera2D->SetModelViewMatrix(mpGraphics->GetLowLevel());

				if(mpCurrentWorld2D){
					mpCurrentWorld2D->Render(pCamera2D);
				}

				mpGraphics->GetRenderer2D()->RenderObjects(pCamera2D,mpCurrentWorld2D->GetGridMapLights(),mpCurrentWorld2D);
			}
			else
			{
				cCamera3D* pCamera3D = static_cast<cCamera3D*>(mpActiveCamera);

				if(mpCurrentWorld3D)
				{
					START_TIMING(RenderWorld)
					mpGraphics->GetRenderer3D()->RenderWorld(mpCurrentWorld3D, pCamera3D, mpRenderList, afFrameTime);
					STOP_TIMING(RenderWorld)
				}
			}
			START_TIMING(PostSceneDraw)
			apUpdater->OnPostSceneDraw();
			STOP_TIMING(PostSceneDraw)
			
			START_TIMING(PostEffects)
			mpGraphics->GetRendererPostEffects()->Render(mpRenderList);
			STOP_TIMING(PostEffects)
		}
		else
		{
			apUpdater->OnPostSceneDraw();
			//S
			//mpGraphics->GetLowLevel()->SetClearColor(cColor(0,1));
			//mpGraphics->GetLowLevel()->ClearScreen();
		}
		mpGraphics->GetDrawer()->DrawAll();
		
		apUpdater->OnPostGUIDraw();
	}

	//-----------------------------------------------------------------------

	void cRenderCoordinator::FetchOcclusionQueries()
	{
		//if(mbLog) Log("Fetching Occlusion Queries Result:\n");

		//With depth test
		cOcclusionQueryObjectIterator it = mpRenderList->GetQueryIterator();
		while(it.HasNext())
		{
			cOcclusionQueryObject *pObject = it.Next();
			//LogUpdate("Query: %d!\n",pObject->mpQuery);

			while(pObject->mpQuery->FetchResults()==false);

			//if(mbLog) Log(" Query: %d SampleCount: %d\n",	pObject->mpQuery,
			//												pObject->mpQuery->GetSampleCount());
		}

		//if(mbLog) Log("Done fetching queries\n");
	}
	
	//-----------------------------------------------------------------------

	void cRenderCoordinator::SetSceneInfo( iCamera* apCamera, cWorld2D* apWorld2D, cWorld3D* apWorld3D )
	{
		mpActiveCamera = apCamera;
		mpCurrentWorld2D = apWorld2D;
		mpCurrentWorld3D = apWorld3D;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------
	
	void cRenderCoordinator::UpdateRenderList(cRenderList* apRenderList, cWorld3D* apWorld, cCamera3D* apCamera, float afFrameTime)
	{
		//Clear all objects to be rendereded
		apRenderList->Clear();

		//Set some variables
		apRenderList->SetFrameTime(afFrameTime);
		apRenderList->SetCamera(apCamera);

		//Set the frustum
		cFrustum* pFrustum = apCamera->GetFrustum();
		cRenderSettings* pRenderSettings = mpGraphics->GetRenderer3D()->GetRenderSettings();
		pRenderSettings->mpFrustum = apCamera->GetFrustum();

		//Setup fog BV

		// todo: multiple viewpoints; do not handle rendersettings in Renderer3D
		// todo: mFogBV
		//if(pRenderSettings->mbFogActive && pRenderSettings->mbFogCulling)
		//{
		//	//This is becuase the fog line is a stright line infront of the camera.
		//	float fCornerDist = (pRenderSettings->mfFogEnd *2.0f) /
		//						cos(apCamera->GetFOV()*apCamera->GetAspect()*0.5f);
		//	
		//	mFogBV.SetSize(fCornerDist);
		//	mFogBV.SetPosition(apCamera->GetPosition());
		//}

		//Add all objects to be rendered
		apWorld->GetRenderContainer()->GetVisible(pFrustum, apRenderList);

		//Compile an optimized render list.
		apRenderList->Compile();
	}
}
