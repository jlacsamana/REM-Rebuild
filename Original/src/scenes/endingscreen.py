import pygame
from rendering.rendering import Renderer
from uiElements.uiEvtManager import UiEventManager
from uiElements.baseUIElement import baseUIElement
from uiElements.TextObject import TextObject
from singletons.singletons import game, GameState, renderer, uiEvtManager
from pathlib import Path
from uiElements.dialogueWithChoices import DialogueWithChoice
from scenes import titlescreen

def PrepareGUIElements(renderer: Renderer, uiEvtManager: UiEventManager):
    ''''''
    screen_size = renderer.get_screen_size()
    original_image = pygame.image.load(Path('assets/final/title.png')).convert()
    background_image =  baseUIElement(0,0, surface= pygame.transform.scale(original_image, screen_size))

    questionText = TextObject("hey, maybe you should take a break too", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
    ansOneText = TextObject("a. okay.", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
    debugChoiceMenu = DialogueWithChoice(300, renderer.get_screen().get_rect().centery+100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText,
                                                 optionOneText=ansOneText, optOneCallback=returnToMenu)
    return [background_image, debugChoiceMenu]

def returnToMenu():
    game.state = GameState.TITLESCREEN
    uiEvtManager.clear()
    renderer.clear()
    renderer.set_elements(titlescreen.PrepareGUIElements(renderer, uiEvtManager))


def Init():
    ''''''

def Exec(events : list[pygame.event.Event]):
    ''''''
    for event in events:
        if event.type == pygame.QUIT:
            game.running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
               game.running = False
