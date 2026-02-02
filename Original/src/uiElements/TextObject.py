import pygame
from pathlib import Path

class TextObject():
    def __init__(self, displayText: str, fontUri: str, fontSize: int, color: tuple[int,int,int], offset: tuple[int, int] = (0,0)):
        self.font = pygame.font.Font(Path(fontUri), fontSize)
        self.text = displayText
        self.color = color
        self.built = self.font.render(displayText, True, self.color)
        self.offset = offset

    def getOffset(self): 
        return self.offset
    
    def getCompiled(self):
        return self.built