#include "Game.h"

Game::Game(){
	this->window = NULL;
	this->renderer = NULL;
	this->font = NULL;
	this->isRunning = true;
	this->isClicked = false;
	this->isLMouseUp = false;
	this->isRMouseUp = false;
	this->isEscDown = false;
	this->numEnemy = maxEnemy[0];
	this->mousePosition = { 0,0 };
	this->player = NULL;
	this->tickscount = 0;
	this->currentFloor = 1;
	this->clearFloor = 0;
	this->upButton = NULL;
	this->downButton = NULL;
	this->pauseButton = NULL;
	this->isPlaying = false;
	this->isClear = false;
	this->cleartime = 0;
}

const int Game::enemyHp[] = {
	100, 200, 800, 1000, 1500, 2000, 4000, 8000, 10000, 15000
};

const int Game::maxEnemy[] = {
	100, 150, 200, 250, 300, 350, 400, 450, 500, 550
};

bool Game::Initialize() {
	//SDL������
	int sdlResult = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlResult != 0) {
		SDL_Log(u8"SDL���������o���܂���:%s", SDL_GetError());
		return false;
	}

	//�E�B���h�E�쐬
	window = SDL_CreateWindow("Putiputi", 0, 0, WindowWidth, WindowHeight, 0);
	if (!window) {
		SDL_Log(u8"�E�B���h�E�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
		return false;
	}

	//�����_���[�쐬
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_Log(u8"�����_���[�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	//SDL_ttf������
	int sdlTtfResult = TTF_Init();
	if (sdlTtfResult != 0) {
		SDL_Log(u8"SDL_ttf���������o���܂���");
		return false;
	}

	//SDL_mixer������
	int sdlMixerResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	if (sdlMixerResult != 0) {
		SDL_Log(u8"SDL_mixer���������o���܂���");
		return false;
	}
	//�`�����l������100��
	Mix_AllocateChannels(100);

	//���ʉ��ǂݍ���
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�L�����Z��2.wav"));//0
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�V���b�g����.wav"));//1
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�i�C�t�𓊂���.wav"));//2
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�p���[�A�b�v.wav"));//3
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\����A�{�^������9.wav"));//4
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\����A�{�^������13.wav"));//5
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\����A�{�^������15.wav"));//6
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\����A�{�^������32.wav"));//7
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\���e������.wav"));//8
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\��C2.wav"));//9
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\��.wav"));//10
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�X�e�[�^�X�㏸���@2.wav"));//11
	sounds.insert(sounds.end(), Mix_LoadWAV(u8"Data\\Sound\\�^�C�g���\��.wav"));//12
	for (auto i : sounds) {
		if (i == NULL) {
			SDL_Log(u8"���ʉ��̃��[�h�Ɏ��s���܂���");
			return false;
		}
	}

	//font�ǂݍ���
	font = new Font();
	font->Load("Data\\Font\\PixelMplus10-Regular.ttf");

	player = new Player();

	for (int i = 0; i < numEnemy; i++) {
		enemies.insert(enemies.end(), new Enemy(enemyHp[currentFloor-1]));
	}

	for (int i = 0; i < Player::skillNumMax; i++) {
		skillButton.insert(skillButton.end(), new SkillButton(i));
	}
	for (int i = 0; i < Player::skillNumMax; i++) {
		cdBar.insert(cdBar.end(), new CoolDownBar(i));
	}

	upButton = new SquareButton(1800,400);
	downButton = new SquareButton(1800,500);
	pauseButton = new SquareButton(1800, 50);

	for (int i = 0; i < Player::skillNumMax; i++) {
		coolDown.insert(coolDown.end(), 0);
	}

	return true;
}

void Game::RunLoop() {
	while (isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown(){
	if (font != NULL) {
		font->Unload();
	}
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

void Game::ProcessInput() {

	//�}�E�X�֘A��t
	SDL_Event event;
	isLMouseUp = false;
	isRMouseUp = false;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				isClicked = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				isClicked = false;
				isLMouseUp = true;
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				isRMouseUp = true;
			}
			break;
		}
	}

	//player�ɃL�[���͓n��
	const Uint8* state = SDL_GetKeyboardState(NULL);
	player->ProcessKeyboard(state);

	//��������isPlaying��true��
	if (state[SDL_SCANCODE_W]
		|| state[SDL_SCANCODE_UP]
		||state[SDL_SCANCODE_A]
		|| state[SDL_SCANCODE_LEFT]
		||state[SDL_SCANCODE_S]
		|| state[SDL_SCANCODE_DOWN]
		||state[SDL_SCANCODE_D]
		|| state[SDL_SCANCODE_RIGHT]) {
		isPlaying = true;
	}

	//�{�^���Ƀ}�E�X�֘A�n��
	for (int i = 0; i < Player::skillNumMax; i++) {
		skillButton[i]->ProcessInput(isClicked);
	}
	upButton->ProcessInput(isClicked);
	downButton->ProcessInput(isClicked);
	pauseButton->ProcessInput(isClicked);

	//�}�E�X���Wset
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

	//�|�[�Y(escape)
	if (isEscDown && !state[SDL_SCANCODE_ESCAPE]) {
		isEscDown = false;
	}
	if (!isEscDown && state[SDL_SCANCODE_ESCAPE]) {
		Mix_PlayChannel(-1, sounds[0], 0);
		isPlaying = false;
		isEscDown = true;
		Pause();
	}

	//�z�[�~���O
	if (player->GetSkillLevel(0) > 0 && state[SDL_SCANCODE_SPACE] && coolDown[0] <= 0 && numEnemy > 0) {
		float min = player->Distance(enemies[0]);
		Enemy *closestEnemy = enemies[0];
		for (auto i : enemies) {
			if (min > player->Distance(i)) {
				min = player->Distance(i);
				closestEnemy = i;
			}
		}
		int arrowRange = player->skill[0][player->GetSkillLevel(0) - 1];
		if (min < arrowRange) {
			Mix_PlayChannel(-1, sounds[2], 0);
			homingArrows.insert(homingArrows.end(), new HomingArrow(player, closestEnemy));
			coolDown[0] = Player::coolDownMax[0];
		}
	}

	//�o���[�W
	if (player->GetSkillLevel(1) > 0
		&& isLMouseUp
		&& coolDown[1] <= 0) {
		//�{�^�����N���b�N�����ꍇ�͏��O
		bool isPressButton = false;
		for (auto i : skillButton) {
			if (i->IsPressed()) {
				isPressButton = true;
				break;
			}
		}
		if (pauseButton->IsPressed()
			|| upButton->IsPressed()
			|| downButton->IsPressed()) {
			isPressButton = true;
		}

		if (!isPressButton) {
			Mix_PlayChannel(-1, sounds[8], 0);
			barrages.insert(barrages.end(), new Barrage(player, (float)(mousePosition.x), (float)(mousePosition.y), player->skill[1][player->GetSkillLevel(1) - 1]));
			coolDown[1] = Player::coolDownMax[1];
		}
	}

	//�G�N�X�v���[�W����
	if (player->GetSkillLevel(2) > 0
		&& isRMouseUp
		&& coolDown[2] <= 0) {
		float range = (float)Explosion::range;
		Object* skillRange = new Object((float)(mousePosition.x)-range, (float)(mousePosition.y)-range, range*2);
		for (auto i : enemies) {
			if (skillRange->IsHit(i)) {
				Mix_PlayChannel(-1, sounds[7], 0);
				i->SetIsExplosion(true);
			}
		}
		coolDown[2] = Player::coolDownMax[2];
	}

	//���C�g�j���O
	if (player->GetSkillLevel(3) > 0 && state[SDL_SCANCODE_Q] && coolDown[3] <= 0 && numEnemy > 0){
		float min = player->Distance(enemies[0]);
		Enemy* closestEnemy = enemies[0];
		for (auto i : enemies) {
			if (min > player->Distance(i)) {
				min = player->Distance(i);
				closestEnemy = i;
			}
		}
		Mix_PlayChannel(-1, sounds[10], 0);
		lightnings.insert(lightnings.end(), new Lightning(player, enemies, player->skill[3][player->GetSkillLevel(3) - 1]));
		coolDown[3] = Player::coolDownMax[3];
	}
}

void Game::UpdateGame(){
	//deltaTime
	float deltaTime = (SDL_GetTicks() - tickscount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	tickscount = SDL_GetTicks();

	//�v���C�������N���A�Ȃ�^�C������
	if (isPlaying && !isClear) {
		cleartime += deltaTime;
	}

	//Update�֘A
	player->UpdatePlayer(deltaTime);
	for (auto i : homingArrows) {
		i->UpdateArrow(deltaTime);
	}
	for (auto i : barrages) {
		for (auto j : i->arrows) {
			j->UpdateArrow(deltaTime);
		}
	}
	for (auto i : explosions) {
		i->UpdateExplosion(deltaTime, player->skill[2][player->GetSkillLevel(2) - 1]);
	}
	for (auto i : lightnings) {
		i->UpdateLightning(deltaTime);
	}

	//�{�^���n isAvailable
	for (int i = 0; i < Player::skillNumMax; i++) {
		skillButton[i]->SetIsAvailable(player->GetSp() >= Player::upgradePoint[i][player->GetSkillLevel(i)] && player->GetSkillLevel(i) < Player::skillLevelMax);
	}
	upButton->SetIsAvailable(currentFloor <= clearFloor && currentFloor < maxFloor);
	downButton->SetIsAvailable(currentFloor > 1);
	pauseButton->SetIsAvailable(true);

	//skill�{�^���������΃��x���グ��
	for (int i = 0; i < Player::skillNumMax; i++) {
		if (skillButton[i]->IsPressed() && skillButton[i]->GetIsAvailable() && player->GetSkillLevel(i) < Player::skillLevelMax) {
			Mix_PlayChannel(-1, sounds[4], 0);
			player->IncSp(-(Player::upgradePoint[i][player->GetSkillLevel(i)]));
			player->IncSkillLevel(i);
		}
	}

	//cd���炷
	for (int i = 0; i < Player::skillNumMax; i++) {
		coolDown[i] -= deltaTime;
		if (coolDown[i] < 0) {
			coolDown[i] = 0;
		}
	}

	//�̓�����_���[�W
	int hitindex = HitEnemyIndex();
	if (hitindex >= 0) {
		enemies[hitindex]->Damage(20);
		//player->Damage(5);
	}

	//�z�[�~���O�̃_���[�W
	int NumArrow = homingArrows.size();
	for (int i = NumArrow - 1; i >= 0; i--) {
		for (auto j : enemies) {
			if (j->IsHit(homingArrows[i])) {
				j->Damage(player->skill[0][player->GetSkillLevel(0)-1]);
				homingArrows.erase(homingArrows.begin() + i);
				break;
			}
		}
	}
	//�o���[�W�̃_���[�W
	int NumBarrage = barrages.size();
	for (int i = NumBarrage - 1; i >= 0; i--) {
		for (auto j : barrages[i]->arrows) {
			for (auto k : enemies) {
				if (k->IsHit(j)) {
					k->Damage(Barrage::damage);
				}
			}
		}
	}
	//�G�N�X�v���[�W�����̃_���[�W
	int NumExplosions = explosions.size();
	for (int i = NumExplosions - 1; i >= 0; i--) {
		for (auto j : enemies) {
			if (j->IsHit(explosions[i])) {
				j->Damage(Explosion::damage);
			}
		}
	}
	//���C�g�j���O�̃_���[�W��Lightning���ŏ���


	//�͈͊O�̃z�[�~���O����
	NumArrow = homingArrows.size();
	for (int i = NumArrow - 1; i >= 0; i--) {
		if (homingArrows[i]->GetX() > Game::WindowWidth - homingArrows[i]->GetSize()
			|| homingArrows[i]->GetX() < 0
			|| homingArrows[i]->GetY() > Game::WindowHeight - homingArrows[i]->GetSize()
			|| homingArrows[i]->GetY() < 0){
			homingArrows.erase(homingArrows.begin() + i);
		}
	}
	//�͈͊O�̃o���[�W����
	NumBarrage = barrages.size();
	for (int i = NumBarrage - 1; i >= 0; i--) {
		NumArrow = barrages[i]->arrows.size();
		for (int j = NumArrow - 1; j >= 0; j--) {
			if (barrages[i]->arrows[j]->GetX() > Game::WindowWidth - barrages[i]->arrows[j]->GetSize()
				|| barrages[i]->arrows[j]->GetX() < 0
				|| barrages[i]->arrows[j]->GetY() > Game::WindowHeight - barrages[i]->arrows[j]->GetSize()
				|| barrages[i]->arrows[j]->GetY() < 0) {
				barrages[i]->arrows.erase(barrages[i]->arrows.begin() + j);
			}
		}
	}

	//�G�N�X�v���[�W��������
	NumExplosions = explosions.size();
	for (int i = NumExplosions - 1; i >= 0; i--) {
		if (explosions[i]->getAlpha() <= 0) {
			explosions.erase(explosions.begin() + i);
		}
	}

	//���C�g�j���O����
	int NumLightnings = lightnings.size();
	for (int i = NumLightnings - 1; i >= 0; i--) {
		if (lightnings[i]->GetEnd()) {
			lightnings.erase(lightnings.begin() + i);
		}
	}

	////�s����̂Ȃ��������       ���s����Ȃ������炻�̂܂ܔ�Ԃ悤�ɕύX����
	//NumArrow = homingArrows.size();
	//for (int i = NumArrow - 1; i >= 0; i--) {
	//	if (homingArrows[i]->objto->GetHp() <= 0) {
	//		homingArrows.erase(homingArrows.begin() + i);
	//	}
	//}

	//HP0�Ȃ玀�񂾔���
	for (int i = numEnemy-1; i >= 0; i--) {
		if (enemies[i]->GetHp() <= 0) {
			if (enemies[i]->GetIsExplosion()) {
				Mix_PlayChannel(-1, sounds[9], 0);
				explosions.insert(explosions.end(), new Explosion(enemies[i]->GetX(), enemies[i]->GetY()));
			}
			Mix_PlayChannel(-1, sounds[6], 0);
			enemies.erase(enemies.begin() + i);
			numEnemy -= 1;
			player->IncSp((enemyHp[currentFloor-1]/10)+((currentFloor-1)*2));
		}
	}

	//�t���A���N���A��������
	if (numEnemy < maxEnemy[currentFloor - 1]*0.1
		&& currentFloor > clearFloor
		&& currentFloor <= maxFloor) {
		Mix_PlayChannel(-1, sounds[11], 0);
		clearFloor += 1;
		if (clearFloor >= 10) {
			isClear = true;
			Mix_HaltChannel(-1);
			Mix_PlayChannel(-1, sounds[12], 0);
			FinishScreen();
		}
	}

	//��{�^��
	if (upButton->IsPressed() && upButton->GetIsAvailable()) {
		Mix_PlayChannel(-1, sounds[0], 0);
		currentFloor += 1;
		enemies.clear();
		homingArrows.clear();
		barrages.clear();
		explosions.clear();
		numEnemy = maxEnemy[currentFloor - 1];
		for (int i = 0; i < numEnemy; i++){
			enemies.insert(enemies.end(), new Enemy(enemyHp[currentFloor - 1]));
		}
	}
	//���{�^��
	if (downButton->IsPressed() && downButton->GetIsAvailable()) {
		Mix_PlayChannel(-1, sounds[0], 0);
		currentFloor -= 1;
		enemies.clear();
		homingArrows.clear();
		barrages.clear();
		explosions.clear();
		numEnemy = maxEnemy[currentFloor - 1];
		for (int i = 0; i < numEnemy; i++) {
			enemies.insert(enemies.end(), new Enemy(enemyHp[currentFloor - 1]));
		}
	}

	//pause
	if (pauseButton->IsPressed()) {
		Mix_PlayChannel(-1, sounds[0], 0);
		isPlaying = false;
		Pause();
	}
}

void Game::GenerateOutput() {

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);

	//player
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect p{
		(int)(player->GetX()),
		(int)(player->GetY()),
		(int)(player->GetSize()), (int)(player->GetSize())
	};
	SDL_RenderFillRect(renderer, &p);

	//enemy
	for (auto i : enemies) {
		int alpha = (int)(255 * (i->GetHp()) / enemyHp[currentFloor-1]);
		if (alpha < 30) {
			alpha = 30;
		}
		if (i->GetIsExplosion()) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 125, alpha);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 70, 175, 70, alpha);
		}
		SDL_Rect e{
			(int)(i->GetX()),
			(int)(i->GetY()),
			(int)(i->GetSize()), (int)(i->GetSize())
		};
		SDL_RenderFillRect(renderer, &e);
	}

	//homingarrow
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	for (auto i : homingArrows) {
		SDL_Rect ha{
			(int)(i->GetX()),
			(int)(i->GetY()),
			(int)(i->GetSize()), (int)(i->GetSize())
		};
		SDL_RenderFillRect(renderer, &ha);
	}
	//barrage
	SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
	for (auto i : barrages) {
		for (auto j : i->arrows) {
			SDL_Rect b{
				(int)(j->GetX()),
				(int)(j->GetY()),
				(int)(j->GetSize()), (int)(j->GetSize())
			};
			SDL_RenderFillRect(renderer, &b);
		}
	}
	//explosion
	for (auto i : explosions) {
		int alpha = i->getAlpha();
		SDL_SetRenderDrawColor(renderer, 255, 80, 0, alpha);
		SDL_Rect ex{
			(int)(i->GetX()),
			(int)(i->GetY()),
			(int)(i->GetSize()), (int)(i->GetSize())
		};
		SDL_RenderFillRect(renderer, &ex);
	}
	//lightning
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	for (auto i : lightnings) {
		i->RenderLightning(renderer);
	}

	//�N�[���_�E���o�[
	for (int i = 0; i < Player::skillNumMax; i++) {
		cdBar[i]->SetColor(0, 200, 255, 255);
		cdBar[i]->RenderBar(renderer, coolDown[i]);
	}

	//����\��
	font->SetColor(255, 255, 255);
	std::string text = "Floor:" + std::to_string(currentFloor);
	font->RenderText(renderer, text, 36, 20, 20);
	text = "SP:" + std::to_string(player->GetSp());
	font->RenderText(renderer, text, 36, 20, 20+36);
	text = "Time:" + std::_Floating_to_string("%.2f", cleartime);
	font->RenderText(renderer, text, 36, 20, 20 + 36 + 36);
	
	//�X�L���{�^���֌W
	for (int i = 0; i < Player::skillNumMax; i++) {
		skillButton[i]->SetColor(0, 200, 255, 255);
	}
	font->SetColor(255, 255, 255);
	if (player->GetSkillLevel(0) <= 0) {
		std::string text = "Unlock [" + std::to_string(Player::upgradePoint[0][player->GetSkillLevel(0)]) + " SP]";
		skillButton[0]->RenderButton(renderer, font, "Homing Arrow", text);
	}
	else if(player->GetSkillLevel(0) < Player::skillLevelMax){
		std::string text = "Upgrade [" + std::to_string(Player::upgradePoint[0][player->GetSkillLevel(0)]) + " SP]";
		skillButton[0]->RenderButton(renderer, font, "[Space]:Homing Arrow", text);
	}
	else {
		skillButton[0]->RenderButton(renderer, font, "[Space]:Homing Arrow", "Max");
	}
	if (player->GetSkillLevel(1) <= 0) {
		std::string text = "Unlock [" + std::to_string(Player::upgradePoint[1][player->GetSkillLevel(1)]) + " SP]";
		skillButton[1]->RenderButton(renderer, font, "Barrage", text);
	}
	else if (player->GetSkillLevel(1) < Player::skillLevelMax) {
		std::string text = "Upgrade [" + std::to_string(Player::upgradePoint[1][player->GetSkillLevel(1)]) + " SP]";
		skillButton[1]->RenderButton(renderer, font, "[LB]:Barrage", text);
	}
	else {
		skillButton[1]->RenderButton(renderer, font, "[LB]:Barrage", "Max");
	}
	if (player->GetSkillLevel(2) <= 0) {
		std::string text = "Unlock [" + std::to_string(Player::upgradePoint[2][player->GetSkillLevel(2)]) + " SP]";
		skillButton[2]->RenderButton(renderer, font, "Explosion", text);
	}
	else if (player->GetSkillLevel(2) < Player::skillLevelMax) {
		std::string text = "Upgrade [" + std::to_string(Player::upgradePoint[2][player->GetSkillLevel(2)]) + " SP]";
		skillButton[2]->RenderButton(renderer, font, "[RB]:Explosion", text);
	}
	else {
		skillButton[2]->RenderButton(renderer, font, "[RB]:Explosion", "Max");
	}
	if (player->GetSkillLevel(3) <= 0) {
		std::string text = "Unlock [" + std::to_string(Player::upgradePoint[3][player->GetSkillLevel(3)]) + " SP]";
		skillButton[3]->RenderButton(renderer, font, "Lightning", text);
	}
	else if (player->GetSkillLevel(3) < Player::skillLevelMax) {
		std::string text = "Upgrade [" + std::to_string(Player::upgradePoint[3][player->GetSkillLevel(3)]) + " SP]";
		skillButton[3]->RenderButton(renderer, font, "[Q]:Lightning", text);
	}
	else {
		skillButton[3]->RenderButton(renderer, font, "[Q]:Lightning", "Max");
	}

	//�㉺�{�^��
	upButton->SetColor(255, 255, 255, 255);
	upButton->RenderButton(renderer, font, "+");
	downButton->SetColor(255, 255, 255, 255);
	downButton->RenderButton(renderer, font, "-");
	//�|�[�Y�{�^��
	pauseButton->SetColor(255, 255, 255, 255);
	pauseButton->RenderButton(renderer, font, u8"�~");


	//�`��
	SDL_RenderPresent(renderer);
}

void Game::Pause(){

	bool paused = true;
	RectButton* continueButton = new RectButton(
		(Game::WindowWidth - RectButton::buttonWidth) / 2,
		(Game::WindowHeight - RectButton::buttonHeight * 2) / 3
	);
	RectButton* quitButton = new RectButton(
		(Game::WindowWidth - RectButton::buttonWidth) / 2,
		Game::WindowHeight - ((Game::WindowHeight - RectButton::buttonHeight * 2) / 3) - RectButton::buttonHeight
	);
	continueButton->SetIsAvailable(true);
	quitButton->SetIsAvailable(true);
	while (paused) {
		//input
		SDL_Event event;
		isLMouseUp = false;
		isRMouseUp = false;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					isClicked = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					isClicked = false;
					isLMouseUp = true;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) {
					isRMouseUp = true;
				}
				break;
			}
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (isEscDown && !state[SDL_SCANCODE_ESCAPE]) {
			isEscDown = false;
		}
		if (!isEscDown && state[SDL_SCANCODE_ESCAPE]) {
			isEscDown = true;
			paused = false;
		}
		continueButton->ProcessInput(isClicked);
		quitButton->ProcessInput(isClicked);

		//update
		if (continueButton->IsPressed()) {
			Mix_PlayChannel(-1, sounds[0], 0);
			isPlaying = true;
			paused = false;
		}
		if (quitButton->IsPressed()) {
			paused = false;
			isRunning = false;
		}

		//output
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		continueButton->RenderButton(renderer, font, "continue");
		quitButton->RenderButton(renderer, font, "quit");

		SDL_RenderPresent(renderer);
	}
}

void Game::FinishScreen(){
	bool close = false;
	RectButton* continueButton = new RectButton(1100,650);
	RectButton* quitButton = new RectButton(1100,650+RectButton::buttonHeight+50);
	continueButton->SetIsAvailable(true);
	quitButton->SetIsAvailable(true);
	while (!close) {
		//input
		SDL_Event event;
		isLMouseUp = false;
		isRMouseUp = false;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					isClicked = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					isClicked = false;
					isLMouseUp = true;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) {
					isRMouseUp = true;
				}
				break;
			}
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (isEscDown && !state[SDL_SCANCODE_ESCAPE]) {
			isEscDown = false;
		}
		if (!isEscDown && state[SDL_SCANCODE_ESCAPE]) {
			isEscDown = true;
		}
		continueButton->ProcessInput(isClicked);
		quitButton->ProcessInput(isClicked);

		//update
		if (continueButton->IsPressed()) {
			Mix_PlayChannel(-1, sounds[0], 0);
			isPlaying = true;
			close = true;
		}
		if (quitButton->IsPressed()) {
			close = true;
			isRunning = false;
		}

		//output
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		continueButton->RenderButton(renderer, font, "continue");
		quitButton->RenderButton(renderer, font, "quit");

		font->RenderText(renderer, "Clear", 256, 100, 100);
		std::string text = "Time:" + std::_Floating_to_string("%.2f", cleartime);
		font->RenderText(renderer, text, 128, 100, 100 + 256 + 100);

		SDL_RenderPresent(renderer);
	}
}

int Game::HitEnemyIndex() {
	for (int i = 0; i < numEnemy; i++) {
		if (player->IsHit(enemies[i])) {
			return i;
		}
	}
	return -1;
}
