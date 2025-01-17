﻿#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Player.h"
#include "Timer.h"
#ifndef ENEMY_H
#define ENEMY_H
//---------------------------------------------------------
//---------------초기화 및 시간계산 함수----------------

//적 NPC 버퍼 시간 계산 함수
int CalculateEnemyTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - EnemyInputTime > ENEMYTIMEBUFFER / EnemySpeed) { EnemyInputTime = CheckedTime; return 0; }
	else return 1;
}

//적 위치 초기화 함수
void ClearEnemyPosition() {
	ENEMY_POS_X = ENEMY_ORIGIN_POS_X;
	ENEMY_POS_Y = ENEMY_ORIGIN_POS_Y;
	direction = EnemyIsMoving = 0;
}

void InitStageEnemyHealth() { StageEnemyHealth = Enemy_Health[StageNumber - 1]; }
void InitInfiniteModeEnemyHealth() { StageEnemyHealth = 600; }

//----------------------------------------------------------
//-----------------적 이미지 출력함수--------------------

//적 삭제 함수
void HideEnemy() {
	for (int i = 0; i < ENEMYSIZE_H; i++) {
		for (int j = 0; j < ENEMYSIZE_W; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}

//적 출력 함수
void ShowEnemy() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	for (int i = 0; i < ENEMYSIZE_H; i++) {
		for (int j = 0; j < ENEMYSIZE_W; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf("%c", EnemyModel[i][j]);
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//----------------------------------------------------------
//-------------------충돌검사 함수------------------------

//적이 벽에 충돌하였는지 유무 확인 함수
int DetectCollision_Enemy(int x, int y) {
	for (int i = 0; i < ENEMYSIZE_H; i++) {
		for (int j = 0; j < ENEMYSIZE_W; j++)
			if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == WALL) return 1;
	}
	return 0;
}

//-------------------------------------------------------------
//-----------------EnemyMotion 관련함수-------------------

void shiftEnemyLeft() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X - 1, ENEMY_POS_Y)) { direction = DIRECTION_LEFT; ENEMY_POS_X--; }
	else direction = DIRECTION_RIGHT;
	ShowEnemy();
}
void shiftEnemyRight() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X + 1, ENEMY_POS_Y)) { direction = DIRECTION_RIGHT; ENEMY_POS_X++; }
	else direction = DIRECTION_LEFT;
	ShowEnemy();
}
void shiftEnemyUp() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X, ENEMY_POS_Y - 1)) { direction = DIRECTION_UP; ENEMY_POS_Y--; }
	else direction = DIRECTION_DOWN;
	ShowEnemy();
}
void shiftEnemyDown() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X, ENEMY_POS_Y + 1)) { direction = DIRECTION_DOWN; ENEMY_POS_Y++; }
	else direction = DIRECTION_UP;
	ShowEnemy();
}
void shiftEnemyLeftUp() {
	int CombinedDirection = 0;
	shiftEnemyLeft(); CombinedDirection += direction;
	shiftEnemyUp(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyLeftDown() {
	int CombinedDirection = 0;
	shiftEnemyLeft(); CombinedDirection += direction;
	shiftEnemyDown(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyRightUp() {
	int CombinedDirection = 0;
	shiftEnemyRight(); CombinedDirection += direction;
	shiftEnemyUp(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyRightDown() {
	int CombinedDirection = 0;
	shiftEnemyRight(); CombinedDirection += direction;
	shiftEnemyDown(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}

//---------------------------------------------------------------
//------------------EnemyMovement 함수---------------------
//원래 좌표로 돌아간다
int EnemyMotion_MoveToOriginPos() {
	int flag = 0;
	if (ENEMY_POS_X < ENEMY_ORIGIN_POS_X) shiftEnemyRight();
	else if (ENEMY_POS_X > ENEMY_ORIGIN_POS_X) shiftEnemyLeft();
	else flag++;

	if (ENEMY_POS_Y < ENEMY_ORIGIN_POS_Y) shiftEnemyDown();
	else if (ENEMY_POS_Y > ENEMY_ORIGIN_POS_Y) shiftEnemyUp();
	else flag++;

	if (flag > 1) { EnemyIsMoving = 0; direction = 0; return 1; } return 0;		//처음 자리로 되돌아 왔으면 1 반환, 그 외 0 반환
}

//좌우로 평범하게 움직인다
void EnemyMotion_MovingLeftRight() {
	if (direction == DIRECTION_RIGHT) shiftEnemyRight();
	else if(direction == DIRECTION_LEFT) shiftEnemyLeft();
}

//랜덤 포지션으로 점멸하며 움직인다--X좌표에만 해당
void EnemyMotion_FlashToRandomPosX() {
	if (TimeCheckerEnd() - PausingTime - EnemyMovementTiming > ENEMYMOVEMENTDURATION_ver1) { 
		HideEnemy();
		ENEMY_POS_X = rand() % (GAMEBOARD_ROW - ENEMYSIZE_W - 2) + GAMEBOARD_ORIGIN_X + 2;
		ShowEnemy();
		EnemyMovementTiming += ENEMYMOVEMENTDURATION_ver1;
	}
}

//랜덤 포지션으로 점멸하며 움직인다 --X, Y좌표 모두 해당
void EnemyMotion_FlashToRandomPosXY() {
	if (TimeCheckerEnd() - PausingTime - EnemyMovementTiming > ENEMYMOVEMENTDURATION_ver2) {
		HideEnemy();
		ENEMY_POS_X = rand() % (GAMEBOARD_ROW - ENEMYSIZE_W - 2) + GAMEBOARD_ORIGIN_X + 2;
		ENEMY_POS_Y = rand() % (GAMEBOARD_COLUMN - ENEMYSIZE_H - 1) + GAMEBOARD_ORIGIN_Y + 1;
		ShowEnemy();
		EnemyMovementTiming += ENEMYMOVEMENTDURATION_ver2;
	}
}

//중심으로 이동하고 멈춘다
void EnemyMotion_MoveToCenter() {
	if (ENEMY_POS_X == ENEMY_ORIGIN_POS_X && ENEMY_POS_Y == GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - (ENEMYSIZE_H / 2)) return;

	if (ENEMY_POS_X < ENEMY_ORIGIN_POS_X) shiftEnemyRight();
	else if (ENEMY_POS_X > ENEMY_ORIGIN_POS_X) shiftEnemyLeft();

	if (ENEMY_POS_Y < GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - (ENEMYSIZE_H / 2)) shiftEnemyDown();
	else if (ENEMY_POS_Y > GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - (ENEMYSIZE_H / 2)) shiftEnemyUp();
}

//벽을 튕기면서 이동
void EnemyMotion_BouncingAroundWall() {
	switch (direction) {
	case 1: shiftEnemyUp(); break;
	case 2: shiftEnemyDown(); break;
	case 3: shiftEnemyLeft(); break;
	case 4: shiftEnemyRight(); break;
	case 5: shiftEnemyLeftUp(); break;
	case 6: shiftEnemyRightUp(); break;
	case 7: shiftEnemyLeftDown(); break;
	case 8: shiftEnemyRightDown(); break;
	}
}

//--------------------------------------------------------------
//--------------------EnemySkill 함수------------------------- 

void InitializePrisonInfo() {
	P.Prison_H = 7; P.Prison_W = 24;
	P.LU_X = P.LU_Y = P.RD_X = P.RD_Y = 0;
}

//----------------EnemySkillPrison 출력 함수---------------

//감옥 정보 갱신
void InvalidatePrisonInfo() {
	P.LU_X = PLAYER_POS_X - (P.Prison_W - 6) / 2 - 2;
	P.LU_Y = PLAYER_POS_Y - (P.Prison_H - 1) / 2 - 1;
	P.RD_X = P.LU_X + P.Prison_W + 2;
	P.RD_Y = P.LU_Y + P.Prison_H;
}

//감옥 출력 함수
void DrawEnemySkillPrison() {
	for (int i = 0; i <= P.Prison_H; i++) {
		SetCurrentCursorPos(P.LU_X, P.LU_Y + i);
		if (i == 0) printf("┏");
		else if (i == P.Prison_H) printf("┗");
		else printf("┃");
		SetCurrentCursorPos(P.RD_X, P.LU_Y + i);
		if (i == 0) printf("┓");
		else if (i == P.Prison_H) printf("┛");
		else printf("┃");
	}

	for (int i = 2; i <= P.Prison_W; i += 2) {
		SetCurrentCursorPos(P.LU_X + i, P.LU_Y);
		printf("━");
		SetCurrentCursorPos(P.LU_X + i, P.RD_Y);
		printf("━");
	}
}

//감옥 삭제 함수
void EraseEnemySkillPrison() {
	for (int i = 0; i <= P.Prison_H; i++) {
		SetCurrentCursorPos(P.LU_X, P.LU_Y + i);
		printf("  ");
		SetCurrentCursorPos(P.RD_X, P.LU_Y + i);
		printf("  ");
	}

	for (int i = 2; i <= P.Prison_W; i += 2) {
		SetCurrentCursorPos(P.LU_X + i, P.LU_Y);
		printf("  ");
		SetCurrentCursorPos(P.LU_X + i, P.RD_Y);
		printf("  ");
	}
}

//------------스킬 발동 함수---------------

void ActivateEnemySkill_Prison() {
	DrawEnemySkillPrison();
	EnemySkillPrisonActivation = 1;
}
void DeactivateEnemySkill_Prison() {
	if (EnemySkillPrisonActivation) {
		EraseEnemySkillPrison();
		EnemySkillPrisonActivation = 0;
	}
}

//--------------------------------------------------------------
//-------------------Invalidation 함수-------------------------

//적 갱신 함수
void InvalidateEnemy() {
	ShowEnemy();
	if (!CalculateEnemyTimeBuffer()) {
		if (PatternNumber == 1) { 
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else {
				if (!direction) direction = DIRECTION_LEFT;	//방향이 정해져있지 않을 때 방향 설정
				EnemyMotion_MovingLeftRight();
			}
		}
		else if (PatternNumber == 2 || PatternNumber == 3 || PatternNumber == 9) {
			if (PatternTimeEnded) {
				if (PatternNumber == 2) DeactivateEnemySkill_Prison(); //패턴 넘버가 2번이면 감옥 제거
				if (EnemyMotion_MoveToOriginPos()) { EnemyIsMoving = 0; return; }//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			}
			else { 
				if (PatternNumber == 2) { 
					if (!EnemySkillPrisonActivation) { HidePlayer(); ClearPlayerPosition(); InvalidatePrisonInfo(); } 
					ActivateEnemySkill_Prison();
				} 
				EnemyMotion_FlashToRandomPosX();
			}
		}
		else if (PatternNumber == 7 || PatternNumber == 8) {
			if (PatternTimeEnded) { EnemySpeed = 1.0; if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else {
				EnemySpeed = 0.5;
				if (!direction) direction = rand() % 2 + 7;
				EnemyMotion_BouncingAroundWall();
			}
		}
		else if(PatternNumber == 4) {	//Enemy Motion 수정 필요
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else EnemyMotion_MoveToCenter();
		}
		else if (PatternNumber == 5) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else EnemyMotion_FlashToRandomPosXY();
		}
		else if (PatternNumber == 6) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else EnemyMotion_FlashToRandomPosX();
		}
		else if (PatternNumber == 10) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//패턴 지속시간이 끝났을 경우 다시 제자리로 이동하는데 다 이동했으면 Enemy이동 인디케이터 0으로 갱신
			else if (ENEMY_POS_X < GAMEBOARD_ROW - ENEMYSIZE_W) shiftEnemyRight();
			else {
				HideEnemy();
				ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 4;
			}
		}
	}
}
#endif // !ENEMY_H
