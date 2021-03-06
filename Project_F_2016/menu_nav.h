#ifndef __MENU_NAV_H__
#define __MENU_NAV_H__

#include "lcd.h"
#include "ddr_images.h"
#include "ddr_animations.h"
#include "ft6x06.h"
#include "ps2.h"

#define x_left_threshold  (0xFFF / 4) * 3
#define y_up_threshold  	(0xFFF / 4) * 3
#define x_right_threshold (0xFFF / 4)
#define y_down_threshold  (0xFFF / 4)

// offset macro
#define offset 1

// x is zero for drawing boxes
#define draw_line_x 0 

// macros for main menu
#define menu_play_now_x 2
#define menu_play_now_y 2
#define menu_high_scores_x 1
#define menu_high_scores_y 4

//hit, miss, boo screen macros
#define hit_screen_x 10
#define hit_screen_y 10

#define miss_screen_x 10
#define miss_screen_y 10

#define boo_screen_x 10
#define boo_screen_y 10

//printing pause screen 
#define pause_screen_continue_x 3
#define pause_screen_continue_y 5

#define pause_screen_menu_x 5
#define pause_screen_menu_y 10

//printing end screen 
#define end_screen_play_x 2
#define end_screen_play_y 5

#define end_screen_high_x 2
#define end_screen_high_y 10 

//macros for high scores screen
#define high_screen_x 0
#define high_screen_y 4

#define score_screen_x 0
#define score_screen_y 5

#define longest_screen_x 0
#define longest_screen_y 7

#define time_screen_x 0
#define time_screen_y 8

#define game_screen_x 0
#define game_screen_y 10

#define mode_screen_x 0
#define mode_screen_y 11

#define back_screen_x 5
#define back_screen_y 18

#define MNAV_STR_BACK_X					3
#define MNAV_STR_BACK_Y					14
#define MNAV_STR_BACK_COLOR			LCD_COLOR_RED
#define MNAV_BACK_RGN_X					MNAV_STR_BACK_X
#define MNAV_BACK_RGN_LOW_Y			MNAV_STR_BACK_Y - 1
#define MNAV_BACK_RGN_HIGH_Y		MNAV_STR_BACK_Y + 1

#define MNAV_RESET_TOUCH_LOW_Y  63
#define MNAV_RESET_TOUCH_HIGH_Y 99
#define MNAV_RESET_TOUCH_LOW_X  38
#define MNAV_RESET_TOUCH_HIGH_X 180


// MACROS for win screen 
#define your_score_x  0
#define your_score_y 13

#define high_score_x  0
#define high_score_y 14 

#define new_score_x  0
#define new_score_y 15

#define h_score_x 0
#define h_score_y 16

// MACROS for Select Difficulty Screen images (arrows)
#define arrow_easy_x 180
#define arrow_easy_y 200

#define arrow_medium_x 180
#define arrow_medium_y 164

#define arrow_difficult_x 		180
#define arrow_difficult_y 		135


typedef enum {
	NOTHING,
	PLAY_NOW,
	HIGH_SCORES
} SELECTED_ITEM;

typedef enum {
	DIFFICULTY_SELECT_NONE,
	DIFFICULTY_SELECT_EASY,
	DIFFICULTY_SELECT_MEDIUM,
	DIFFICULTY_SELECT_HARD
} diff_select_t;

typedef enum {
	MENU, MODE_SELECTION, PLAY, WIN, LOSE, HIGH_SCORE
} game_state_fsm;


void display_selected_menu_item();
void navigate_main_menu(uint16_t y_adc_data);
void update_ui_init_new_state(game_state_fsm new_state);

void update_ui_init_mode_selecion(void);
void choose_mode_from_selected_item(void);
void navigate_game_mode(uint16_t y_adc_data);
void display_selected_difficulty_item(void);

void update_ui_init_main_menu(void);
void update_ui_high_scores(void);
void draw_line(uint8_t y);
void clear_line(uint8_t y);

void print_pause_screen(void);
void print_high_scores(void);

void print_high_scores(void);
void lose_screen(void);
void win_screen (void);

void print_reset_button(void);

void	clear_select_arrow_area(void);
void	print_select_arrow(diff_select_t difficulty_selected);
#endif
