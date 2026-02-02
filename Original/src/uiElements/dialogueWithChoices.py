import pygame
from uiElements.baseUIElement import baseUIElement
from uiElements.TextObject import TextObject
from uiElements.button import Button
from singletons.singletons import uiEvtManager, renderer, game
from pathlib import Path

class DialogueWithChoice(baseUIElement):

    def __init__(self, x, y, buttonAssetUri=None, surface=None, questionText : TextObject = None, optionOneText : TextObject = None, optionTwoText : TextObject = None, optionThreeText : TextObject = None, optOneCallback: any = None, optTwoCallback: any = None, optThreeCallback: any = None):
        super().__init__(x, y, buttonAssetUri, surface, questionText)
        self.btns = []
        self.is_dialogue = True
        if optionOneText != None:
            size = optionOneText.getCompiled().get_size()
            transparent_surface = pygame.Surface((size[0] + 15, size[1] + 15), pygame.SRCALPHA)
            btnOne = Button(0,0, surface= transparent_surface,  TextObject=optionOneText, callback= self.unlockCallback)
            btnRect = btnOne.getSurface().get_rect()
            btnRect.topleft = (self.image.get_rect().topleft[0] + 200, self.image.get_rect().topleft[1] + 215)
            btnOne.collideRect.topleft = (300, 830)
            btnOne.collideRect.width = 850
            self.image.blit(btnOne.getSurface(), btnRect)
            self.btns.append(btnOne)
        if optionTwoText != None:
            size = optionTwoText.getCompiled().get_size()
            transparent_surface = pygame.Surface((size[0] + 15, size[1] + 15), pygame.SRCALPHA)
            btnTwo = Button(0,0, surface= transparent_surface,  TextObject=optionTwoText, callback=self.unlockCallback2)
            btnRect = btnTwo.getSurface().get_rect()
            btnRect.topleft = (self.image.get_rect().topleft[0] + 200, self.image.get_rect().topleft[1] + 255)
            btnTwo.collideRect.topleft = (300, 870)
            btnTwo.collideRect.width = 850
            self.image.blit(btnTwo.getSurface(), btnRect)
            self.btns.append(btnTwo)
        if optionThreeText != None:
            size = optionThreeText.getCompiled().get_size()
            transparent_surface = pygame.Surface((size[0] + 15, size[1] + 15), pygame.SRCALPHA)
            btnThree = Button(0,0, surface= transparent_surface,  TextObject=optionThreeText, callback=self.unlockCallback3)
            btnRect = btnThree.getSurface().get_rect()
            btnRect.topleft = (self.image.get_rect().topleft[0] + 200, self.image.get_rect().topleft[1] + 295)
            btnThree.collideRect.topleft = (300, 910)
            btnThree.collideRect.width = 850
            self.image.blit(btnThree.getSurface(), btnRect)
            self.btns.append(btnThree)
    
        self.callback1 = optOneCallback
        self.callback2 = optTwoCallback
        self.callback3 = optThreeCallback


        uiEvtManager.setLocking(self.btns)
        game.dialogue_lock = True
        
    def unlockCallback(self):
        game.dialogue_lock = False
        uiEvtManager.clearLocking()
        renderer.remove_element(self)
        if self.callback1 != None:
            self.callback1()

    def unlockCallback2(self):
        game.dialogue_lock = False
        uiEvtManager.clearLocking()
        renderer.remove_element(self)
        if self.callback2 != None:
            self.callback2()

    def unlockCallback3(self):
        game.dialogue_lock = False
        uiEvtManager.clearLocking()
        renderer.remove_element(self)
        if self.callback3 != None:
            self.callback3()