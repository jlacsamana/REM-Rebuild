import pygame
from uiElements.TextObject import TextObject
class baseUIElement:

    def __init__(self, x, y, buttonAssetUri = None, surface = None, textObj : TextObject = None):
        if buttonAssetUri != None:
            self.image = pygame.image.load(buttonAssetUri).convert_alpha()
        elif surface != None:
            self.image = surface
        self.position = (x, y)
        self.collideRect = None
        self.is_dialogue = False
        if textObj != None:
            text_rect = textObj.getCompiled().get_rect()
            offset = textObj.getOffset()
            text_rect.topleft = (self.image.get_rect().topleft[0] + offset[0], self.image.get_rect().topleft[1] + offset[1])
            self.image.blit(textObj.getCompiled(), text_rect)
            # pygame.draw.rect(self.image, textObj.color, text_rect)

    def getSurface(self):
        return self.image
    
    def getPosition(self):
        return self.position