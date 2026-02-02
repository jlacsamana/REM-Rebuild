import pygame
from uiElements.baseUIElement import baseUIElement
from pathlib import Path

OFFSET_X_SCALE = 10
OFFSET_Y_SCALE = 10

class Renderer:
    def __init__(self):
        self.screen = pygame.display.set_mode((1920, 1080))
        self.elements: list[baseUIElement] = []
        self.bg_image = pygame.transform.scale(pygame.image.load(Path('assets/final/final_bg.png')).convert(),
            (self.screen.get_width()+200, self.screen.get_height()+100))
        self.background = pygame.Surface((self.screen.get_width()+200, self.screen.get_height()+100))

        self.laptop_view_num = 0
        self.laptop_view_paths = ["assets/final/zoomed_laptop_states/interaction_1_0.png",
                                  "assets/final/zoomed_laptop_states/interaction_1_1.png",
                                  "assets/final/zoomed_laptop_states/interaction_1_2.png",
                                  "assets/final/zoomed_laptop_states/interaction_2_0.png",
                                  "assets/final/zoomed_laptop_states/interaction_3_0.png",
                                  "assets/final/zoomed_laptop_states/interaction_3_1.png",
                                  "assets/final/zoomed_laptop_states/interaction_4_0.png",
                                  "assets/final/zoomed_laptop_states/interaction_4_1.png"] 
        self.laptop_view = pygame.transform.scale(pygame.image.load(Path(self.laptop_view_paths[0])).convert_alpha(),
                                                  (self.screen.get_width()+200, self.screen.get_height()+100))
        
        self.notebook_view = pygame.transform.scale(pygame.image.load(Path('assets/final/final_book_zoomin.png')).convert_alpha(),
                                                  (self.screen.get_width()+200, self.screen.get_height()+100))

        self.fade_view = pygame.Surface(self.get_screen_size(), pygame.SRCALPHA)
        self.fade_view.fill("black")

        self.x_offset = 0
        self.y_offset = 0
        self.fade_opacity = 0
        self.delta_fade_opacity = 0

        self.is_laptop_view = False
        self.is_notebook_view = False
        self.triggered_view = ""

    def get_screen_size(self):
        return (self.screen.get_width(), self.screen.get_height())

    def set_camera_offset(self, mouse_x, mouse_y):
        self.x_offset = (self.background.get_width()//2-mouse_x)/OFFSET_X_SCALE - 100
        self.y_offset = (self.background.get_height()//2-mouse_y)/OFFSET_Y_SCALE - 50
        
    def get_is_laptop_view(self):
        return self.is_laptop_view
    
    def get_is_notebook_view(self):
        return self.is_notebook_view

    def add_element(self, element):
        self.elements.append(element)

    def remove_element(self, element):
        self.elements.remove(element)

    def clear(self):
        self.elements.clear()

    def set_elements(self, elements):
        self.elements.clear()
        self.elements = elements

    def get_screen(self):
        return self.background
    
    def get_background(self):
        return self.background

    def draw(self):
        self.screen.fill("black")

        if self.is_notebook_view:
            self.screen.blit(self.notebook_view, (self.x_offset, self.y_offset))
            for element in self.elements:
                pos = element.getPosition()
                if (element.is_dialogue):
                    self.notebook_view.blit(element.getSurface(), (pos[0], pos[1]))
        elif self.is_laptop_view:
            self.screen.blit(self.laptop_view, (self.x_offset, self.y_offset))
        else:
            self.background.blit(self.bg_image, (0, 0))
            for element in self.elements:
                pos = element.getPosition()
                self.background.blit(element.getSurface(), (pos[0], pos[1]))
                if (element.collideRect):
                    element.collideRect[0] = pos[0]+self.x_offset
                    element.collideRect[1] = pos[1]+self.y_offset
            self.screen.blit(self.background, (self.x_offset, self.y_offset))
            
        if self.delta_fade_opacity != 0:
            self.fade()
            return
        
    def toggle_notebook_view(self):
        self.is_notebook_view = not self.is_notebook_view

    def toggle_laptop_view(self):
        self.delta_fade_opacity = 10
        self.triggered_view = "laptop"

    def increment_laptop_view_num(self):
        self.laptop_view_num += 1
        self.laptop_view = pygame.transform.scale(pygame.image.load(Path(self.laptop_view_paths[self.laptop_view_num])).convert_alpha(),
                                                  (self.screen.get_width()+200, self.screen.get_height()+100))

    def fade(self):
        if (self.fade_opacity == 255):
            if self.triggered_view == "laptop":
                self.is_laptop_view = not self.is_laptop_view
            self.delta_fade_opacity = -10
        self.fade_opacity = max(0, min(self.fade_opacity+self.delta_fade_opacity, 255))
        self.fade_view.fill((0, 0, 0, self.fade_opacity))
        self.screen.blit(self.fade_view, (0, 0))
        if (self.fade_opacity == 0):
            self.delta_fade_opacity = 0
