#include "ddr_animations.h"

extern queue_t *queue;

extern bool Alert_Timer0A;
extern bool Alert_Timer0B;
extern game_state_fsm game_state;
extern uint8_t GAME_MODE;
extern uint16_t score;

uint8_t numArrows = 0;
uint8_t LED_LEVELS = 4; 

static bool is_arrow_green = false;
static arrow_t *last_arrow_hit;

bool isPaused = false; 

//*****************************************************************************
//
// PLAY MODE ANIMATIONS
//
//*****************************************************************************

//*****************************************************************************
// Initializes the UI for PLAY mode
//*****************************************************************************
void update_ui_init_play(void) {
	uint16_t timer_val = get_timer0A_current_value();
 	uint16_t i = 0;
	lcd_clear_screen(LCD_COLOR_BLACK);
	init_play_top_arrows();
	printf("GAME MODE: %d\n", GAME_MODE);

	srand(timer_val); // TODO: This might be bad to call multiple times
	//print pause button at bottom of the screen 
	lcd_draw_image( 10, pauseWidthPixels, 16, pauseHeightPixels, pauseBitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK );
}

//*****************************************************************************
// Updates the entire user interface of the game in PLAY mode
// Increments all of the onscreen arrows by 1	
//*****************************************************************************
void update_ui_play(button_dir_t button_data) {
	// need button to be stateful so it can be handled when timer goes off
	static button_dir_t button_val = BTN_NONE; 
	static uint16_t ticks = 0;
	static uint16_t mode_level_ticks = 0; 
	
	handle_pause_screen();
	
	// handle glitchy '2' that appears in button data before correct value appears
	if(button_data != BTN_NONE && button_data != 2) {
		button_val = button_data;
	}
	
		print_score();
	  handle_game_end();
			
		animate_arrows(button_val);
		add_random_arrow();
		button_val = BTN_NONE; // after processing the button value, reset it to NONE
		mode_level_ticks = 0; 
	 
	
	
		// To handle the green flash on hit 
		ticks++;
		if(ticks > DELAY_FLASH) {ticks = 0;}
		if((ticks == DELAY_FLASH) && (is_arrow_green == true)){
			print_top_arrow(last_arrow_hit->arrow_type);
			is_arrow_green = false;
			ticks = 0;
		}
	
	//clear miss/hit message on LCD
	clear_hit_miss_message();
	//led_blink(FAST);
}


void handle_game_end() {
			uint8_t max_arrows = (GAME_MODE == DIFFICULTY_MODE_EASY) ? 
			MAX_ARROWS_EASY : (GAME_MODE == DIFFICULTY_MODE_MEDIUM) ? MAX_ARROWS_MEDIUM : MAX_ARROWS_HARD;
		
			if((numArrows > max_arrows) || (LED_LEVELS < 1)) {
			if (score > 0) { 
				game_state = WIN; 
			} else {
				game_state = LOSE;
			}
			if (read_high_score() < score) {
				write_high_score(score);
				write_game_mode(GAME_MODE);
			}
		}
}


void animate_arrows(uint8_t button_val) {	
	print_type_t print_type;
	queue_node *curr_node = queue->head;
	
	arrow_t *arrow = curr_node->key;

	// nothing to animate if the queue is empty!
	if(queue->head == NULL_VALUE) return;
	
	// evaluate arrow position and button values together
	print_type = process_arrow(arrow, button_val);
	
	// process print returns new head node, function itself handles outcome of button press
	curr_node = process_print(print_type);
	// change_LED_expander_state(print_type);
	
	// MOVE THE REST OF THE ARROWS UP
	while(curr_node != NULL_VALUE) {
		arrow = curr_node->key;
		arrow->y_pos++;
		print_arrow(arrow);
		curr_node = curr_node->next;
	}
}

/* Handle Pause screen - go back to main menu / continue */
void handle_pause_screen() {
	 uint16_t x,y;
   uint8_t touch_event;
			
	 x = ft6x06_read_x();
	 y = ft6x06_read_y();
	 touch_event = ft6x06_read_td_status();	
	 if((touch_event > 0 && touch_event!=255) && !isPaused 
		 && (y > 0 && y <= 60) && (x > 0 && x <= 35)) {
			isPaused = true; 
			print_pause_screen();
		}
			while(isPaused) {
				y = ft6x06_read_y();
				if( y <= continue_upper_bound && y >= continue_lower_bound) {
					isPaused = false;
					lcd_clear_screen(LCD_COLOR_BLACK);
					update_ui_init_play();
				} else if (y <= menu_upper_bound && y >= menu_lower_bound) {
					game_state = MENU; 
					lcd_clear_screen(LCD_COLOR_BLACK);
					empty_the_queue(queue);
					isPaused = false;
				}
		}
}


void init_play_top_arrows(void) {
	print_top_arrow(ARROW_DIR_UP);
	print_top_arrow(ARROW_DIR_DOWN);
	print_top_arrow(ARROW_DIR_LEFT);
	print_top_arrow(ARROW_DIR_RIGHT);
}



//*****************************************************************************
// ARROW PROCESSING FUNCTIONS
//*****************************************************************************
print_type_t process_arrow(arrow_t *arrow, button_dir_t button_val) {
	uint16_t y_pos_top = arrow->y_pos + ARROW_HEIGHT;
	uint16_t y_pos_trgt_top	= ARROW_POS_TRGT_TOP_Y;
	uint16_t difference;
	
	// we had to use this if-else to decide which order to subtract because they're unsigned
	// also had to use tops of each image in case the arrow went offscreen (MISS)
	difference = (y_pos_trgt_top >= y_pos_top) ? 
	(y_pos_trgt_top - y_pos_top) : (y_pos_top - y_pos_trgt_top );
	
	// correct button, but need to see what region it was in (level of correctness)
	if (correct_button_pressed(arrow, button_val)) {
		return determine_button_outcome(difference, y_pos_top);
	} 
	
	// nothing pressed, but need to check if offscreen or just far away from target region
	else if(button_val == BTN_NONE) {
		return (y_pos_top >= ARROW_POS_END_Y) ? MISS : NONE;
	}
	
	// wrong button and on screen
	else return BOO;
}

bool correct_button_pressed(arrow_t * arrow, uint8_t button_val) {
	switch (arrow->arrow_type) {
		case ARROW_DIR_UP:
			return (button_val == BTN_U) ? true : false;
		case ARROW_DIR_DOWN:
			return (button_val == BTN_D) ? true : false;
		case ARROW_DIR_LEFT:
			return (button_val == BTN_L) ? true : false;
		case ARROW_DIR_RIGHT:
			return (button_val == BTN_R) ? true : false;
	}
}

print_type_t determine_button_outcome(uint16_t difference, uint16_t arrow_y_pos_top) {
	// miss case, goes off screen 
	if(arrow_y_pos_top >= RGN_MISS) {
		printf("MISS: %x\n", difference);
		return MISS;
	} else if (difference <= RGN_GOOD) {
		printf("GOOD: %x\n", difference);
		score += 10;
		return GOOD; 
	} else if (difference > RGN_GOOD) {
		printf("BOO: %x\n", difference);
		return BOO;
		//none region (would never come here)
	} else {
		printf("NONE: %x\n", difference);
		return NONE;
	}
}

// Returns either the first node in the queue or the next node after removing head
queue_node *process_print(print_type_t print_type) {
	arrow_t *arrow;
	
	// if NONE don't dequeue
	switch(print_type) {
		case NONE:
			//print_top_arrow_hit(arrow->arrow_type);
			break;
		case GOOD:
			print_hit_second();
			printf("process_print=good\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow_hit(arrow->arrow_type);
			is_arrow_green = true; 
			last_arrow_hit = arrow;
			break;
		case MISS:
			print_miss_second();
			LED_LEVELS --; 
			//ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_GPIO_BASE , 0xF0);
			printf("process_print=miss\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow(arrow->arrow_type);
			break;
		case BOO:
			print_boo_second();
			printf("process_print=boo\n");
			break;
		default:
			printf("process_print=default\n");
			break;
	}
	return queue->head;
}

//*****************************************************************************
//
//
// HIGH SCORE MODE SET UPS
//
//
//*****************************************************************************
void update_ui_init_high_score() {
    uint16_t x,y;
    uint8_t touch_event;

    lcd_clear_screen(LCD_COLOR_BLACK);
    print_high_scores();
}

//*****************************************************************************
//
//
// WIN MODE SET UPS
//
//
//*****************************************************************************

void update_ui_init_win() {
    uint16_t x,y;
    uint8_t touch_event;

    print_win();
    print_end_screen();
    touch_event = ft6x06_read_td_status();
    if(touch_event <= play_again_upper_bound && touch_event >= play_again_lower_bound) {
        // NEEDS TO START PLAY AGAIN
        game_state = PLAY;
    }
    else if(touch_event <= high_scores_upper_bound && touch_event >= high_scores_lower_bound) {
        // NEEDS TO DISPLAY THE HIGH SCORES PAGE
        game_state = HIGH_SCORE;
    }
}


//*****************************************************************************
//
//
// LOSE MODE SET UPS
//
//
//*****************************************************************************
void update_ui_init_lose() {
    uint16_t x,y;
    uint8_t touch_event;

    print_lose();
    print_end_screen();
    touch_event = ft6x06_read_td_status();
    if(touch_event <= play_again_upper_bound && touch_event >= play_again_lower_bound) {
        // NEEDS TO START PLAY AGAIN
        game_state = PLAY;
    }
    else if(touch_event <= high_scores_upper_bound && touch_event >= high_scores_lower_bound) {
        // NEEDS TO DISPLAY THE HIGH SCORES PAGE
        game_state = HIGH_SCORE;
    }
}


uint8_t led_level(uint8_t level) {
	
	switch(level) {
		case 4: 
			return LED_LEVEL_4; 
			break;
		case 3: 
			return LED_LEVEL_3; 
			break;
		case 2: 
			return LED_LEVEL_2; 
			break;
		case 1: 
			return LED_LEVEL_1; 
			break;
		case 0: 
			return LED_LEVEL_0; 
			break;
		default:
			break;
	}
	
}


