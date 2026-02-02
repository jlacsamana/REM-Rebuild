import pygame
from rendering.rendering import Renderer
from uiElements.uiEvtManager import UiEventManager
from uiElements.button import Button
from uiElements.baseUIElement import baseUIElement
from uiElements.TextObject import TextObject
from singletons.singletons import game, GameState, renderer, uiEvtManager
from pathlib import Path
from scenes import mainscreen

start_button = None
quit_button = None

# helper functions
def shutdownGame():
    print("closing game")
    game.state = False
    pygame.quit()
    exit()

def startGame():
    print("starting game")
    game.state = GameState.GAME
    game.input_delay = 0
    uiEvtManager.clear()
    renderer.set_elements(mainscreen.PrepareGUIElements(renderer, uiEvtManager))
    pygame.mixer.music.load(Path("assets/sound_effects/backgroundNoise.wav"))
    pygame.mixer.music.set_volume(20)
    pygame.mixer.music.play()

def PrepareGUIElements(renderer: Renderer, uiEvtManager: UiEventManager):
    ''''''
    global start_button, quit_button
    screen_size = renderer.get_screen_size()
    original_image = pygame.image.load(Path('assets/final/title.png')).convert()
    background_image =  baseUIElement(0,0, surface= pygame.transform.scale(original_image, screen_size))

    original_image = pygame.image.load(Path('assets/UI/default/startGame.png')).convert()
    x_pos = screen_size[0]//2 - original_image.get_width()//2
    y_pos = screen_size[1]//2 - original_image.get_height()//2 + 100
    start_button = Button(x_pos, y_pos, buttonAssetUri= Path("assets/UI/default/startGame.png"), 
                          buttonHoverAssetUri= Path("assets/UI/hover/startGameHover.png"), callback=startGame)
    quit_button = Button(x_pos, y_pos+100, buttonAssetUri= Path("assets/UI/default/quitGame.png"), 
                         buttonHoverAssetUri= Path("assets/UI/hover/quitGameHover.png"), callback=shutdownGame)
    uiEvtManager.register(start_button)
    uiEvtManager.register(quit_button)

    return [background_image, start_button, quit_button]


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

        mouse_pos = pygame.mouse.get_pos()
        if start_button:
            start_button.check_hovered(mouse_pos)
        if quit_button:
            quit_button.check_hovered(mouse_pos)
