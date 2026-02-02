# Example file showing a basic pygame "game loop"
import pygame
from scenes import titlescreen, mainscreen, endingscreen
from singletons.singletons import GameState, renderer, uiEvtManager, game

# pygame setup
running = True
pygame.init()
clock = pygame.time.Clock()
renderer.set_elements(titlescreen.PrepareGUIElements(renderer, uiEvtManager))


while game.running:
    time_delta = clock.tick(60)/1000.0
    game.input_delay += time_delta
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    # for event in pygame.event.get():
    #     if event.type == pygame.QUIT:
    #         running = False

    #     if event.type == pygame.KEYDOWN:
    #         if event.key == pygame.K_ESCAPE:
    #             running = False

    input_data = pygame.event.get()

    if game.state == GameState.TITLESCREEN:
        titlescreen.Exec(input_data)
    elif game.state == GameState.GAME:
        game.time_elapsed += time_delta
        mainscreen.Exec(input_data)
    elif game.state == GameState.ENDINGSCREEN:
        endingscreen.Exec(input_data)

    uiEvtManager.process(input_data)

    renderer.draw()
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

pygame.quit()