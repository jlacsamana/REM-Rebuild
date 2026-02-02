from enum import Enum
from rendering.rendering import Renderer 
from uiElements.uiEvtManager import UiEventManager

class GameState(Enum):
    TITLESCREEN = 1
    GAME = 2
    ENDINGSCREEN = 3

# game state
class Game():
    state = GameState.TITLESCREEN
    running = True
    sanity = 100
    laptop_interaction = 0
    notebook_interaction = 0
    redbull_interaction = 0
    input_delay = 0
    time_elapsed = 0
    dialogue_lock = False

game = Game()

uiManager = None

renderer = Renderer()

uiEvtManager = UiEventManager()