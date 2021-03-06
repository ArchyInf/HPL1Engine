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
#include <hpl.h>

using namespace hpl;

class cHOECamera : public iUpdateable
{
public:
	cHOECamera(cGame *apGame, float afSpeed,cVector3f avStartPos,bool abShowFPS);
	~cHOECamera();

	void Update(float afFrameTime);
	
	void OnDraw();

	cCamera3D* GetCamera(){ return  mpCamera;}
private:
	void CalculateCameraPos();	

	cGame *mpGame;
	iFontData* mpFont;
	cCamera3D* mpCamera;

	float mfSpeed;

	cVector3f mvAngle;
	cVector3f mvStartPos;
	float mfMinDist;
	float mfMaxDist;
};