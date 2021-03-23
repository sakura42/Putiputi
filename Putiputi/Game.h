#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Player.h"
#include "HomingArrow.h"
#include "Barrage.h"
#include "Font.h"
#include "Button.h"
#include "Explosion.h"
#include "Lightning.h"
#include "CoolDownBar.h"
#include <vector>
#include <string>

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	static const int WindowHeight = 1080;
	static const int WindowWidth = 1920;

	static const int maxFloor = 10;
	//�e�K�̓GHP
	static const int enemyHp[maxFloor];
	//�e�K�̓G��
	static const int maxEnemy[maxFloor];
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	//�|�[�Y���
	void Pause();
	//�N���A���
	void FinishScreen();
	//player�ɐG��Ă���G��index�̂������Ԃ�
	//���Ȃ����-1
	int HitEnemyIndex();

	SDL_Window* window;
	SDL_Renderer* renderer;
	class Font* font;
	std::vector<class SkillButton*> skillButton;
	std::vector<class CoolDownBar*> cdBar;
	class SquareButton* upButton;
	class SquareButton* downButton;
	class SquareButton* pauseButton;
	std::vector<Mix_Chunk*> sounds;
	bool isRunning;
	Uint32 tickscount;

	SDL_Point mousePosition;
	bool isClicked;
	bool isLMouseUp;
	bool isRMouseUp;
	bool isEscDown;

	class Player* player;
	std::vector<class Enemy*> enemies;
	int numEnemy;
	std::vector<class HomingArrow*> homingArrows;
	std::vector<class Barrage*> barrages;
	std::vector<class Explosion*> explosions;
	std::vector<class Lightning*> lightnings;
	std::vector<float> coolDown;
	int currentFloor;
	int clearFloor;

	//�ŏ��ɑ��삵�Ă���|�[�Y��ʈȊO��true
	bool isPlaying;
	//�N���A���Ă��邩
	bool isClear;
	float cleartime;
};