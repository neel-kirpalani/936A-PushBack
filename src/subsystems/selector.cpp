#include "robot/selector.h"
#include "pros/screen.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_tabview.h"
#include "display/lv_objx/lv_btnm.h"
#include "display/lv_themes/lv_theme.h"
#include <cstring>
 
namespace subsystems {

static const char* DEFAULT_AUTONS[] = {"Front", "Back", "Do Nothing", ""};

Selector::Selector(Auton* auton)
    : auton(auton), selected_auton(AUTON_ROUTINE::NONE), 
      auton_count(0) {
    for (int i = 0; i < MAX_AUTONS + 1; i++) {
        btnm_map[i] = "";
    }
}

void Selector::setup_button_maps(const char** autons) {
    int i = 0;
    do {
        btnm_map[i] = autons[i];
        i++;
    } while(strcmp(autons[i], "") != 0 && i < MAX_AUTONS);
    auton_count = i;
}

void Selector::init() {
    setup_button_maps(DEFAULT_AUTONS);
    
    lv_theme_t* th = lv_theme_alien_init(360, NULL);
    lv_theme_set_current(th);
    
    create_tab_view();
    create_auton_tabs();
    create_skills_tab();
    create_debug_tab();
    
    if (auton->get_selected_auton() == AUTON_ROUTINE::SKILLS) {
        lv_tabview_set_tab_act(tabview, 2, LV_ANIM_NONE);
    } else if (static_cast<int>(auton->get_selected_auton()) < 0) {
        lv_tabview_set_tab_act(tabview, 1, LV_ANIM_NONE);
    }
    
    start_tab_watcher();
}

void Selector::create_tab_view() {
    tabview = lv_tabview_create(lv_scr_act(), NULL);
}

void Selector::create_auton_tabs() {
    lv_obj_t* red_tab = lv_tabview_add_tab(tabview, "Red");
    lv_obj_t* blue_tab = lv_tabview_add_tab(tabview, "Blue");
    
    red_btnm = lv_btnm_create(red_tab, NULL);
    lv_btnm_set_map(red_btnm, const_cast<const char**>(btnm_map));
    lv_btnm_set_action(red_btnm, red_btnm_action);
    lv_btnm_set_toggle(red_btnm, true, static_cast<int>(auton->get_selected_auton()) - 1);
    lv_obj_set_size(red_btnm, BUTTON_WIDTH, BUTTON_HEIGHT);
    lv_obj_set_pos(red_btnm, 0, BUTTON_Y_POS);
    lv_obj_align(red_btnm, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_free_ptr(red_btnm, this);
    
    blue_btnm = lv_btnm_create(blue_tab, NULL);
    lv_btnm_set_map(blue_btnm, const_cast<const char**>(btnm_map));
    lv_btnm_set_action(blue_btnm, blue_btnm_action);
    lv_btnm_set_toggle(blue_btnm, true, abs(static_cast<int>(auton->get_selected_auton())) - 1);
    lv_obj_set_size(blue_btnm, BUTTON_WIDTH, BUTTON_HEIGHT);
    lv_obj_set_pos(blue_btnm, 0, BUTTON_Y_POS);
    lv_obj_align(blue_btnm, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_free_ptr(blue_btnm, this);
}

void Selector::create_skills_tab() {
    lv_obj_t* skills_tab = lv_tabview_add_tab(tabview, "Skills");
    
    skills_btn = lv_btn_create(skills_tab, NULL);
    lv_obj_t* label = lv_label_create(skills_btn, NULL);
    lv_label_set_text(label, "Skills");
    lv_btn_set_action(skills_btn, LV_BTN_ACTION_CLICK, skills_btn_action);
    lv_obj_set_size(skills_btn, BUTTON_WIDTH, BUTTON_HEIGHT);
    lv_obj_set_pos(skills_btn, 0, BUTTON_Y_POS);
    lv_obj_align(skills_btn, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_free_ptr(skills_btn, this);
}

void Selector::create_debug_tab() {
    lv_obj_t* debug_tab = lv_tabview_add_tab(tabview, "Debug");
    
    debug_auton_label = lv_label_create(debug_tab, NULL);
    lv_label_set_text(debug_auton_label, "Selected Auton: None");
    lv_obj_align(debug_auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, DEBUG_LABEL_SPACING);
    
    debug_detection_label = lv_label_create(debug_tab, NULL);
    lv_label_set_text(debug_detection_label, "Detection Status: --");
    lv_obj_align(debug_detection_label, debug_auton_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, DEBUG_LABEL_SPACING);
}

void Selector::update_debug_info() {
    const char* auton_name;
    switch(selected_auton) {
        case AUTON_ROUTINE::RED_LEFT: auton_name = "Red Left (Front)"; break;
        case AUTON_ROUTINE::RED_RIGHT: auton_name = "Red Right (Back)"; break;
        case AUTON_ROUTINE::BLUE_LEFT: auton_name = "Blue Left (Front)"; break;
        case AUTON_ROUTINE::BLUE_RIGHT: auton_name = "Blue Right (Back)"; break;
        case AUTON_ROUTINE::SKILLS: auton_name = "Skills"; break;
        default: auton_name = "None"; break;
    }
    
    char auton_str[50];
    sprintf(auton_str, "Selected Auton: %s", auton_name);
    lv_label_set_text(debug_auton_label, auton_str);
}

lv_res_t Selector::red_btnm_action(lv_obj_t* btnm, const char* txt) {
    Selector* selector = (Selector*)lv_obj_get_free_ptr(btnm);
    for(int i = 0; i < selector->auton_count; i++) {
        if(strcmp(txt, selector->btnm_map[i]) == 0) {
            selector->selected_auton = static_cast<AUTON_ROUTINE>(i + 1);
            selector->auton->set_selected_auton(selector->selected_auton);
            selector->update_debug_info();
            break;
        }
    }
    return LV_RES_OK;
}

lv_res_t Selector::blue_btnm_action(lv_obj_t* btnm, const char* txt) {
    Selector* selector = (Selector*)lv_obj_get_free_ptr(btnm);
    for(int i = 0; i < selector->auton_count; i++) {
        if(strcmp(txt, selector->btnm_map[i]) == 0) {
            selector->selected_auton = static_cast<AUTON_ROUTINE>(-(i + 1));
            selector->auton->set_selected_auton(selector->selected_auton);
            selector->update_debug_info();
            break;
        }
    }
    return LV_RES_OK;
}

lv_res_t Selector::skills_btn_action(lv_obj_t* btn) {
    Selector* selector = (Selector*)lv_obj_get_free_ptr(btn);
    selector->selected_auton = AUTON_ROUTINE::SKILLS;
    selector->auton->set_selected_auton(selector->selected_auton);
    selector->update_debug_info();
    return LV_RES_OK;
}

void Selector::tab_watcher_fn(void* param) {
    Selector* selector = static_cast<Selector*>(param);
    int active_tab = lv_tabview_get_tab_act(selector->tabview);
    
    while(true) {
        int current_tab = lv_tabview_get_tab_act(selector->tabview);
        
        if(current_tab != active_tab) {
            active_tab = current_tab;
            int current_auton = static_cast<int>(selector->selected_auton);
            
            if(active_tab == 0) {  
                if(current_auton == 0) current_auton = 1; 
                current_auton = abs(current_auton);  
                selector->selected_auton = static_cast<AUTON_ROUTINE>(current_auton);
                lv_btnm_set_toggle(selector->red_btnm, true, current_auton - 1);
            }
            else if(active_tab == 1) { 
                if(current_auton == 0) current_auton = 1; 
                current_auton = -abs(current_auton);  
                selector->selected_auton = static_cast<AUTON_ROUTINE>(current_auton);
                lv_btnm_set_toggle(selector->blue_btnm, true, abs(current_auton) - 1);
            }
            else {  
                selector->selected_auton = AUTON_ROUTINE::SKILLS;
            }
            selector->auton->set_selected_auton(selector->selected_auton);
        }
        pros::delay(20);
    }
}

void Selector::start_tab_watcher() {
    pros::Task tab_watcher(tab_watcher_fn, this, "Tab Watcher");
}

void Selector::update() {
    update_debug_info();
}

}
