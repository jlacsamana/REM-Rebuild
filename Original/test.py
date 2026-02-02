# Example file showing a basic pygame "game loop"
import pygame
import src.rendering.rendering as rendering

# pygame setup
pygame.init()

clock = pygame.time.Clock()
running = True

renderer = rendering.Renderer()
blue_surface = pygame.Surface((50, 50))
blue_surface.fill((0, 0, 255))

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                renderer.toggle_laptop_view()

    keys = pygame.key.get_pressed()
    if keys[pygame.K_ESCAPE]:
        running = False

    # fill the screen with a color to wipe away anything from last frame

    # RENDER YOUR GAME HERE
    renderer.set_camera_offset(*pygame.mouse.get_pos())
    renderer.draw()

    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

pygame.quit()