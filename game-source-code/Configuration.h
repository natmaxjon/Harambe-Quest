#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <cmath>

/*---- Game Properties ----*/

const auto GAME_WIDTH = 828.0f; //782.0f;
const auto GAME_HEIGHT = 900.0f;
const auto GAME_TITLE = "HARAMBE'S QUEST";
const auto WINDOW_STYLE = (sf::Style::Resize + sf::Style::Close); // sf::Style::Titlebar | sf::Style::Close; // sf::Style::Default;
const auto FRAME_RATE = 60.0f;
const auto MS_PER_FRAME = 1000.0f/FRAME_RATE;

/*---- Maze Properties ----*/

const auto TILE_LENGTH = 34.f;  // pixels

/*---- Direction Vectors ----*/

const auto LEFT = sf::Vector2f{-1,0};
const auto RIGHT = sf::Vector2f{1,0};
const auto UP = sf::Vector2f{0,-1};
const auto DOWN = sf::Vector2f{0,1};

/*----- Character Speeds -----*/

const auto MIN_CHANGE = 1;
const auto NORMAL_CHARACTER_SPEED = 0.225;
const auto POWER_MODE_SPEED = 1.1*NORMAL_CHARACTER_SPEED;
const auto SUPER_MODE_SPEED = 1.1*NORMAL_CHARACTER_SPEED;
const auto PLAYER_SPEED_INCREASE = 1.05;

const auto NORMAL_ENEMY_SPEED = 0.8*NORMAL_CHARACTER_SPEED;
const auto CHASE_MODE_SPEED = 1*NORMAL_ENEMY_SPEED;
const auto SCATTER_MODE_SPEED = NORMAL_ENEMY_SPEED;
const auto FRIGHTENED_MODE_SPEED = 0.6*NORMAL_ENEMY_SPEED;
const auto ENEMY_SPEED_INCREASE = 1.075;

const auto MAX_SPEED = 0.5;



/*----- SCORES -----*/
const auto FRUIT_SCORE = 50;
const auto PELLET_SCORE = 100;
const auto GHOST_SCORE = 200;


/*----- Character States -----*/
const auto POWER_MODE_TIME = 5000.0; // milliseconds
const auto SUPER_MODE_TIME = 5000.0;
const auto EATING_TIME = 500.0;
const auto DEATH_TIME = 1000.0;
const auto NUMBER_OF_LIVES = 3;

const auto CHASE_MODE_TIMES = std::vector<float>{10000};
const auto SCATTER_MODE_TIMES = std::vector<float>{5000};
const auto SCATTER_MODE_TIME = SCATTER_MODE_TIMES[0];
const auto FRIGHTENED_MODE_TIME = 7000;
const auto ENEMY_DEATH_TIME = 100;
const auto ENEMY_PEN_TIME = 5000;

/*-------- States --------*/

// Splash State
const auto SPLASH_DISPLAY_TIME = 5.0;   // Seconds
const auto INTER_DISPLAY_TIME = 3.0;

const auto PROGRESS_BAR_WIDTH = GAME_WIDTH/2;
const auto PROGRESS_BAR_HEIGHT = PROGRESS_BAR_WIDTH/20;
const auto PROGRESS_BAR_POSITION = sf::Vector2f{GAME_WIDTH/2 - PROGRESS_BAR_WIDTH/2,
                                                5*GAME_HEIGHT/6 - PROGRESS_BAR_HEIGHT/2};
const auto PROGRESS_BAR_COLOUR = sf::Color::Red;

const auto PROGRESS_BAR_OUTLINE_WIDTH = PROGRESS_BAR_WIDTH + 10;
const auto PROGRESS_BAR_OUTLINE_HEIGHT = PROGRESS_BAR_HEIGHT + 10;
const auto PROGRESS_BAR_OUTLINE_POSITION = sf::Vector2f{PROGRESS_BAR_POSITION.x + PROGRESS_BAR_WIDTH/2,
                                                        PROGRESS_BAR_POSITION.y + PROGRESS_BAR_HEIGHT/2};
const auto PROGRESS_BAR_OUTLINE_THICKNESS = 3;

const auto PERCENTAGE_POSITION = PROGRESS_BAR_OUTLINE_POSITION + sf::Vector2f{0, 50};

// Endless Level State
const auto NUM_ROWS = 25;
const auto NUM_COLS = 23;

// Level Editor State
//const auto GRID_POSITION = sf::Vector2f{45,45};
//const auto GRID_SPACING = 30.f;
//const auto GRID_SIZE = sf::Vector2f{NUM_COLS * GRID_SPACING, NUM_ROWS * GRID_SPACING};
const auto LINK_LINE_THICKNESS = 3.f;
const auto PI = 2*acos(0.0);

/*-------File Paths ------*/

// Graphics
const auto SPLASH_BACKGROUND_FILEPATH = "resources/graphics/splash-screen.png";
const auto MENU_BACKGROUND_FILEPATH = "resources/graphics/bg1.png";
const auto AUX_BACKGROUND_FILEPATH = "resources/graphics/bg4.png";

const auto GRASS_FILEPATH = "resources/graphics/grass.png";

const auto MENU_BUTTON_FILEPATH = "resources/graphics/menu-button.png";
const auto EXIT_BUTTON_FILEPATH = "resources/graphics/exit-button.png";
const auto ERASE_BUTTON_FILEPATH = "resources/graphics/erase-button.png";
const auto LEFT_TRIANGLE_FILEPATH = "resources/graphics/left-triangle.png";
const auto RIGHT_TRIANGLE_FILEPATH = "resources/graphics/right-triangle.png";

const auto PLAYER_DEFAULT_FILEPATH = "resources/graphics/pacman.png";
const auto PLAYER_SUPER_FILEPATH = "resources/graphics/pacman_super.png";
const auto ENEMY_DEFAULT_FILEPATH = "resources/graphics/ghost.png";

/*---------------- Harambe Sprites --------------------------*/
const auto HARAMBE_RIGHT = "resources/graphics/harambe-right.png";
const auto HARAMBE_LEFT = "resources/graphics/harambe-left.png";
const auto HARAMBE_UP = "resources/graphics/harambe-up.png";
const auto HARAMBE_DOWN = "resources/graphics/harambe-down.png";

const auto SUPER_HARAMBE_RIGHT = "resources/graphics/super-harambe-right.png";
const auto SUPER_HARAMBE_LEFT = "resources/graphics/super-harambe-left.png";
const auto SUPER_HARAMBE_UP = "resources/graphics/super-harambe-up.png";
const auto SUPER_HARAMBE_DOWN = "resources/graphics/super-harambe-down.png";

const auto KILL_HARAMBE_RIGHT = "resources/graphics/kill-harambe-right.png";
const auto KILL_HARAMBE_LEFT = "resources/graphics/kill-harambe-left.png";
const auto KILL_HARAMBE_UP = "resources/graphics/kill-harambe-up.png";
const auto KILL_HARAMBE_DOWN = "resources/graphics/kill-harambe-down.png";

const auto KILL_SUPER_HARAMBE_RIGHT = "resources/graphics/kill-super-harambe-right.png";
const auto KILL_SUPER_HARAMBE_LEFT = "resources/graphics/kill-super-harambe-left.png";
const auto KILL_SUPER_HARAMBE_UP = "resources/graphics/kill-super-harambe-up.png";
const auto KILL_SUPER_HARAMBE_DOWN = "resources/graphics/kill-super-harambe-down.png";

const auto HIT_HARAMBE_RIGHT = "resources/graphics/hit-harambe-right.png";
const auto HIT_HARAMBE_LEFT = "resources/graphics/hit-harambe-left.png";
const auto HIT_HARAMBE_UP = "resources/graphics/hit-harambe-up.png";
const auto HIT_HARAMBE_DOWN = "resources/graphics/hit-harambe-down.png";

const auto HIT_SUPER_HARAMBE_RIGHT = "resources/graphics/hit-super-harambe-right.png";
const auto HIT_SUPER_HARAMBE_LEFT = "resources/graphics/hit-super-harambe-left.png";
const auto HIT_SUPER_HARAMBE_UP = "resources/graphics/hit-super-harambe-up.png";
const auto HIT_SUPER_HARAMBE_DOWN = "resources/graphics/hit-super-harambe-down.png";

const auto HARAMBE_DEAD = "resources/graphics/harambe-dead.png";
const auto HARAMBE_HEAD = "resources/graphics/harambe-head.png";

/*------------------- Police Sprites --------------------------*/

const auto RED_POLICE = "resources/graphics/red_police.png";
const auto GREEN_POLICE = "resources/graphics/green_police.png";
const auto PURPLE_POLICE = "resources/graphics/purple_police.png";
const auto BROWN_POLICE = "resources/graphics/brown_police.png";
const auto BLUE_POLICE = "resources/graphics/blue_police.png";

const auto POLICE_DEAD = "resources/graphics/police_dead.png";

const auto RED_HEAD = "resources/graphics/red-head.png";
const auto GREEN_HEAD = "resources/graphics/green-head.png";
const auto PURPLE_HEAD = "resources/graphics/purple-head.png";
const auto BROWN_HEAD = "resources/graphics/brown-head.png";

/*-------------------------------------------------------------*/

/*------------------- Coffin Sprites --------------------------*/

const auto COFFIN_1 = "resources/graphics/coffin1.png";
const auto COFFIN_2 = "resources/graphics/coffin2.png";
const auto COFFIN_3 = "resources/graphics/coffin3.png";
const auto COFFIN_4 = "resources/graphics/coffin4.png";
const auto COFFIN_5 = "resources/graphics/coffin5.png";
const auto COFFIN_6 = "resources/graphics/coffin6.png";
const auto COFFIN_7 = "resources/graphics/coffin7.png";
const auto COFFIN_8 = "resources/graphics/coffin8.png";

/*-------------------------------------------------------------*/

/*------------------- Xue + Sakura Sprites --------------------*/

const auto SAKURA_TREE = "resources/graphics/sakura.png";

const auto PETALS_1 = "resources/graphics/petals1.png";
const auto PETALS_2 = "resources/graphics/petals2.png";
const auto PETALS_3 = "resources/graphics/petals3.png";
const auto PETALS_4 = "resources/graphics/petals4.png";
const auto PETALS_5 = "resources/graphics/petals5.png";
const auto PETALS_6 = "resources/graphics/petals6.png";
const auto PETALS_7 = "resources/graphics/petals7.png";
const auto PETALS_8 = "resources/graphics/petals8.png";
const auto PETALS_9 = "resources/graphics/petals9.png";
const auto PETALS_10 = "resources/graphics/petals10.png";
const auto PETALS_11 = "resources/graphics/petals11.png";

const auto PIAO_PIAO = "resources/graphics/piao-piao.png";

/*-------------------------------------------------------------*/

const auto WALL_FILEPATH = "resources/graphics/wall.png";
const auto CORNER_FILEPATH = "resources/graphics/corner.png";
const auto GATE_FILEPATH = "resources/graphics/gate.png";
const auto BROKEN_GATE_FILEPATH = "resources/graphics/broken-gate.png";
const auto BANANA_FILEPATH = "resources/graphics/banana.png";
const auto POWER_PELLET_FILEPATH = "resources/graphics/power-pellet.png";
const auto SUPER_PELLET_FILEPATH = "resources/graphics/super-pellet.png";
const auto KEY_FILEPATH = "resources/graphics/key.png";
const auto EMPTY_FILEPATH = "resources/graphics/empty.png";
const auto BLANK_BUTTON_FILEPATH = "resources/graphics/blank-button.png";
const auto QUESTION_MARK_FILEPATH = "resources/graphics/question-mark.png";

// Fonts
const auto FINE_8_BIT_FONT_FILEPATH = "resources/fonts/retro_gaming.ttf";
const auto COARSE_8_BIT_FONT_FILEPATH = "resources/fonts/8-bit-pusab.ttf";
const auto PRESS_START_8_BIT_FONT_FILEPATH = "resources/fonts/pressStart.ttf";
const auto ANCIENT_8_BIT_FONT_FILEPATH = "resources/fonts/ancient-modern.ttf";

// Audio
const auto BUTTON_SFX1_FILEPATH = "resources/audio/button1.wav";
const auto SELECT_BUTTON_SFX1_FILEPATH = "resources/audio/select-button.wav";
const auto KEY_SFX_FILEPATH = "resources/audio/key.wav";
const auto GATE_LINK_SFX_FILEPATH = "resources/audio/gate-link.wav";
const auto GATE_BREAK_SFX_FILEPATH = "resources/audio/gate-break.wav";
const auto PLAYER_DIE_SFX_FILEPATH = "resources/audio/harambe-death.wav";
const auto SUPER_PELLET_SFX_FILEPATH = "resources/audio/super-pellet.wav";
const auto POWER_PELLET_SFX_FILEPATH = "resources/audio/power-pellet.wav";
const auto ERROR_BUTTON_SFX_FILEPATH = "resources/audio/button-error.wav";
const auto EAT_GHOST_SFX_FILEPATH = "resources/audio/punch.wav";

const auto COFFIN_DANCE_FILEPATH = "resources/audio/coffin-dance.ogg";
const auto UNRAVEL_FILEPATH = "resources/audio/unravel.ogg";
const auto XUE_HUA_PIAO_FILEPATH = "resources/audio/xue-hua-piao.ogg";
const auto GIORNO_FILEPATH = "resources/audio/giorno.ogg";
const auto CARAMELLDANSEN_FILEPATH = "resources/audio/caramelldansen.ogg";
const auto MEGALOVANIA_FILEPATH = "resources/audio/megalovania.ogg";
const auto FULL_METAL_FILEPATH = "resources/audio/full-metal.ogg";
const auto CRAB_RAVE_FILEPATH = "resources/audio/crab-rave.ogg";
const auto DEJA_VU_FILEPATH = "resources/audio/deja-vu.ogg";
const auto RUNNING_IN_90S_FILEPATH = "resources/audio/running-in-90s.ogg";
const auto RICK_ROLL_FILEPATH = "resources/audio/rick-roll.ogg";
const auto LEVAN_POLKA_FILEPATH = "resources/audio/levan-polka.ogg";
const auto DAMAGED_CODA_FILEPATH = "resources/audio/damaged-coda.ogg";
const auto SANDSTORM_FILEPATH = "resources/audio/sandstorm.ogg";

const auto PLAYLIST = std::vector<std::string>{"full metal",
                                    "sandstorm",
                                    "giorno",
                                    "caramelldansen",
                                    "megalovania",
                                    "crab rave",
                                    "deja vu",
                                    "running in 90s",
                                    "levan polka"};

// Mazes
const auto CLASSIC_LAYOUT_FILEPATH = "resources/mazes/classic/layout.txt";
const auto CLASSIC_ROTATION_FILEPATH = "resources/mazes/classic/orientations.txt";
const auto CLASSIC_KEYMAP_FILEPATH = "resources/mazes/classic/key_map_1.txt";
const auto CLASSIC_STARTPOS_FILEPATH = "resources/mazes/classic/start_positions.txt";

const auto MAZE_DIRECTORY = "resources/mazes/";
const auto MAZE_LIST_FILEPATH = "resources/mazes/maze_list.txt";

// High Scores
const auto HIGH_SCORE_FILEPATH = "resources/highscores/highscores.txt";
const auto HIGH_SCORE_DIRECTORY = "resources/highscores/";

const auto CREDITS_FILEPATH = "resources/credits.txt";


#endif
