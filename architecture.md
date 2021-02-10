# DBZ Architecture Guideline

This document outlines some software architecture decisions for the project.

## High-level design strategy.

1. Use a GameObject abstract base class to allow all the stuff in the game to be processed in a uniform way. This is the "Entity" in ECS
2. Make Components be pure data elements that entities can optionally contain. The current components in mind are:
    a. Sprite/graphics
    b. physics
    c. AI
    d. Location
3. Make "Engine" classes that process through the game objects, mutating their internal state based on their components. E.g., the PhysicsEngine will take all the GameObjects and update them based on their PhysicsComponents

Fundamentally, "Engines" are processors, "Components" are a way to group related data, and "Objects" are the things in the game.

## Game Loop

The game loop will consist of a flow like this:

1. InputEngine applies mutations to GameObjects based on inputs
2. AiEngine applies mutations on GameObjects with an AI Component
3. PhysicsEngine accumulates physics on each GameObject with a physics component
4. CollisionEngine detects any object collisions
5. LocationEngine updates location of objects based on output of AI/Physics/Collisions
6. GraphicsEngine draws all the objects on the screen
7. Wait until it is time to process the next frame.
