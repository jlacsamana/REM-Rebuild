import pygame
import pathlib
from pathlib import Path
from singletons.singletons import game, renderer, GameState, uiEvtManager
from rendering.rendering import Renderer
from uiElements.uiEvtManager import UiEventManager
from uiElements.button import Button
from uiElements.TextObject import TextObject
from uiElements.dialogueWithChoices import DialogueWithChoice
from player.player import Player
from scenes import endingscreen
from uiElements.TextObject import TextObject
from uiElements.dialogueWithChoices import DialogueWithChoice

laptop = None
book = None
redbull = None
player = None

def laptopClick():
    print("laptop click")
    if game.input_delay > 1:
        if game.laptop_interaction in [0, 3, 4, 5, 6, 8, 9]:
            renderer.toggle_laptop_view()
        else:
           renderer.increment_laptop_view_num()
        if game.laptop_interaction == 10:
            notebook_sound = pygame.mixer.Sound(Path("assets/sound_effects/windowsError.wav"))
            notebook_sound.play()
        if game.laptop_interaction in [4, 6, 9]:
            renderer.increment_laptop_view_num()
        if game.laptop_interaction in [3, 5, 8]:
            player.lower_sanity(15)
        game.laptop_interaction += 1
        game.input_delay = 0

def bookClick():
    print("book click")
    if game.input_delay > 1:
        renderer.toggle_notebook_view()
        notebook_sound = pygame.mixer.Sound(Path("assets/sound_effects/notebookFlipping.wav"))
        notebook_sound.play()
        if (renderer.get_is_notebook_view()):
            player.do_homework()
        game.input_delay = 0

def redbullClick():
    print("redbull click")
    if game.input_delay > 1:
        player.drink_redbull()
        game.input_delay = 0

def PrepareGUIElements(renderer: Renderer, uiEvtManager: UiEventManager):
    ''''''

    global laptop, book, redbull, player
    relpath = pathlib.Path( "assets" ) / "final" 
    bg_rect = renderer.get_background().get_rect()
    laptop = Button(bg_rect.left+210, bg_rect.centery-300, 
                    buttonAssetUri= relpath / "final_laptop.png",
                    buttonHoverAssetUri= relpath / "final_laptop_hover.png", callback=laptopClick)
    book = Button(bg_rect.centerx-200, bg_rect.centery+70, 
                  buttonAssetUri= relpath / "final_book.png",
                  buttonHoverAssetUri= relpath / "final_book_hover.png", callback=bookClick)
    redbull = Button(bg_rect.centerx+500, bg_rect.centery-100, 
                     buttonAssetUri= relpath / "final_redCow.png",
                     buttonHoverAssetUri= relpath / "final_redCow_hover.png", callback=redbullClick)
    
    # questionText = TextObject("question?", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
    # ansOneText = TextObject("a. opt a", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
    # ansTwoText = TextObject("b. opt b", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
    # ansThreeText = TextObject("c. opt c", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
    # debugChoiceMenu = DialogueWithChoice(300, bg_rect.centery+100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText, optionOneText=ansOneText, optionTwoText=ansTwoText, optionThreeText=ansThreeText, optOneCallback=testCallback, optTwoCallback=testCallback2, optThreeCallback=testCallback3)

    uiEvtManager.register(laptop)
    uiEvtManager.register(book)
    uiEvtManager.register(redbull)
    
    player = Player()
    # menu interaction btns

    # return [laptop, book, redbull, debugChoiceMenu]
    return [laptop, book, redbull]

def Init():
    ''''''

def Exec(events : list[pygame.event.Event]):
    ''''''
    for event in events:
        if event.type == pygame.QUIT:
             game.running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE and not renderer.get_is_laptop_view():
                game.running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            if renderer.get_is_laptop_view():
                laptopClick()

            if renderer.get_is_notebook_view():
                bookClick()

        mouse_pos = pygame.mouse.get_pos()
        renderer.set_camera_offset(*mouse_pos)

        if game.time_elapsed >= 300:
            bg_rect = renderer.get_background().get_rect()
            questionText = TextObject("My battery is running low... Should I charge my laptop?", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
            ansOneText = TextObject("a. no", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            ansTwoText = TextObject("b. yes", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            debugChoiceMenu = DialogueWithChoice(300, bg_rect.centery + 100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText,
                                                 optionOneText=ansOneText, optionTwoText=ansTwoText, optOneCallback=go_home, optTwoCallback=None)
            renderer.add_element(debugChoiceMenu)

        if laptop:
            laptop.check_hovered(mouse_pos)
        if book:
            book.check_hovered(mouse_pos)
        if redbull:
            redbull.check_hovered(mouse_pos)

def go_home():
    game.state = GameState.ENDINGSCREEN
    uiEvtManager.clear()
    renderer.set_elements(endingscreen.PrepareGUIElements(renderer, uiEvtManager))

def nothing():
    pass
    

# def testCallback():
#      print("1")

# def testCallback2():
#      print("2")

# def testCallback3():
#      print("3")