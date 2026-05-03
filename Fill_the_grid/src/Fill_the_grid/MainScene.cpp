#include "MainScene.h"

#include "MenuButton.h"
#include "EndGameButton.h"
#include "ShowLevelSelectionButton.h"
#include "ExitButton.h"
#include "MusicsVolumeDownButton.h"
#include "MusicsVolumeUpButton.h"
#include "SoundsVolumeDownButton.h"
#include "SoundsVolumeUpButton.h"
#include "PlayButton.h"
#include "LeftLevelButton.h"
#include "RightLevelButton.h"

#include "Grid.h"
#include "Tetromino.h"
#include "Debug.h"
#include "SoundManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

void MainScene::OnInitialize()
{
	srand(time(NULL));

	m_draggedTetromino = nullptr;

	// Boutons du menu des paramètres
	{
		m_button = CreateRectangle<MenuButton>(100, 50, sf::Color::Transparent, nullptr);
		m_button->Initialize("Menu", 20, 1, sf::Color::White);
		m_button->SetPosition(10, 10, 0.f, 0.f);

		Button* tempButton = CreateRectangle<SoundsVolumeDownButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("-", 20, 1, sf::Color::White);
		tempButton->SetPosition(400, 100, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);

		tempButton = CreateRectangle<SoundsVolumeUpButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("+", 20, 1, sf::Color::White);
		tempButton->SetPosition(830, 100, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);

		tempButton = CreateRectangle<MusicsVolumeDownButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("-", 20, 1, sf::Color::White);
		tempButton->SetPosition(400, 300, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);

		tempButton = CreateRectangle<MusicsVolumeUpButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("+", 20, 1, sf::Color::White);
		tempButton->SetPosition(830, 300, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);

		tempButton = CreateRectangle<ExitButton>(120, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Quitter", 20, 1, sf::Color::White);
		tempButton->SetPosition(580, 500, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);

		tempButton = CreateRectangle<ShowLevelSelectionButton>(250, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Retour au menu", 20, 1, sf::Color::White);
		tempButton->SetPosition(515, 600, 0.f, 0.f);
		tempButton->SetActive(false);
		m_pauseButtons.push_back(tempButton);
	}

	// Boutons du menu des score
	{
		m_levelSelectionButton = CreateRectangle<ShowLevelSelectionButton>(250, 50, sf::Color::Transparent, nullptr);
		m_levelSelectionButton->Initialize("Retour au menu", 20, 1, sf::Color::White);
		m_levelSelectionButton->SetPosition(515, 500, 0.f, 0.f);
		m_levelSelectionButton->SetActive(false);
	}

	//Boutons en jeu
	{
		m_endGameButton = CreateRectangle<EndGameButton>(150, 50, sf::Color::Transparent, nullptr);
		m_endGameButton->Initialize("Terminer", 20, 1, sf::Color::White);
		m_endGameButton->SetPosition(1120, 660, 0.f, 0.f);
		m_endGameButton->SetActive(false);
	}

	// Bouttons de la séléction de niveaux
	{
		Button* tempButton = CreateRectangle<PlayButton>(100, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Jouer", 20, 1, sf::Color::White);
		tempButton->SetPosition(GetWindowWidth() / 2, GetWindowHeight() - 200);
		tempButton->SetActive(true);
		m_levelSelectionButtons.push_back(tempButton);

		tempButton = CreateRectangle<LeftLevelButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize(" < ", 20, 1, sf::Color::White);
		tempButton->SetPosition(50, GetWindowHeight() / 2);
		tempButton->SetActive(false);
		m_levelSelectionButtons.push_back(tempButton);

		tempButton = CreateRectangle<RightLevelButton>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize(" > ", 20, 1, sf::Color::White);
		tempButton->SetPosition(GetWindowWidth() - 50, GetWindowHeight() / 2);
		tempButton->SetActive(true);
		m_levelSelectionButtons.push_back(tempButton);
	}

	// Etoiles du menu de scores
	{
		Entity* tempStar;

		for (int i = 0; i < 3; i++)
		{
			tempStar = CreateSprite<Entity>(120, 50, "res/assets/icon_star.png", nullptr);
			tempStar->SetPosition(480 + 100 * i, 300, 0.f, 0.f);
			tempStar->SetActive(false);
			m_scoreStars.push_back(tempStar);
		}
	}

	// Etat du jeu
	{
		m_gameState = LevelSelection;
	}

	//Scores
	{
		for (int i = 0; i < m_levelsCount; ++i)
			m_bestScores.push_back(0);
	}

	// Chargement des sons et des musiques
	{
		m_soundManager = SoundManager::GetInstance();
		m_soundManager->SetGlobalVolume(500);
		m_soundManager->SetMusicVolume(5);
		m_soundManager->LoadSound("res/sounds/click1.wav");
		m_soundManager->LoadSound("res/sounds/swipe1.wav");
		m_soundManager->LoadSound("res/sounds/swipe2.wav");
	}

	// Musique
	{
		m_soundManager->PlayMusic("res/musics/house.ogg", true);
	}
}

void MainScene::OnEvent(const sf::Event& event)
{
	switch (m_gameState)
	{
	case Pause:
		OnEventPause(event);
		break;
	case Game:
		OnEventGame(event);
		break;
	case Scores:
		OnEventScores(event);
		break;
	case LevelSelection:
		OnEventLevelSelection(event);
		break;
	default:
		break;
	}
}

void MainScene::OnUpdate()
{
	switch (m_gameState)
	{
	case Pause:
		OnUpdatePause();
		break;
	case Game:
		OnUpdateGame();
		break;
	case Scores:
		OnUpdateScores();
		break;
	case LevelSelection:
		OnUpdateLevelSelection();
		break;
	default:
		break;
	}
}

void MainScene::OnEventGame(const sf::Event& event)
{
	// Rotation des pieces
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Q && m_draggedTetromino != nullptr && m_tetrominoRotation)
		{
			PlayRandomSwipe();
			m_draggedTetromino->RotateClockwise();
			m_draggedTetrominoRotationCount += 1;
		}
		else if (event.key.code == sf::Keyboard::D && m_draggedTetromino != nullptr && m_tetrominoRotation)
		{
			PlayRandomSwipe();
			m_draggedTetromino->RotateCounterClockwise();
			m_draggedTetrominoRotationCount -= 1;
		}
	}

	// Drag and drop
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));

			if (m_draggedTetromino == nullptr)
			{
				for (Tetromino* tempTetromino : m_tetrominos)
				{
					if (tempTetromino->IsMouseInside(mousePosition))
					{
						PlayRandomClick();
						m_draggedTetromino = tempTetromino;
						
						if (m_grid->Unfill(tempTetromino))
						{
							m_score -= m_draggedTetromino->GetSquareNb() * 86;
							m_mult = 1;
						}
					}
						
				}
			}
			else
			{
				if (m_grid->Fill(m_draggedTetromino))
				{
					m_score += m_draggedTetromino->GetSquareNb() * 86 * m_mult;
					m_mult += 0.15;

					//Get the staticPosition of the draggedTetromino and change it
					sf::Vector2f draggedTetrominoPos = m_draggedTetromino->GetStaticPosition();

					m_draggedTetromino->SetStaticPosition(m_draggedTetromino->GetBaseSquare()->entity->GetPosition());

					m_draggedTetrominoRotationCount = 0;

					if (m_draggedTetromino->HasBeenReplaced() == false)
					{
						PlayRandomClick();
						m_draggedTetromino->Replace();

						//Create new tetromino
						Tetromino* tetromino = new Tetromino(this);

						tetromino->SetPosition({ draggedTetrominoPos.x, draggedTetrominoPos.y });
						tetromino->SetStaticPosition({ draggedTetrominoPos.x, draggedTetrominoPos.y });
						tetromino->GenerateRandomShape();
						tetromino->SetSquareSize(m_levelSquareSize);

						m_tetrominos.push_back(tetromino);
					}

					m_draggedTetromino = nullptr;
				}
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right && m_draggedTetromino != nullptr)
		{
			PlayRandomClick();

			for (int i = 0; i < std::abs(m_draggedTetrominoRotationCount); ++i)
			{
				if (m_draggedTetrominoRotationCount < 0)
					m_draggedTetromino->RotateClockwise();
				else
					m_draggedTetromino->RotateCounterClockwise();
			}

			m_draggedTetrominoRotationCount = 0;

			m_draggedTetromino->CancelDrag();

			if (m_grid->Fill(m_draggedTetromino))
			{
				m_score += m_draggedTetromino->GetSquareNb() * 86 * m_mult;
				m_mult += 0.15;
			}

			m_draggedTetromino = nullptr;
		}
	}
}

void MainScene::OnUpdateGame()
{
	Debug::DrawText(GetWindowWidth() / 2, 10, "Score : " + std::to_string((int)m_score), sf::Color::White);

	Debug::DrawText(GetWindowWidth() - 280, 10, "Multiplicateur : x" + std::to_string(m_mult), sf::Color::White);
	
	// Le tetromino selectionne suis la souris
	if (m_draggedTetromino != nullptr)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));
		m_draggedTetromino->SetPosition({ (float)mousePosition.x , (float)mousePosition.y });
	}
}

void MainScene::OnEventPause(const sf::Event& event)
{

}

void MainScene::OnUpdatePause()
{
	// Affichage texte pour parametres
	if (m_soundManager != nullptr)
	{
		Debug* debug = Debug::Get();

		debug->DrawText(500, 110, "Volume des bruitages : " + std::to_string(m_soundManager->GetSoundVolume()), sf::Color::White);
		debug->DrawText(500, 310, "Volume de la musique : " + std::to_string(m_soundManager->GetMusicVolume()), sf::Color::White);
	}
}

void MainScene::OnEventLevelSelection(const sf::Event& event)
{

}

void MainScene::OnUpdateLevelSelection()
{
	Debug::DrawText(GetWindowWidth() / 2 - 100, 150, "Meilleur score : " + std::to_string(m_bestScores[m_currentLevelIndex - 1]), sf::Color::White);

	Debug::DrawText(GetWindowWidth() / 2 - 40, GetWindowHeight() / 2, "Niveau " + std::to_string(m_currentLevelIndex), sf::Color::White);
}

void MainScene::OnEventScores(const sf::Event& event)
{

}

void MainScene::OnUpdateScores()
{
	Debug::Get()->DrawText(500, 200, "Score de la partie : ", sf::Color::White);
	Debug::Get()->DrawText(600, 250, std::to_string((int)m_score), sf::Color::White);
}

void MainScene::UpdatesGameStateChange()
{
	// Grille et bouton de fin de partie
	if (m_grid != nullptr)
		m_grid->SetActive(m_gameState == Game);

	if (m_endGameButton != nullptr)
		m_endGameButton->SetActive(m_gameState == Game);

	// Pieces
	for (Tetromino* tetromino : m_tetrominos)
	{
		tetromino->SetActive(m_gameState == Game);
	}
	if (m_draggedTetromino != nullptr)
	{
		m_draggedTetromino->CancelDrag();
		m_draggedTetromino = nullptr;
	}

	SetLevelSelectionButtonsActive(m_gameState == LevelSelection);

	// Menu de scores
	if (m_levelSelectionButton != nullptr)
		m_levelSelectionButton->SetActive(m_gameState == Scores);
	for (Entity* star : m_scoreStars)
		star->SetActive(false);

	// Boutons du menu pause
	SetPauseButtonsActive(m_gameState == Pause);
}

void MainScene::ShowLeftLevel()
{
	PlayRandomClick();

	m_currentLevelIndex = std::max(1, m_currentLevelIndex - 1);

	m_levelSelectionButtons[2]->SetActive(true);

	if (m_currentLevelIndex == 1)
	{
		m_levelSelectionButtons[1]->SetActive(false);
	}
}

void MainScene::ShowRightLevel()
{
	PlayRandomClick();

	m_currentLevelIndex = std::min(m_levelsCount, m_currentLevelIndex + 1);

	m_levelSelectionButtons[1]->SetActive(true);

	if (m_currentLevelIndex == m_levelsCount)
	{
		m_levelSelectionButtons[2]->SetActive(false);
	}
}

void MainScene::ReturnToLevelSelection()
{
	m_gameState = LevelSelection;

	UpdatesGameStateChange();
}

void MainScene::ShowMenu()
{
	PlayRandomClick();

	if (m_gameState == Game)
	{
		m_gameState = Pause;
		m_lastGameState = Game;
	}
	else if (m_gameState == LevelSelection)
	{
		m_gameState = Pause;
		m_lastGameState = LevelSelection;
	}
	else if (m_gameState == Scores)
	{
		m_gameState = Pause;
		m_lastGameState = Scores;
	}
	else
	{
		m_gameState = m_lastGameState;
	}

	UpdatesGameStateChange();
}

void MainScene::EndGame()
{
	PlayRandomClick();

	m_gameState = Scores;

	UpdatesGameStateChange();

	if (m_score >= 1196 + m_currentLevelIndex * 6500)
		m_scoreStars[0]->SetActive(true);
	if(m_score >= 1994 + m_currentLevelIndex * 8500)
		m_scoreStars[1]->SetActive(true);
	if(m_score >= 823 + m_currentLevelIndex * 10150)
		m_scoreStars[2]->SetActive(true);

	m_bestScores[m_currentLevelIndex - 1] = std::max(m_bestScores[m_currentLevelIndex - 1], (int)m_score);

	DestroyTetrominos();
}

void MainScene::PlayRandomClick()
{
	if (m_soundManager == nullptr)
		return;


	int soundNumber = rand() % 1 + 1;

	m_soundManager->PlaySound("../../../res/sounds/click" + std::to_string(soundNumber) + ".wav");
}

void MainScene::PlayRandomSwipe()
{
	if (m_soundManager == nullptr)
		return;

	int soundNumber = rand() % 2 + 1;

	m_soundManager->PlaySound("../../../res/sounds/swipe" + std::to_string(soundNumber) + ".wav");
}

void MainScene::SetPauseButtonsActive(bool active)
{
	for (Button* currentButton : m_pauseButtons)
	{
		currentButton->SetActive(active);
	}
}

void MainScene::SetLevelSelectionButtonsActive(bool active)
{
	for (Button* currentButton : m_levelSelectionButtons)
	{
		currentButton->SetActive(active);
	}
}

void MainScene::LoadLevel()
{
	m_score = 0;
	m_mult = 1.f;

	if (m_grid != nullptr)
		delete m_grid;

	switch (m_currentLevelIndex)
	{
	case 1:
		m_levelSquareSize = 64;
		m_grid = new Grid(8, 8, this, m_levelSquareSize);
		break;
	case 2:
		m_levelSquareSize = 60;
		m_grid = new Grid(10, 10, this, m_levelSquareSize);
		break;
	case 3:
		m_levelSquareSize = 54;
		m_grid = new Grid(12, 12, this, m_levelSquareSize);
		break;
	default:
		break;
	}

	m_grid->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2, 0.5f, 0.5f);

	// Creation de 2 tetrominos
	Tetromino* test = new Tetromino(this);
	test->SetPosition({ 200, 200 });
	test->SetStaticPosition({ 200, 200 });
	test->GenerateRandomShape();

	m_tetrominos.push_back(test);

	Tetromino* test1 = new Tetromino(this);
	test1->SetPosition({ 200, 400 });
	test1->SetStaticPosition({ 200, 400 });
	test1->GenerateRandomShape();

	m_tetrominos.push_back(test1);

	Tetromino* test2 = new Tetromino(this);

	test->SetSquareSize(m_levelSquareSize);
	test1->SetSquareSize(m_levelSquareSize);
	test2->SetSquareSize(m_levelSquareSize);

	switch (m_currentLevelIndex)
	{
	case 1:
		test2->SetPosition({ 200, 600 });
		test2->SetStaticPosition({ 200, 600 });
		test2->GenerateRandomShape();
		m_tetrominos.push_back(test2);
		break;
	case 2:
		delete test2;
		break;
	case 3:
		delete test2;
		m_tetrominoRotation = false;
		break;
	default:
		break;
	}

	m_gameState = Game;

	UpdatesGameStateChange();
}

void MainScene::DestroyTetrominos()
{
	for (Tetromino* currentTetromino : m_tetrominos)
	{
		currentTetromino->~Tetromino();
	}
}