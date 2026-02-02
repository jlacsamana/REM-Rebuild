from uiElements.button import Button
import pygame
class UiEventManager:

    def __init__(self):
        self.activeUIElements: list[Button]= []
        self.locking_element = None

    def register(self, button):
        self.activeUIElements.append(button)

    def setLocking(self, btn):
        self.locking_element = btn

    def clearLocking(self):
        self.locking_element = None

    def clear(self):
        self.activeUIElements.clear()
        self.clearLocking()

    def process(self, events: list[pygame.event.Event]):
        for event in events:
            pos = pygame.mouse.get_pos()
            if event.type == pygame.MOUSEBUTTONDOWN:
                from singletons.singletons import game
                if (not game.dialogue_lock):
                    for uielement in self.activeUIElements:
                        if uielement.is_clicked(pos): 
                            uielement.execCallback()
                elif self.locking_element != None and game.dialogue_lock:
                    for lock in self.locking_element:
                        if lock.is_clicked(pos): 
                            lock.execCallback()

            for uielement in self.activeUIElements:          
                uielement.check_hovered(pos)