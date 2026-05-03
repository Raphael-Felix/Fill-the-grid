#pragma once
#include "Scene.h"

class Entity;
class Grid;
class MenuButton;
class EndGameButton;
class ShowLevelSelectionButton;
class Button;
class Tetromino;
class SoundManager;

enum GameState {Pause = 0, Game = 1, Scores = 2, LevelSelection = 3};

class MainScene :
    public Scene
{
private:
    SoundManager* m_soundManager;

    GameState m_lastGameState;
    GameState m_gameState;
    
    MenuButton* m_button;

    EndGameButton* m_endGameButton;

    ShowLevelSelectionButton* m_levelSelectionButton;

    std::vector<Button*> m_pauseButtons;

    std::vector<Button*> m_levelSelectionButtons;

    std::vector<Entity*> m_scoreStars;

    Grid* m_grid;

    bool m_tetrominoRotation = true;
    std::vector<Tetromino*> m_tetrominos;

    Tetromino* m_draggedTetromino;
    int m_draggedTetrominoRotationCount = 0;

    std::vector<int> m_bestScores;

    int m_levelSquareSize = 64;
    int m_levelsCount = 3;
    int m_currentLevelIndex = 1;

    float m_score = 0;
    float m_mult = 1;

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void OnEventGame(const sf::Event& event);
    void OnUpdateGame();

    void OnEventPause(const sf::Event& event);
    void OnUpdatePause();

    void OnEventLevelSelection(const sf::Event& event);
    void OnUpdateLevelSelection();

    void ShowMenu();
    void ShowLeftLevel();
    void ShowRightLevel();

    void ReturnToLevelSelection();

    void OnEventScores(const sf::Event& event);
    void OnUpdateScores();

    void UpdatesGameStateChange();

    void EndGame();

    void PlayRandomClick();
    void PlayRandomSwipe();

    void SetPauseButtonsActive(bool active);
    void SetLevelSelectionButtonsActive(bool active);

    void LoadLevel();

    void DestroyTetrominos();
};
