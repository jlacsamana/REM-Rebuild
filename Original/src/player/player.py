from singletons.singletons import game, GameState, renderer
import pygame
from pathlib import Path
from uiElements.baseUIElement import baseUIElement 
from uiElements.dialogueWithChoices import DialogueWithChoice
from uiElements.TextObject import TextObject
from uiElements.LockingButton import LockingButton


class Player:
    def __init__(self):
        self.sanity = 100
        self.hallucination = [False] * 6

    def lower_sanity(self, delta):
        self.sanity -= delta
        bg_rect = renderer.get_background().get_rect()

        if self.sanity <= 85 and not self.hallucination[1]:
            self.hallucination[1] = True
            book_dropping_sound = pygame.mixer.Sound(Path("assets/sound_effects/bookDropping.wav"))
            book_dropping_sound.play()
        if self.sanity <= 75 and not self.hallucination[2]:
            self.hallucination[2] = True
            blood = baseUIElement(bg_rect.centerx-100, bg_rect.centery+100, surface= pygame.image.load(Path('assets/final/final_san75_overlay.png')).convert_alpha())
            renderer.add_element(blood)
        if self.sanity <= 60 and not self.hallucination[3]:
            self.hallucination[3] = True
            shadow = baseUIElement(bg_rect.centerx-200, bg_rect.top-140, surface= pygame.image.load(Path('assets/final/final_san60_overlay.png')).convert_alpha())
            renderer.add_element(shadow)
        if self.sanity <= 50 and not self.hallucination[4]:
            self.hallucination[4] = True
            bloody_bull = baseUIElement(bg_rect.centerx+554, bg_rect.centery+11, surface= pygame.image.load(Path('assets/final/final_san50_overlay.png')).convert_alpha())
            renderer.add_element(bloody_bull)
        if self.sanity <= 35 and not self.hallucination[5]:
            self.hallucination[5] = True
            laptop_flash = baseUIElement(bg_rect.centerx-750, bg_rect.centery-270, surface= pygame.image.load(Path('assets/final/final_san35_overlay.png')).convert_alpha())
            renderer.add_element(laptop_flash)
            red_aura = baseUIElement(0, 0, surface= pygame.image.load(Path('assets/final/final_large_overlay.png')).convert_alpha())
            renderer.add_element(red_aura)
        if self.sanity <= 0:
            game.state = GameState.ENDINGSCREEN
        print(self.sanity)

    def drink_redbull(self):
        redbull_sound = pygame.mixer.Sound(Path("assets/sound_effects/drinkRedbull.wav"))
        if game.redbull_interaction < 3:
            redbull_sound.play()
        bg_rect = renderer.get_background().get_rect()
        if game.redbull_interaction == 0:
            LockingButton(300, bg_rect.centery + 100, Path("assets/UI/dialog_bubble_regular.png"), TextObject= TextObject("I feel a bit more awake", Path("assets/Tox Typewriter.ttf"), 30, (255, 255, 255), (150, 150)))
        if game.redbull_interaction == 1:
            LockingButton(300, bg_rect.centery + 100, Path("assets/UI/dialog_bubble_regular.png"), TextObject= TextObject("This is helping... just a little. But I'm a bit shaky.", Path("assets/Tox Typewriter.ttf"), 30, (255, 255, 255), (150, 150)))
            self.lower_sanity(5)
        if game.redbull_interaction == 2:
            LockingButton(300, bg_rect.centery + 100, Path("assets/UI/dialog_bubble_regular.png"), TextObject= TextObject("That was my last sip.", Path("assets/Tox Typewriter.ttf"), 30, (255, 255, 255), (150, 150)))
            self.lower_sanity(10)
        game.redbull_interaction += 1
        print(game.redbull_interaction)
    
    def do_homework(self):
        if game.notebook_interaction > 3:
            return
        bg_rect = renderer.get_background().get_rect()
        if game.notebook_interaction == 0:
            LockingButton(300, bg_rect.centery + 100, Path("assets/UI/dialog_bubble_regular.png"), TextObject= TextObject("my brain just won't process anything now. Everything's noise...", Path("assets/Tox Typewriter.ttf"), 30, (255, 255, 255), (150, 150)))
        if game.notebook_interaction == 1:    
            questionText = TextObject("In a network of computers, a message travels along connections without repeating any connection. What is this type of path called?", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
            ansOneText = TextObject("a. Eulerian path", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            ansTwoText = TextObject("b. Hamiltonian cycle", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            ansThreeText = TextObject("c. Spanning tree", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            debugChoiceMenu = DialogueWithChoice(300, bg_rect.centery+100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText, optionOneText=ansOneText, optionTwoText=ansTwoText, optionThreeText=ansThreeText, optOneCallback=None, optTwoCallback=None, optThreeCallback=None)
            renderer.add_element(debugChoiceMenu)
        elif game.notebook_interaction == 2: 
            questionText = TextObject("Fra2lnex quibl7or shayth, dreEvo uNthak plimzor gs15ree… sn2th wivo7k?", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
            ansOneText = TextObject("a. 12", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            ansTwoText = TextObject("b. 19", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            debugChoiceMenu = DialogueWithChoice(300, bg_rect.centery+100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText, optionOneText=ansOneText, optionTwoText=ansTwoText, optOneCallback=self.macm_insanity_callback, optTwoCallback=self.minor_macm_insanity_callback)
            renderer.add_element(debugChoiceMenu)
        elif game.notebook_interaction == 3: 
            questionText = TextObject("Why dont you go to sleep?", Path("assets\Tox Typewriter.ttf"), 30, (255,255,255), (200, 165))
            ansOneText = TextObject("a. I don't know", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            ansTwoText = TextObject("b. I can't I can't I can't I can't", Path("assets\Tox Typewriter.ttf"), 24, (255,255,255))
            debugChoiceMenu = DialogueWithChoice(300, bg_rect.centery+100, buttonAssetUri=Path("assets/UI/dialog_bubble_mc.png"), questionText=questionText, optionOneText=ansOneText, optionTwoText=ansTwoText, optOneCallback=self.macm_insanity_callback, optTwoCallback=self.macm_insanity_callback)
            renderer.add_element(debugChoiceMenu)

        game.notebook_interaction += 1
        print(game.notebook_interaction)        

    def minor_macm_insanity_callback(self):
        self.lower_sanity(5)
        
    def macm_insanity_callback(self):
        self.lower_sanity(15)