﻿#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
#include "VariableSets.h"
#include "Timer.h"
#ifndef SOUNDPLAY_H
#define SOUNDPLAY_H

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openDamageSound;
MCI_PLAY_PARMS playDamageSound;
MCI_OPEN_PARMS openNpcSound;
MCI_PLAY_PARMS playNpcSound;
MCI_OPEN_PARMS openBulletSound;
MCI_PLAY_PARMS playBulletSound;
MCI_OPEN_PARMS openReloadSound;
MCI_PLAY_PARMS playReloadSound;
MCI_OPEN_PARMS openMissionCompleteSound;
MCI_PLAY_PARMS playMissionCompleteSound;
MCI_OPEN_PARMS openMissionFailedSound;
MCI_PLAY_PARMS playMissionFailedSound;
MCI_OPEN_PARMS openGetExpSound;
MCI_PLAY_PARMS playGetExpSound;
MCI_OPEN_PARMS openGetItemSound;
MCI_PLAY_PARMS playGetItemSound;
MCI_OPEN_PARMS openWarningSound;
MCI_PLAY_PARMS playWarningSound;

#define BGM L"BGM_B1.mp3"	//BGM
#define SOUNDEFFECT_COLLISION L"COLLISION.mp3"		//DAMAGE 효과음
#define SOUNDEFFECT_DEFAULTGUN L"DEFAULTGUN.mp3"
#define SOUNDEFFECT_SHOTGUN L"SHOTGUN.mp3"
#define SOUNDEFFECT_MACHINEGUN L"MACHINEGUN.mp3"
#define SOUNDEFFECT_RELOAD L"RELOAD.mp3"
#define SOUNDEFFECT_NPCDAMAGED L"NPC_DAMAGED.mp3"
#define SOUNDEFFECT_GETEXP L"GETEXP.mp3"
#define SOUNDEFFECT_GETITEM L"GETITEM.mp3"
#define SOUNDEFFECT_WARNING L"WARNING.mp3"
#define MISSIONCOMPLETE L"MISSIONCOMPLETE.mp3"
#define MISSIONFAILED L"MISSIONFAILED.mp3"

UINT dwID;

void PlayBGMSound() {
	MCI_DGV_SETAUDIO_PARMS BgmVolume;
	BgmVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	BgmVolume.dwValue = 200;
	openBgm.lpstrElementName = BGM;
	openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 형식, wav 형식이면 "waveaudio" 작성
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommandW(dwID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&BgmVolume);
	mciSendCommandW(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playBgm);    //음악 반복 재생
}

UINT dwIDSE_D;

void PlayCOLLISIONSound() {
	MCI_DGV_SETAUDIO_PARMS CollisionVolume;
	CollisionVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	CollisionVolume.dwValue = 450;
	openDamageSound.lpstrElementName = SOUNDEFFECT_COLLISION;    //파일 오픈
	openDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDamageSound);
	dwIDSE_D = openDamageSound.wDeviceID;
	mciSendCommandW(dwIDSE_D, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&CollisionVolume);
	mciSendCommandW(dwIDSE_D, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playDamageSound);    //음악을 한 번 재생
}

UINT dwIDSE_NPCD;

void PlayNPCDAMAGEDSound() {
	MCI_DGV_SETAUDIO_PARMS NPCDAMAGEDVolume;
	NPCDAMAGEDVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	NPCDAMAGEDVolume.dwValue = 450;
	openNpcSound.lpstrElementName = SOUNDEFFECT_NPCDAMAGED;    //파일 오픈
	openNpcSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openNpcSound);
	dwIDSE_NPCD = openNpcSound.wDeviceID;
	mciSendCommandW(dwIDSE_NPCD, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playNpcSound);    //음악을 한 번 재생
}

UINT dwIDSE_R;

void PlayRELOADSound() {
	MCI_DGV_SETAUDIO_PARMS RELOADVolume;
	RELOADVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	RELOADVolume.dwValue = 450;
	openReloadSound.lpstrElementName = SOUNDEFFECT_RELOAD;    //파일 오픈
	openReloadSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openReloadSound);
	dwIDSE_R = openReloadSound.wDeviceID;
	mciSendCommandW(dwIDSE_R, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playReloadSound);    //음악을 한 번 재생
}

UINT dwIDSE_B;

void PlayGUNSHOOTSound(LPCWSTR Filename, LPCWSTR Filetype) {
	MCI_DGV_SETAUDIO_PARMS BulletVolume;
	BulletVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	BulletVolume.dwValue = 450;
	openBulletSound.lpstrElementName = Filename;    //파일 오픈
	openBulletSound.lpstrDeviceType = Filetype;    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBulletSound);
	dwIDSE_B = openBulletSound.wDeviceID;
	mciSendCommandW(dwIDSE_B, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&BulletVolume);
	mciSendCommandW(dwIDSE_B, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playBulletSound);    //음악을 한 번 재생
}

UINT dwIDSE_EXP;

void PlayGETEXPSound() {
	MCI_DGV_SETAUDIO_PARMS GETEXPVolume;
	GETEXPVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	GETEXPVolume.dwValue = 450;
	openGetExpSound.lpstrElementName = SOUNDEFFECT_GETEXP;    //파일 오픈
	openGetExpSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openGetExpSound);
	dwIDSE_EXP = openGetExpSound.wDeviceID;
	mciSendCommandW(dwIDSE_EXP, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&GETEXPVolume);
	mciSendCommandW(dwIDSE_EXP, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playGetExpSound);    //음악을 한 번 재생
}

UINT dwIDSE_ITEM;

void PlayGETITEMSound() {
	MCI_DGV_SETAUDIO_PARMS GETITEMVolume;
	GETITEMVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	GETITEMVolume.dwValue = 450;
	openGetItemSound.lpstrElementName = SOUNDEFFECT_GETITEM;    //파일 오픈
	openGetItemSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openGetItemSound);
	dwIDSE_ITEM = openGetItemSound.wDeviceID;
	mciSendCommandW(dwIDSE_ITEM, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&GETITEMVolume);
	mciSendCommandW(dwIDSE_ITEM, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playGetItemSound);    //음악을 한 번 재생
}

UINT dwID_MC;

void PlayMISSIONCOMPLETESound() {
	MCI_DGV_SETAUDIO_PARMS MCVolume;
	MCVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	MCVolume.dwValue = 350;
	openMissionCompleteSound.lpstrElementName = MISSIONCOMPLETE;    //파일 오픈
	openMissionCompleteSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openMissionCompleteSound);
	dwID_MC = openMissionCompleteSound.wDeviceID;
	mciSendCommandW(dwID_MC, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&MCVolume);
	mciSendCommandW(dwID_MC, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playMissionCompleteSound);    //음악을 한 번 재생
}

UINT dwID_MF;

void PlayMISSIONFAILEDSound() {
	MCI_DGV_SETAUDIO_PARMS MFVolume;
	MFVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	MFVolume.dwValue = 450;
	openMissionFailedSound.lpstrElementName = MISSIONFAILED;    //파일 오픈
	openMissionFailedSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openMissionFailedSound);
	dwID_MF = openMissionFailedSound.wDeviceID;
	mciSendCommandW(dwID_MF, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&MFVolume);
	mciSendCommandW(dwID_MF, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playMissionFailedSound);    //음악을 한 번 재생
}

UINT dwIDSE_W;

void PlayWARNINGSound() {
	MCI_DGV_SETAUDIO_PARMS WVolume;
	WVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	WVolume.dwValue = 450;
	openWarningSound.lpstrElementName = SOUNDEFFECT_WARNING;    //파일 오픈
	openWarningSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openWarningSound);
	dwIDSE_W = openWarningSound.wDeviceID;
	mciSendCommandW(dwIDSE_W, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&WVolume);
	mciSendCommandW(dwIDSE_W, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playWarningSound);    //음악을 한 번 재생
}
#endif // !SOUNDPLAY_H